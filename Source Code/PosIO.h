/* Citation and Sources...
Final Project Milestone 2
Module: PosIO.h
Filename: PosIO.h
Version 1.0
Author	Devon Chan
Revision History
-----------------------------------------------------------
Date      Reason
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
#ifndef POSIO_H_
#define POSIO_H_
#include <iostream>
#include <fstream>
namespace sdds {
	class PosIO {
	public:
		virtual ~PosIO();
		virtual std::ostream& write(std::ostream& ostr) const = 0;
		virtual std::istream& read(std::istream& istr) = 0;
		virtual std::ofstream& save(std::ofstream& ostr) const = 0;
		virtual std::ifstream& load(std::ifstream& istr) = 0;
	};
	std::ostream& operator<<(std::ostream& ostr, const PosIO& pos);
	std::ofstream& operator<<(std::ofstream& ostr, const PosIO& pos);
	std::istream& operator>>(std::istream& istr, PosIO& pos);
	std::ifstream& operator>>(std::ifstream& istr, PosIO& pos);
}
#endif