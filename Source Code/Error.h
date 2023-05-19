/* Citation and Sources...
Final Project Milestone 2
Module: Error
Filename: Error.h
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
#ifndef ERROR_H_
#define ERROR_H_
#include <iostream>

namespace sdds {
	class Error {
		char* error;
	public:
		Error();
		Error(Error& src);
		~Error();
		Error(const char* msg);
		Error& operator=(const char* msg);
		Error& operator=(const Error& src);
		operator bool() const;
		Error& clear();
		std::ostream& display(std::ostream& ostr = std::cout) const;
	};

	std::ostream& operator<<(std::ostream& ostr, const Error& src);
}
#endif