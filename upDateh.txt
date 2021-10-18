//
// Created by Hagop on 4/4/2021.
//

#ifndef MYDATE_UPDATE_H
#define MYDATE_UPDATE_H

#include <string>
#include <iostream>
using namespace std;

class upDate {
private:
    //int monthNum, day, year;
    string monthName;
    int *ptr;

public:
    upDate(); //default constructor
    upDate(int, int, int); //overloaded constructor #1
    upDate(int); //overloaded constructor #2
    upDate(upDate&); //copy constructor
    ~upDate(); //destructor
    upDate& operator=(upDate);//assignment operator
    upDate& operator+=(int);//plus-equals operator
    upDate& operator-=(int);//minus-equals operator
    upDate operator+(int);//plus operator
    friend upDate& operator+(int, const upDate&);//r-value on left side
    upDate operator-(int);//minus operator
    int operator-(upDate&);//days between
    friend ostream& operator<<(ostream&, const upDate&);//ostream operator
    upDate& operator++();//post-increment plus operator
    upDate& operator++(int);//pre-increment plus operator
    upDate& operator--();//post-increment minus operator
    upDate& operator--(int);//pre-increment minus operator
    bool operator==(upDate&);//equality operator
    bool operator<(upDate&);//less-than operator
    bool operator>(upDate&);//greater-than operator
    int julian();
    void setDate(int, int, int);
    int getMonth();
    int getDay();
    int getYear();
    string getMonthName();
    void numToString();
    static int objectCount;
    static int GetDateCount();
};

#endif //MYDATE_UPDATE_H
