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
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iomanip>
#include "PosApp.h"
#include "Bill.h"
using namespace std;

namespace sdds {

	//constructor
	PosApp::PosApp(const char string[]) {
		strcpy(fileName, string);

		Iptr[0] = {0};
		nptr = 0;
	}

	//Reads user menu selection 
	istream& PosApp::readMenu(int& select, istream& istr) {
		do {
			if (!(istr >> select))
			{
				cout << "Invalid Integer, try again: ";
				istr.clear();
				istr.ignore(100, '\n');
				select = -1;
			}
			else
			{
				if (select < 0 || select > 5) {
					cout << "[0<=value<=5], retry: > ";
				}
			}
		} while (select < 0 || select > 5);
		return istr;
	}

	//Operates the menu
	int PosApp::menu() {
		int* select = new int;
		displayUI(-1);
		readMenu(*select, cin);
		int temp = select[0];
		delete select;
		return temp;
	}

	void PosApp::run() {
		int selection;
		loadRecs();
		do {
			selection = menu();
			switch (selection) {
			case 1:
				listItems(true);
				break;
			case 2:
				addItem();
				break;
			case 3:
				removeItem();
				break;
			case 4:
				stockItem();
				break;
			case 5:
				POS();
				break;
			case 0:
				saveRecs();
			}
		} while (selection != 0);
	}

	std::istream& PosApp::addItem(std::istream& istr) {
		actionTitle("Adding Item to the store");
		char perishable;
		bool loop = true;
		if (nptr >= MAX_NO_ITEMS)
			displayUI(1);
		else {
			Item* item = nullptr;
			do
			{
				cout << "Is the Item perishable? (Y)es/(N)o: ";
				istr >> perishable;
				if (perishable == 'y' || perishable == 'Y')
					item = new Perishable();
				else if (perishable == 'n' || perishable == 'N')
					item = new NonPerishable();
				else
					cout << "Invalid answer\n";
			} while ((perishable != 'y' && perishable != 'Y') && (perishable != 'n' && perishable != 'N'));
			
			while (loop) {
				item->read(istr);
				if (!item) {
					istr.clear();
					istr.ignore(100, '\n');
					cout << item << ", try again...\n";
				}
				else if (item) {
					loop = 0;
					Iptr[nptr] = item;
					nptr++;
				}
			}
		}
		actionTitle("DONE!");
		return istr;
	}
	std::ostream& PosApp::removeItem(std::ostream& ostr) {
		actionTitle("Remove Item");
		int selection = selectItem(ostr);
		ostr << "Removing...." << endl;
		Iptr[selection - 1]->displayType(2);
		Iptr[selection - 1]->write(ostr);
		delete Iptr[selection - 1];
		nptr--;
		for (int i = selection - 1; i < nptr; i++) {
			Iptr[i] = Iptr[i + 1];
		}

		actionTitle("DONE!");
		return ostr;
	}

	int PosApp::selectItem(std::ostream& ostr) {
		actionTitle("Item Selection by row number");
		bool loop = true;
		int selection = 0;
		ostr << "Press <ENTER> to start....";
		do {
			cin.get();
		} while (cin.get() != '\n');
		listItems();
		ostr << "Enter the row number: ";
		do {
			cin >> selection;
			if (!cin.fail() && selection > 0 && selection < nptr)
				loop = false;
			else if (cin.fail()) {
				ostr << "Invalid Integer, try again: ";
				cin.clear();
				cin.ignore(100, '\n');
			}
			else if (selection <= 0 || selection > nptr) {
				ostr << "[1<=value<=" << nptr << "], retry: Enter the row number: ";
			}
			else
				loop = false;
		} while (loop);
		return selection;
	}

	std::ostream& PosApp::stockItem(std::ostream& ostr) {
		actionTitle("Select an item to stock");
		bool loop = true;
		int qtyLimit, qtyToAdd;
		int selection = selectItem(ostr);
		ostr << "Selected Item:" << endl;
		Iptr[selection - 1]->displayType(2);
		Iptr[selection - 1]->write(ostr);
		ostr << "Enter quantity to add: ";
		qtyLimit = MAX_STOCK_NUMBER - Iptr[selection - 1]->quantity();
		do {
			cin >> qtyToAdd;
			if (!cin.fail() && qtyToAdd > 0 && qtyToAdd < qtyLimit)
				loop = false;
			else if (cin.fail()) {
				ostr << "Invalid Integer, try again: ";
				cin.clear();
				cin.ignore(100, '\n');
			}
			else if (qtyToAdd <= 0 || qtyToAdd > qtyLimit) {
				ostr << "[1<=value<=" << qtyLimit << "], retry: Enter quantity to add: ";
			}
			else
				loop = false;
		} while (loop);
		Iptr[selection - 1]->operator+=(qtyToAdd);
		actionTitle("DONE!");
		return ostr;
	}

