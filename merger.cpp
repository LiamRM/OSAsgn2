#include <stdio.h>  // perror()
#include <stdlib.h> // exit(), EXIT_SUCCESS, EXIT_FAILURE
#include <unistd.h> // fork()
#include <sys/wait.h> // wait()
#include <iostream>
#include "bubblesort.h"
#include "taxpayer.h"

using namespace std;

void merger(int rootpid) {

    // receives partial sorted results from workers through pipes

    // sends a SIGUSR2 to root to signal the completion of sorting
    cout<<"Merger is sending SIGUSR2 to root with pid <"<<rootpid<<">"<<endl;
    kill(rootpid, SIGUSR2);
}   