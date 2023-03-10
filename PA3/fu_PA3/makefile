# CC and CFLAGS are varilables
CC = g++ -std=c++11
CFLAGS = -c
AR = ar
ARFLAGS = rcv
# -c option ask g++ to compile the source files, but do not link.
# -g option is for debugging version
# -O2 option is for optimized version
DBGFLAGS = -g -D_DEBUG_ON_
OPTFLAGS = -O3

all : bin/cb
	@echo -n ""

# optimized version
bin/cb : acyclic_opt.o mst_opt.o main_opt.o
	$(CC) $(OPTFLAGS) acyclic_opt.o mst_opt.o main_opt.o -o bin/cb
main_opt.o: src/main.cpp
	$(CC) $(CFLAGS) $< -Ilib -o $@
acyclic_opt.o : src/acyclic.cpp src/acyclic.h
	$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@
mst_opt.o : src/mst.cpp src/mst.h
	$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@

# clean all the .o and executable files
clean:
		rm -rf *.o lib/*.a lib/*.o bin/* outputs/*