#include "transaction.h"

void Transaction::addProduct(string prod_name, unsigned int q, Shop &s) {
    int pos = s.special_Binary_search(s.getvectorProducts(), prod_name);
    totalPrice += s.getvectorProducts().at(pos).getPrice()*q;
    history.push(make_pair(prod_name, q));
    RemOrAdd.push(true);
    if (ShoppingCart.find(prod_name) == ShoppingCart.end()){
        ShoppingCart[prod_name] = q;
    }
    else{
        ShoppingCart[prod_name] += q;
    }
}


void Transaction::Undo(Shop &s) {
    if (history.empty()){
        return;
    }
    auto lastAction = history.top();
    int pos = s.special_Binary_search(s.getvectorProducts(), lastAction.first);
    if (RemOrAdd.top()) {
        totalPrice -= s.getvectorProducts().at(pos).getPrice()*lastAction.second;
        ShoppingCart[lastAction.first] -= lastAction.second;
        if (ShoppingCart[lastAction.first] == 0) {
            ShoppingCart.erase(lastAction.first);
        }

    }
    else{
        totalPrice += s.getvectorProducts().at(pos).getPrice() *lastAction.second;
        if (ShoppingCart.find(lastAction.first) == ShoppingCart.end()){
            ShoppingCart[lastAction.first] = lastAction.second;
        }
        else{
            ShoppingCart[lastAction.first] += lastAction.second;
        }
    }
    history.pop();
    RemOrAdd.pop();
}

void Transaction::RemoveProduct(string prod_name, unsigned int q, Shop &s) {
    int pos = s.special_Binary_search(s.getvectorProducts(), prod_name);
    totalPrice -= s.getvectorProducts().at(pos).getPrice() * q;
    ShoppingCart[prod_name] -= q;
    history.push(make_pair(prod_name, q));
    RemOrAdd.push(false);
    if (ShoppingCart[prod_name] == 0)
        ShoppingCart.erase(prod_name);
}

void Transaction::RemoveProduct(string prod_name,Shop &s) {
    int pos = s.special_Binary_search(s.getvectorProducts(), prod_name);
    totalPrice -= s.getvectorProducts().at(pos).getPrice()*ShoppingCart[prod_name];
    history.push(make_pair(prod_name, ShoppingCart[prod_name]));
    RemOrAdd.push(false);
    ShoppingCart.erase(prod_name);
}

void Transaction::showProductsCar(Shop &s) const {
    cout << "---------------------------------------------------------------------" << endl;
    for (auto & x: ShoppingCart){
        int pos = s.special_Binary_search(s.getvectorProducts(), x.first);
        cout << endl << x.first << endl << x.second << " x " << s.getvectorProducts().at(pos).getPrice() << "     " << x.second*s.getvectorProducts().at(pos).getPrice() << "\n";
    }
    cout << endl << "TOTAL:  " << totalPrice << endl;
    cout << "---------------------------------------------------------------------" << "\n\n";

}

void Transaction::showCommands() const {
    cout << "---------------------------------------------------------------------" << endl;
    cout << "Commands:" << endl;
    cout << "'P' -> Show products." << endl;
    cout << "'C' -> Show shopping cart." << endl;
    cout << "'A' -> Add a product." << endl;
    cout << "'R' -> Remove quantity Q of product P." << endl;
    cout << "'D' -> Removes product P from cart." << endl;
    cout << "'U' -> Undoes the last operation." << endl;
    cout << "'#' -> End shopping or cancel last operation." << endl;
    cout << "'X' -> Cancels the transaction and leaves the shop." << endl;
    cout << "---------------------------------------------------------------------" << endl;
}

bool Transaction::getInputforAdd(string &prod_name, int &q, Shop & s) {
    string in;
    int added;
    int pos;
    cout << "Product? ";
    cin >> in;
    cin.clear();
    cin.ignore(10000, '\n');
    while (true) {
        if (in == "#")
            return false;
        pos = s.special_Binary_search(s.getvectorProducts(), in);
        if(pos == -1){
            cout << "Product name invalid, please try again! ";
            cin >> in;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else{
            prod_name = in;
            break;
        }
    }
    if (ShoppingCart.find(prod_name) == ShoppingCart.end()){
        added = 0;
    }
    else{
        added = ShoppingCart[prod_name];
    }
    cout << "Quantity? ";
    while(true) {
        if (cin.peek() == '#'){
            cin.clear();
            cin.ignore(10000, '\n');
            return false;
        }
        else if(!(cin >> q) || q == 0) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Wrong input! Try again: ";
        }
        else if(s.getvectorProducts().at(pos).getStock()-added == 0){
            cout << "No more " << in << " in stock!" << endl;
            return false;
        }
        else if(s.getvectorProducts().at(pos).getStock() < q + added){
            cout << "Sorry! We only have " << s.getvectorProducts().at(pos).getStock()-added  << " " <<  s.getvectorProducts().at(pos).getproductName() << " in stock " << endl;
            cout << "Please enter a valid quantity: " ;
            cin.ignore(10000,'\n');
        }
        else {
            break;
        }
    }
    return true;
}

