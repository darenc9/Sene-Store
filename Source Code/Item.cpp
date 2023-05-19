/* Citation and Sources...
Final Project Milestone 2
Module: Item.cpp
Filename: Item.cpp
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
#define _CRT_SECURE_NO_WARNINGS
#include "Item.h"
#include <cstring>
#include <iomanip>
using namespace std;
namespace sdds {
	Item::Item() {
		SKU[0] = '\0';
		name = nullptr;
		price = 0;
		taxed = false;
		qty = 0;
		disType = 0;
		
	}
	Item::Item(const Item& src) {
		strcpy(SKU, src.SKU);
		name = new char[strlen(src.name) +1];
		strcpy(name, src.name);
		price = src.price;
		taxed = src.taxed;
		qty = src.qty;
		disType = src.disType;
		err = src.err;
	}
	Item& Item::operator=(const Item& src) {
		price = src.price;
		taxed = src.taxed;
		qty = src.qty;
		disType = src.disType;
		err = src.err;
		strcpy(SKU, src.SKU);
		if (name != nullptr) {
			delete[] name;
			name = nullptr;
		}
		name = new char[strlen(src.name) +1];
		strcpy(name, src.name);
		return *this;
	}
	Item::~Item() {
		if (name != nullptr) {
			delete[] name;
			name = nullptr;
		}
	}

	bool Item::operator==(Item& right) const {
		return (strcmp(SKU, right.SKU) == 0 ? 1 : 0);
	}
	bool Item::operator==(const char* right) const {
		return (strcmp(SKU, right) == 0 ? 1 : 0);
	}
	bool Item::operator>(Item& right) const {
		return (strcmp(SKU, right.SKU) > 0 ? 1 : 0);
	}
	int Item::operator+=(int right) {
		qty += right;
		if (qty > MAX_STOCK_NUMBER) {
			qty = MAX_STOCK_NUMBER;
			err = ERROR_POS_QTY;
		}
		return qty;
	}
	int Item::operator-=(int right) {
		qty -= right;
		if (qty < 0) {
			qty = 0;
			err = ERROR_POS_STOCK;
		}
		return qty;
	}
	Item::operator bool() const {
		return (err ? 0 : 1);
	}

	Item& Item::displayType(int type) {
		if (type == POS_LIST || type == POS_FORM)
			disType = type;
		return *this;
	}
	double Item::cost() const {
		return price * (1 + taxed * TAX);
	}
	int Item::quantity() const {
		return qty;
	}
	Item& Item::clear() {
		err.clear();
		return *this;
	}

	std::ostream& Item::write(std::ostream& ostr) const {
		if (!err) {
			if (disType == POS_LIST) {
				
				ostr << setfill(' ') << setw(7) << fixed << left << SKU << "|" << left;
				if (strlen(name) > 20)
					ostr.write(name, 20);
				else
					ostr << setw(20) << name;
				ostr << "|" << setw(7) << fixed << right << setprecision(2) << price << "|"
					<< fixed << setw(3) << (taxed ? " X |" : "   |");
				ostr << setw(4) << right << qty << "|" << setw(9) << fixed << setprecision(2) << cost() * quantity() << "|";
			}
			if (disType == POS_FORM) {
				ostr << "=============v" << endl;
				ostr << setfill(' ') << setw(13) << left << "Name:" << name << endl;
				ostr << setw(13) << left << "Sku:" << SKU << endl;
				ostr << setw(13) << left << fixed << setprecision(2) << "Price:" << price << endl;
				ostr << setw(13) << left << "Price + tax:";
				if (taxed)
					ostr << cost() << endl;
				else
					ostr << "N/A" << endl;
				ostr << setw(13) << left << "Stock Qty:" << quantity() << endl;
			}

			ostr << left << setprecision(0) << setw(0) << "";
		}
		else
			ostr << err;
		return ostr;
	}
	std::istream& Item::read(std::istream& istr) {
		bool check = true;
		char buffer[MAX_NAME_LEN + 3];
		clear();
		//read and validate SKU
		cout << "Sku" << endl;
		do {
			if (err)
				cout << err << endl;
			clear();
			cout << "> ";
			istr >> buffer;
			if (strlen(buffer) > MAX_SKU_LEN)
				err = "ERROR_POS_SKU";
			else
				strcpy(SKU, buffer);
		} while (strlen(buffer) > MAX_SKU_LEN);

		//read and validate Name
		cout << "Name" << endl;
		do {
			if (err)
				cout << err << endl;
			clear();
			cout << "> ";
			istr.clear();
			istr.ignore(100,'\n');
			istr.getline(buffer, MAX_NAME_LEN + 2);
			buffer[strlen(buffer)] = '\0';

			if (strlen(buffer) > MAX_NAME_LEN)
				err = ERROR_POS_NAME;
			else {
				if (name != nullptr) {
					delete[] name;
					name = nullptr;
				}
				name = new char[strlen(buffer) + 1];
				strcpy(name, buffer);
			}
		} while (strlen(buffer) > MAX_NAME_LEN);

		//read and validate Price
		cout << "Price" << endl;
		do {
			if (err)
				cout << err << endl;
			clear();
			cout << "> ";
			if (istr >> price) {
				if (price > 0)
					check = false;
			}
			if (check) {
				err = ERROR_POS_PRICE;
				istr.clear();
				istr.ignore(100, '\n');
			}
		} while (check);

		//read and validate Taxed
		cout << "Taxed?" << endl;
		cout << "(Y)es/(N)o: ";
		check = true;
		do {
			clear();
			istr >> buffer;
			if (strcmp(buffer, "y") == 0 || strcmp(buffer, "n") == 0) {
				taxed = (strcmp(buffer, "y") == 0 ? true : false);
				check = false;
			}
			else {
				err = ERROR_POS_TAX;
				cout << "Only 'y' and 'n' are acceptable: ";
			}
		} while (check);
		
		//read and validate Quantity
		cout << "Quantity" << endl;
		check = true;
		do {
			if (err)
				cout << err << endl;
			clear();
			cout << "> ";
			if (istr >> qty) {
				if(qty > 0 && qty < MAX_STOCK_NUMBER)
					check = false;
			}
			if (check) {
				err = ERROR_POS_QTY;
				istr.clear();
				istr.ignore(100, '\n');
			}
		} while (check);

		return istr;
	}

	std::ofstream& Item::save(std::ofstream& ostr) const {
		if (!err) {
			ostr << itemType() << "," << SKU << "," << name << "," << fixed
				<< setprecision(2) << price << "," << (int)taxed << "," << qty;
		}
		else
			cerr << err;
		return ostr;
	}

	std::ifstream& Item::load(std::ifstream& istr) {
		clear();
		bool flag = true;
		//Local attribute copies
		char bufferSKU[MAX_NAME_LEN];
		char bufferName[100];
		double bufferPrice;
		bool bufferTaxed;
		int bufferQty;

		//loads all variables first
		istr.getline(bufferSKU, MAX_NAME_LEN, ',');
		istr.getline(bufferName, 100, ',');
		istr >> bufferPrice;
		istr.ignore();
		istr >> bufferTaxed;
		istr.ignore();
		istr >> bufferQty;

		//Validates all variables
		if (!istr.fail()) {
			if (strlen(bufferSKU) > MAX_SKU_LEN) {
				err = ERROR_POS_SKU;
				flag = false;
			}
			else if (strlen(bufferName) > MAX_NAME_LEN) {
				err = ERROR_POS_NAME;
				flag = false;
			}
			else if (bufferPrice < 0) {
				err = ERROR_POS_PRICE;
				flag = false;
			}
			else if (bufferTaxed != 0 && bufferTaxed != 1) {
				err = ERROR_POS_TAX;
				flag = false;
			}
			else if (bufferQty < 0 || bufferQty > MAX_STOCK_NUMBER) {
				flag = false;
				err = ERROR_POS_QTY;
			}
		}
		else
			flag = false;
		//Sets all attributes
		if (flag) {
			strcpy(SKU, bufferSKU);
			price = bufferPrice;
			taxed = bufferTaxed;
			qty = bufferQty;
			if (name != nullptr) {
				delete[] name;
				name = nullptr;
			}
			name = new char[strlen(bufferName) + 1];
			strcpy(name, bufferName);
		}
		return istr;
	}

	std::ostream& Item::bprint(std::ostream& ostr) const {
		ostr << "| " << left;
		if (strlen(name) > 20)
			ostr.write(name, 20);
		else
			ostr << setfill(' ') << setw(20) << name;
		ostr << "|" << setw(10) << right << fixed << setprecision(2)
			<< cost() << " |  " << (taxed ? "T" : " ") << "  |" << endl;
		return ostr;
	}
	
	char* Item::getName() {
		return name;
	}
	char* Item::getSKU() {
		return SKU;
	}

	double operator+=(double& left, const Item& right) {
		double value = right.cost() * right.quantity();
		value += left;
		return value;
	}

}