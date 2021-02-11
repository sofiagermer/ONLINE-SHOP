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

class Message{
    string email;
    string message;
    bool answered = false;
public:
    /**
     * Constructor of class Message.
     * @param message Message to be inicialized.
     * @param email Email to be inicialized.
     */
    Message(string message,string email);
    /**
     *
     * @param message Message to be inicialized.
     * @param email Email to be inicialized.
     * @param answered True if the message has already been dealt with,false otherwise.
     */
    Message(string message,string email,bool answered);
    /**
     * Returns the email of the client the messages belong to.
     * @return Email of the client the messages belong to.
     */
    string getEmail() const;
    /**
     * Sets the bool answered to the value provided in the parameter.
     * @param answered Value to set answered to.
     */
    void setAnswered(bool answered);
    /**
     * Returns the message.
     * @return message.
     */
    string getMessage() const;
    /**
     * Returns wether the messages has been dealt with or not.
     * @return
     */
    bool getAnswered() const;
};


class registedClient: public clientInfo{
public:
    string email;
    vector<Message> messagesSent;
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
    /**
     * Returns the vector Messages containing all of the client's messages.
     * @return The vector Messages containing all of the client's messages.
     */
    vector<Message> getMessages() const;
    /**
     * Sets the vector messages to the vector passsed as parameter.
     * @param messages Vector to be changed to.
     */
    void setMessages(vector<Message> messages);
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

