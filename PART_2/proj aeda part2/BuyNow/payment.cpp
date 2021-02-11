#include "payment.h"

Date::Date() {}

Date::Date(int d, int m, int y) {
    if (d < 1 || d>31){
        throw "day";
    }
    else if(m < 1 || m >12)
        throw "month";
    else{
        day = d;
        month = m;
        year = y;
    }
}

ostream & operator<<(ostream &out, Date & d){
    out << d.day << "/" << d.month << "/" << d.year;
    return out;
}

bool Date::TestDate(Date & d){
    set <int> ThirtyDayMonths = {4, 6, 9, 11};
    set <int> ThirtyOneDayMonths = {1, 3, 5, 7, 8, 10, 12};
    try{
        if (d.day < 1 || d.day >31){
            throw InvalidDate(d);
        }
        else if(d.month < 1 || d.month >12) {
            throw InvalidDate(d);
        }
        else if(d.year < 1 || d.year > 9999){
            throw InvalidDate(d);
        }
        else if (d.month == 2 && d.day > 29) {
            throw InvalidDate(d);
        }
        else if (day == 30 && ThirtyDayMonths.find(d.month) == ThirtyOneDayMonths.end()){
            throw InvalidDate(d);
        }
        else if (day == 31 && ThirtyOneDayMonths.find(d.month) == ThirtyOneDayMonths.end()){
            throw InvalidDate(d);
        }
    }
    catch(InvalidDate & c){
        cout << c;
        return false;
    }
    return true;
}

bool Date::checkExpiration(Date & date){
    try {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        if ((year < 1900 + ltm->tm_year)) //verifica se a dateidade do cartão não expirou
            throw (ExpiredCard(date));
        else if (date.year == 1900 + ltm->tm_year && date.month < 1 + ltm->tm_mon)
            throw (ExpiredCard(date));
        else if (date.year == 1900 + ltm->tm_year && date.month == 1 + ltm->tm_mon && date.day < ltm->tm_mday)
            throw (ExpiredCard(date));
    }
    catch(ExpiredCard & c){
        cout << c;
        return false;
    }
    return true;
}

Payment::Payment(float v, clientInfo p, map<string, unsigned int> s) : value(v), person(p), ShoppingCart(s){}

float Payment::GetValue() const {return value;}


MBway::MBway(float v, clientInfo p, map<string, unsigned int> s, long long int phoneN) : Payment(v, p, s), PhoneNumber(phoneN){}

long long int MBway::GetPhoneNumber() const {return PhoneNumber;}

void MBway::Receipt(){
    ofstream file;
    stringstream ss;

    time_t now = time(0);
    char* dt = ctime(&now);

    ss << setw(30) << "Receipt" << endl;
    ss << "---------------------------------------------------------------" << endl << endl;
    ss << "Prod.  |  Quant." << endl;
    for (auto x: ShoppingCart){
        ss << x.first << "  :  " << x.second << endl;
    }
    if (person.getRegisted() == 1){
        ss << endl << "Discount:" << "\n\n";
        ss << "RegistedClient: -15%" << endl;
        ss << "DiscountedValue: -" << value*0.15 << "€" << "\n\n";
        value = value*0.85;
    }
    ss << endl << "TOTAL: " << value << "€" << endl;
    ss << endl << "---------------------------------------------------------------" << endl;
    ss << "Name:    " << person.getClientName() << endl;
    ss << "NIF:     " << person.getNIF() << endl;
    ss << "Payment Method: MBway" << endl;
    ss << "PhoneNumber: " << PhoneNumber << endl;
    ss << setw(25) << dt << endl;

    file.open("Receipt "+ person.getClientName() +".txt");
    if (file.fail())
        return;
    file << ss.str();
    file.close();

    file.open("transactionRegist.txt", fstream::app);
    if (file.fail()){
        return;
    }
    file << ss.str() << endl;
    file << "===============================================================" << "\n\n";
    file.close();
}


