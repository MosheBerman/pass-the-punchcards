//
//  Customer.h
//  AccountsReceivable
//
//  Created by Moshe Berman on 10/11/12.
//  Copyright (c) 2012 Moshe Berman. All rights reserved.
//



#ifndef AccountsReceivable_Customer_h
#define AccountsReceivable_Customer_h

#include <iostream>
#include <iomanip>

using namespace std;

class Customer {
public:
    int customerNumber;
    char name[20];
    int balanceDue;
    int previousBalance;
    
    //
    //  This method logs out a description of the class.
    //  It doesn't bother with state so you can see the
    //  values, regardless of others. (For example, not all
    //  values of type are paired with a valid itemQuantity
    //  value.)
    //
    
    void description(){
        
        cout << "Customer:\n---\nCustomer Number: " << customerNumber;
        cout << "\nName: " << name;
        cout << "\nBalance: " << setprecision(2) << fixed << balanceDue;
        cout << "\nPrevious \nBalance: " << setprecision(2) << fixed << previousBalance;
        cout << '\n';
    }
};


#endif
