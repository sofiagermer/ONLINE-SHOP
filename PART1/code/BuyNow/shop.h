#pragma once

#include <fstream>
#include <iomanip>

#include "client.h"
#include "product.h"
#include "fstream"
#include "sstream"
#include "ctime"

#include "realshops.h"
#include "QuickSort.h"


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

    unsigned int stockMin = 5;
    float profitMargin = 1.45;
public:
    /**
     * Constructor of class Shop
     */
    Shop(){};
    /**
     * Creates the vector of products from the online shop.
     * Creates the vector of real shops and for each real shop creates their own vector of products.
     * If there is no previous data it creates a map with the statistics all initialized at 0,else it reads from the BuyNowStatistics.txt file.
     * @param s  Supplier's file containing their products and prices.
     */
    Shop(Supplier &s);
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
    void removeRegistation(clientInfo & c);
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
     * @param clientName Name of client to be checked.
     * @param NIF NIF of client to be checked.
     * @return Return true if client is already registered.
     */
    bool clientIsRegistered(const string& clientName, int NIF);
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
    static bool checkIfInt(const string& name);

    /**
    * Reads file with products from online Shop
    * Creates vectorProducts from the class Shop
    * @param name
    */
    void readproducts_file(const string& filename,Supplier &s);

    /**
     * Reads file with the real Shops
     * Creates vector of Real Shops
     * @param RSfilename, filename of the RealShop to be read
     * @param s, supplier s from each we will calculate the price of the product
     */
    void read_RealShops(string RSfilename,Supplier &s);

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
