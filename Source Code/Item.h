/* Citation and Sources...
Final Project Milestone 2
Module: Item.h
Filename: Item.h
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
#ifndef ITEM_H_
#define ITEM_H_
#include <iostream>
#include "POS.h"
#include "Error.h"
#include "PosIO.h"
#include <fstream>
namespace sdds {

	class Item : public PosIO{
		char SKU[MAX_SKU_LEN];
		char* name;
		double price;
		bool taxed;
		int qty;
	protected:
		int disType;
		Error err;
	public:
		Item();
		Item(const Item& src);
		Item& operator=(const Item& src);
		~Item();

		char* getName();
		char* getSKU();
		double cost() const;

		bool operator==(Item& right) const;
		bool operator==(const char* right) const;
		bool operator>(Item& right) const;
		int operator+=(int right);
		int operator-=(int right);
		operator bool() const;

		virtual char itemType() const = 0;
		Item& displayType(int type);
		int quantity() const;
		Item& clear();

		std::ostream& write(std::ostream& ostr) const;
		std::istream& read(std::istream& istr);
		std::ofstream& save(std::ofstream& ostr) const;
		std::ifstream& load(std::ifstream& istr);

		std::ostream& bprint(std::ostream& ostr) const;
	};
	double operator+=(double& left, const Item& right);
}
#endif