bool Transaction::getInputforRemove(string prod_name, int &q, bool all) {
    string in;
    bool Pdateid = false;
    cout << "Product? ";
    cin >> in;
    cin.ignore(10000, '\n');
    while (true) {
        if (in == "#")
            return false;
        for (auto x: ShoppingCart) {
            if (x.first == in) {
                prod_name = x.first;
                Pdateid = true;
            }
        }
        if (Pdateid)
            break;
        else{
            cout << "Invalid product name! Try again: ";
            cin >> in;
            cin.ignore(10000, '\n');
        }
    }
    if (all){
        return true;
    }
    cout << "Quantity? ";
    while(true) {
        if (cin.peek() == '#'){
            cin.ignore(10000, '\n');
            return false;
        }
        else if(!(cin >> q)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Wrong input! Type a number: ";
        }
        else if(ShoppingCart[prod_name] < q){
            cout << "Wrong input! Your removing a quantity higher than the one you have on your shopping cart (" << ShoppingCart[prod_name] << ")!" << endl;
            cin.ignore(10000, '\n');
        }
        else if(ShoppingCart[prod_name] >= q){
            break;
        }
    }
    return true;
}

bool Transaction::loop(Shop & s){
    char input;
    int Q;
    string prod_name;
    s.showProducts();
    showCommands();
    cout << "Welcome to our Shop! You may now begin choosing the products you want!" << endl;
    cout << "Type: ";
    cin >> input;
    cin.ignore(10000, '\n');
    while(input != '#') {
        switch (toupper(input)) {
            case 'P':
                s.showProducts();
                break;
            case 'C':
                showProductsCar(s);
                break;

            case 'A':
                if (getInputforAdd(prod_name,Q, s)){
                    addProduct(prod_name, Q, s);
                    cout << "Added " << Q << "x  " << prod_name << " !" << endl;
                }
                break;

            case 'R':
                if (getInputforRemove(prod_name, Q, false)){
                    RemoveProduct(prod_name, Q, s);
                    cout << "Removed " << Q << "x  " << prod_name << " !" << endl;
                }
                break;

            case 'D':
                if (getInputforRemove(prod_name, Q, true)){
                    RemoveProduct(prod_name, s);
                    cout << "Deleted " << prod_name << " !" << endl;
                }
                break;

            case 'U':
                Undo(s);
                cout << "Last action was undone!" << endl;
                break;

            case 'H':
                showCommands();
                break;
            case 'X':
                return false;
            default:
                cout << "Input unrecognized!" << endl;
                break;
        }
        showCommands();
        cout << "Type: ";
        cin >> input;
        cin.ignore(10000, '\n');
    }
    if (ShoppingCart.size() == 0){
        return false;
    }
    return true;
}

