//
// Created by Hagop on 4/4/2021.
//

//ptr[0] = monthNumber
//ptr[1] = day
//ptr[2] = year

#include <iostream>
#include <string>
#include "upDate.h"

using namespace std;

int upDate::objectCount = 0;

int Greg2Julian(int month, int day, int year)
{
    int I = year, J = month, K = day;
    return K - 32075 + 1461 * (I + 4800 + (J - 14) / 12) / 4 + 367 * (J - 2 - (J - 14) / 12 * 12) / 12 - 3 * ((I + 4900 + (J - 14) / 12) / 100) / 4;
}

void Julian2Greg(int JD, int &month, int &day, int &year)
{
    int L = JD + 68569;
    int N = 4 * L / 146097;
    L = L - (146097 * N + 3) / 4;
    int I = 4000 * (L + 1) / 1461001;
    L = L - 1461 * I / 4 + 31;
    int J = 80 * L / 2447;
    int K = L - 2447 * J / 80;
    L = J / 11;
    J = J + 2 - 12 * L;
    I = 100 * (N - 49) + I + L;
    year = I;
    month = J;
    day = K;
}

void upDate::numToString() {
    if(ptr[0] == 1) {
        monthName = "January";
    }
    else if(ptr[0] == 2) {
        monthName = "February";
    }
    else if(ptr[0] == 3) {
        monthName = "March";
    }
    else if(ptr[0] == 4) {
        monthName = "April";
    }
    else if(ptr[0] == 5) {
        monthName = "May";
    }
    else if(ptr[0] == 6) {
        monthName = "June";
    }
    else if(ptr[0] == 7) {
        monthName = "July";
    }
    else if(ptr[0] == 8) {
        monthName = "August";
    }
    else if(ptr[0] == 9) {
        monthName = "September";
    }
    else if(ptr[0] == 10) {
        monthName = "October";
    }
    else if(ptr[0] == 11) {
        monthName = "November";
    }
    else if(ptr[0] == 12) {
        monthName = "December";
    }
}

upDate::upDate() {
    ptr = new int[3];
    ptr[0] = 5;
    ptr[1] = 11;
    ptr[2] = 1959;
    numToString();
    objectCount++;
}

upDate::upDate(int m, int d, int y) {
    ptr = new int[3];
    ptr[0] = m;
    ptr[1] = d;
    ptr[2] = y;
    Julian2Greg(Greg2Julian(m, d, y), ptr[0], ptr[1], ptr[2]);
    if(ptr[0] != m || ptr[1] != d || ptr[2] != y) {
        ptr[0] = 5;
        numToString();
        ptr[1] = 11;
        ptr[2] = 1959;
    }
    numToString();
    objectCount++;
}

upDate::upDate(int JD) {
    ptr = new int[3];
    Julian2Greg(JD, ptr[0], ptr[1], ptr[2]);
    numToString();
    objectCount++;
}

upDate::upDate(upDate& UD) {
   ptr = new int[3];
   ptr[0] = UD.getMonth();
   ptr[1] = UD.getDay();
   ptr[2] = UD.getYear();
   monthName = UD.getMonthName();
   objectCount++;
}

upDate::~upDate() {
    objectCount--;
    delete[] ptr;
}

upDate& upDate::operator=(upDate UD) {
    ptr[0] = UD.getMonth();
    ptr[1] = UD.getDay();
    ptr[2] = UD.getYear();
    monthName = UD.getMonthName();
    return *this;
}

upDate& upDate::operator+=(int n) {
    int date = Greg2Julian(ptr[0], ptr[1], ptr[2]);
    date += n;
    Julian2Greg(date, ptr[0], ptr[1], ptr[2]);
    return *this;
}

upDate& upDate::operator-=(int n) {
    int date = Greg2Julian(ptr[0], ptr[1], ptr[2]);
    date -= n;
    Julian2Greg(date, ptr[0], ptr[1], ptr[2]);
    return *this;
}

