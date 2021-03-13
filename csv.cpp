#include <string.h>     // for strerror, which produces error strings
#include <errno.h>      // for strerror, which produces error strings
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "taxpayer.h"
#include "csv.h"

#define NUM_TAXPAYER_PARAMS 7

using namespace std;

int getFileSize(string filename) {
    // File pointer 
    fstream fin; 
  
    // Open an existing file 
    fin.open(filename, ios::in); 

    //In case the opening of the file fails
    if(fin.fail()) {
        cout<<"The file failed to open. Reason: "<< strerror(errno)<<endl;
    }
    else {
        string line, word; 
        int j = 0;                      // j is the size of the file
        
        while (!fin.eof()) {            // While the file has NOT reached the end --> Traversing the file
            getline(fin, line);         // read an entire row and store it in a string variable 'line' 
            stringstream s(line);       // used for breaking words 
            j++;
        }
        // cout<<"File size obtained successfully!"<<endl;         // for testing purposes
        fin.close();
        return j;
    }
    fin.close();
    return 0;
}

// Reads taxpayers from a specified file
void read_taxpayers(string filename, Taxpayer* tarray[]) 
{ 
    // File pointer 
    fstream fin; 
  
    // Open an existing file 
    fin.open(filename, ios::in); 

    //In case the opening of the file fails
    if(fin.fail()) {
        cout<<"The file failed to open. Reason: "<< strerror(errno)<<endl;
    }
    else {
        // Read the Data from the file as String Vector 
        string line, word; 
        string wordArray [NUM_TAXPAYER_PARAMS];

        int j = 0;                      // j is index of tarray

        while (!fin.eof()) {            // While the file has NOT reached the end --> Traversing the file

            getline(fin, line);         // read an entire row and store it in a string variable 'line' 
            stringstream s(line);       // used for breaking words 

            int i = 0;                  // i is index of wordArray
            // read every column data of a row and store it in a string variable, 'word', delimited by a space
            while (getline(s, word, ' ')) { 

                if(word.compare("") != 0) {     // if the 'word' is NOT a space
                    wordArray[i] = word;        // add all the column data of a row to an array
                    i++;
                }
            } 
            
            // DO NOT CREATE A TEMP TAXPAYER THEN PASS &TEMP --> USE 'NEW' KEYWORD (I don't know why but it works)
            Taxpayer* temp = new Taxpayer(stoi(wordArray[0]), wordArray[1], wordArray[2], stoi(wordArray[3]), stod(wordArray[4]), stoi(wordArray[5]));
            tarray[j] = temp;
            j++;
        }
        // cout<<"File read successfully!"<<endl;   // for testing purposes
    }
}

// Writing to a new CSV file with name "filename"
void writeToFile(string filename, Taxpayer* tarray[], int size) {
    // file pointer 
	fstream fout; 

	// opens an existing csv file or creates a new file. 
	fout.open(filename, ios::out); 

    //In case the opening of the file fails
    if(fout.fail()) {
        cout<<"The file failed to open. Reason: "<< strerror(errno)<<endl;
    }
    else {
        cout<<endl<<"Writing to output file..."<<endl;
        // Looping through the contents of the entire tArray
        for(int i = 0; i < size; i++) {
            
            // Insert the data to file 
            fout << tarray[i]->RID << ", "
                << tarray[i]->fname << ", "
                << tarray[i]->lname << ", "
                << tarray[i]->numDep << ", "
                << tarray[i]->income << ", "
                << tarray[i]->zipcode
                << "\n"; 
        }
        cout<<"Successfully wrote to output file."<<endl;
    }
    fout.close();
}