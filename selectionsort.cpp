#include <iostream>
#include <string>
#include "taxpayer.h"
#include "selectionsort.h"

using namespace std;

// has O(n^2) time complexity
void t_selection_sort(Taxpayer* tarray[], int attributeNum, int n, int startIndex, int endIndex, string order) {
    
    //n is the range provided to for sorter nodes to sort through

    switch ((attributeNum)) {

        // 0 indicates sort by Resident-ID (RID)
        case 0:
            // Ascending Order (lowest to highest)
            if(order == "a") {
                for(int i = 0; i < n - 1; i++) {
                    for(int j = i+1; j < n; j++) {
                        if(tarray[j]->RID < tarray[i]->RID) {
                            Taxpayer* temp = tarray[j];
                            tarray[j] = tarray[i];
                            tarray[i] = temp;
                        }
                    }
                }
                cout<<"Successfully selected sorted subarray by RID (in ascending order)!"<<endl;
            }
            // Descending Order (highest to lowest)
            else if(order == "d") {
                for(int i = 0; i < n-1; i++) {
                    for(int j = i+1; j < n; j++) {
                        if(tarray[j]->RID > tarray[i]->RID) {
                            Taxpayer* temp = tarray[j];
                            tarray[j] = tarray[i];
                            tarray[i] = temp;
                        }
                    }
                }
                cout<<"Successfully selected sorted by RID (in descending order)!"<<endl;
            }
            else {
                cout<<"Neither ascending nor descending was chosen. Not sorted."<<endl;
            }
            break;
        
        // 3 indicates sort by # of Dependents
        case 3: 
            // Ascending Order (lowest to highest)
            if(order == "a") {
                for(int i = 0; i < n - 1; i++) {
                    for(int j = i+1; j < n; j++) {
                        if(tarray[j]->numDep < tarray[i]->numDep) {
                            Taxpayer* temp = tarray[j];
                            tarray[j] = tarray[i];
                            tarray[i] = temp;
                        }
                    }
                }
                cout<<"Successfully selected sorted by # of Dependents (in ascending order)!"<<endl;
            }
            // Descending Order (highest to lowest)
            else if(order == "d") {
                for(int i = 0; i < n-1; i++) {
                    for(int j = i+1; j < n; j++) {
                        if(tarray[j]->numDep > tarray[i]->numDep) {
                            Taxpayer* temp = tarray[j];
                            tarray[j] = tarray[i];
                            tarray[i] = temp;
                        }
                    }
                }
                cout<<"Successfully selected sorted by # of Dependents (in descending order)!"<<endl;
            }
            else {
                cout<<"Neither ascending nor descending was chosen. Not sorted."<<endl;
            }
            break;

        // 4 indicates sort by income
        case 4:
            // Ascending Order (lowest to highest)
            if(order == "a") {
                for(int i = 0; i < n - 1; i++) {
                    for(int j = i+1; j < n; j++) {
                        if(tarray[j]->income < tarray[i]->income) {
                            Taxpayer* temp = tarray[j];
                            tarray[j] = tarray[i];
                            tarray[i] = temp;
                        }
                    }
                }
                cout<<"Successfully selected sorted by income (in ascending order)!"<<endl;
            }
            // Descending Order (highest to lowest)
            else if(order == "d") {
                for(int i = 0; i < n-1; i++) {
                    for(int j = i+1; j < n; j++) {
                        if(tarray[j]->income > tarray[i]->income) {
                            Taxpayer* temp = tarray[j];
                            tarray[j] = tarray[i];
                            tarray[i] = temp;
                        }
                    }
                }
                cout<<"Successfully selected sorted by income (in descending order)!"<<endl;
            }
            else {
                cout<<"Neither ascending nor descending was chosen. Not sorted."<<endl;
            }
            break;

        // 5 indicates sort by postal-code
        case 5:
            // Ascending Order (lowest to highest)
            if(order == "a") {
                for(int i = 0; i < n - 1; i++) {
                    for(int j = i+1; j < n; j++) {
                        if(tarray[j]->zipcode < tarray[i]->zipcode) {
                            Taxpayer* temp = tarray[j];
                            tarray[j] = tarray[i];
                            tarray[i] = temp;
                        }
                    }
                }
                cout<<"Successfully selected sorted by zipcode (in ascending order)!"<<endl;
            }
            // Descending Order (highest to lowest)
            else if(order == "d") {
                for(int i = 0; i < n-1; i++) {
                    for(int j = i+1; j < n; j++) {
                        if(tarray[j]->zipcode > tarray[i]->zipcode) {
                            Taxpayer* temp = tarray[j];
                            tarray[j] = tarray[i];
                            tarray[i] = temp;
                        }
                    }
                }
                cout<<"Successfully selected sorted by zipcode (in descending order)!"<<endl;
            }
            else {
                cout<<"Neither ascending nor descending was chosen. Not sorted."<<endl;
            }
            break;

        default:
            cout<<"The attribute number was not 0, 3, 4, or 5. Please enter a correct attribute number."<<endl;
    }

    // pass sorted subarray to named pipe to be merged by merger node here

}