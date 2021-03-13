
myhie: myhie.o csv.o taxpayer.o bubblesort.o selectionsort.o coord.o merger.o
	g++ myhie.o csv.o taxpayer.o bubblesort.o selectionsort.o coord.o merger.o -o myhie

myhie.o: myhie.cpp		#maybe csvread.h and taxpayer.h
	g++ -c myhie.cpp

coord.o: coord.cpp
	g++ -c coord.cpp

csv.o: csv.cpp
	g++ -c csv.cpp

merger.o: merger.cpp
	g++ -c merger.cpp

taxpayer.o: taxpayer.cpp
	g++ -c taxpayer.cpp

bubblesort.o: bubblesort.cpp
	g++ -c bubblesort.cpp

selectionsort.o: selectionsort.cpp
	g++ -c selectionsort.cpp

clean: 
	rm *.o myhie

# target: dependencies			#STRUCTURE OF A MAKEFILE
# 	action