//
// Created by Michelino De Laurentiis on 19/09/24.
//

#ifndef LABPROGRAMMAZIONE_USER_H
#define LABPROGRAMMAZIONE_USER_H

#include "ShoppingList.h"
#include "Observer.h"
#include <string>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <list>
#include <map>
#include <memory>
#include <algorithm>
using namespace std;

class User: public Observer{
public:
    User();
    User(const string& userName);
    virtual ~User();

    virtual void update(const string& listName) override;

    void addShoppingList(ShoppingList& shoppingList);
    void removeShoppingList(const string& name);

    const map<string, shared_ptr<ShoppingList>>& getMyLists() const;

    const string &getUserName() const;


private:
    string userName;
    // le liste sono le shoppingList (Subject), un User può avere più liste della spesa ovvero più Subject
    map<string, shared_ptr<ShoppingList>> myLists;
};


#endif //LABPROGRAMMAZIONE_USER_H
