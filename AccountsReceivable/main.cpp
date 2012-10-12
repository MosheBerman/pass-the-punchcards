//
//  main.cpp
//  AccountsReceivable
//
//  Created by Moshe Berman on 10/11/12.
//  Copyright (c) 2012 Moshe Berman. All rights reserved.
//
//  This is the first assignment for Professor Lowenthal's Data Structures class.
//

#include <iostream>
#include <fstream>
#include <exception>

#include "Record.h"
#include "Customer.h"

using namespace std;

//

//  Function prototypes
//

bool openInputStream(ifstream &, string); 
bool openOutputStream(ofstream &, string);

int main() {
    
    //
    //  Some variables to work with files
    //

    string transactionFileName = "transactionAccountsReceivable";
    string masterFileName = "masterAccountsReceivable";
    ifstream transactionFileStream;
    ofstream masterFileStream;
    
    //
    //  Get the transaction type
    //
    
    char transactionType;
    
    //
    //  Open the file streams
    //
    
    if(!openInputStream(transactionFileStream, transactionFileName)){
        
        cerr << "Can't open file " << transactionFileName << ". " << '\n';
        
        throw runtime_error("Can't open transaction file.");        
        
    }
    
    if(!openOutputStream(masterFileStream, masterFileName)){
        
        cerr << "Can't open file " << masterFileName << ". " << '\n';
        

        throw runtime_error("Can't open master file.");
    }
    
    //
    //  Process the transactions
    //
    
    while (transactionFileStream >> transactionType) {
        
        //
        //  Variables for processing records
        //
        
        Record record;
        Customer customer;
        
        //
        //  Store the appropriate record type for later.
        //  I read it here because of the design of the
        //  file format.
        //
        
        if (transactionType == 'P') {
            record.type = Payment;
        }
        else if(transactionType == 'O'){
            record.type = Order;
        }
        
        //
        //  Get the customer number next
        //
        
        if(!(transactionFileStream >> customer.customerNumber)){
            throw runtime_error("Can't read customer number.");
        }
        
        //
        //     Process a payment record
        //
        
        if (record.type == Payment) {
            
            if(!(transactionFileStream >> record.cashAmount)){
                throw runtime_error("Can't read payment amount.");
            }
            
        }
        
        //
        //  Process an Order record
        //
        
        else if (record.type == Order){
            
            if(!(transactionFileStream >> record.itemName)){
                throw runtime_error("Can't read item name");
            }
            
            if(!(transactionFileStream >> record.itemQuantity)){
                throw runtime_error("Can't read item quantity.");
            }
            
            if(!(transactionFileStream >> record.cashAmount)){
                throw runtime_error("Can't read price per unit.");
            }
            
        }
        
        //
        //  We need to put the item into the master file
        //
        
        record.description();
        customer.description();
        
    }
    
    
    return 0;
}

//
//  Opens an input stream
//

bool openInputStream(ifstream &stream, string fileName){
    
    stream.open(fileName.c_str());
    
    if (!stream.good()) {
        return false;
    }
    
    return true;
}


//
//  Opens an output stream
//

bool openOutputStream(ofstream &stream, string fileName){
    
    stream.open(fileName.c_str());
    
    if (!stream.good()) {
        return false;
    }
    
    return true;
}

