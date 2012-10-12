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

#include "Record.h"
#include "Customer.h"

using namespace std;

//
//  Function prototypes
//

bool openInputStream(ifstream &, string); 
bool openOutputStream(ofstream &, string);
void readNCharactersFromStreamIntoArray(ifstream &, int, char*);

int main() {
    
    //
    //  Some variables to work with files
    //

    string transactionFileName = "transactionAccountsReceivable";
    string masterFileName = "masterAccountsReceivable";
    ifstream transactionFileStream;
    ofstream masterFileStream;
    
    //
    //  Variables for processing records
    //
    
    Record record = Record();
    Customer customer = Customer();
    
    //
    //  Get the transaction type
    //
    
    char transactionType;
    
    //
    //  Open the file streams
    //
    
    if(!openInputStream(transactionFileStream, transactionFileName)){
        
        cerr << "Can't open file " << transactionFileName << ". " << '\n';
        
        return 1;
    }
    
    if(!openOutputStream(masterFileStream, masterFileName)){
        
        cerr << "Can't open file " << masterFileName << ". " << '\n';
        
        return 1;
    }
    
    //
    //  Process the transactions
    //
    
    
    
    while (transactionFileStream.good()) {
        
        transactionFileStream >> transactionType;
        
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
        
        transactionFileStream >> customer.customerNumber;
        
        //
        //     Process a payment record
        //
        
        if (record.type == Payment) {
            
            transactionFileStream >> record.cashAmount;
            
        }
        
        //
        //  Process an Order record
        //
        
        else if (record.type == Order){
            
            readNCharactersFromStreamIntoArray(transactionFileStream, 20, record.itemName);
            
            transactionFileStream >> record.itemQuantity;
            transactionFileStream >> record.cashAmount;
            
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

void readNCharactersFromStreamIntoArray(ifstream &stream, int n, char*characters){

    for (int i = 0; i<n; i++) {
        stream >> characters[n];
    }
}
