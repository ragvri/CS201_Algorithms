#!/bin/bash

QSORT_MEDIAN="assg04b_1.c"
QSORT_RANDOM="assg04b_2.c"
RAND_GEN_FILE="randInput.c"
TESTCASE_SIZE="10000 20000 50000 75000 100000"
NUMBER_OF_INSTANCE="50"
QSORT_EXE_MEDIAN="assg04b_1"
QSORT_EXE_RANDOM="assg04b_2"
RAND_GEN_EXE="randInput"
CC="cc"
inputfile="input.txt"
outFilemedian="outTimemedian.txt"
outFilerandom="outTimerandom.txt"
datafile="datafile.txt"
gnuplotdatafile="gnuplotdatafile.txt"
gnuscriptfile="gnuscriptfile.scr"
percent="1"

rm -f $datafile


$CC $QSORT_MEDIAN -g -o $QSORT_EXE_MEDIAN -lm
$CC $QSORT_RANDOM -g -o $QSORT_EXE_RANDOM -lm
$CC $RAND_GEN_FILE -g -o $RAND_GEN_EXE -lm

for size in $TESTCASE_SIZE
do
	iteration="0";
	printf  "%d"  $size >> $datafile
	while test $iteration -ne $NUMBER_OF_INSTANCE
	do
		./$RAND_GEN_EXE $size > $inputfile 
		
		/usr/bin/time --format="EXECUTION_TIME: %U"  -o $outFilemedian  ./$QSORT_EXE_MEDIAN < $inputfile
		exeTimem=`awk '/^EXECUTION_TIME/ {print $2}' $outFilemedian`
		printf ":%f " $exeTimem >> $datafile
		
		echo Script Running... $percent		
		percent=`expr $percent + 1`

		/usr/bin/time --format="EXECUTION_TIME: %U"  -o $outFilerandom  ./$QSORT_EXE_RANDOM < $inputfile
		exeTimer=`awk '/^EXECUTION_TIME/ {print $2}' $outFilerandom`
		printf ":%f " $exeTimer >> $datafile

		iteration=`expr $iteration + 1`
	done
	printf "\n" >> $datafile
done

awk -F":" '{  sum_M = 0; sum_R = 0; count = 50;
		for(i=2;i<=NF;i++){
			if(i%2 == 0){
				sum_M = sum_M + $i;
			}else{
				sum_R = sum_R + $i;
			}
		}
		avTime_M = sum_M/count;
		avTime_R = sum_R/count;
		printf("%d  %f  %f\n",$1,avTime_M,avTime_R);
}' $datafile > $gnuplotdatafile 

echo "set terminal postscript color" > $gnuscriptfile
echo "set output \"assg04b_3.ps\"" >> $gnuscriptfile
echo "set xlabel \"Size\"" >> $gnuscriptfile
echo "set ylabel \"Execution time\"" >> $gnuscriptfile
echo "plot \"$gnuplotdatafile\" using 1:2 title \"median\" with lines, \"$gnuplotdatafile\" using 1:3 title \"random\" with  lines"  >> $gnuscriptfile
echo "quit" >> $gnuscriptfile

gnuplot $gnuscriptfile

echo Script Ended

DISPLAY=:0 gv assg04b_3.ps

