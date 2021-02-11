#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <map>
#include <sstream>

#include "bst.h"

using namespace std;

class supplier {
    /**
     * Supplier's name
     */
    string name;
    /**
     * Supplier's NIF
     */
    long long int NIF;
    /**
     * Name of the product that the supplier is selling
     */
    string productname;
    /**
     * price of the product
     */
    float price;
    /**
     * quantity of the product
     */
    int quantity;

public:
    /**
     * default constructor
     */
    supplier() =default;

    /**
     * Supplier's contructor
     * @param name name
     * @param NIF NIF
     * @param prodname productname
     * @param price price
     * @param quant quantity
     */
    supplier(string name, long long int NIF, string prodname, float price, int quant);

    /**
     * Function that returns the supplier's name
     * @return name
     */
    string getName() const;

    /**
     * Function that returns the supplier's NIF
     * @return NIF
     */
    long long int getNIF() const;

    /**
     * Function that returns the supplier's product name
     * @return product name
     */
    string getProductname() const;

    /**
     * Function that returns the supplier's product price
     * @return price
     */
    float getPrice() const;

    /**
     * Function that returns the supplier's product quantity
     * @return quantity
     */
    int getQuantity() const;

    /**
     * Function updates the supplier's NIF
     * @param n new NIF
     */
    void setNIF(long long int n);

    /**
     * Function that removes product's quantity
     * @param q quantity to be removed
     */
    void removeQuantity(int q);

    /**
     * Overload of the operator '<' to compare 2 suppliers
     * @param s another supplier
     * @return (Check function)
     */
    bool operator<(const supplier &s) const;

    /**
     * Overload of the operator '==' to compare 2 suppliers
     * @param s
     * @return true if both have the same NIF
     */
    //bool operator==(const supplier &s) const;

    /**
     * Overload of the operator '<<' to display on the console the supplers info
     * @param out output
     * @param sup supplier to be written
     * @return "out" parameter
     */
    friend ostream &operator<<(ostream &out, const supplier &sup);

    friend bool operator==(const supplier &s1, const supplier &s2);
};

class Supply{
    /**
     * Vector of all available suppliers
     */
    vector<supplier> suppliers;
public:
    /**
     * Supplier constructor
     * @param filename Name of the file with the info of all suppliers
     */
    Supply(string filename);

    /**
     * Function that returns all the suppliers for a given product
     * @param productname product's name
     * @return all the suppliers for a the product "productname"
     */
    BST<supplier> getSuppliers(string productname);

    /**
     * Function that updates the suppliers' vector
     * @param s BST with all the suppliers
     */
    void setSuppliers(BST<supplier> s);

    /**
     * Funtion that saves all the suppliers info to a file
     * @param filename file's name
     */
    void saveSupplier(string filename);
};