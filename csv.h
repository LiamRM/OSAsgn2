#ifndef CSV_H       // file guards to prevent re-definitions
#define CSV_H

#include "taxpayer.h"
#include <string>

int getFileSize(std::string filename);
void read_taxpayers(std::string filename, Taxpayer* tarray[]);
void writeToFile(std::string filename, Taxpayer* tarray[], int size);

#endif