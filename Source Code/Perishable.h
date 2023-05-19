/* Citation and Sources...
Final Project Milestone 4
Module: Perishable.h
Filename: Perishable.h
Version 1.0
Author	Devon Chan
Revision History
-----------------------------------------------------------
Date      Reason
Mar 31	  Initial Release for MS4
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------
OR
-----------------------------------------------------------
Write exactly which part of the code is given to you as help and
who gave it to you, or from what source you acquired it.
-----------------------------------------------------------*/
#ifndef PERISHABLE_H_
#define PERISHABLE_H_
#include <iostream>
#include <fstream>
#include "Item.h"
#include "Date.h"
namespace sdds {

	class Perishable : public Item {
		Date expDate;
	public:
		char itemType() const;

		std::ostream& write(std::ostream& ostr) const;
		std::istream& read(std::istream& istr);
		std::ofstream& save(std::ofstream& ostr) const;
		std::ifstream& load(std::ifstream& istr);
	};
}
#endif