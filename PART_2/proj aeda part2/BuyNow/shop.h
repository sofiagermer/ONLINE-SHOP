#pragma once

#include <fstream>
#include <iomanip>
#include <unordered_set>

#include "client.h"
#include "product.h"
#include "fstream"
#include "sstream"
#include "ctime"
#include "queue"

#include "realshops.h"
#include "QuickSort.h"
#include "truck.h"

struct userRecordHash
{
    int operator() (const Message& ur) const
    {
        int v = 1;
        for(auto &c: ur.getEmail())
            v = v + int(c);
        return v % 17;
    }

    bool operator() (const Message& ur1, const Message& ur2) const
    {
        return ur1.getMessage() == ur2.getMessage();
    }
};

typedef unordered_set<Message, userRecordHash, userRecordHash> HashTabUser;

typedef enum{
    manual, PriceAscending, PriceDescending
}SupplyModel;

class Shop{
private:
    /**
     * Shop's profit
     */
    float ShopWallet = 0;
    /**
     *
     */
    vector<clientInfo> clients;
    vector<registedClient> regclients;

    vector<Product> vectorProducts;
    vector<RealShop> realShops;
    map<string,int> statistic;
    HashTabUser receivedMessages;

    vector<pair<string, int>> volumes;
    priority_queue<Truck> trucks;

    unsigned int stockMin = 5;
    float profitMargin = 1.45;

    SupplyModel sm = PriceAscending;
public:
    /**
     * Constructor of class Shop
     */
    Shop(){};
    /**
     * Creates the vector of products from the online shop.
     * Creates the vector of real shops and for each real shop creates their own vector of products.
     * If there is no previous data it creates a map with the statistics all initialized at 0,else it reads from the BuyNowStatistics.txt file.
     * @param s  Supply's file containing their products and prices.
     */
    Shop(Supply &s);
    /**
     * Asks the user for his name and NIF, and checks if the user has already been to the shop.
     * @return Returns the object of  the class clientInfo,representing a client.
     */
    clientInfo initialInfo();
    /**
    * Asks the user if he wishes to register himself and checks if the user is already registered.
    * @param c Receives the client c and registers him or not.
    * @return Returns a bool, which is true if clients wants to register, and false otherwise.
    */
    bool registationDesire(clientInfo &c);
    /**
     * Proceeds to ask the client the remaining info for its registation.
     * @param c Client c who wants to register himself.
     * @return Returns an object to a registedClient.
     */
    static registedClient registation(clientInfo &c);
    /**
     * Reads the clients that have already been to the shop and adds them to the vectors of clients in the class Shop.
     * @param fileName Name of the file containing the inicial clients.
     */
    void readInitial_Clients_file(const string& fileName);
    /**
      * Checks if input has commas.
      * @param name Name to be checked
      * @return True is there is commas,false otherwise
      */
    bool checkCommas(string name);
    /**
     * Asks a registed client if he wishes to remove his registation or not.
     * @param c Client who is interrogated.
     */
    bool removeRegistation(clientInfo & c);
    /**
     * Adds clients to the file when the shop closes.
     * @param filename Name of the file every client is beeing added to.
     */
    void addClientsToFile(const string& filename);
    /**
     * Adds a reggistered client to the vector of registed clients in the class Shop.
     * @param c Registed client to be added.
     */
    void addRegisteredClient(const registedClient& c);
    /**
     * Adds a normal client to the vector of normal clients int the class Shop.
     * @param c Client to be added.
     */
    void addClient(clientInfo &c);
    /**
     * Finds the client whose NIF is equal to NIF(parameter).
     * @param NIF NIF of the client the function searches for.
     * @return Returns the client with the same NIF.
     */
    clientInfo getClient(int NIF);

    /**
     * Adds all the messages existing in the shop for a posterior opening.
     * @param filename Filename of the file where the messages are going to be loaded without any extra information.
     * @param filename2 Filename of the file where the messages are going to be loaded with extra information.
     */
    void addMessagesToFile(const string& filename,const string& filename2);

    /**
     * Load the messages left by clients on the previous  opening of the shop.
     * @param filename Filename where the messages are saved.
     */
    void loadPreviousClientsMessages(const string& filename);
    /**
     * Function that allows the manager to handle all the client's messages and decide wether he wants to deal with them or not.
     */
    void handleClientsMessages();
    /**
     * Function that functions as the procedure for all clients who enter the shop.
     * @return Returns either a normal client or a registed client.
     */
    clientInfo allClientsInfo();
    /**
     * Checks if the NIF typed by a new client does not belong to him.
     * @param clientName Name of the client who typed the NIF.
     * @param NIF NIF to search.
     * @return  Returns true if NIF does not belong  to client of name clientName and false otherwise.
     */
    bool clientWrongNIF(string clientName, int NIF);
    /**
     * Checks if client is already registered or not.
     * @param NIF NIF of client to be checked.
     * @return Return true if client is already registered.
     */
    bool clientIsRegistered(int NIF);
    /**
     * Checks if client of name clientName already exists.
     * @param clientName Name of client to be checked.
     * @param NIF NIF of client to be checked.
     * @return Return true if client already exists and false otherwise.
     */
    bool clientAlreadyExists(const string& clientName, int NIF);
    /**
     * Checks if client c exists.
     * @param c Client to be checked.
     * @return Returns true if client c already exists and false otherwise.
     */
    bool clientExists(clientInfo &c);

