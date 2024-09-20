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

class User: public Observer{
public:
    User();
    explicit User(const std::string& name);
    ~User() override;

    void onUpdate(const std::string& list) override;

    void addList(ShoppingList& list);
    void removeList(const std::string& name);

    const std::map<std::string, std::shared_ptr<ShoppingList>>& getLists() const;

    const std::string &getName() const;

private:
    std::string name;
    // le liste sono le shoppingList (Subject), un User può avere più liste della spesa ovvero più Subject
    std::map<std::string, std::shared_ptr<ShoppingList>> lists;
};


#endif //LABPROGRAMMAZIONE_USER_H