void Transaction::getPaymentMethod(clientInfo &c, Shop & s){
    string choice;
    string answer;
    set<string> correctInputs = {"YES", "Yes","yes","NO","No","no"};
    cout << "Which payment method do you wish to use?" << endl;
    cout << " -----------------------------------"<< endl;
    cout << "|   Press 1 for -> MBWAY            |" << endl;
    cout << "|   Press 2 for -> ATM              |" << endl;
    cout << "|   Press 3 for -> CreditCard       |" << endl;
    cout << " -----------------------------------" << endl;
    cout << "If you wish to cancel the operation type 'X'!" << endl;
    getline(cin, choice, '\n');
    while(choice.size() != 1){
        cout << "That's the wrong input! Try again."<<endl;
        getline(cin, choice, '\n');
    }
    bool paymentcheck = false;
    while(!paymentcheck) {
        switch (choice[0]) {
            case '1':{
                string phonenumber;
                cout << "Since you have chosen MBWAY we will need your phone number. Insert it below." << endl;
                cout << "If you wish want to go back press '1'" << endl;
                getline(cin, phonenumber);
                while (!(s.checkIfInt(phonenumber) && (phonenumber.size() == 9 || stoll(phonenumber) == 1))) {
                    cout << "That's the wrong input! Try again." << endl;
                    getline(cin, phonenumber);
                }
                if (stoll(phonenumber) == 1) {
                    getPaymentMethod(c, s);
                    paymentcheck = true;
                    break;
                }


                showProductsCar(s);
                cout << "Do you wish to proceed with your transaction?(YES/NO)? " << endl;
                getline(cin, answer);
                while (correctInputs.find(answer) == correctInputs.end()) {
                    cout << "That is the wrong input please try again:\n";
                    getline(cin, answer);
                }
                if (answer == "YES" || answer == "yes" || answer == "Yes") {
                    MBway p(totalPrice, c, ShoppingCart, stoll(phonenumber));
                    p.Receipt();
                    showProductsCar(s);
                    for (const auto &x: ShoppingCart) {
                        s.updateStock(x.first, x.second);
                    }
                    paymentcheck = true;
                    cout << "Your purchase was successful." << endl;
                }


                paymentcheck = true;
                break;
            }
            case '2': {
                string reference;
                cout << "Since you have chosen ATM we will need your reference. Insert it below." << endl;
                cout << "If you wish to change payment method press '1'" << endl;
                getline(cin, reference);
                while (!(s.checkIfInt(reference) && (reference.size() == 9 || stoll(reference) == 1))) {
                    cout << "That's the wrong input! Try again." << endl;
                    getline(cin, reference);
                }
                if (stoll(reference) == 1) {
                    getPaymentMethod(c, s);
                    paymentcheck = true;
                    break;
                }


                showProductsCar(s);
                cout << "Do you wish to proceed with your transaction?(YES/NO)" << endl;
                getline(cin, answer);
                while (correctInputs.find(answer) == correctInputs.end()) {
                    cout << "That is the wrong input please try again:\n";
                    getline(cin, answer);
                }
                if (answer == "YES" || answer == "yes" || answer == "Yes") {
                    ATM p(totalPrice, c, ShoppingCart, stoll(reference));
                    p.Receipt();
                    for (const auto &x: ShoppingCart) {
                        s.updateStock(x.first, x.second);
                    }
                    paymentcheck = true;
                    cout << "Your purchase was successful" << endl;
                }
                else{
                    paymentcheck = true;
                }
                break;
            }
            case '3': {
                string DateInput;
                string cardnumber;
                int day, month, year;
                Date date;
                bool validDate;
                cout<< "Since you have chosen CreditCard we will need your credit card number and expiration date. "<< endl;
                cout << "If you wish to change payment method press '1'" << endl;
                cout << "Credit Card number: " << endl;
                getline(cin, cardnumber);
                while (!(s.checkIfInt(cardnumber) && (cardnumber.size() == 9 || stoll(cardnumber) == 1))) {
                    cout << "That's the wrong input! Try again." << endl;
                    getline(cin, cardnumber);
                }
                if (stoll(cardnumber) == 1) {
                    getPaymentMethod(c, s);
                    paymentcheck = true;
                    break;
                }


                do {
                    validDate = false;
                    while(!validDate) {
                        validDate = true;
                        cout << "Date(dd-mm-yyyy): ";
                        getline(cin, DateInput);
                        if (DateInput.size() != 10){
                            cout << "Wrong date format!" << endl;
                            validDate = false;
                        }
                        else {

                            if (!s.checkIfInt((DateInput.substr(0, 2)))) {
                                cout << "Invalid day input!" << endl;
                                validDate = false;
                            }
                            if (!s.checkIfInt((DateInput.substr(3, 2)))) {
                                cout << "Invalid month input!" << endl;
                                validDate = false;
                            }
                            if (!s.checkIfInt((DateInput.substr(6)))) {
                                cout << "Invalid year input!" << endl;
                                validDate = false;
                            }
                        }
                    }
                    date.day = stoi(DateInput.substr(0, 2));
                    date.month = stoi(DateInput.substr(3, 2));
                    date.year = stoi(DateInput.substr(6));
                } while (!date.TestDate(date) || !date.checkExpiration(date));


                showProductsCar(s);
                cout << "Do you wish to proceed with your transaction?(YES/NO)" << endl;
                getline(cin, answer);
                while (correctInputs.find(answer) == correctInputs.end()) {
                    cout << "That is the wrong input please try again:\n";
                    getline(cin, answer);
                }
                if (answer == "YES" || answer == "yes" || answer == "Yes") {
                    CreditCard p(totalPrice, c, ShoppingCart, stoll(cardnumber), date);
                    p.Receipt();
                    for (const auto &x: ShoppingCart) {
                        s.updateStock(x.first, x.second);
                    }
                    paymentcheck = true;
                    cout << "Your purchase was successful" << endl;
                }


                paymentcheck = true;
                break;
            }
            case 'X':

                paymentcheck = true;
                break;
            default:

                cout << "That's the wrong input! Try again: ";
                getline(cin, choice, '\n');
                while(choice.size() != 1){
                    cout << "That's the wrong input! Try again: ";
                    getline(cin, choice, '\n');
                }
        }
    }
}