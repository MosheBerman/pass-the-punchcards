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
    
    Customer customerMaster;
    Record record;
    Customer customer;
    
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
    
    
    while (masterFileStream >> customerMaster.customerNumber) {
        
        //
        //  Read the customer info in from the master file
        //
        
        masterFileStream >> customerMaster.name;
        
        masterFileStream >> customerMaster.balanceDue;
        
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
            
        }
        
        //
        //  Close the transaction file
        //
        
        closeIntputStream(transactionFileStream);
        
        //
        //  Output the updated customer info
        //  into the new file.
        //
        
        newMasterFileStream << customerMaster.customerNumber;
        newMasterFileStream << "\t";
        newMasterFileStream << customerMaster.name;
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
