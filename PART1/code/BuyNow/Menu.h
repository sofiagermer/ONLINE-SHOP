#pragma once

#include "shop.h"
#include "transaction.h"
#include "payment.h"

#include <stdlib.h>
#include <conio.h>
#include <cctype>
#include <stdio.h>
#include <cstdlib>

using namespace std;

class Menu{
public:
    /**
    * Default constructor.
    */
    Menu();
    /**
    * Asks for the password to acess manager's mode.
    */
    void Admission();
    /**
    * Starts the menu.
    * @param p Online shop.
    */
    void mainMenu(Shop & p);
    /**
    * Opens the clientsMenu.
    */
    void clientsMenu();
    /**
    * Opens the beginning menu.
    */
    void beginingMenu();
    /**
    * Opens the manager's menu.
    */
    void managerMenu();
    /**
     * Prints out a logo from the shop.
     */
    void frontpage();
    /**
     * Displays the ProfitMargin menu
     * @param p The OnlineShop
     */
    void ProfitMargin(Shop &p);
    /**
     * Displays the statistics menu
     * @param p The OnlineShop

     */
    void statistics(Shop &p);
    /**
     * Function that updates all the files
     * @param p The OnlineShop
     */
    void closeShop(Shop &p);
    /**
     * Function that starts the transaction process
     * @param p The OnlineShop
     * @param t Transaction pointer where the transaction will be saved to
     */
    void StartShopping(Shop &p, Transaction *t);
};




