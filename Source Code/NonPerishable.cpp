/* Citation and Sources...
Final Project Milestone 4
Module: NonPerishable.cpp
Filename: NonPerishable.cpp
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
#include "NonPerishable.h"

namespace sdds {
	char NonPerishable::itemType() const {
		return 'N';
	}

	std::ostream& NonPerishable::write(std::ostream& ostr) const {
		Item::write(ostr);
		if (Item::operator bool()) {
			if (disType == POS_LIST)
				ostr << "     N / A   |";
			else if (disType == POS_FORM)
				ostr << "=============^" << std::endl;
		}
		return ostr;
	}
}