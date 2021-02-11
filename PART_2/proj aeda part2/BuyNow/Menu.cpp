#include "Menu.h"


Menu::Menu() {};

void Menu::Admission() {
    string userinput;
    string password = "aeda";
    cout << "Enter password: ";
    getline(cin,userinput);
    if (userinput != password) {
        cout << "Password Invalid... Try Again: ";
        getline(cin,userinput);
    }
    else cout << "Password Accepted... " << "Welcome!" << endl;
}

void Menu::frontpage()
{   cout<<"============================================================"<< endl;
    cout << "  ____  _    ___     __  _   _  ______          __      "<< endl;
    cout << " |  _ \\| |  | \\ \\   / / | \\ | |/ __ \\ \\        / /" << endl;
    cout << " | |_) | |  | |\\ \\_/ /  |  \\| | |  | \\ \\  /\\  / / " << endl;
    cout << " |  _ <| |  | | \\   /   | . ` | |  | |\\ \\/  \\/ /    " << endl;
    cout << " | |_) | |__| |  | |    | |\\  | |__| | \\  /\\  /      " << endl;
    cout << " |____/ \\____/   |_|    |_| \\_|\\____/   \\/  \\/     " << endl;
    cout << "                                                        " << endl;
    cout<<"============================================================"<< endl;
}

void Menu::mainMenu(Shop & p, Supply &s)
{
    p.readInitial_Clients_file("clientesiniciais.txt");
    p.loadPreviousClientsMessages("messagesbackup.txt");
    string choice;
    bool manager;
    bool left = false;
    do
    {
        frontpage();
        beginingMenu();
        cout << endl << "Make your choice: " ;
        getline(cin, choice);
        while(choice.size() != 1){
            cout << "Invalid Input! Choose again: ";
            getline(cin, choice);
        }
        switch(choice[0]) {
            case '1': {
                bool clientmode = true;
                while(clientmode) {
                    Transaction *t = new Transaction;
                    clientsMenu();
                    string secondChoice;
                    cout << endl << "Make your choice: ";
                    getline(cin, secondChoice);
                    while (secondChoice.size() != 1) {
                        cout << "Invalid Input! Choose again: ";
                        getline(cin, secondChoice);
                    }
                    switch (secondChoice[0]) {
                        case '1' : {
                            system("CLS");
                            StartShopping(p, t);
                            system("CLS");
                            break;
                        }
                        case '2': {
                            p.showRealShops();
                            break;
                        }
                        case '3': {
                            clientmode = false;
                            break;
                        }
                        default:
                            cout << "Not a Valid Choice. \n" << "Choose again.\n";
                            break;
                    }
                }
                break;
            }

            case '2':
                Admission();
                manager = true;
                while(manager) {
                    managerMenu();
                    string thirdChoice;
                    cout << endl << "Make your choice: ";
                    getline(cin, thirdChoice);
                    while(thirdChoice.size() != 1){
                        cout << "Invalid Input! Choose again: ";
                        getline(cin, thirdChoice);
                    }
                    switch (thirdChoice[0]) {
                        case '1':
                            ProfitMargin(p);
                            break;
                        case '2':
                            statistics(p);
                            break;
                        case '3':
                            p.handleClientsMessages();
                            break;
                        case '4':
                            p.manageTrucks();
                            break;
                        case '5':
                            p.manageSuppliers();
                            break;
                        case '6':
                            manager = false;
                            break;
                        default:
                            cout << "Not a Valid Choice. \n" << "Choose again.\n";
                            break;
                    }
                }
                break;
            case '3':
                left = true;
                closeShop(p, s);
                break;
            default:
                cout << "Invalid Input! Choose again: ";
                break;
        }
    } while (!left);
    exit(1);
}
void Menu::StartShopping(Shop &p, Transaction *t){
    clientInfo a = p.allClientsInfo();
    p.updateVectors();
    system("CLS");
    if (!t->loop(p)) {
        delete t;
        cout << "\n\n";
    }
    else {
        t->getPaymentMethod(a, p);
        delete t;
    }
}
void Menu::closeShop(Shop &p, Supply &s){
    p.updateVectors();
    p.addMessagesToFile("ClientsMessages.txt","messagesbackup.txt");
    p.addClientsToFile("clientesiniciais.txt");
    p.updateFile();
    s.setSuppliers(p.getAllSuppliers());
    s.saveSupplier("supplier.txt");
}

void Menu::statistics(Shop &p){
    char input;
    cout << "---------------------------------STATISTICS---------------------------------" << endl;
    p.show_statistics();
    cout << endl
         << "If you want to reset the statistics, insert '0', else insert another input: ";
    cin >> input;
    cin.ignore(10000, '\n');
    if (input == '0') {
        p.clear_statistics();
    }
}
void Menu::ProfitMargin(Shop &p){
    float newPm;
    cout << "Currently your profit margin is set at :  " << p.getProfitMargin() << "\n\n";
    cout << "Retail price = profit margin * supplier's price" << "\n\n";
    cout << "How much do you want to set your profit margin to?(Insert 0 if you don't intend to change it) ";
    while (!(cin >> newPm) || !(newPm > 1 || newPm == 0)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid profit margin! " << endl;
    }
    if (newPm != 0) {
        p.setProfitMargin(newPm);
    }
}

void Menu::clientsMenu()
{   cout <<"=================" << endl;
    cout <<" 1. Start Shopping" << endl;
    cout <<" 2. More about us" << endl;
    cout << " 3. Exit" << endl;
    cout <<"================="<<endl;
}

//---------------------------------------------------------------------------
// subMenu
//---------------------------------------------------------------------------
void Menu::beginingMenu()
{
    cout << " 1. Client's mode" << endl;
    cout << " 2. Manager mode" << endl;
    cout << " 3. Exit" << endl;
    cout <<"===================" << endl;
}

void Menu::managerMenu(){
    cout <<"==========================" << endl;
    cout << " 1. Change Profit Margin  " << endl;
    cout << " 2. Check Shop Statistics " << endl;
    cout << " 3. Handle Client's Messages" << endl;
    cout << " 4. Manage Trucks           " << endl;
    cout << " 5. Manage Suppliers        " << endl;
    cout << " 6. Go Back               " << endl;
    cout <<"==========================" << endl;

}