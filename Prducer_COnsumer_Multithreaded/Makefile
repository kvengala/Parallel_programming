# This is the make file to execute the file
# 
CC=g++
CFLAGS=-c 
CONDITIONS=-lpthread -std=c++11 -g `pkg-config --cflags gtk+-3.0`  `pkg-config --libs gtk+-3.0`
PACKCMD = $(shell  if   ! dpkg -l libgtk* | grep -e '^i' | grep -e 'libgtk-*3' -c  >o; then sudo apt-get install libgtk-3-dev; else echo "echo Dependencies are installed"; fi )
all: Dependency_Checker Compiling Executing
	
Dependency_Checker: 
	@echo "Checking for dependencies............"
	@echo "Checking if gtk+3 is installed ......"
	$(PACKCMD)


Compiling:
	@echo "Compiling the file............"
	$(CC) Producer_Consumer.cpp -o PC_OUTPUT.o $(CONDITIONS) 
	rm o
	
Executing:
	@echo "Executing the program............"
	./PC_OUTPUT.o
clean:
	@echo "Removing the executables............"
	rm *.o