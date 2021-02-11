#include "shop.h"

ostream & operator<<(ostream &out, const ClientIsAlreadyRegistered &cl) //Lança a exceção e dá print ao nome do cliente já registado.
{ out << "You are already registered! " << cl.clientName << endl; return out; }

ostream & operator<<(ostream &out, const clientIsNotNew &c) //Lança a exceção e dá print ao nome do cliente já registado.
{ out << "You are not a new costumer or you might have typed your NIF in the wrong way. Welcome anyways " << c.clientName << "!" <<  endl; return out; }

void Shop::updateVectors(){
    for(unsigned i = 0; i < clients.size(); i++) {
        for(unsigned j = 0; j < regclients.size(); j++) {
            if (clients[i].getNIF() == regclients[j].getNIF())
                if (clients[i].getRegisted() != regclients[j].getRegisted()) {
                    clients.erase(clients.begin() + i);
                    i--;
                }
        }
    }
}
void Shop::addClientsToFile(const string& filename) {
    ofstream clients_file_update;
    stringstream ss;
    clients_file_update.open(filename, std::ostream::trunc);
    for(unsigned i = 0; i < clients.size(); i++){
        ss << clients[i].getClientName() << "," << clients[i].getNIF() << "," << clients[i].getRegisted() << endl;
    }
    for(unsigned j = 0; j < regclients.size(); j++){
        ss << regclients[j].getClientName() << "," << regclients[j].getNIF() << "," << regclients[j].getRegisted() << "," << regclients[j].getID()<< "," << regclients[j].getEmail() << endl;
    }
    if(clients_file_update.fail())
        return ;
    clients_file_update << ss.str();
    clients_file_update.close();
}

void Shop::readInitial_Clients_file(const string& fileName)
{
    string infoClient;
    ifstream clients_file;
    clients_file.open(fileName);
    if(clients_file.is_open()){
        while (getline(clients_file, infoClient))
        {
            vector<string> result;
            stringstream ss(infoClient);
            while (ss.good()) {
                string substr;
                getline(ss, substr, ',');
                result.push_back(substr);
            }
            if(result.size() == 3)
                clients.push_back(clientInfo(result[0],stoi(result[1]),(bool)stoi(result[2])));
            else{
                regclients.push_back(registedClient(result[0],stoi(result[1]),result[4],(bool)stoi(result[3])));
            }
        }
    }
    else{
        cerr << "ERROR OPENING FILE!";
    }
    clients_file.close();
}

void Shop::removeRegistation(clientInfo & c){
    string answer;
    cout << "You are already registered in our shop! "<< endl;
    cout << "Do you wish to continue or do you want to cancel your registation? If so, type 'Cancel': " ;
    getline(cin,answer);
    if(answer != "Cancel") // check for input error
    {
        return;
    }
    for(unsigned i=0;i<regclients.size();i++) {
        if (c.getNIF() == regclients[i].getNIF())
            regclients.erase(regclients.begin() + i);
    }
    cout << "You sucessfuly canceled your registation! " << endl;
}
clientInfo Shop::getClient(int NIF){
    for(auto & c: clients){
        if(NIF == c.getNIF())
            return c;
    }
    return clientInfo();
}

bool Shop::registationDesire(clientInfo &c){
    try{
        if(clientIsRegistered(c.getClientName(),c.getNIF()))
        {
            throw ClientIsAlreadyRegistered(c.getClientName());
        }
    }
    catch(ClientIsAlreadyRegistered &c){
        cout << c;
        return false;
    }
    string answer;
    set<string> correctInputs = {"YES", "Yes","yes","NO","No","no"};
    cout << "------------------------------------------------------"<< endl;
    cout << "|                                                    |"<< endl;
    cout << "|             If you register in our shop            |"<< endl;
    cout << "|           You will have a discount in your         |"<< endl;
    cout << "|                 final price of 15%                 |"<< endl;
    cout << "|                                                    |"<< endl;
    cout << "------------------------------------------------------"<< endl;
    cout << "Do you wish to register in our shop?(YES/NO)" << endl;
    getline(cin,answer);
    while(correctInputs.find(answer) == correctInputs.end()) {
        cout << "That is the wrong input please try again:\n";
        getline(cin,answer);
    }
    if(answer == "YES" || answer == "yes" || answer == "Yes"){
        try{
            if(clientIsRegistered(c.getClientName(),c.getNIF()))
            {
                throw ClientIsAlreadyRegistered(c.getClientName());
            }
        }
        catch(ClientIsAlreadyRegistered &c){
            cout << c;
            return false;
        }
        cout << "That was a wise decision! Welcome to our shop." << endl;
        return true;
    }
    else{
        return false;
    }
}

