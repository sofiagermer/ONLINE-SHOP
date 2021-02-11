#include "supplier.h"

bool operator==(const supplier &s1, const supplier &s2){
    return s1.getNIF() == s2.getNIF();
}

supplier::supplier(string name, long long NIF, string prodname, float price, int quant) {
    this->name = name;
    this->NIF = NIF;
    productname = prodname;
    this->price = price;
    quantity = quant;
}

string supplier::getName() const{return name;}

long long int supplier::getNIF() const{return NIF;}

string supplier::getProductname() const{return productname;}

float supplier::getPrice() const{return price;}

int supplier::getQuantity() const{return quantity;}

void supplier::setNIF(long long n) {NIF = n;}

void supplier::removeQuantity(int q) {
    quantity -= q;
}

bool supplier::operator<(const supplier &s) const{
    if (price == s.price){
        if (quantity == s.quantity){
            if (name == s.name){
                return NIF < s.NIF;
            }
            return name < s.name;
        }
        return quantity > s.quantity;
    }
    return price < s.price;
}

//bool supplier::operator==(const supplier &s) const{
   // return getNIF() == s.getNIF();
//}

ostream &operator<<(ostream &out, const supplier &sup){
    out << "Name:   " << sup.name << endl;
    out << "NIF:    " << sup.NIF << endl;
    out << "Prod.:  " << sup.productname << endl;
    out << "Price:  " << sup.price << endl;
    out << "Quant.: " << sup.quantity << endl;
    return out;
}

Supply::Supply(string filename) {
    string input;
    string name, prodname;
    long long int NIF;
    float price;
    int quantity;
    ifstream file;
    file.open(filename);
    if(file.is_open()) {
        while (getline(file, name, ';')) {
            getline(file, input, ';');
            NIF = stoll(input);
            getline(file, prodname, ';');
            getline(file, input, ';');
            price = stof(input);
            getline(file, input, '\n');
            quantity = stoi(input);
            suppliers.push_back(supplier(name, NIF, prodname, price, quantity));
        }
        file.close();
    }
    else{
        cerr << "ERROR OPENING FILE!";
    }
}

BST<supplier> Supply::getSuppliers(string productname){
    BST<supplier> AvailableSuppliers(supplier("", 0, "", 0.0, 0));
    AvailableSuppliers.makeEmpty();
    for (auto &x : suppliers){
        if (x.getProductname() == productname){
            AvailableSuppliers.insert(x);
        }
    }
    return AvailableSuppliers;
}

void Supply::setSuppliers(BST<supplier> s) {
    BSTItrIn<supplier> it(s);
    suppliers.clear();
    while(!it.isAtEnd()){
        suppliers.push_back(it.retrieve());
        it.advance();
    }
}

void Supply::saveSupplier(string filename) {
    stringstream ss;
    ofstream f;
    for(auto &x : suppliers){
        ss << x.getName() << ";" << x.getNIF() << ";" << x.getProductname() << ";" << x.getPrice() << ";" << x.getQuantity() << endl;
    }
    f.open(filename);
    f << ss.str();
    f.close();
}