ATM::ATM(float v, clientInfo p, map<string, unsigned int> s, long long int ref) : Payment(v, p, s), reference(ref){}

long long int ATM::GetReference() const {return reference;}

void ATM::Receipt() {
    ofstream file;
    stringstream ss;

    time_t now = time(0);
    char* dt = ctime(&now);

    ss << setw(17) << "Receipt" << endl;
    ss << "---------------------------------------------------------------" << endl << endl;
    ss << "Prod.  |  Quant." << endl;
    for (auto x: ShoppingCart){
        ss << x.first << "  :  " << x.second << endl;
    }
    if (person.getRegisted() == 1){
        ss << endl << "Discount:" << "\n\n";
        ss << "RegistedClient: -15%" << endl;
        ss << "DiscountedValue: -" << value*0.15 << "€" << "\n\n";
        value = value*0.85;
    }
    ss << endl << "TOTAL: " << value << "€" << endl;
    ss << endl << "---------------------------------------------------------------" << endl;
    ss << "Name:    " << person.getClientName() << endl;
    ss << "NIF:     " << person.getNIF() << endl;
    ss << "Payment Method: ATM" << endl;
    ss << "Ref.: " << reference << endl;
    ss << setw(25) << dt << endl;

    file.open("Receipt "+ person.getClientName() + ".txt");
    if (file.fail())
        return;
    file << ss.str();
    file.close();

    file.open("transactionRegist.txt", fstream::app);
    if (file.fail()){
        return;
    }
    file << ss.str() << endl;
    file << "---------------------------------------------------------------" << "\n\n";
    file.close();
}


CreditCard::CreditCard(float v, clientInfo p, map<string, unsigned int> s, long long int numeroc, Date val) : Payment(v, p, s), cardnumber(numeroc), expiration(val){
}

long long int CreditCard::GetCardNumber() const {return cardnumber;}

Date CreditCard::GetExpiration() const {return expiration;}

void CreditCard::Receipt(){
    ofstream file;
    stringstream ss;

    time_t now = time(0);
    char* dt = ctime(&now);

    ss << setw(17) << "Receipt" << endl;
    ss << "---------------------------------------------------------------" << endl << endl;
    ss << "Prod.  |  Quant." << endl;
    for (auto x: ShoppingCart){
        ss << x.first << "  :  " << x.second << endl;
    }
    if (person.getRegisted() == 1){
        ss << endl << "Discount:" << "\n\n";
        ss << "RegistedClient: -15%" << endl;
        ss << "DiscountedValue: -" << value*0.15 << "€" << "\n\n";
        value = value*0.85;
    }
    ss << endl << "TOTAL: " << value << "€" << endl;
    ss << endl << "---------------------------------------------------------------" << endl;
    ss << "Name:    " << person.getClientName() << endl;
    ss << "NIF:     " << person.getNIF() << endl;
    ss << "Payment Method: Cartao de credito" << endl;
    ss << "Card number: " << cardnumber << endl;
    ss << setw(25) << dt << endl;

    file.open("Receipt "+ person.getClientName()+".txt");
    if (file.fail())
        return;
    file << ss.str();
    file.close();

    file.open("transactionRegist.txt", fstream::app);
    if (file.fail()){
        return;
    }
    file << ss.str() << endl;
    file << "---------------------------------------------------------------" << "\n\n";
    file.close();
}

InvalidDate::InvalidDate(Date &d) : invalid(d){}

ostream & operator<<(ostream &out, InvalidDate &v){
    out << "The " << v.invalid << " introduced is invalid! Check if your entering the date accordingly: ";
    return out;
}

ExpiredCard::ExpiredCard(Date &v) : expiration(v){}

ostream & operator<<(ostream &out, ExpiredCard &v){
    out << "Your credit card is expired (" << v.expiration<< "), verify if you insert it correctly" << endl;
    return out;
}