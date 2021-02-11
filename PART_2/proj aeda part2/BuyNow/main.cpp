#include "Menu.h"

using namespace std;

int main() {
    Menu a;
    Supply s("supplier.txt");
    Shop shop(s);
    a.mainMenu(shop, s);

}

