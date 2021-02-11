#include "product.h"

#include <sstream>

Product::Product(){}

Product::Product(string productName, float price, int stock) {
    this -> productName = move(productName);
    this -> price = price;
    this -> stock = stock;
}
string Product::getproductName() const{
    return productName;
}

float Product::getPrice() const {
    return price;
}

int Product::getStock() const {
    return stock;
}

void Product::addStock(int stockToAdd) {
    stock = stock + stockToAdd;
}

void Product::removeStock(int stockToRemove) {
    stock = stock - stockToRemove;
}

//OVERLOADING << FOR DISPLAING PRODUCT INFORTMATION
ostream& operator<<(ostream& out, const Product & prod) {
    int size = 70;
    size = size - prod.getproductName().size();
    out << prod.getproductName()  <<  setfill('-') << setw(size) <<  " " << setprecision(2) << fixed << prod.getPrice() << "€" << endl;
    return out;
}


//COMPARES TWO PRODUCTS ON ALFABETIC ORDER
bool operator<(const Product &prod1, const Product &prod2){
    return prod1.getproductName() < prod2.getproductName();
}

bool operator>(const Product & prod1, const Product & prod2)
{
    return prod1.getproductName() > prod2.getproductName();
}

bool operator==(const Product &prod1, const Product &prod2){
    return prod1.getproductName() == prod2.getproductName();
}