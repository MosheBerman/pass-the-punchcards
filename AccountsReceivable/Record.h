//
//  Record.h
//  AccountsReceivable
//
//  Created by Moshe Berman on 10/11/12.
//  Copyright (c) 2012 Moshe Berman. All rights reserved.
//

#ifndef AccountsReceivable_Record_h
#define AccountsReceivable_Record_h

//
//  An enum to support the usage of the Record struct
//

enum RecordType {
    Order = 0,
    Payment = 1
    };

//
//  A structure to hold 
//

struct Record {
    RecordType type;
    //Used for either the amount per item, or amount paid. In either case, stored in pennies.
    int cashAmount;
    char itemName[0];
    int itemQuantity;
};

#endif
