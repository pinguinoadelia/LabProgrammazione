//
// Created by Michelino De Laurentiis on 19/09/24.
//

#include "User.h"

User::User() : name("User") {}

User::User(const std::string& name) : name(name) {}

// Rimuove l'utente come osservatore da tutte le liste della spesa a cui è iscritto
User::~User() {
    for (auto& itr :lists) {
        itr.second->removeObserver(this);
    }
}

void User::onUpdate(const std::string& list) {
    // Trova la lista della spesa che è stata aggiornata
    auto itr = lists.find(list);

    // Stampa un messaggio per indicare l'aggiornamento della lista
    std::cout << "List '" << list << "' updated:" << std::endl;
    std::cout << std::endl;

    // Stampa gli oggetti non acquistati nella lista aggiornata
    itr->second->printNotBoughtItems();
}

void User::addList(ShoppingList& list) {
    // Crea un puntatore condiviso alla lista della spesa che viene fornita come argomento
    std::shared_ptr<ShoppingList> ptr = std::make_shared<ShoppingList>(list);

    // Inserisce la lista della spesa nella mappa delle liste dell'utente
    lists.insert(make_pair(list.getListName(), ptr));

    // Aggiunge l'utente come osservatore della lista della spesa
    list.addObserver(this);
}

void User::removeList(const std::string& name) {
    // Trova la lista della spesa con il nome specificato nella mappa delle liste
    auto shoppingListItr = lists.find(name);

    if (shoppingListItr == lists.end()) {
        // Se la lista non esiste, lancia un'eccezione
        throw std::invalid_argument("Shopping list not found");
    } else {
        // Rimuove l'utente dalla lista degli osservatori della lista specificata
        shoppingListItr->second->removeObserver(this);

        // Rimuove la lista della spesa dalla mappa delle liste dell'utente
        lists.erase(shoppingListItr);
    }
}

// Restituisce la mappa delle liste della spesa associate all'utente
const std::map<std::string, std::shared_ptr<ShoppingList>>& User::getLists() const {
    return lists;
}

// Restituisce il nome dell'utente
const std::string &User::getName() const {
    return name;
}
