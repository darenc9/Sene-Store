/* Citation and Sources...
Final Project Milestone ?
Module: Whatever
Filename: Whatever.cpp
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
#ifndef POSAPP_H_
#define POSAPP_H_
#include <iostream>
#include "Item.h"
#include "Bill.h"
#include "Perishable.h"
#include "NonPerishable.h"

namespace sdds {
	const int MAX_FILE_LEN = 128;
	class PosApp {
		char fileName[MAX_FILE_LEN];
		Item* Iptr[MAX_NO_ITEMS];
		int nptr;

		std::istream& readMenu(int& select, std::istream& istr = std::cin);
		int menu();
		std::istream& addItem(std::istream& istr = std::cin);
		std::ostream& removeItem(std::ostream& ostr = std::cout);
		int selectItem(std::ostream& ostr = std::cout);
		std::ostream& stockItem(std::ostream& ostr = std::cout);
		std::ostream& listItems(bool showTotal = false, std::ostream& ostr = std::cout);
		std::ostream& POS(std::ostream& ostr = std::cout);
		int search();
		void saveRecs();
		void loadRecs();
		
		std::ostream& displayUI(int option, std::ostream& ostr = std::cout);
	public:
		//constructor
		PosApp(const char* string);
		//copy and assignment prohibition
		PosApp(PosApp& p) = delete;
		PosApp& operator=(PosApp& p) = delete;
		
		~PosApp();
		void run();
	};

	std::ostream& actionTitle(const char* title, std::ostream& ostr = std::cout);
}
#endif