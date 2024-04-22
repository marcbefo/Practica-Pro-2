OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra  -Wno-sign-compare -std=c++11

program.exe: program.o cluster.o pending_proces_area.o proces.o procesor.o BinTree.o
	g++ -o program.exe program.o cluster.o pending_proces_area.o proces.o procesor.o

cluster.o:  cluster.cc cluster.hh 
	g++ -c cluster.cc $(OPCIONS)

BinTree.o: BinTree.hh
	g++ -c BinTree.hh $(OPCIONS)

pending_proces_area.o:  pending_proces_area.cc pending_proces_area.hh 
	g++ -c pending_proces_area.cc $(OPCIONS)

proces.o:  proces.cc proces.hh 
	g++ -c proces.cc $(OPCIONS)

procesor.o:  procesor.cc procesor.hh 
	g++ -c procesor.cc $(OPCIONS)

program.o:  program.cc
	g++ -c program.cc $(OPCIONS)

tar: program.cc cluster.cc pending_proces_area.cc proces.cc procesor.cc BinTree.hh cluster.hh pending_proces_area.hh proces.hh procesor.hh Makefile
	tar -cvf practica.tar program.cc cluster.cc pending_proces_area.cc proces.cc procesor.cc BinTree.hh cluster.hh pending_proces_area.hh proces.hh procesor.hh Makefile

clean:
	rm -f *.o
	rm -f *.exe
