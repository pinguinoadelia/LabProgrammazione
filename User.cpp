//
// Created by Michelino De Laurentiis on 19/09/24.
//

#include "User.h"

User::User() : userName("User") {}

User::User(const string& userName) : userName(userName) {}

User::~User() {
    for (auto& itr : myLists) {
        itr.second->detach(this);
    }
}

void User::update(const std::string& listName) {
    auto itr = myLists.find(listName);
    cout << "Lista '" << listName << "' aggiornata:" << endl;
    cout << endl;
    itr->second->printNotBought();
    //stampa dentro lista
}

void User::addShoppingList(ShoppingList& shoppingList) {
    // Creo un puntatore condiviso (shared_ptr) alla ShoppingList passata come argomento
    shared_ptr<ShoppingList> shoppingListPtr = make_shared<ShoppingList>(shoppingList);

    // Inserisco la lista della spesa nella mappa myLists
    myLists.insert(make_pair(shoppingList.getShoppingListName(), shoppingListPtr));

    // Aggiungo l'utente come osservatore della lista della spesa
    shoppingList.attach(this);
}

void User::removeShoppingList(const std::string& name) {
    // Trovo la lista della spesa con il nome specificato nella mappa myLists
    auto shoppingListItr = myLists.find(name);

    if (shoppingListItr == myLists.end()) {
        // Se la lista della spesa non è stata trovata, lancio un'eccezione
        throw std::invalid_argument("Shopping list not found");
    } else {
        // Rimuovo l'utente dalla lista degli osservatori della lista della spesa
        shoppingListItr->second->detach(this);

        // Rimuovo la lista della spesa dalla mappa myLists
        myLists.erase(shoppingListItr);
    }
}

const map<string, shared_ptr<ShoppingList>>& User::getMyLists() const {
    return myLists;
}

const string &User::getUserName() const {
    return userName;
}
