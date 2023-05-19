/* Citation and Sources...
Final Project Milestone 2
Module: Date
Filename: Date.cpp
Version 1.0
Author	Devon Chan
Revision History
-----------------------------------------------------------
Date      Reason

-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------
OR
-----------------------------------------------------------
Write exactly which part of the code is given to you as help and
who gave it to you, or from what source you acquired it.
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <iomanip>
#include "Date.h"
#include "POS.h"
using namespace std;

namespace sdds {
    //retrieves current date and time. this function was provided.
    void Date::getSystemDate(int& year, int& mon, int& day, int& hour, int& min, bool dateOnly) {
        time_t t = time(NULL);
        tm lt = *localtime(&t);
        day = lt.tm_mday;
        mon = lt.tm_mon + 1;
        year = lt.tm_year + 1900;
        if (dateOnly) {
            hour = min = 0;
        }
        else {
            hour = lt.tm_hour;
            min = lt.tm_min;
        }
    }
    //returns unique int that holds the date-time value. this function was provided.
    int uniqueDateValue(int year, int mon, int day, int hour, int min){
        return (year * 535680 + mon * 44640 + day * 1440 + hour * 60 + min);
    }

    //returns number of days in the month. this function was provided   
    int daysOfMonth(int year, int month){
    int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
    int mon = month >= 1 && month <= 12 ? month : 13;
    mon--;
    return days[mon] + int((mon == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
    }
    //Custom function to validate the object's date
    void Date::validateDate() {
        bool go = true;
        if (year < MIN_YEAR || year > MAX_YEAR) {
            go = false;
            err="Invalid Year";
        }
        if ((month <= 0 || month > 12) && go)  {
            go = false;
            err="Invalid Month";
        }
        if ((day <= 0 || day > daysOfMonth(year, month)) && go) {
            go = false;
            err="Invalid Day";
        }
        if ((hour < 0 || hour > 23) && go && !onlyDate) {
            go = false;
            err="Invalid Hour";
        }
        if ((minute < 0 || minute > 59) && go && !onlyDate) {
            go = false;
            err="Invlid Minute";
        }
    }
    //default constructor
    Date::Date() {
        onlyDate = false;
        getSystemDate(year, month, day, hour, minute, onlyDate);
       
    }
    //date only constructor
    Date::Date(int year, int month, int day) {
        this->year = year;
        this->month = month;
        this->day = day;
        hour = 0;
        minute = 0;
        onlyDate = true;
        validateDate();
    }
    //date and time constructor
    Date::Date(int year, int month, int day, int hour, int minute) {
        this->year = year;
        this->month = month;
        this->day = day;
        this->hour = hour;
        this->minute = minute;
        onlyDate = false;
        validateDate();
    }
    //copy constructor
    Date::Date(Date& src) {
        year = src.year;
        month = src.month;
        day = src.day;
        hour = src.hour;
        minute = src.minute;
        onlyDate = src.onlyDate;
        err = src.err;
    }
    /* Comparison Operator Overloads */
    bool Date::operator==(const Date d) const{
        return uniqueDateValue(year, month, day, hour, minute) == uniqueDateValue(d.year, d.month, d.day, d.hour, d.minute);
    }
    bool Date::operator!=(const Date d) const{
        return uniqueDateValue(year, month, day, hour, minute) != uniqueDateValue(d.year, d.month, d.day, d.hour, d.minute);
    }
    bool Date::operator>(const Date d) const{
        return uniqueDateValue(year, month, day, hour, minute) > uniqueDateValue(d.year, d.month, d.day, d.hour, d.minute);
    }
    bool Date::operator<(const Date d) const {
        return uniqueDateValue(year, month, day, hour, minute) < uniqueDateValue(d.year, d.month, d.day, d.hour, d.minute);
    }
    bool Date::operator>=(const Date d) const {
        return uniqueDateValue(year, month, day, hour, minute) >= uniqueDateValue(d.year, d.month, d.day, d.hour, d.minute);
    }
    bool Date::operator<=(const Date d) const {
        return uniqueDateValue(year, month, day, hour, minute) <= uniqueDateValue(d.year, d.month, d.day, d.hour, d.minute);
    }
    //setter function for dateOnly
    Date& Date::dateOnly(bool flag) {
        onlyDate = flag;
        if (flag) {
            hour = 0;
            minute = 0;
        }
        return *this;
    }
    //Returns the opposite of the state of the error attribute
    Date::operator bool() {
        return !(err.operator bool());
    }

    //error query
    Error& Date::error() {
        return err;
    }

    ostream& Date::display(ostream& ostr) const {
        if (err) {
            ostr << err << "(";
        }        
        ostr << year << "/" << right << setfill('0') << setw(2) << month << "/" << setfill('0') << setw(2) << day;
        if (!onlyDate)
            ostr << ", " << setfill('0') << setw(2) << hour << ":" << setfill('0') << setw(2) << minute;
        if (err) {
            ostr << ")";
        }
        ostr << left;
        return ostr;
    }

    ostream& operator<<(ostream& ostr, const Date& src) {
        return src.display(ostr);
    }
    //This function is used to set all attributes to 0 to match with Matrix's system time and correct output of all 0's.
    void Date::setZero() {
        year = 0;
        month = 0;
        day = 0;
        hour = 0;
        minute = 0;
    }

    istream& Date::read(istream& istr) {
        err.clear();
        bool flag = true;
        setZero();
        if (istr >> year) 
            istr.ignore();
        else {
            flag = false;
            err="Cannot read year entry";
        }

        if (flag) {
            if (istr >> month) 
                  istr.ignore();
            else {
                flag = false;
                err="Cannot read month entry";
            }
        }

        if (flag) {
            if (istr >> day) {
                if (!onlyDate)
                    istr.ignore();
            }
            else {
                flag = false;
                err="Cannot read day entry";
            }
        }

        if (flag && !onlyDate) {
            if (istr >> hour)
                istr.ignore();
            else {
                flag = false;
                err="Cannot read hour entry";
            }
        }

        if (flag && !onlyDate) {
            if (!(istr >> minute)){
                flag = false;
                err="Cannot read minute entry";
            }
        }

        if (flag)
            validateDate();
        return istr;
    }

    istream& operator>>(istream& istr, Date& src) {
        return src.read(istr);
    }

    Date& Date::clear() {
        err.clear();
        return *this;
    }

    std::ifstream& Date::fileRead(std::ifstream& istr) {
        clear();
        bool flag = true;
        setZero();
        if (istr >> year)
            istr.ignore();
        else {
            flag = false;
            err = "Cannot read year entry";
        }

        if (flag) {
            if (istr >> month)
                istr.ignore();
            else {
                flag = false;
                err = "Cannot read month entry";
            }
        }

        if (flag) {
            if (istr >> day) {
                if (!onlyDate)
                    istr.ignore();
            }
            else {
                flag = false;
                err = "Cannot read day entry";
            }
        }

        if (flag && !onlyDate) {
            if (istr >> hour)
                istr.ignore();
            else {
                flag = false;
                err = "Cannot read hour entry";
            }
        }

        if (flag && !onlyDate) {
            if (!(istr >> minute)) {
                flag = false;
                err = "Cannot read minute entry";
            }
        }

        if (flag)
            validateDate();
        return istr;
    }

    std::ifstream& operator>>(std::ifstream& istr, Date& src) {
        return src.fileRead(istr);
    }

}