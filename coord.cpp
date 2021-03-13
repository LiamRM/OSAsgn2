#include <stdio.h>      // perror()
#include <stdlib.h>     // exit(), EXIT_SUCCESS, EXIT_FAILURE
#include <unistd.h>     // fork()
#include <sys/wait.h>   // wait()
#include <cmath>        // floor()
#include <sys/time.h>   //gettimeofday()
#include <stdlib.h>     // srand, rand()
#include <iostream>
#include <string>
#include "bubblesort.h"
#include "selectionsort.h"
#include "taxpayer.h"
#include "merger.h"

using namespace std;

void coord(int rootpid, Taxpayer* tarray[], int numWorkers, int attributeNum, int arraySize, string order, bool random) {
    //The pid_t data type is a signed integer type which is capable of representing a process ID.
    pid_t pid;
    int range, leftover, randomLeftover = 0;
    
    int rangeArray[numWorkers];                 // stores the range of each worker node
    int startIndexArray[numWorkers];            // stores the start index of worker node
    int endIndexArray[numWorkers];              // stores the end index of worker node 

    if(random) {
        //Determine the range of each sorter node randomly
        cout<<"Working with random ranges!"<<endl;
        if(numWorkers > arraySize) {
            cout<<"Unable to distribute 1 data point to each worker. There are more workers than data points."<<endl;
        }
        else {
            // Distribute a minimum of 1 data point to each worker
            for(int i = 0; i < numWorkers; i++) {
                rangeArray[i] = 1;
            }

            randomLeftover = arraySize - numWorkers;        // indicates leftover data points to distribute randomly
            // cout<<"Num workers: "<<numWorkers<<"\tRandom Leftover: "<<randomLeftover<<endl;      // uncomment this to see how the random function works!

            while(randomLeftover != 0) {
                // This code is needed to generate NEW random numbers every time the program is run. 
                // Borrowed from: https://stackoverflow.com/questions/8449234/c-random-number-between-2-numbers-reset
                static bool init = false;
                if (!init) {
                    srand(time(NULL));
                    init = true;
                }

                int randomNum = rand() % randomLeftover + 1;   // generates a random number between 1 and randomLeftover
                int randomIndex = rand() % (numWorkers-1) + 0; // generates a random integer between 0 and largest index of rangeArray

                // add random range to the rangeArray at randomIndex
                rangeArray[randomIndex] = randomNum + rangeArray[randomIndex];

                // cout<<"Random Number: "<<randomNum<<"\tRandom Index: "<<randomIndex<<endl;         // uncomment this to see how the random function works!

                randomLeftover = randomLeftover - randomNum;   // slowly decrement randomLeftover
            }
        }   
    }
    else {
        // Range is equally distributed 
        range = floor(arraySize / numWorkers);
        leftover = arraySize % numWorkers; 

        //============DETERMINE RANGE==================
        // add 1 to the range to evenly distribute the leftover data points
        for(int i = 0; i < numWorkers; i++) {
            if(leftover != 0) {
                rangeArray[i] = range + 1;      // range of worker node [i] = range + 1
                leftover--;                     // subtract 1 from leftover data points until none are left
            }
            // no more leftover data points to distribute, range is now normal
            else {
                rangeArray[i] = range;
            }
        }
        //===============================================

    }
    //===========DETERMINE START/END INDICES=========
    for(int i = 0; i < numWorkers; i++) {
        if(i == 0) {
            startIndexArray[i] = 0;         // the starting index of the first worker is always 0
        }
        else {
            int runningTotal = 0;
            // Add ranges of all previous sorter nodes to get the starting index (ex: node[3] start index is 84 + 84 for 12 workers and 1000 data points)
            for(int j = 0; j < i; j++) {
                runningTotal = rangeArray[j] + runningTotal;
            }
            startIndexArray[i] = runningTotal;
        }
        endIndexArray[i] = startIndexArray[i] + rangeArray[i] - 1;      // end index is (the start index + range - 1)
    }

    cout<<"+===================================================================="<<endl
        <<"----------------------------TIME STATISTICS--------------------------"<<endl
        <<"****Odd indices use Bubble Sort, and even indices use Selection Sort"<<endl
        <<"**** SI indicates Start Index, EI indicates End Index"<<endl;

    //=============CREATING SORTER NODES======================
    for (int i = 0; i < numWorkers; i++) {
        // Get initial time stamp
        struct timeval tv1;
        gettimeofday(&tv1,NULL);

        pid = fork();

        // Inside the sorter node
        if(pid == 0) {

            // Even sorter nodes --> SELECTION SORT
            if(i % 2 == 0) {
                // This code causes a strange error that allows the first subarray to be sorted, but none afterwards.
                //t_selection_sort(tarray, attributeNum, rangeArray[i], startIndexArray[i], endIndexArray[i], order);
            }
            // Odd sorter nodes  --> BUBBLE SORT
            else {
                // This code causes a strange error that allows the first subarray to be sorted, but none afterwards.
                //t_bubble_sort(tarray, attributeNum, rangeArray[i], startIndexArray[i], endIndexArray[i], order);
            }
            
            // send SIGUSR1 signal to root
            kill(rootpid, SIGUSR1);

            // prints time stats for each worker
            struct timeval tv2;
            gettimeofday(&tv2,NULL);
            cout<<"Sorter <"<<i+1<<">\tTime taken: "<<tv2.tv_usec - tv1.tv_usec<<" microseconds."
                <<"\tRange: "<<rangeArray[i]
                <<"\tSI: ["<<startIndexArray[i]         // indicates start index
                <<"] \tEI: ["<<endIndexArray[i]<<"]"    // indicates end index
                <<endl;

            exit(0);
        }

        // Inside Parent
        if(pid > 0) {
            wait(NULL);             // parent must wait for the child before continuing the loop
            
        }   
    }
    //====================================================


    //==========SPAWN A MERGER NODE===================//
    // Inside child (merger.cpp)
    if(fork()==0) {
        merger(rootpid);
        exit(0);
    }
    // Inside parent (myhie.cpp)
    else{
        wait(NULL);
    }

    
}
