/* Citation and Sources...
Final Project Milestone 4
Module: NonPerishable.h
Filename: NonPerishable.h
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
#ifndef NONPERISHABLE_H_
#define NONPERISHABLE_H_
#include <iostream>
#include "Item.h"

namespace sdds {

	class NonPerishable : public Item {

	public:
		char itemType() const;
		std::ostream& write(std::ostream& ostr) const;
	};
}
#endif