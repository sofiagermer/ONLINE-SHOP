#pragma once


#include <iostream>
#include <vector>
#include <iomanip>

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
public:
    Product();
    /**
     * Product constructor
     * @param productName
     * @param price
     * @param stock
     */
    Product(string productName, float price, int stock);
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
     * adds stockToAdd to stock
     * @param stockToAdd
     */
    void addStock(int stockToAdd);
    /**
     * removes stockToRemove to stock
     * @param stockToRemove
     */
    void removeStock(int stockToRemove);
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

