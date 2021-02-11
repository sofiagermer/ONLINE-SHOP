#pragma once

#include <iostream>
#include <vector>
#include "product.h"
#include <fstream>
#include <stdio.h>
#include "QuickSort.h"
#include "supplier.h"
using namespace std;

class RealShop{
private:
    /**
     * Vector that keeps the RealShop's products
     */
    vector<Product> vector_products;
    /**
     * Name of the RealShop's file
     */
    string filename;
    /**
     * Value of the minimum stock for every product in the RealShop
     */
    int stockOK = 10;
    /**
     * RealShop's adress
     */
    string adress;
    /**
     * RealShop's postal code
     */
    string postal_code;
    /**
     * RealShop's telephone number
     */
    string telephone;
public:
    /**
     * Constructor that initializes the variables in RealShop
     * @param filename
     * @param adress
     * @param postal_code
     * @param telefone
     * @param profitMargin
     * @param s Supplier
     */
    RealShop(string filename, string adress, string postal_code, string telefone , float profitMargin,  Supplier s);
    /**
     * Read products file of a Real Shop and creates it's vector of products
     * @param fileName
     * @param s Supplier
     * @param profitMargin
     */
    void read_products_file(const string& fileName, Supplier &s, float profitMargin);
    /**
     * Removes the a given quantity to the stock of the product at position pos of the vector_products
     * @param pos position of the product which the stock is going to be reduced
     * @param quantity quantity of stock to be removed
     */
    void RemoveStock(int pos, int quantity);
    /**
     * Function that returns the string in the variable "filename"
     * @return filename
     */
    string getFileName() const;
    /**
     * Function that returns the value in the variable "stockOK"
     * @return stockOK
     */
    unsigned int getstockOK() const;
    /**
     * Function that returns the vector<Product> in the variable "vector_products"
     * @return vector_products
     */
    vector <Product> get_vector_products() const;
    /**
     * Funtion that overloads the operator "<<" to display the RealShop's information
     * @param out output destination
     * @param realShop Variable you want to output
     * @return "out" argument
     */
    friend ostream& operator<<(ostream& out, const RealShop &realShop);
};
