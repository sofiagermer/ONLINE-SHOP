#include "product.h"

#include <sstream>

Product::Product(){}

Product::Product(string productName, float price, int stock, int volume, BST<supplier> suppliers){
    this -> productName = move(productName);
    this -> suppliers = suppliers;
    this -> stock = stock;
    this -> volume = volume;
    this -> price = price;
    CurrentSupplier = *suppliers.begin();
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

int Product::getVolume() const {
    return volume;
}

supplier Product::getCurrentSupplier() {
    return CurrentSupplier;
}

BST<supplier> Product::getSuppliers(){
    return suppliers;
}

void Product::setStock(int stock){
   this->stock = stock;
}

void Product::setProductname(string name) {
    productName = name;
}

bool Product::setCurrentSupplier(supplier s) {
    if (suppliers.find(s).getNIF() == s.getNIF()){
        CurrentSupplier = suppliers.find(s);
        return true;
    }
    return false;
}

bool Product::CheckSupplier(){
    if (CurrentSupplier.getQuantity() == 0) {
        return false;
    }
    else
        return true;
}

int Product::BuyFromSupplier(const float ProfitMargin, float &cost){
    int units;
    price = CurrentSupplier.getPrice() * ProfitMargin;
    if (CurrentSupplier.getQuantity() >= 30){
        cost = CurrentSupplier.getPrice()*30;
        stock+=30;
        units = 30;
        CurrentSupplier.removeQuantity(30);
    }
    else{
        cost = CurrentSupplier.getPrice()*CurrentSupplier.getQuantity();
        stock+= CurrentSupplier.getQuantity();
        units = CurrentSupplier.getQuantity();
        CurrentSupplier.removeQuantity(CurrentSupplier.getQuantity());
    }
    BSTItrIn<supplier> it(suppliers);
    while (!it.isAtEnd()){
        if (it.retrieve() == CurrentSupplier){
            suppliers.remove(it.retrieve());
            break;
        }
        it.advance();
    }
    suppliers.insert(CurrentSupplier);
    return units;
}

void Product::addStock(int stockToAdd) {
    stock = stock + stockToAdd;
}

void Product::removeStock(int stockToRemove) {
    stock = stock - stockToRemove;
}

void Product::showSuppliers() {
    BSTItrIn<supplier> it(suppliers);
    while(!it.isAtEnd()){
        cout << it.retrieve();
        cout << "------------" << endl;
        it.advance();
    }
}

void Product::showCurrentSupplier() {
    cout << "Current Supplier -> Name: " << CurrentSupplier.getName() << " | NIF: " << CurrentSupplier.getNIF() << endl << endl;
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