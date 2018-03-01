#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define true 1
#define false 0
#define N 4

//Program realizat de Mindru Alexandru-Ionut
//Grupa 311CB

typedef struct
{
	unsigned char ip[N];
	unsigned char masca_retea[N];
	unsigned int masca;
}lista_ip;

typedef struct
{
	unsigned char ip_1[N];
	unsigned char ip_2[N];
	unsigned char masca_retea[N];
	unsigned int masca;
	int num_ls;
}ip_work;

void read_ip_work(ip_work *temp)
{
	scanf("%hhu.%hhu.",   &temp->ip_1[0], &temp->ip_1[1]);
	scanf("%hhu.%hhu/%u", &temp->ip_1[2], &temp->ip_1[3], &temp->masca);
	scanf("%hhu.%hhu.",   &temp->ip_2[0], &temp->ip_2[1]);
	scanf("%hhu.%hhu %u", &temp->ip_2[2], &temp->ip_2[3], &temp->num_ls);
}

void read_lista_ip(lista_ip *lista_temp, int num_ls)
{
	int i;
	for(i = 0; i < num_ls; i++)
	{
		scanf("%hhu.%hhu.", &lista_temp[i].ip[0], &lista_temp[i].ip[1]);
		scanf("%hhu.%hhu",  &lista_temp[i].ip[2], &lista_temp[i].ip[3]); 
		scanf("/%u", &lista_temp[i].masca);
	}
}

void creare_masca(unsigned char *temp_ip, unsigned int masca)
{
	unsigned char bitt = 255; // ne folosim de 2^8 - 1
	int i;                    // pentru a crea masca mai usor
	for(i = 0; i < N; i++)
	{
		if(masca > 8)
		{
			temp_ip[i] = bitt;  // toata ideea functiei este
			masca -= 8;			// sa transforme doar ce e necesar
		}						// (32 - masca), adica doar
		else if(masca > 0)      // partile din codul binar al mastii
		{						// care sunt 0
			temp_ip[i] = bitt << (8 - masca);
			masca = 0;
		}
		else
		{
			temp_ip[i] = 0;
		}
	}
}

int check_adresa_retea(unsigned char *temp_ip1, unsigned char *temp_ip2,
						unsigned char *masca)
{
	int i, pass = 0;
	for(i = 0; i < N; i++)
	{
		if((temp_ip1[i] & masca[i]) == (temp_ip2[i] & masca[i]))
		{
			pass++;
		}
	}
	if(pass == 4)
	{
		return true;
	}
	return false;
}

void decimal_to_binary(unsigned char *temp)
{
	int i, j, binary[8];
	for(i = 0; i < N; i++)
	{
		int num = temp[i], pass = 0;
		while(pass < 8)
		{
			if(num)		// functie de la decimal in binar adaptata
			{			// din cauza ca trb sa afisam si 8 de 0 daca e cazul
				binary[pass++] = num % 2;
				num /= 2;
			}
			else
			{
				binary[pass++] = 0;
			}
		}
		for(j = 7; j >= 0;j--)
		{
			printf("%d", binary[j]); // se afiseaza invers
		}							 
		if(i < 3)					
		{							
			printf(".");
		}
	}
	return;
}

void afisare_baza32(unsigned char *ip)
{
	int i;
	int div, rest;		// ^^ vector ce contine toate literele pt baza 32
	for(i = 0; i < N; i++)
	{
		div  = ip[i] / 32;
		rest = ip[i] % 32;
		if(div != 0)
		{
			printf("%d", div);	// se verifica rest-ul daca trb sau nu 
		}						// sa fie modificat astfel incat 
		if(rest < 10)			// sa se afiseze litera resp din baza 32
		{
			printf("%d", rest);
		}
		else
		{
			printf("%c", (rest + 'A' - 10));
		}
		if(i < 3)
		{
			printf(".");
		}
	}
}

