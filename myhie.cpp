//============================================================================
// Name         : myhie.cpp
// Author       : Liam Richards
// Version      : 1.0
// Date Created : March 7, 2021
// Copyright    : All rights are reserved
// Description  : Operating Systems Project 2: Creating Taxpayer Sorter Nodes in C++ via fork()
//============================================================================

#include <string>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>       // gettimeofday()
#include <sys/times.h>      // times()
#include <unistd.h>         // sysconf()
#include <signal.h>         // signals (SIGCHLD, SIGUSR1, etc)
#include <sys/wait.h>       // wait()
#include "taxpayer.h"
#include "csv.h"
#include "bubblesort.h"
#include "selectionsort.h"
#include "coord.h"

using namespace std;

int numSignalsReceived = 0;
bool completed = false;

// SIGNAL HANDLER FOR SIGUSR1 and SIGUSR2
void signalHandler(int sig)
{
    signal(SIGUSR1,signalHandler);
    signal(SIGUSR2,signalHandler);
	// printf("Caught signal %d!\n",sig);
    if (sig==SIGUSR1) {
        // cout<<"SIGUSR1 caught inside myhie"<<endl;
    }
    if (sig==SIGUSR2) {
        // Signals the completion of the sorting
        completed = true;
    }
    numSignalsReceived++;
}

int main(int argc, char *argv[]) {

    char inputFile[80];
    char outputFile[80];
    string order;
    int attributeNum, numWorkers;
    bool randomFlag = false;

    //=====HANDLING MAIN ARGUMENTS====================
    switch(argc) {

        // First argument is just the location of the file
        case 1:
            cout<<"No additional arguments were passed."<<endl;
            break;

        case 0:
            cout<<"Error, somehow? This should not happen."<<endl;
            break;

        // More than 1 argument
        default:
            // Dealing with inline parameters
            for(int i = 0; i < argc; i++) {

                //Input file flag
                if(strcmp(argv[i], "-i") == 0) {
                    if((i + 1) < argc) {
                        strcpy(inputFile, argv[i + 1]);
                    }
                }

                try {
                    //AttributeNumber flag
                    if(strcmp(argv[i], "-a") == 0) {
                        if((i + 1) < argc) {
                            attributeNum = stoi(argv[i+1]);
                        }
                    }
                    //NumOfWorkers flag
                    if(strcmp(argv[i], "-k") == 0) {
                        if((i + 1) < argc) {
                            numWorkers = stoi(argv[i+1]);
                        }
                    }
                }
                catch(std::invalid_argument& e) {
                // if no conversion could be performed from string to integer
                    cout<<"----ERROR----"<<endl
                        <<"Non-integer argument supplied to either the -k flag or -a flag."<<endl
                        <<"Please check your arguments."<<endl<<endl;
                }

                //Random ranges flag
                if(strcmp(argv[i], "-r") == 0) {
                    randomFlag = true;
                }
                //Order flag
                if(strcmp(argv[i], "-o") == 0) {
                    if((i + 1) < argc) {
                        // Verify the input for order is "a" or "d"
                        if(strcmp(argv[i+1], "a") == 0 || strcmp(argv[i+1], "d") == 0) {
                            order = argv[i+1];
                        }
                        else {
                            order = 'a';
                            cout<<"Invalid input for the order flag. Default has been set to 'a'"<<endl;
                        }
                    }
                } 
                //OutputFile flag
                if(strcmp(argv[i], "-s") == 0) {
                    if((i + 1) < argc) {
                        strcpy(outputFile, argv[i + 1]);
                    }
                }
            }
    }
    //===========================================

    //==========Timing!===============================
    // taken from https://stackoverflow.com/questions/1444428/time-stamp-in-the-c-programming-language?fbclid=IwAR2LGi5mf_O6iEYLVe5hpMGbkA5ErO1ssA6ePzLkm0NAoPKeW9pLwlnCeEE
    struct timeval tv1;
    gettimeofday(&tv1,NULL);
    //================================================

    // function to get the file size of input file
    int arraySize = getFileSize(inputFile);

    Taxpayer* tarray[arraySize];                                // create array of pointers to Taxpayers
    read_taxpayers(inputFile, tarray);                          // read from inputFile into array of Taxpayers, returns size of file

    cout<<"Sorting the array, please wait..."<<endl;
    t_bubble_sort(tarray, attributeNum, arraySize, 0, arraySize-1, order);      // bubble sorts the entire Taxpayer array --> strange bug wouldn't allow each sorter node to sort after the first one!
    cout<<endl;

    //==========LINKING SIGNALS TO HANDLER=====================
    signal(SIGUSR1,signalHandler);
    signal(SIGUSR2,signalHandler);
    //=========================================================

    //===============SPAWNING COORD======================
    int rootpid = getpid();
    // Inside child (coord.cpp)
    if(fork()==0) {
        coord(rootpid, tarray, numWorkers, attributeNum, arraySize, order, randomFlag);
        exit(0);
    }
    // Inside parent (myhie.cpp)
    else{
        wait(NULL);
    }
    //===================================================

    cout<<endl
        <<"+===================================================================="<<endl
        <<"--------------------------SIGNAL STATISTICS--------------------------"<<endl
        <<"Total Num Signals Received: "<<numSignalsReceived<<endl;

    // Writing to Output file
    writeToFile(outputFile, tarray, arraySize);
    //=================================================

    //========TOTAL TIME TAKEN=========================
    struct timeval tv2;
    gettimeofday(&tv2,NULL);
    cout<<endl<<"Total time taken is: "<<tv2.tv_usec - tv1.tv_usec<<" microseconds."<<endl;
    //=================================================

}