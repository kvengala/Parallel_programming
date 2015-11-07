CC=gcc

FLAG= -c 

all: Serial_output Parallel_output_openmp Parallel_2pthread Parallel_4pthread Parallel_8pthread Parallel_16pthread Parallel_32pthread
	

Serial_output: 
	$(CC) Serial.c -o Serial.o -w
Parallel_output_openmp:
	$(CC) parallel_Openmp.c -o OpenMp.o -fopenmp -w
Parallel_2pthread: 
	$(CC) Pthread_2_parallel.c -o Pthread_2.o -pthread -w
Parallel_4pthread: 
	$(CC) Pthread_4_parallel.c -o Pthread_4.o -pthread -w
Parallel_8pthread:
	$(CC) Pthread_8_parallel.c -o Pthread_8.o -pthread -w
Parallel_16pthread:
	$(CC) Pthread_16_parallel.c -o Pthread_16.o -pthread -w
Parallel_32pthread:
	$(CC) Pthread_32_parallel.c -o Pthread_32.o -pthread -w


clean:
	rm -r *.o 
