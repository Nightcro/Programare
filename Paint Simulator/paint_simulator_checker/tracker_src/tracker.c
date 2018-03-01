/**
 * @author claudiugh, andreiparvu, raduiacob
 * @file tracker.c
 *
 * launches `paint_simulator` silently on current directory after
 * and sets limit on CPU execution time
 * 
 * Arguments:
 * argv[1]: timeout - float value in seconds 
 * 
 * Any executing errors are shown in the file error.exec
 * The output of the execution is shown in the file output.time
 * In case of the limit exceedance an apropiate message is shown in error.time
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/wait.h>

#define UERR 1000 /* error admitted for comparing time values, in microseconds */

#define UFACT 1000000 /* micro-factor: 10^6 */

int setup_job(int timeout) {
    struct rlimit limit;

    /* set the processor time limit */
    limit.rlim_cur = timeout;
    limit.rlim_max = 2 * timeout;
    setrlimit(RLIMIT_CPU, &limit);

    return 0;
}

int main(int argc, char *argv[], char *const envp[]) {
    pid_t child_pid;
    int status, signal;

    if (argc != 2) {
        fprintf(stderr, "Usage: ./tracker <timeout_seconds>\n");
        exit(EXIT_FAILURE);
    }

    float ftimeout;
    int timeout;
    sscanf(argv[1], "%f", &ftimeout);
    timeout = (int)ceil(ftimeout);

    child_pid = fork();
    if (-1 == child_pid) {
        fprintf(stderr, "Error in fork(): %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    } else if (0 == child_pid) {
        if (setup_job(timeout)) {
            exit(EXIT_FAILURE);
        }

        execl("./paint_simulator", "paint_simulator", NULL);

        /* should not be here */
        fprintf(stderr, "Error in exec(): %s\n", strerror(errno)); 
        exit(EXIT_FAILURE);
    } else {
        struct rusage accounting;
        wait4(child_pid, &status, 0, &accounting);
        /* print some stats */
        int seconds = (int)accounting.ru_utime.tv_sec + (int)accounting.ru_stime.tv_sec;
        int useconds = (int)accounting.ru_utime.tv_usec + (int)accounting.ru_stime.tv_usec;
        float totalseconds = seconds + (float) useconds / UFACT - (float) UERR / UFACT;
        int fd1 = open("output.time", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        dup2(fd1, 1);
        int fd2 = open("error.time", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        dup2(fd2, 2);

        if (totalseconds >= ftimeout) {
          fprintf(stderr, "CPU time limit exceeded\n");
          return 1;
        }
        /* success */
        float ftime = (float)seconds + (float)useconds / UFACT;
        fprintf(stdout, "%f", ftime);
        
        if (WIFSIGNALED(status)) {

           signal = WTERMSIG(status);           
           if (signal == 11) {
            fprintf(stderr, "Programul s-a oprit cu segmentation fault. ");
            fprintf(stderr, "Urmeaza pasii de debugging de la pagina:\n");
            fprintf(stderr, "http://ocw.cs.pub.ro/courses/programare/debugging\n");            
           }
           else if (signal == 6){
            fprintf(stderr, "Programul a fost oprit cu SIGABRT.\n");
            fprintf(stderr, "Acest lucru poate indica o problema de tipul ");
            fprintf(stderr, "double-free sau o corupere a heap-ului.\n");
            fprintf(stderr, "Verifica apelurile pentru functiile de alocare ");
            fprintf(stderr, "de memorie: malloc(), calloc(), etc.\n");
            fprintf(stderr, "Urmeaza pasii de debugging de la pagina:\n");
            fprintf(stderr, "http://ocw.cs.pub.ro/courses/programare/debugging\n");            
           }     
           else if (signal == 24) {
            fprintf(stderr, "Programul a fost oprit dupa un timp relativ mare de rulare.\n");
            fprintf(stderr, "Este posibil sa fi intrat intr-o bucla infinita.\n");                   
           }       
           else {
            fprintf(stderr, "killed by signal %d\n", WTERMSIG(status));
           }      
           return 1;
           
        } else if (WIFSTOPPED(status)) {
           fprintf(stderr, "stopped by signal %d\n", WSTOPSIG(status));
           return 1;
        }
        
        fprintf(stderr, "Exit status %d\n", WEXITSTATUS(status));
        return WEXITSTATUS(status);
    }

    return 0;
}