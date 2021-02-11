#include "realshops.h"

RealShop::RealShop(string filename, string adress, string postal_code, string telephone, float profitMargin, Supplier s) {
    read_products_file(filename, s, profitMargin);
    this -> adress = move(adress);
    this ->postal_code = move(postal_code);
    this -> telephone = move(telephone);
    this -> filename = filename;
}

void RealShop::read_products_file(const string& fileName, Supplier &s, float profitMargin)
{
    string name;
    float price;
    int stock;
    string string_stock;
    ifstream product_file;
    product_file.open(fileName);
    if(product_file.is_open()){
        while (getline(product_file, name, ';')  && getline(product_file, string_stock))
        {
            stock = stoi(string_stock);
            name.pop_back();
            price = s.getPrices()[name] * profitMargin;
            Product c(name, price,stock);
            vector_products.push_back(c);
        }
    }
    else{
        cerr<< "Sorry!! We had a problem showing our products";

    }
    QuickSort <Product> (&vector_products, 0, vector_products.size() - 1, true);
    product_file.close();
}

void RealShop::RemoveStock(int pos, int quantity){
    vector_products.at(pos).removeStock(quantity);
}

string RealShop::getFileName() const {
    return filename;
}

unsigned int RealShop::getstockOK() const {
    return stockOK;
}

ostream &operator<<(ostream &out, const RealShop &realShop) {
    out << "Adress: " << realShop.adress << endl;
    out << "Postal Code: " << realShop.postal_code << endl;
    out << "Contact: " << realShop.telephone << endl;
    return out;
}

vector<Product> RealShop::get_vector_products() const{
    return vector_products;
}

