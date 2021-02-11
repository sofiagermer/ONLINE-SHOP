#pragma once

#include <ctime>
#include <map>
#include <stack>

#include "shop.h"
#include "payment.h"
#include "client.h"



using namespace std;

class Transaction{
    /**
     * Transaction's total price
     */
    float totalPrice=0;
    /**
     * Map that contains the list of all products selected by the user
     */
    map<string, unsigned int > ShoppingCart;
    /**
     * stack that contains the products and quantities used in the operation chosen by the user
     */
    stack <pair<string, unsigned>> history;
    /**
     * stack that contains the type of operations done by the user, removal(false) or addition(true) of a product
     */
    stack <bool> RemOrAdd;
public:
    /**
     * Default constructor
     */
    Transaction() = default;
    /**
     * Function that adds a product to the ShoppingCart
     * @param prod_name Product's name
     * @param q Quantity of the product to be added
     * @param s The OnlineShop
     */
    void addProduct(string prod_name, unsigned int q, Shop &s);
    /**
     * Function that undoes the last action done by the user
     * @param s The OnlineShop
     */
    void Undo(Shop &s);
    /**
     * Function that removes a product from the ShoppingCart
     * @param prod_name Product's name
     * @param q Quantity of the product to be removed
     * @param s The OnlineShop
     */
    void RemoveProduct(string prod_name, unsigned int q,Shop &s);
    /**
     * Function that removes all the elements of a certain product from the ShoppingCart
     * @param prod_name Product's name
     * @param s The OnlineShop
     */
    void RemoveProduct(string prod_name, Shop &s);
    /**
     * Function that gets the necessary inputs from the user to add a product to the ShoppingCart
     * @param prod_name Product's name
     * @param q Quantity of the product to be added
     * @param s The OnlineShop
     * @return Returns False if the action was cancelled midway, True if otherwise
     */
    bool getInputforAdd(string &prod_name, int &q, Shop & s);
    /**
     * Function that gets the necessary inputs from the user to remove a product from the ShoppingCart
     * @param prod_name Product's name
     * @param q Quantity of the product to be removed
     * @param all Passes as True if the user chose to remove all the elements of a products from the ShoppingCart, False if otherwise
     * @return Returns False if the action was cancelled midway, True if otherwise
     */
    bool getInputforRemove(string prod_name, int &q, bool all);
    /**
     * Function that gets the necessary inputs from the user to process the payment
     * @param c Client who's making the purchase
     * @param s The Onlineshop
     */
    void getPaymentMethod(clientInfo &c,Shop & s);
    /**
     * Displays on the console the ShoppingCart and the totalPrice of the transaction at that moment
     * @param s The Onlineshop
     */
    void showProductsCar(Shop &s) const;
    /**
     * Displays on the console the commands to the transaction
     */
    void showCommands() const;
    /**
     * Function where the user is provived with the tools use the OnlineShop
     * @param s The Onlineshop
     * @return Returns False if the action was cancelled midway or the user ended his trasaction with no items bought, True if otherwise
     */
    bool loop(Shop & s);
    bool MBwayPayment(string answer, bool paymentcheck,clientInfo &c, Shop & s);
};