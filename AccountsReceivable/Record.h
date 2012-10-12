//
//  Record.h
//  AccountsReceivable
//
//  Created by Moshe Berman on 10/11/12.
//  Copyright (c) 2012 Moshe Berman. All rights reserved.
//

#ifndef AccountsReceivable_Record_h
#define AccountsReceivable_Record_h

#include <iostream>
#include <iomanip>

using namespace std;

//
//  An enum to support the usage of the Record struct
//

enum RecordType {
    Order = 0,
    Payment = 1
    };

//
//  A structure to hold the record information.
//
//  This is a class so that we can print it out
//  as necessary using the description() method.
//
//  Everything is public for convenience, otherwise
//  reading from a stream becomes cumbersome.
//

class Record {
    
public:
    
    RecordType type;
    
    //
    //  cashAmount is used for either the price
    //  per unit, or amount paid, depending on the type.
    //
    //  (Usually, it's dumb to use anything but pennies and ints
    //  for money, but it's a HW assignment, not the next Great
    //  American App.)
    //
    
    double cashAmount;
    char itemName[20];
    int itemQuantity;
    
    //
    //  This method logs out a description of the class.
    //  It doesn't bother with state so you can see the
    //  values, regardless of others. (For example, not all
    //  values of type are paired with a valid itemQuantity
    //  value.)
    //
    
    void description(){
        
        cout << "Record:\n---\nType: " << type;
        cout << "\nAmount: " << setprecision(2) << fixed << cashAmount;
        cout << "\nItem: " << itemName;
        cout << "\nQuantity: " << itemQuantity;
        cout << '\n';
    }
    
};

#endif
