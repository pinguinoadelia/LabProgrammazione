//
// Created by Michelino De Laurentiis on 19/09/24.
//

#include "User.h"

User::User() : name("User") {}

User::User(const std::string& name) : name(name) {}

User::~User() {
    for (auto& itr :lists) {
        itr.second->removeObserver(this);
    }
}

void User::onUpdate(const std::string& list) {
    auto itr = lists.find(list);
    std::cout << "List '" << list << "' updated:" << std::endl;
    std::cout << std::endl;
    itr->second->printNotBoughtItems();
    //stampa dentro lista
}

void User::addList(ShoppingList& list) {
    // Creo un puntatore condiviso (shared_ptr) alla ShoppingList passata come argomento
    std::shared_ptr<ShoppingList> ptr = std::make_shared<ShoppingList>(list);

    // Inserisco la lista della spesa nella mappa myLists
    lists.insert(make_pair(list.getListName(), ptr));

    // Aggiungo l'utente come osservatore della lista della spesa
    list.addObserver(this);
}

void User::removeList(const std::string& name) {
    // Trovo la lista della spesa con il nome specificato nella mappa myLists
    auto shoppingListItr = lists.find(name);

    if (shoppingListItr == lists.end()) {
        // Se la lista della spesa non è stata trovata, lancio un'eccezione
        throw std::invalid_argument("Shopping list not found");
    } else {
        // Rimuovo l'utente dalla lista degli osservatori della lista della spesa
        shoppingListItr->second->removeObserver(this);

        // Rimuovo la lista della spesa dalla mappa myLists
        lists.erase(shoppingListItr);
    }
}

const std::map<std::string, std::shared_ptr<ShoppingList>>& User::getLists() const {
    return lists;
}

const std::string &User::getName() const {
    return name;
}
