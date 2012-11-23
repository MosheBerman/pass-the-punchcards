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
void closeIntputStream(ifstream &stream);
void closeOutputStream(ofstream &);

int main() {
    
    //
    //  Some variables to work with files
    //
    
    string transactionFileName = "transactionAccountsReceivable";
    string masterFileName = "masterAccountsReceivable";
    string newMasterFileName = "newMaster";
    ifstream transactionFileStream;
    ifstream masterFileStream;
    ofstream newMasterFileStream;

    
    //
    //  A place to store the transaction type
    //
    
    char transactionType;
    
    //
    //  Variables for processing records
    //
    
    Customer customer;
    Record record;
    
    //
    //  Open the file streams...
    //
    
    if(!openInputStream(masterFileStream, masterFileName)){
        
        cerr << "Can't open file " << masterFileName << ". " << '\n';
        
        throw runtime_error("Can't open transaction file.");
    }
    
    if(!openOutputStream(newMasterFileStream, newMasterFileName)){
        
        cerr << "Can't open file " << masterFileName << ". " << '\n';
        
        throw runtime_error("Can't open transaction file.");
    }
    
    //
    //  Process the transactions
    //
    
    
    while (masterFileStream >> customer.customerNumber) {
        
        //
        //  Read the customer info in from the master file
        //
        
        masterFileStream >> customer.name;
        
        masterFileStream >> customer.balanceDue;
        
        //
        //  Open the transactions file
        //
        
        if(!openInputStream(transactionFileStream, transactionFileName)){
            
            cerr << "Can't open file " << masterFileName << ". " << '\n';
            
            throw runtime_error("Can't open transaction file.");
        }
        
        //
        //  Look for matching transactions
        //
        
        while (transactionFileStream >> transactionType) {
            
            //
            //  Buffer for the transaction's customer number
            //
            
            int customerNumberPerTransaction = NULL;
            
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
            
            if(!(transactionFileStream >> customerNumberPerTransaction)){
                throw runtime_error("Can't read customer number.");
            }
            
            //
            //     Process a payment record
            //
            
            if (record.type == Payment) {
                
                if(!(transactionFileStream >> record.cashAmount)){
                    throw runtime_error("Can't read payment amount.");
                }
                
                
                record.cashAmount = 0;
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
            //  If this transaction applies to this customer,
            //  then apply it to the customer.
            //
            
            if (customer.customerNumber == customerNumberPerTransaction) {
             
                //
                //  If we're adding an order, we need to add the
                //  amount due to the customer's balance.
                //  Otherwise, subtract it.
                //
                
                if (record.type == Order) {
                    customer.balanceDue += record.cashAmount;
                }
                else{
                    customer.balanceDue -= record.cashAmount;
                }
            }
        }
        
        //
        //  Close the transaction file
        //
        
        closeIntputStream(transactionFileStream);
        
        //
        //  Output the updated customer info
        //  into the new file.
        //
        
        newMasterFileStream << customer.customerNumber;
        newMasterFileStream << "\t";
        newMasterFileStream << customer.name;
        newMasterFileStream << "\t";
        newMasterFileStream << customer.balanceDue;
    }
    
    closeOutputStream(newMasterFileStream);
    
    closeIntputStream(masterFileStream);

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

//
//  Close the input stream
//

void closeIntputStream(ifstream &stream){
    stream.close();
}

//
//  Close the output stream
//

void closeOutputStream(ofstream &stream){
    stream.close();
}
