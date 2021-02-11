#pragma once


#include <iostream>
#include <vector>
#include <iomanip>

#include "supplier.h"
using namespace std;


class Product{
    /**
     * Product's name
     */
    string productName;
    /**
     * Product's price
     */
    float  price{};
    /**
     * Product's stock
     */
    int stock{};
    /**
     * Product's packaging volume
     */
    int volume;
    /**
     * Product's available suppliers
     */
    BST<supplier> suppliers = BST<supplier>(supplier());
    /**
     * Product's current supplier
     */
    supplier CurrentSupplier;
public:
    Product();
    /**
     * Product constructor
     * @param productName
     * @param price
     * @param stock
     * @param volume
     */
    Product(string productName, float price, int stock, int volume, BST<supplier> suppliers);
    /**
     * Function that returns the value "productname"
     * @return productName
     */
    string getproductName() const;
    /**
     * Function that returns the value "price"
     * @return price
     */
    float getPrice() const;
    /**
     * Function that returns the value "stock"
     * @return stock
     */
    int getStock() const;
    /**
     * Function that returns the value "volume"
     * @return volume
     */

    int getVolume() const;
    /**
     * adds stockToAdd to stock
     * @param stockToAdd
     */
    supplier getCurrentSupplier();

    /**
     * Function that returns the available suppliers
     * @return suppliers
     */
    BST<supplier> getSuppliers();

    /**
     * Function that updates the product's name
     * @param name Product's new name
     */
    void setProductname(string name);

    /**
     * Function that updates the product's stock
     * @param name Product's new stock
     */
    void setStock(int stock);

    /**
     * Function that updates the product's current supplier
     * @param name Product's new current supplier
     */
    bool setCurrentSupplier(supplier s);

    /**
     * Verifies if the Current Supplier has product to be bought
     * @return true if he has, false otherwise
     */
    bool CheckSupplier();

    /**
     * Function that buys product from the Current Supplier
     * @param ProfitMargin profit margin
     * @param cost variable passed by reference to save the expense of the purchase
     * @return returns the numbers of units bought to the supplier
     */
    int BuyFromSupplier(const float ProfitMargin, float &cost);

    /**
     * Function that adds stock
     * @param stockToAdd stock to be added
     */
    void addStock(int stockToAdd);
    /**
     * removes stockToRemove to stock
     * @param stockToRemove
     */
    void removeStock(int stockToRemove);

    /**
     * Displays on the console the available Suppliers
     */
    void showSuppliers();

    /**
     * Displays on the console the Current Supplier
     */
    void showCurrentSupplier();

    /**
     * Used for making the dispaly of products easier
     * @param out
     * @param prod
     * @return out
     */
    friend ostream& operator<<(ostream& out, const Product & prod);
    /**
     * Used for comparing two products based on alphabetical order
     * @param prod1
     * @param prod2
     * @return true if product1 has a smaller name than product 2, else returns false
     */
    friend bool operator<(const Product &prod1, const Product &prod2);
    /**
     * Used for comparing two products based on alphabetical order
     * @param prod1
     * @param prod2
     * @return true if product1 has a biggger name than product 2, else returns false
     */
    friend bool operator>(const Product &prod1, const Product &prod2);
    /**
     * Used for comparing two products based on their names
     * @param prod1
     * @param prod2
     * @return true if prod1 and prod2 have the same name
     */
    friend bool operator==(const Product &prod1, const Product &prod2);
};