bool Shop::checkIfInt(const string& name){
    for(auto c: name){
        if(!isdigit(c))
            return false;}
    return true;
}

bool Shop::checkCommas(string name){
    for(char c : name) {
        if(c == ',')
            return true;
    }
    return false;
}

clientInfo Shop::initialInfo(){
    string name;
    string NIF;
    cout << "Welcome to our shop! We need to get some information from you."<<endl;
    cout << "Please enter your name: "<< endl;
    getline(cin,name);
    while (cin.fail() || checkCommas(name)) // check for input error
    {
        cout << "Wrong input. Try again!" << endl;
        getline(cin,name);
    }
    cout << "We also need you to tell us your NIF: "<< endl;
    getline(cin,NIF);
    while(!checkIfInt(NIF) || NIF.size() != 9 || clientWrongNIF(name,stoll(NIF))){
        cout << "Your either typing the wrong input or that NIF does not belong to you." << endl;
        getline(cin,NIF);
    }
    try{
        if(clientAlreadyExists(name, stoll(NIF)))
        {
            throw clientIsNotNew(name);
        }
    }
    catch(clientIsNotNew &c){
        cout  << c;
        return getClient(stoll(NIF));
    }
    return clientInfo(name,stoll(NIF),0);
}

bool Shop::clientWrongNIF(string clientName, int NIF){
    for(auto & c: clients){
        if(c.getClientName() != clientName)
            if(c.getNIF() == NIF)
                return true;
    }
    return false;
}

bool Shop::clientAlreadyExists(const string& clientName, int NIF){
    for(auto & cl: clients){
        if(cl.getClientName() == clientName)
            if(cl.getNIF() == NIF)
                return true;
    }
    return false;
}

bool Shop::clientExists(clientInfo &c){
    for(auto & cl: clients){
        if(cl.getClientName() == c.getClientName())
            if(cl.getNIF() == c.getNIF())
                return true;
    }
    return false;
}

bool Shop::clientIsRegistered(const string& clientName, int NIF){
    for(auto & c: regclients){
        if(c.getClientName() == clientName)
            if(c.getNIF() == NIF)
                return true;
    }
    return false;
}

void Shop::addClient(clientInfo &c){
    clients.push_back(c);
}

void Shop::addRegisteredClient(const registedClient& c){
    regclients.push_back(c);
}

registedClient Shop::registation(clientInfo &c){
    string email;
    string name = c.getClientName();
    const regex pattern(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    cout << "In order to register we need you to tell us your email.\nYou can write it here: "<< endl;
    getline(cin,email);
    while (!regex_match(email, pattern)){
        cout << "Please enter correct email format:\n" << endl;
        getline(cin,email);
    }
    c.setRegisted(true);
    return registedClient(name,c.getNIF(),email,c.getRegisted());
}


clientInfo Shop::allClientsInfo(){
    clientInfo  m;
    registedClient c;
    m = initialInfo();
    if(!clientExists(m))
        addClient(m);
    if(clientIsRegistered(m.getClientName(),m.getNIF())){
        removeRegistation(m);
    }
    else if(registationDesire(m)){
        c = registation(m);
        addRegisteredClient(c);
        return c;
    }
    return m;
}

Shop::Shop(Supplier &s) {
    readproducts_file("products.txt",s);
    read_RealShops("real_shops.txt", s);
    read_statistics();
}

void Shop::setProfitMargin(float profitMargin){
    this->profitMargin = profitMargin;
}

float Shop::getProfitMargin() const{
    return profitMargin;
}

void Shop::readproducts_file(const string& fileName, Supplier &s)
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
            vectorProducts.push_back(c);
        }
    }
    else{
        cerr<< "Sorry!! We had a problem showing our products";
    }
    QuickSort <Product> (&vectorProducts, 0, vectorProducts.size() - 1, true);
    product_file.close();
}

