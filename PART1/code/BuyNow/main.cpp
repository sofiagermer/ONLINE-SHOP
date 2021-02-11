#include "Menu.h"

using namespace std;

int main() {
    Menu a;
    Supplier s("supplier.txt");
    Shop shop(s);
    a.mainMenu(shop);
}
