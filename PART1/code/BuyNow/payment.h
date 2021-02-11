#pragma once

#include <ctime>
#include <map>
#include <set>
#include <fstream>
#include <sstream>

#include "product.h"
#include "client.h"

class Date{
public:
    /**
     * date's day
     */
    int day;
    /**
     * date's month
     */
    int month;
    /**
     * date's year
     */
    int year;
    /**
     * Default constructor.
     */
    Date();
    /**
     * Constructor that initializes the variables.
     * @param d "day".
     * @param m "month".
     * @param y "year".
     */
    Date(int d, int m, int y);
    /**
     * Function who checks if the date is valid in the Gregorian calendar.
     * @param d Date that will be tested.
     * @return True if the Date is valid, False if otherwise.
     */
    bool TestDate(Date & d);
    /**
     * Function who checks if the date passed in the argument is expired.
     * @param date Date that will be tested.
     * @return True if the date is yet to be reached, False if otherwise.
     */
    bool checkExpiration(Date & date);
    /**
     * Function that overloads the operator "<<" for the "Data" class
     * @param out Destination of the output
     * @param d Date that will be outputted
     * @return Return the output destination in the variable "out"
     */
    friend ostream & operator<<(ostream &out, Date & d);
};



class Payment{
protected:
    /**
     * Price of the transaction
     */
    float value;
    /**
     * User's information
     */
    clientInfo person;
    /**
     * Products chosen by the user
     */
    map<string, unsigned int> ShoppingCart;

public:
    /**
     * Default constructor
     */
    Payment(){};
    /**
     * Constructor that initializes the variables.
     * @param v "value"
     * @param p "person"
     * @param s "ShoppingCart"
     */
    Payment(float v, clientInfo p, map<string, unsigned int> s);
    /**
     * Function that returns the variable "value"
     * @return value
     */
    float GetValue() const;
    /**
     * Pure virtual function
     */
    virtual void Receipt()=0;
};

class MBway : public Payment{
    /**
     * User's phone number
     */
    long long int PhoneNumber;
public:
    /**
     * Default constructor
     */
    MBway(){};
    /**
     * Constructor that initializes the variables.
     * @param v "value"
     * @param p "person"
     * @param s "ShoppingCart"
     * @param phoneN "PhoneNumber"
     */
    MBway(float v, clientInfo p, map<string, unsigned int> s,long long int phoneN);
    /**
     * Function that returns the variable "PhoneNumber"
     * @return PhoneNumber
     */
    long long int GetPhoneNumber() const;
    /**
     * Function that outputs a custom receipt File and updates the "transactionRegist" file with the same receipt
     */
    void Receipt();
};

class ATM : public Payment{
    /**
     * User's ATM reference
     */
    long long int reference;
public:
    ATM(){};
    /**
     * Constructor that initializes the variables.
     * @param v "value"
     * @param p "person"
     * @param s "ShoppingCart"
     * @param ref "reference"
     */
    ATM (float v, clientInfo p, map<string, unsigned int> s, long long int ref);
    /**
     * Function that returns the variable "reference"
     * @return reference
     */
    long long int GetReference() const;
    /**
     * Function that outputs a custom receipt File and updates the "transactionRegist" file with the same receipt
     */
    void Receipt();
};

class CreditCard : public Payment{
    /**
     * User's credit card number
     */
    long long int cardnumber;
    /**
     * User's credit card expiration date
     */
    Date expiration;
public:
    CreditCard(){};
    /**
     * Constructor that initializes the variables.
     * @param v "value"
     * @param p "person"
     * @param s "ShoppingCart"
     * @param numeroc "cardnumber"
     * @param val "expiration"
     */
    CreditCard(float v, clientInfo p, map<string, unsigned int> s, long long int numeroc, Date val);
    /**
     * Function that returns the variable "cardnumber"
     * @return cardnumber
     */
    long long int GetCardNumber() const;
    /**
     * Function that returns the variable "expiration"
     * @return expiration
     */
    Date GetExpiration() const;
    /**
     * Function that outputs a custom receipt File and updates the "transactionRegist" file with the same receipt
     */
    void Receipt();
};

class InvalidDate{
public:
    /**
     * Saved invalid date
     */
    Date invalid;
    /**
     * Initializes the variable
     * @param d "invalid"
     */
    InvalidDate(Date &d);
    /**
     * Funtion that overloads the operator "<<" to display the InvalidDate's information
     * @param out output destination
     * @param v Variable you want to output
     * @return "out" argument
     */
    friend ostream & operator<<(ostream &out, InvalidDate &v);
};


class ExpiredCard{
public:
    /**
     * Saved card's expired date
     */
    Date expiration;
    /**
     * Initializes the variable
     * @param d "expiration"
     */
    ExpiredCard(Date &v);
    /**
     * Funtion that overloads the operator "<<" to display the ExpiredCard's information
     * @param out output destination
     * @param v Variable you want to output
     * @return "out" argument
     */
    friend ostream & operator<<(ostream &out, ExpiredCard &v);

};