void Shop::read_RealShops(string RS_filename, Supplier &s) {
    string filename;
    ifstream file_realshops(RS_filename);
    string adress;
    string postal_code;
    string telephone;

    if (file_realshops.is_open()) {
        while ((getline(file_realshops, filename, ';') && getline(file_realshops, adress, ';')  && getline(file_realshops, postal_code, ';')) && getline(file_realshops, telephone)){
            filename.pop_back();
            filename= "shop_" + filename + ".txt";
            adress.pop_back();
            postal_code.pop_back();
            telephone.pop_back();
            RealShop shop(filename, adress, postal_code, telephone, profitMargin,s);
            realShops.push_back(shop);
        }
    }
    else{
        cerr << "Soryy!! We had a problem accessing our Real Shops";
    }
    file_realshops.close();
}

void Shop::read_statistics() {
    ifstream file;
    string productName, string_timesSold, input;
    int timesSold;
    for(int c=0; c<vectorProducts.size(); c++){
        statistic[vectorProducts[c].getproductName()] = 0;
    }
    file.open("BuyNowStatistics.txt");
    if (file.is_open()) {
        getline(file, input, '\n');
        ShopWallet = stof(input.substr(8, input.size()));
        getline(file, input, '\n');
        while (getline(file, productName, ';') && getline(file, string_timesSold)) {
            timesSold = stoi(string_timesSold);
            productName.pop_back();
            statistic[productName] = timesSold;
        }
    }
    else {
        cerr << "Soryy!! We had a problem accessing our statistics";
    }
    file.close();
}

void Shop::showRealShops(){
    vector<RealShop> :: iterator it;
    for(it = realShops.begin(); it != realShops.end(); it++){
        int size = 70;
        string nome = it->getFileName();
        nome.erase(0,5);
        nome.erase(nome.end()-4, nome.end());
        size = size - nome.size()/2;
        cout << setfill('-') << setw(size) << nome << setfill('-') << setw(size) << '-' << endl;
        cout << *it;
        cout << endl << endl;
    }
}

void Shop::showProducts() {
    cout << "---------------------------------PRODUCTS---------------------------------" << endl;
    for(const auto & x:vectorProducts){
        cout << x;
    }
}

bool Shop::checkRealShop(const string& productname, int quantity) {
    vector<RealShop>::iterator itr;
    for (const auto& x: realShops) {
        int pos = special_Binary_search(x.get_vector_products(), productname);
        if (x.get_vector_products().at(pos).getStock() - quantity > x.getstockOK()) {
            return true;
        }
    }
    return false;
}

string Shop:: GetFromRealShop(const string& productname, int quantity) {
    int BiggestStock = 0;
    string BiggestRealShop;
    map<string, int> stocks;
    for (const auto & x: realShops) {
        int pos = special_Binary_search(x.get_vector_products(), productname);
        if (x.get_vector_products().at(pos).getproductName() == productname) {
            stocks[x.getFileName()] = x.get_vector_products().at(pos).getStock();
        }
    }
    for (const auto & x: stocks) {
        if (x.second > BiggestStock) {
            cout << endl;
            BiggestStock = x.second;
            BiggestRealShop = x.first;
        }
    }


    for (auto &x : realShops) {
        if (x.getFileName() == BiggestRealShop) {
            int pos = special_Binary_search(x.get_vector_products(), productname);
            if (x.get_vector_products().at(pos).getproductName() == productname) {
                x.RemoveStock(pos, quantity);
                return BiggestRealShop;
            }
        }
    }
    return "";
}

