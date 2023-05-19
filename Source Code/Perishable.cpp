/* Citation and Sources...
Final Project Milestone 4
Module: Perishable.cpp
Filename: Perishable.cpp
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

#include "Perishable.h"
namespace sdds {
	char Perishable::itemType() const {
		return 'P';
	}

	std::ostream& Perishable::write(std::ostream& ostr) const {
		Item::write(ostr);
		if (Item::operator bool()) {
			ostr << std::left;
			if (disType == POS_LIST)
				ostr << "  " << expDate << " |";
			else if (disType == POS_FORM)
				ostr << "Expiry date: " << expDate << "\n=============^" << std::endl;
		}
		return ostr;
	}

	std::istream& Perishable::read(std::istream& istr) {
		Item::read(istr);
		if (Item::operator bool() || !istr.fail()) {
			std::cout << "Expiry date (YYYY/MM/DD)" << std::endl;
			Date buffer;
			buffer.dateOnly(1);
			std::cout << "> ";
			buffer.read(istr);
			if (buffer)
				expDate = buffer;
			else
				err = buffer.error();
			} 
		return istr;
	}
	std::ofstream& Perishable::save(std::ofstream& ostr) const {
		Item::save(ostr);
		if (Item::operator bool())
			ostr << "," << expDate;
		return ostr;
	}
	std::ifstream& Perishable::load(std::ifstream& istr) {
		Item::load(istr);
		if (Item::operator bool()) {
			Date buffer;
			buffer.dateOnly(1);
			istr.ignore();
			buffer.fileRead(istr);
			if (buffer)
				expDate = buffer;
			else
				err = buffer.error();
		}
		return istr;
	}
}