    /**
     * Verifies if the string is composed by numbers
     * @param name string to be tested
     * @return True if the string is composed by numbers, False otherwise
     */
    static bool checkIfInt(const string& name);

    /**
    * Reads file with products from online Shop
    * Creates vectorProducts from the class Shop
    * @param name
    */
    void readproducts_file(const string& filename,Supply &s);

    /**
     * Reads file with the real Shops
     * Creates vector of Real Shops
     * @param RSfilename, filename of the RealShop to be read
     * @param s, Supply s from each we will calculate the price of the product
     */
    void read_RealShops(string RSfilename);

    /**
     * Reads file with the statistics
     */
    void read_statistics();

    /**
     * Check if one of the Real Shops has stock to restock the online shop
     * Real shop should not end with a stock smaller than stockmin
     * @param productname, name of the product that we want to restock on the online Shop
     * @param quantity, quantity to be removed from RealShop
     * @return true if one of the real shop has enough stock to be removed, else returns false
     */

    bool checkRealShop(const string& productname, int quantity);

    /**
     * Creates a map with the realshop name and the stock on that shop
     * Searches for the shop with more stock
     * Removes the quantity given in the stock
     * @param productname, name of the product that we want to restock on the online Shop
     * @param quantity, quantity that we want to add to the online Shop
     * @return string with the name of the Real Shop with more stock
     */

    string GetFromRealShop(const string& productname, int quantity);

    /**
     * Function that returns the vector<Product> in the variable "vectorProducts"
     * @return "vectorProducts"
     */
    vector<Product> getvectorProducts();

    /**
     * sets the value of the profitmargin
     * @param profitMargin ( value that, multiplied by the Supplys price, determines the price that the online shop sells one product)
     */

    BST<supplier> getAllSuppliers();

    /**
     * sets the value of the profitmargin
     * @param profitMargin ( value that, multiplied by the suppliers price, determines the price that the online shop sells one product)
     */
    void setProfitMargin(float profitMargin);

    /**
     * Function return the value of the variable "profitmargin"
     * @return "profitmargin"
     */
    float getProfitMargin() const;
    /**
     * Fuction that when the shop closes it updates "clients" and "regclients" vectors with the new clients
     */


    void updateVectors();

    /**
     * updates file from online shop products
     * updates the products file from each Real Shop
     * updates statistics file
     * calls function update_trucks_File
     */
    void updateFile();

    /**
     * prints all products and the respective price
     */
    void showProducts();

    /**
     * prints all RealShops and their information (name, adress, postal code, telephone)
     */
    void showRealShops();

    /**
     * Uses the binary search logic for searcing for a Product by it's name
     * @param prod product object
     * @param product_name name of the product
     * @return -1 if not found product in vector prod with name product_name, else returns position of product with product_name in vector prod
     */
    static int special_Binary_search(const vector <Product>& prod, const string& product_name) ;

    /**
     * Updates Stock of online shop and does the reposition of stock if necessary (updating the real shop stock if removed from there)
     * @param product_name name of the product
     * @param quantity quantity to be restocked
     */
    void updateStock(const string& product_name, int quantity);
    /**
     * Displays on the console the commands to the transaction
     */
    void show_statistics();
    /**
     * Function that wipes the map "statistic" and equals the "ShopWallet" to 0
     */
    void clear_statistics();

    /**
     * Asks the registed client wether he would like to leave a message or not.If he wishes to, he can leave as many as he want.
     * @param c
     */
    void askForMessage(registedClient c);

    /**
    * Returns the registed client which already exists whose name is the same as clientName.
    * @param clientName Name of the client beeing searched.
    * @param NIF Nif of the client beeing searched.
    * @return Registed client who already exists.
    */
    registedClient getRegistedClient(const string& clientName, int NIF);

    /**
     * Function that adds prod to truck with the smallest volume avaiable, but still has enough space for adding the product
     * If there isn't any truck avaiable in such conditions, we create a new truck and add the product to that truct
     * @param prod product to be added to one truck
     * @param quant number of orders
     */
    void add_prod_to_truck(const string &prodName, int quant);

    /**
     *Function that reads trucks file (with information about avaiable stock and capacity of each truck)
     */
    void read_trucks_file();
    /**
     * Updates file of trucks
     */
    void update_trucks_File();
    /**
     * Ships truck if it's 90% full
     */
    void ship_truck();
    /**
     * Function that ships a specific truck chosen by the manager of the shop
     * @param truck
     */
    void manager_shipTruck(int truck);
    /**
     * Function that allows the manager to see the avaiable trucks and to ship the ones desired
     * @param truck
     */
    void manageTrucks();

    /**
     * Function that verifies if a supplier with the same NIF as "s" is in a BST
     * @param sup BST
     * @param s supplier
     * @return The supplier in the BST with the same NIF or a "NULL" supplier if there isn't one
     */
    supplier FoundSupplier(BST<supplier> sup, supplier s);

    /**
     * Funtion that manages the change of each product's current supplier
     */
    void manageSuppliers();
};

/**
 * Function that overloads the operator ">" to compare two "pair<int, int>"
 * @param a pair<int, int>
 * @param b pair<int, int>
 * @return bool(a.second > b.second)
 */
bool operator> (const pair<int, int> &a, const pair<int, int> &b);
/**
 * Function that overloads the operator "<" to compare two "pair<int, int>"
 * @param a pair<int, int>
 * @param b pair<int, int>
 * @return bool(a.second < b.second)
 */
bool operator < (const pair<int, int> &a, const pair<int, int> &b);
