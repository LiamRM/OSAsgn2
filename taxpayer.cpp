// The CPP file contains the function/class definitions
#include <string>
#include <iostream>
#include "taxpayer.h"

using namespace std;

Taxpayer::Taxpayer(int RID, string fname, string lname, int dependents, double income, int zipcode)
{
    this->RID = RID;
    this->fname = fname;
    this->lname = lname;
    this->numDep = dependents;
    this->income = income;
    this->zipcode = zipcode;
}

Taxpayer::~Taxpayer(){}

void Taxpayer::printInfo() {
    cout<<"RID: "<<this->RID<<endl;
    cout<<"FNAME: "<<this->fname<<endl;
    cout<<"LNAME: "<<this->lname<<endl;
    cout<<"NUM DEPENDENTS: "<<this->numDep<<endl;
    cout<<"INCOME: "<<this->income<<endl;
    cout<<"ZIPCODE: "<<this->zipcode<<endl;
}