upDate upDate::operator+(int n) {
    upDate D1;
    int m, d, y;
    int date = Greg2Julian(ptr[0], ptr[1], ptr[2]);
    date = date + n;
    Julian2Greg(date, m, d, y);
    D1.setDate(m, d, y);
    return D1;
}

upDate& operator+(int n, const upDate& D1) {
    int m, d, y;
    int date = Greg2Julian(D1.ptr[0], D1.ptr[1], D1.ptr[2]);
    date = date + n;
    Julian2Greg(date, m, d, y);
    D1.ptr[0] = m;
    D1.ptr[1] = d;
    D1.ptr[2] = y;
    return const_cast<upDate &>(D1);
}

upDate upDate::operator-(int n) {
    upDate D1;
    int m, d, y;
    int date = Greg2Julian(ptr[0], ptr[1], ptr[2]);
    date = date - n;
    Julian2Greg(date, m, d, y);
    D1.setDate(m, d, y);
    return D1;
}

int upDate::operator-(upDate& D2) {
    int d1 = Greg2Julian(ptr[0], ptr[1], ptr[2]);
    int d2 = Greg2Julian(D2.getMonth(), D2.getDay(), D2.getYear());
    int x = d2 - d1;
    return x;
}

ostream& operator<<(ostream& out, const upDate& D1) {
    out << D1.ptr[0] << ", " << D1.ptr[1] << ", " << D1.ptr[2];
    return out;
}

upDate& upDate::operator++() {
    int date = Greg2Julian(ptr[0], ptr[1], ptr[2]);
    date++;
    Julian2Greg(date, ptr[0], ptr[1], ptr[2]);
    return *this;
}

upDate& upDate::operator++(int n) {
    int date = Greg2Julian(ptr[0], ptr[1], ptr[2]);
    ++date;
    Julian2Greg(date, ptr[0], ptr[1], ptr[2]);
    return *this;
}

upDate& upDate::operator--() {
    int date = Greg2Julian(ptr[0], ptr[1], ptr[2]);
    date--;
    Julian2Greg(date, ptr[0], ptr[1], ptr[2]);
    return *this;
}

upDate& upDate::operator--(int n) {
    int date = Greg2Julian(ptr[0], ptr[1], ptr[2]);
    --date;
    Julian2Greg(date, ptr[0], ptr[1], ptr[2]);
    return *this;
}

bool upDate::operator==(upDate& D1) {
    int d1 = Greg2Julian(ptr[0], ptr[1], ptr[2]);
    int d2 = Greg2Julian(D1.getMonth(), D1.getDay(), D1.getYear());
    if (d1 == d2) {
        return true;
    }
    return false;
}

bool upDate::operator<(upDate& D1) {
    int d1 = Greg2Julian(ptr[0], ptr[1], ptr[2]);
    int d2 = Greg2Julian(D1.getMonth(), D1.getDay(), D1.getYear());
    if (d1 < d2) {
        return true;
    }
    return false;
}

bool upDate::operator>(upDate& D1) {
    int d1 = Greg2Julian(ptr[0], ptr[1], ptr[2]);
    int d2 = Greg2Julian(D1.getMonth(), D1.getDay(), D1.getYear());
    if (d1 > d2) {
        return true;
    }
    return false;
}

int upDate::julian() {
    int date = Greg2Julian(ptr[0], ptr[1], ptr[2]);
    return date;
}

void upDate::setDate(int m, int d, int y) {
    ptr[0] = m;
    ptr[1] = d;
    ptr[2] = y;
    numToString();
}

int upDate::getMonth() {
    return ptr[0];
}

int upDate::getDay() {
    return ptr[1];
}

int upDate::getYear() {
    return ptr[2];
}

string upDate::getMonthName() {
    numToString();
    return monthName;
}

int upDate::GetDateCount() {
    return objectCount;
}