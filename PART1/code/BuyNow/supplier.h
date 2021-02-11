#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <map>
#include <sstream>

using namespace std;

class Supplier{
    /**
     * Supplier's prices for each product
     */
    map<string, float> supplierPrices;
public:
    /**
     * Returns the Map "supplierPrice"
     * @return "supplierPrices"
     */
    map<string, float> getPrices() const;
    /**
     * Constructor reads the file "fileName" and initializes the map "supplierPrices" with the information given by the file
     * @param fileName Name of the file with the Supplier's prices for each product
     */
    Supplier(string fileName);
};
