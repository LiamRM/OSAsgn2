// The header file contains the function/class declarations
#ifndef TAXPAYER_H
#define TAXPAYER_H

#include <string>

class Taxpayer {
public:
    int RID;
    std::string fname;
    std::string lname;
    int numDep;
    double income;
    int zipcode;

    Taxpayer() {};                 // default constructor
    Taxpayer(int RID, std::string fname, std::string lname, int dependents, double income, int zipcode);
    ~Taxpayer();
    void printInfo();
};

#endif //TAXPAYER_H