	ostream& PosApp::listItems(bool showTotal, std::ostream& ostr) {
		actionTitle("Listing Items");
		int i, j;
		double total = 0;
		displayUI(0);

		for (i = 0; i < nptr - 1; i++) {
			for (j = 0; j < nptr - 1 - i; j++) {
				if (strcmp(Iptr[j]->getName(), Iptr[j + 1]->getName()) > 0) {
					Item* temp = Iptr[j];
					Iptr[j] = Iptr[j + 1];
					Iptr[j + 1] = temp;
				}
			}
		}
		
		for (i = 0; i < nptr; i++) {
			Iptr[i]->displayType(1);
			ostr << setw(4) << right << setfill(' ') << i + 1 << " | ";
			Iptr[i]->write(ostr);
			ostr << endl;
			total += (Iptr[i]->cost() * Iptr[i]->quantity());
		}
		ostr << "-----^--------^--------------------^-------^---^----^---------^-------------^" << endl;
		if (showTotal) {
			ostr << "                               Total Asset: $  |";
			ostr << setw(14) << setfill(' ') << right << fixed << setprecision(2) << total << "|" << endl;
			ostr << "-----------------------------------------------^--------------^\n" << endl;
		}
		return ostr;
	}
	std::ostream& PosApp::POS(std::ostream& ostr) {
		actionTitle("Starting Point of Sale");
		cin.clear();
		cin.ignore(100, '\n');
		Bill bill;
		int index;
		do {
			do {
				displayUI(2);
				index = search();
				if (index == -3) {
					ostr << "!!!!! Item Not Found !!!!!" << endl;
					index = -1;
				}
			} while (index == -1);

			if (index != -2) {
				Iptr[index]->operator-=(1);
				if (Iptr[index]) {
					Iptr[index]->displayType(2);
					Iptr[index]->write(cout);
					ostr << endl;
					bill.add(Iptr[index]);
					ostr << ">>>>> Added to bill" << endl;
					ostr << ">>>>> Total: " << fixed << setprecision(2) << bill.total() << endl;
				}
				else Iptr[index]->clear();
			}
		} while (index != -2);
		bill.print(ostr);
		return ostr;
	}

	int PosApp::search() {
		char result[MAX_SKU_LEN +1];
		int index = -1;
		cin.getline(result,MAX_SKU_LEN);
		if (cin.fail()) {
			cout << "SKU too long" << endl;
			cin.clear();
			cin.ignore(100, '\n');
		}
		else {
			if (strlen(result) == 0)
				index = -2;
			else {
				for (int i = 0; i < nptr; i++) {
					if ((strcmp(Iptr[i]->getSKU(), result) == 0)) {
						index = i;
						if (Iptr[i]->quantity() == 0) {
							index = -1;
							cout << "Item out of stock" << endl;
						}
						i = nptr;
					}
					else index = -3;
				}
			}
		}
		return index;
	}

	void PosApp::saveRecs() {
		actionTitle("Saving Data");
		int i;
		ofstream output(fileName);
		for (i = 0; i < nptr; i++) {
			Iptr[i]->save(output);
			output << endl;
		}
		cout << "Goodbye!" << endl;
	}
	void PosApp::loadRecs() {
		char type;
		actionTitle("Loading Items");
		ifstream input(fileName);

		if (!input) {
			ofstream output(fileName);
			output.close();
			input.open(fileName);
		}
		while (input >> type && nptr < MAX_NO_ITEMS) {
			input.ignore();
			if (type != '\n') {
				if (type == 'P') {
					Iptr[nptr] = new Perishable();
					input >> *Iptr[nptr];
					nptr++;
				}
				else if (type == 'N') {
					Iptr[nptr] = new NonPerishable();
					input >> *Iptr[nptr];
					nptr++;
				}
			}
		}
		input.close();
	}
	PosApp::~PosApp() {
		int i;
		for (i = 0; i < nptr; i++) {
			delete Iptr[i];
		}
		nptr = 0;
	}

	std::ostream& PosApp::displayUI(int option, std::ostream& ostr) {
		if (option == -1) {
			ostr << "The Sene-Store" << endl;
			ostr << "1- List items" << endl;
			ostr << "2- Add item" << endl;
			ostr << "3- Remove item" << endl;
			ostr << "4- Stock item" << endl;
			ostr << "5- POS" << endl;
			ostr << "0- exit program" << endl << "> ";
		}
		else if (option == 0) {
			ostr << " Row | SKU    | Item Name          | Price |TX |Qty |   Total | Expiry Date |" << endl;
			ostr << "-----|--------|--------------------|-------|---|----|---------|-------------|" << endl;
		}
		else if (option == 1) {
			ostr << "Inventory Full!" << endl;
		}
		else if (option == 2) {
			ostr << "Enter SKU or <ENTER> only to end sale..." << endl << "> ";
		}
		return ostr;
	}
	std::ostream& actionTitle(const char* title, std::ostream& ostr) {
		ostr << ">>>> ";
		ostr << left << setw(72) << setfill('.') << title << endl;
		return ostr;
	}
}

