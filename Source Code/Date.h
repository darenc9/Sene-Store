/* Citation and Sources...
Final Project Milestone 2
Module: Date
Filename: Date.h
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
#ifndef DATE_H_
#define DATE_H_
#include <iostream>
#include <fstream>
#include "Error.h"

namespace sdds {
	class Date {
		int year;
		int month;
		int day;
		int hour;
		int minute;
		bool onlyDate;
		Error err;
		//sets date to system date -- this function was provided.
		void getSystemDate(int& year, int& mon, int& day, int& hour, int& min, bool dateOnly);
		void validateDate();
		
		//This function is used to set all attributes to 0 to match with Matrix's system time and correct output of all 0's.
		void setZero();
	public:
		Date();
		Date(int year, int month, int day);
		Date(int year, int month, int day, int hour, int minute = 0);
		Date(Date& src);

		bool operator==(const Date right) const;
		bool operator!=(const Date right) const;
		bool operator>(const Date right) const;
		bool operator<(const Date right) const;
		bool operator>=(const Date right) const;
		bool operator<=(const Date right) const;

		Date& dateOnly(bool flag);

		operator bool();
		Error& error();
		std::ostream& display(std::ostream& ostr = std::cout) const;
		std::istream& read(std::istream& istr = std::cin);
		std::ifstream& fileRead(std::ifstream& istr);
		Date& clear();
		
	};
	
	//helper utility functions. these were provided.
	int uniqueDateValue(int year, int mon, int day, int hour, int min);
	int daysOfMonth(int year, int month);

	std::ostream& operator<<(std::ostream& ostr, const Date& src);
	std::istream& operator>>(std::istream& istr, Date& src);
	std::ifstream& operator>>(std::ifstream& istr, Date& src);
}

#endif