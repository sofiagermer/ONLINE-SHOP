#include "client.h"
#include "shop.h"

string clientInfo::getClientName() const{
    return clientName;
}

clientInfo::clientInfo(){};

int clientInfo::getNIF() const{
    return NIF;
}

int clientInfo::IDcounter = 0;

clientInfo::clientInfo(string clientName,int NIF,bool registed) : clientName(clientName), NIF(NIF), registed(registed){
}

bool clientInfo::getRegisted() const {
    return registed;
}

void clientInfo::setRegisted(bool registed){
    this->registed = registed;
}

int clientInfo::getID() const {
    return clientInfo::ID;
}

string registedClient::getEmail() const{
    return email;
}

registedClient::registedClient(){};

registedClient::registedClient(string clientName, int NIF, string email,bool registed) : clientInfo(clientName,NIF,registed), email(email){
    clientInfo::IDcounter++;
    ID = IDcounter;
}

