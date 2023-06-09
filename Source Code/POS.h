/* Citation and Sources...
Final Project Milestone 2
Module: POS
Filename: POS.h
Version 1.0
Author	Devon Chan
Revision History
-----------------------------------------------------------
Date      Reason
Mar 15	  Updated for MS2
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
#ifndef POS_H_
#define POS_H_
//MS2 Constants
#define TAX 0.13
#define MAX_SKU_LEN 7

#define MIN_YEAR 2000
#define MAX_YEAR 2030

#define MAX_STOCK_NUMBER 99
#define MAX_NO_ITEMS 200
//MS3 Constants
#define MAX_NAME_LEN 40

#define POS_LIST 1
#define POS_FORM 2

#define ERROR_POS_SKU "SKU too long"
#define ERROR_POS_NAME "Item name too long"
#define ERROR_POS_PRICE "Invalid price value"
#define ERROR_POS_TAX "Invalid tax status"
#define ERROR_POS_QTY "Invalid quantity value"
#define ERROR_POS_STOCK "Item out of stock"
#define ERROR_POS_EMPTY "Invalid Empty Item"

#endif