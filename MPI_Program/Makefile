CC=mpicc

FLAG=-c
QSTUB=qsub
NODECNT=2
all: MPI_function
        
MPI_function:
        @echo "compiling the source file "
        $(CC) $(FLAG)  get_data.c 
        @echo "Creating output file"
        $(CC) -o get_data get_data.o
        @echo " running Qsub"
        $(QSTUB) -pe mpich $(NODECNT) run_get_data.bash
        @echo " qstat"
        qstat -u kvengala

