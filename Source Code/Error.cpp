/* Citation and Sources...
Final Project Milestone 2
Module: Error
Filename: Error.cpp
Version 1.0
Author	Devon Chan
Revision History
-----------------------------------------------------------
Date      Reason
Mar 15	  Updated for MS2
Mar 21	  Updated for MS3
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
#include "Error.h"
#include <cstring>

namespace sdds {
	//constructor
	Error::Error() {
		error = nullptr;
	}
	//copy constructor
	Error::Error(Error& src) {
		error = new char[strlen(src.error)+1];
		strcpy(error, src.error);
	}
	//destructor
	Error::~Error() {
		delete[] error;
		error = nullptr;
	}
	//constructor
	Error::Error(const char* msg) {
		error = new char[strlen(msg)+1];
		strcpy(error, msg);
	}
	//copy assignment
	Error& Error::operator=(const Error& src) {
		delete[] error;
		if (src) {
			error = new char[strlen(src.error) + 1];
			strcpy(error, src.error);
		}
		return *this;
	}

	Error& Error::operator=(const char* msg){
		delete[] error;
		error = new char[strlen(msg)+1];
		strcpy(error, msg);
		return *this;
	}
	//returns true if theres an error message
	Error::operator bool() const{
		return (error ? true : false);
	}
	//clears error message
	Error& Error::clear() {
		delete[] error;
		error = nullptr;
		return *this;
	}

	std::ostream& Error::display(std::ostream& ostr) const {
		if (*this)
			ostr << error;
		return ostr;
	}

	std::ostream& operator<<(std::ostream& ostr, const Error& src) {
		return src.display(ostr);
	}
}