void Shop::updateStock(const string& product_name, int quantity) {
    ofstream file;
    stringstream ss;
    string rs;
    int pos = special_Binary_search(vectorProducts, product_name);
    vectorProducts.at(pos).removeStock(quantity);
    statistic[product_name]+=quantity;
    ShopWallet += vectorProducts.at(pos).getPrice()*quantity;
    if(vectorProducts.at(pos).getStock() < stockMin){
        time_t now = time(nullptr);
        char *dt = ctime(&now);
        if(checkRealShop(product_name, 30)){
            rs = GetFromRealShop(product_name, 30);
            vectorProducts.at(pos).addStock(30);
            rs = rs.substr(0, rs.size()-4);
            ss << endl << "\t   Shop <---------------- " << rs  << endl;
            ss << "\t\t     30 x " << vectorProducts.at(pos).getproductName() << "\n\n\n";
            ss << "Date: " << dt << endl;
            ss << "---------------------------------------------------------------" << endl;
        }
        else{
            vectorProducts.at(pos).addStock(30);
            ShopWallet -= (vectorProducts.at(pos).getPrice() * 30)/profitMargin;

            ss << endl << "\t   Shop <---------------- Supplier" << endl;
            ss << "\t\t     30 x " << vectorProducts.at(pos).getproductName() << endl;
            ss << "\t              (-" << vectorProducts.at(pos).getPrice()/profitMargin << "€)\n\n\n";
            ss << "Date: " << dt << endl;
            ss << "---------------------------------------------------------------" << endl;
        }
        file.open("ShopStockTransactions.txt", fstream::app);
        if (file.is_open()){
            file << ss.str();

        }
        else{
            cerr << "Error opening 'ShopStockTransactions.txt'!";
        }
        file.close();
    }
}

void Shop::updateFile(){
    vector <RealShop> :: iterator it;
    ofstream file;
    file.open("products.txt",ofstream::trunc);
    if(file.fail()){
        cerr << "Error opening file!";
        return;
    }
    for(const auto & vectorProduct : vectorProducts){
        file << vectorProduct.getproductName() << " ; " << vectorProduct.getStock() << endl;
    }
    file.close();

    for(it = realShops.begin(); it != realShops.end(); it++){
        file.open(it ->getFileName(),ofstream::trunc);
        if(file.fail()){
            cerr << "Error opening file!";
            return;
        }
        for(const auto& x: it->get_vector_products()){
            file << x.getproductName() << " ; " << x.getStock() << endl;
        }
        file.close();
    }

    file.open("BuyNowStatistics.txt");
    if(file.fail()){
        cerr << "Error opening file!";
        return;
    }
    file << "Profit: " << ShopWallet  << endl;
    file << "Prod. ; Times Sold" << endl;
    for(const auto & x: statistic){
        if (x.second != 0)
            file << x.first << " ; " << x.second << endl;
    }
    file.close();
}

void Shop::show_statistics(){

    double percentagem;
    int totalProdVendidos = 0;
    for(const auto& x: statistic){
        totalProdVendidos += x.second;
    }
    cout << "Profit:   " << ShopWallet << "€ \n\n";
    vector<pair<string, int>> stats;
    for (const auto & x: statistic){
        stats.push_back(x);
    }
    QuickSort<pair<string, int>>(&stats, 0, stats.size()-1, true);
    for (const auto& x: stats) {
        percentagem = (x.second*100)/totalProdVendidos;
        int size = 25;
        size = size - x.first.size();
        cout << x.first << setfill(' ') << setw(size);
        for (int i = 0; i < percentagem; i++) {
            cout << "|";
        }
        cout << "  " << percentagem << "% (sold:" << x.second << ")" << endl;
    }
}

void Shop::clear_statistics() {
    statistic.clear();
    ShopWallet = 0;
}

vector<Product> Shop::getvectorProducts() {
    return vectorProducts;
}

int Shop::special_Binary_search(const vector<Product>& prod, const string& product_name) {
    int left = 0, right = prod.size() - 1;
    while (left <= right)
    {
        int middle = (left + right) / 2;
        if (prod[middle].getproductName() < product_name)
            left = middle + 1;
        else if (product_name < prod[middle].getproductName())
            right = middle -1;
        else
            return middle;
    }
    return -1;
}

bool operator < (const pair<int, int> &a, const pair<int, int> &b) {
    return a.second < b.second;
}

bool operator > (const pair<int, int> &a, const pair<int, int> &b) {
    return a.second > b.second;
}