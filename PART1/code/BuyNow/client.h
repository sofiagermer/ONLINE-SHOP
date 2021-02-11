#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <regex>
#include <string>
#include <algorithm>


using namespace std;

class clientInfo{
public:
    /**
    * Represents the client's name
    */
    string clientName;
    /**
    * Represents the client's NIF
    */
    long long int NIF;
    /**
    * Represents the client's ID
    */
    int ID;
    /**
    * Used to turn the ID into a sequencial variable
    */
    static int IDcounter;
    /**
     * Tells if a client is registered(1) or not(0)
     */
    bool registed = 0;
    /**
     * Default constructor.
     */
    clientInfo();
    /**
     * Initializes the variables clientName, NIF, registed.
     * @param clientName Name of the client.
     * @param NIF NIF of the client.
     * @param registed 1 if registed, 0 if not.
     */
    clientInfo(string clientName,int NIF,bool registed);
    /**
     * Returns the client's name.
     * @return Client's name.
     */
    string getClientName() const;
    /**
     * Returns the client's NIF.
     * @return Client's NIF.
     */
    int getNIF() const;
    /**
     * Returns the client's ID.
     * @return Client's ID.
     */
    int getID() const;
    /**
     * Returns if client is registed or not.
     * @return 1(true) if registed and 0 if not(false).
     */
    bool getRegisted() const;
    /**
     * Sets the variable registed to the value of the parameter.
     * @param registed Value to change to.
     */
    void setRegisted(bool registed);

};

class registedClient: public clientInfo{
public:
    string email;
    /**
     * Default constructor.
     */
    registedClient();
    /**
     * Initializes the variables clientName, NIF, registed and email.
     * @param clientName Name of the client.
     * @param NIF NIF of the client.
     * @param email Email of the client.
     * @param registed 1 if registed, 0 if not.
     */
    registedClient(string clientName, int NIF, string email,bool registed);
    /**
     * Returns the client's email.
     * @return Client's email.
     */
    string getEmail() const;
};

class ClientIsAlreadyRegistered
{
public:
    string clientName;
    /**
     * Initializes the variable clientName.
     * @param name Client's name.
     */
    ClientIsAlreadyRegistered(const string & name) {clientName = name;}
};

class clientIsNotNew
{
public:
    string clientName;
    /**
     * Initializes the variable clientName.
     * @param name Client's name.
     */
    clientIsNotNew(const string & name) {clientName = name;}
};