void task_0(ip_work temp)
{
	printf("-0 ");
	int i;
	for(i = 0; i < N; i++)
	{
		if(i < 3)
		{
			printf("%hhu.",  temp.ip_1[i]);
		}
		else
		{
			printf("%hhu\n", temp.ip_1[i]);
		}
	}
	return;
}

void task_1(ip_work temp)
{
	printf("-1 ");
	int i;
	for(i = 0; i < N; i++)
	{
		if(i < 3)
		{
			printf("%hhu.",  temp.masca_retea[i]);
		}
		else
		{
			printf("%hhu\n", temp.masca_retea[i]);
		}
	}
	return;
}

void task_2(ip_work temp)
{
	printf("-2 ");
	int i;
	for(i = 0; i < N; i++)
	{
		if(i < 3)
		{
			printf("%hhu.",  temp.masca_retea[i] & temp.ip_1[i]);
		}
		else
		{
			printf("%hhu\n", temp.masca_retea[i] & temp.ip_1[i]);
		}
	}
	return;
}

void task_3(ip_work temp)
{
	printf("-3 ");
	int i;
	for(i = 0; i < N; i++)
	{
		if(i < 3)
		{
			printf("%hhu.",  ~temp.masca_retea[i] | temp.ip_1[i]);
		}
		else
		{
			printf("%hhu\n", ~temp.masca_retea[i] | temp.ip_1[i]);
		}
	}
	return;
}

int task_4(ip_work temp)
{
	if(check_adresa_retea(temp.ip_1, temp.ip_2, temp.masca_retea))
	{
		printf("-4 da\n");
		return true;
	}
	printf("-4 nu\n");
	return false;
}

void task_5(ip_work temp)
{
	printf("-5 ");
	printf("%x.%x.",  temp.ip_1[0], temp.ip_1[1]);
	printf("%x.%x ",  temp.ip_1[2], temp.ip_1[3]);
	printf("%o.%o.",  temp.ip_2[0], temp.ip_2[1]);
	printf("%o.%o\n", temp.ip_2[2], temp.ip_2[3]);
	return;
}

void task_6(ip_work temp, lista_ip *lista_temp, int check)
{
	printf("-6 ");
	if(check)
	{
		printf("0");
	}
	else if(temp.num_ls == 0)
	{
		printf("\n");
		return;
	}
	else
	{
		int i;
		for(i = 0; i < temp.num_ls; i++)
		{
			if(check_adresa_retea(temp.ip_2, lista_temp[i].ip,
								 lista_temp[i].masca_retea))
			{
				printf("%d ", i + 1);
			}
		}
	}
	printf("\n");
	return;
}

void task_7(ip_work temp)
{
	printf("-7 ");
	decimal_to_binary(temp.ip_1);
	printf(" ");
	decimal_to_binary(temp.ip_2);
	printf("\n");
	return;
}

void task_8(ip_work temp)
{
	printf("-8 ");
	afisare_baza32(temp.ip_1);
	printf(" ");
	afisare_baza32(temp.ip_2);
	printf("\n");
	return;
}

int main(void)
{
	int set, i, j;
	scanf("%d", &set);
	for(i = 0; i < set; i++)
	{
		ip_work ip;
		read_ip_work(&ip);
		lista_ip *lista = calloc(ip.num_ls, sizeof(lista_ip));
		read_lista_ip(lista, ip.num_ls);
		creare_masca(ip.masca_retea, ip.masca); //creaza masca pentru ip_1
		for(j = 0; j < ip.num_ls; j++)
		{
			creare_masca(lista[j].masca_retea, lista[j].masca);
		}	// ^^ creeaza masca fiecarui ip din lista
		printf("%d\n", i + 1);
		task_0(ip);
		task_1(ip);
		task_2(ip);
		task_3(ip);
		int check = task_4(ip);
		task_5(ip);
		task_6(ip, lista, check);
		task_7(ip);
		task_8(ip);
		free(lista);
	}
	return 0;
}