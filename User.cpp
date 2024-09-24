
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

int User::getNumLists() {
    return lists.size();
}

void User::setName(const std::string &name) {
    User::name = name;
}

void User::addItem(const std::string &ln, const Item &item) {
    auto it = lists.find(ln);  // Cerca nella mappa usando 'ln (listName)' come chiave
    if (it != lists.end() && it->second) {  // Verifica se la lista esiste e il puntatore non è nullo
        it->second->insertItem(item);  // Accedi alla lista tramite il puntatore condiviso e inserisci l'articolo
        it->second->notifyObservers();  // Notifica l'aggiornamento
    }
}

void User::removeItem(const std::string &ln, const Item &item) {
    auto it = lists.find(ln);  // Cerca nella mappa usando 'ln (listName)' come chiave
    if (it != lists.end() && it->second) {  // Verifica se la lista esiste e il puntatore non è nullo
        it->second->removeItem(item.getName());  // Accedi alla lista tramite il puntatore condiviso e inserisci l'articolo
        it->second->notifyObservers();  // Notifica l'aggiornamento
    }
}

int User::getRemainedItems(const std::string &ln) {
    auto it = lists.find(ln);
    return (it != lists.end()) ? it->second->markItemsAsNotBought() : 0;
}
