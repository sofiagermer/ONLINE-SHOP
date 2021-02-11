#include "supplier.h"

Supplier::Supplier(string fileName){
    string productsinfo;
    ifstream supplier_file;
    supplier_file.open(fileName);
    if(supplier_file.is_open())
        while (getline(supplier_file, productsinfo))
        {
            vector<string> result;
            stringstream ss(productsinfo);
            while (ss.good()) {
                string substr;
                getline(ss, substr, ';');
                result.push_back(substr);
            }
            pair<string,float> a(result[0],stof(result[1]));
            supplierPrices.insert(a);
        }
    else{
        cerr << "ERROR OPENING FILE!";
    }
    supplier_file.close();
}

map<string, float> Supplier::getPrices() const{
    return supplierPrices;
}

