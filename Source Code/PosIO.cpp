/* Citation and Sources...
Final Project Milestone 2
Module: PosIO.cpp
Filename: PosIO.cpp
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
#include "PosIO.h"

using namespace std;
namespace sdds {
	PosIO::~PosIO() {}
	std::ostream& operator<<(std::ostream& ostr, const PosIO& pos) {
		return pos.write(ostr);
	}
	std::ofstream& operator<<(std::ofstream& ostr, const PosIO& pos) {
		return pos.save(ostr);
	}
	std::istream& operator>>(std::istream& istr, PosIO& pos) {
		return pos.read(istr);
	}
	std::ifstream& operator>>(std::ifstream& istr, PosIO& pos) {
		return pos.load(istr);
	}
}