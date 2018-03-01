#!/bin/bash

PAINT_EXEC=paint_simulator

function init {
    # Build raw_to_ppm exec.
    make -f Makefile.checker
    make

    if [ ! -f 'README' ] && [ ! -f 'Readme' ]; then
        echo "README file not found!"        
    fi

    # Setup tests which will be run
    tests_nr=20
    points_per_test=$((100/tests_nr))
    if [ $# == 0 ]; then
        s_test=1
        f_test=$tests_nr
    elif [ "$1" == "all" ]; then
        s_test=1
        f_test=$tests_nr
    elif [ $1 -ge 1 ] && [ $1 -le $tests_nr ]; then
        s_test=$1
        f_test=$1
    else
        echo "Test $1 doesn't exist!"
        exit 1
    fi

    # Prepare output dirs.
    mkdir -p output
    mkdir -p output_ppm
    total=0
}

function make_input_file {

    if [ $1 -gt 11 ] && [ $1 -ne 20 ]; then
        pic=$(($1-11))
    else
        pic=$1
    fi

    operations_file=./input/test${1}.in
    ppm_file=./input_ppm/test${pic}.ppm
    input_file=./test.in

    rm -f ./test.in

    if [ $1 -ne 11 ] && [ $1 -ne 20 ]; then
        echo -n "1 " >$input_file
        tail -n+2 $ppm_file | head -n 1 >>$input_file
        tail -n+4 $ppm_file >>$input_file
    fi

    cat $operations_file >>$input_file
}

function run_test {
    output_file=./output/test${1}.out
    output_ppm_file=./output_ppm/test${1}.ppm
    ref_file=./ref/test${1}.ref

    # Prepare input file.
    make_input_file "$1"
    memory_leaks=false
        
    # Run program.
    if [ $1 -eq 20 ]; then
        valgrind --log-file="leak-check" --leak-check=full --trace-children=yes ./tracker 15 <$input_file &>$output_file        
        rc=$?
        
        if grep -q 'LEAK SUMMARY' leak-check; then
            memory_leaks=true
            echo -e "Memory leaks detected!"
        fi
    else
        ./tracker 15 <$input_file &>$output_file
        rc=$?
    fi
    
    if [ $rc -ne 0 ] && [ $1 -lt 12 ]; then
        echo "Program ended abnormally"
        cat error.time
        echo -e "TEST $1 FAILED ... 0 points"
        return 0
    else
        # Dump the pixel matrices to PPM files.
        # May fail if the output file is ill-formatted
        ./raw_to_ppm "$1" ./output_ppm <$output_file
    fi

    # Compare it.
    diff $output_file $ref_file &>/dev/null              
    cmp=$?
    
    if [ $cmp -ne 0 ] || $memory_leaks; then
        cat error.time
        echo -e "TEST $1 FAILED ... 0 points"
    else
        points=$points_per_test
        
        if [ $1 -eq 18 ]; then
            points=3
        elif [ $1 -eq 7 ] || [ $1 -eq 12 ]; then
            points=6
        fi

        echo -e "TEST $1 PASSED ... " $points "points"
        total=$((total + points))
    fi

    rm $input_file &>/dev/null
}

function clean {
    rm -rf output
    rm -rf output_ppm
    rm leak-check &>/dev/null
    make -f Makefile.checker clean
}

function print_result {
    echo -e "\nTotal: $total/100 points"
    if [ $total -eq 100 ]; then
        echo "Congrats!"
    fi
    echo
}

function run_basic_tests {

    # Iterate through each test.
    for ((i=$s_test; i<=$f_test; i++)); do
        # Run this test.
        run_test "$i"
        if [ $? -ne 0 ]; then
            break
        fi
    done

}

# Initialize variables.
init "$@"

run_basic_tests "$@"
print_result
clean
