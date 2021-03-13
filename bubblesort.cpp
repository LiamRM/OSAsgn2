#include <iostream>
#include <string>
#include "taxpayer.h"
#include "bubblesort.h"


using namespace std;

void t_bubble_sort(Taxpayer* tarray[], int attributeNum, int n, int startIndex, int endIndex, string order) {
	//n is the range provided to for sorter nodes to sort through

	switch(attributeNum) {

		// 0 indicates sort by Resident-ID (RID)
		case 0:

			if(order == "a") {
				// Ascending (lowest to highest)
				for(int i = 0; i < n-1; i++) {
					for(int j = 0; j < n-i-1; j++){		//subtracting i since the 'last i elements' are already sorted --> # of j comparisons gets smaller each loop of i
						if(tarray[j]->RID > tarray[j+1]->RID) {		//comparing adjacent
							Taxpayer* temp = tarray[j];
							tarray[j] = tarray[j+1];
							tarray[j+1] = temp;
						}
					}
				}
				cout<<"Successfully bubble sorted by RID (in ascending order)!"<<endl;
			}

			else if (order == "d") {

				// Descending (highest to lowest)
				for(int i = 0; i < n-1; i++) {
					for(int j = 0; j < n-i-1; j++){					//subtracting i since the 'last i elements' are already sorted --> # of j comparisons gets smaller each loop of i
						if(tarray[j]->RID < tarray[j+1]->RID) {		//comparing adjacent
							Taxpayer* temp = tarray[j];
							tarray[j] = tarray[j+1];
							tarray[j+1] = temp;
						}
					}
				}
				cout<<"Successfully bubble sorted by RID (in descending order)!"<<endl;
			}
			else {
				cout<<"Neither ascending nor descending was chosen. Not sorted."<<endl;
			}
			break;

		// 3 indicates sort by number of dependents
		case 3:

			if(order == "a") {
				// Ascending (lowest to highest)
				for(int i = 0; i < n-1; i++) {
					for(int j = 0; j < n-i-1; j++){		//subtracting i since the 'last i elements' are already sorted --> # of j comparisons gets smaller each loop of i
						if(tarray[j]->numDep > tarray[j+1]->numDep) {		//comparing adjacent
							Taxpayer* temp = tarray[j];
							tarray[j] = tarray[j+1];
							tarray[j+1] = temp;
						}
					}
				}
				cout<<"Successfully bubble sorted by # of Dependents (in ascending order)!"<<endl;
			}

			else if (order == "d") {

				// Descending (highest to lowest)
				for(int i = 0; i < n-1; i++) {
					for(int j = 0; j < n-i-1; j++){					//subtracting i since the 'last i elements' are already sorted --> # of j comparisons gets smaller each loop of i
						if(tarray[j]->numDep < tarray[j+1]->numDep) {		//comparing adjacent
							Taxpayer* temp = tarray[j];
							tarray[j] = tarray[j+1];
							tarray[j+1] = temp;
						}
					}
				}
				cout<<"Successfully bubble sorted by # of Dependents (in descending order)!"<<endl;
			}
			else {
				cout<<"Neither ascending nor descending was chosen. Not sorted."<<endl;
			}
			break;

		// 4 indicates sort by income
		case 4:

			if(order == "a") {
				// Ascending (lowest to highest)
				for(int i = 0; i < n-1; i++) {
					for(int j = 0; j < n-i-1; j++){		//subtracting i since the 'last i elements' are already sorted --> # of j comparisons gets smaller each loop of i
						if(tarray[j]->income > tarray[j+1]->income) {		//comparing adjacent
							Taxpayer* temp = tarray[j];
							tarray[j] = tarray[j+1];
							tarray[j+1] = temp;
						}
					}
				}
				cout<<"Successfully bubble sorted by income (in ascending order)!"<<endl;
			}

			else if (order == "d") {

				// Descending (highest to lowest)
				for(int i = 0; i < n-1; i++) {
					for(int j = 0; j < n-i-1; j++){					//subtracting i since the 'last i elements' are already sorted --> # of j comparisons gets smaller each loop of i
						if(tarray[j]->income < tarray[j+1]->income) {		//comparing adjacent
							Taxpayer* temp = tarray[j];
							tarray[j] = tarray[j+1];
							tarray[j+1] = temp;
						}
					}
				}
				cout<<"Successfully bubble sorted by income (in descending order)!"<<endl;
			}
			else {
				cout<<"Neither ascending nor descending was chosen. Not sorted."<<endl;
			}
			break;

		// 5 indicates sort by postal-code
		case 5:
			// Ascending (lowest to highest)
			if(order == "a") {
				for(int i = 0; i < n-1; i++) {
					for(int j = 0; j < n-i-1; j++){		//subtracting i since the 'last i elements' are already sorted --> # of j comparisons gets smaller each loop of i
						if(tarray[j]->zipcode > tarray[j+1]->zipcode) {		//comparing adjacent
							Taxpayer* temp = tarray[j];
							tarray[j] = tarray[j+1];
							tarray[j+1] = temp;
						}
					}
				}
				cout<<"Successfully bubble sorted by zipcode (in ascending order)!"<<endl;
			}
			// Descending (highest to lowest)
			else if (order == "d") {
				for(int i = 0; i < n-1; i++) {
					for(int j = 0; j < n-i-1; j++){					//subtracting i since the 'last i elements' are already sorted --> # of j comparisons gets smaller each loop of i
						if(tarray[j]->zipcode < tarray[j+1]->zipcode) {		//comparing adjacent
							Taxpayer* temp = tarray[j];
							tarray[j] = tarray[j+1];
							tarray[j+1] = temp;
						}
					}
				}
				cout<<"Successfully bubble sorted by zipcode (in descending order)!"<<endl;
			}
			else {
				cout<<"Neither ascending nor descending was chosen. Not sorted."<<endl;
			}
			break;

		default:
			cout<<"The attribute number was not 0, 3, 4, or 5. Please enter a correct attribute number."<<endl;

	}

	// //printing out sorted subarray for testing purposes:
    // cout<<"Start Index: "<<startIndex<<"\t end index: "<<endIndex<<endl;
    // for(int i = startIndex; i < endIndex; i++) {
    //     //Print out every 10th node
    //     if(i%10 == 0) {
    //         cout<<endl<<"Tarray ["<<i<<"] info: ";
    //         tarray[i]->printInfo();
    //     }   
    // }
}

// for creating a bubblesort executable to be executed by the sorter nodes --> how do I pass the arguments like taxpayer array?

// int main(int argc, char *argv[]) {

// 	switch(argc) {

//         // First argument is always just the location of the file
//         case 1:
//             cout<<"No arguments were passed"<<endl;
//             break;

//         case 0:
//             cout<<"Error, somehow? This should not happen"<<endl;
//             break;

//         // More than 1 argument
//         default:
//             cout<<"You entered the following arguments: "<<endl;
//             for(int i = 0; i < argc; i++) {
//                 cout<<"["<<i<<"] "<<argv[i]<<endl;
//             }

// 			// how do I pass a taxpayer array to a 
// 			//t_bubble_sort(stoi(argv[1]), stoi(argv[2), argv[3], argv[4], argv[5], argv[6]);
//     }
// }