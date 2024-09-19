//
// Created by Michelino De Laurentiis on 19/09/24.
//

#include "ShoppingList.h"

void ShoppingList::attach(Observer* o) {
    observers.push_back(o);
}

void ShoppingList::detach(Observer* o) {
    observers.remove(o);
}

void ShoppingList::notify() {
    for (auto observer : observers) {
        observer->update(shoppingListName);
    }
}

void ShoppingList::addItem(const Item& item) {
    auto itr = shoppingList.find(item.getItemName());
    if (itr != shoppingList.end() && itr->second->getItemCategory() == item.getItemCategory()) {
        // L'oggetto è già presente, aggiorno la quantità
        int result = itr->second->getItemQta() + item.getItemQta();
        itr->second->setItemQta(result);
    } else {
        // L'oggetto non è ancora presente, lo inserisco
        auto itemPtr = std::make_shared<Item>(item);
        shoppingList.insert(std::make_pair(item.getItemName(), itemPtr));
    }

    std::string itemCat = item.getItemCategory();
    bool flag = false;
    for (auto& it : categories) {
        if (it.first == itemCat) {
            // Categoria già presente, aggiorno il numero di oggetti nella categoria
            it.second++;
            flag = true;
            break;
        }
    }
    if (!flag) {
        categories.insert(std::make_pair(itemCat, 1));
    }

    // Notifico gli osservatori della modifica nella lista della spesa
    notify();
}


void ShoppingList::removeItem(const string& name) {
    // Trovo l'oggetto con il nome specificato nella mappa shoppingList
    auto itr = shoppingList.find(name);

    if (itr == shoppingList.end()) {
        throw std::invalid_argument("Invalid item name");
    } else {
        // Trovo la categoria dell'oggetto nella mappa categories
        auto& category = itr->second->getItemCategory();
        auto itCategory = categories.find(category);

        // Decremento il conteggio degli oggetti nella categoria corrispondente
        itCategory->second--;

        // Se il conteggio degli oggetti nella categoria diventa 0, rimuovo la categoria dalla mappa categories
        if (itCategory->second == 0) {
            categories.erase(itCategory);
        }

        // Imposto la quantità dell'oggetto a 0 e lo rimuovo dalla mappa shoppingList
        itr->second->setItemQta(0);
        shoppingList.erase(itr);

        // Notifico gli osservatori della modifica alla lista della spesa
        notify();
    }
}


void ShoppingList::setBought(const string& name) {
    auto itr = shoppingList.find(name);

    if (itr != shoppingList.end()) {
        bool isCompleted = itr->second->isBoughtStatus();
        if (isCompleted) {
            itr->second->sell(); // Cambia da completato a non completato
        } else {
            itr->second->buy(); // Cambia da non completato a completato
        }

        notify();
    } else {
        throw std::invalid_argument("Invalid item name");
    }
}


int ShoppingList::getNotBoughtCount() const {
    int count = 0;
    for (const auto& item : shoppingList) {
        if (!item.second->isBoughtStatus()) {
            count += item.second->getItemQta();
        }
    }
    return count;
}


// Implementazione del metodo per stampare gli oggetti non acquistati nella lista
void ShoppingList::printNotBought() const {
    // Variabile per tenere traccia del totale degli oggetti non acquistati
    int totalNotBought = 0;

    // Stampa dell'intestazione con il nome della lista della spesa
    cout << "Oggetti non acquistati in " << shoppingListName << ":" << endl;

    // Iterazione attraverso le categorie degli oggetti
    for (const auto& itr : categories) {
        // Estrai il nome della categoria corrente
        const string& category = itr.first;

        // Variabile per conteggiare gli oggetti non acquistati nella categoria corrente
        int categoryNotBought = 0;

        // Flag per controllare se è il primo oggetto nella categoria corrente
        bool first = true;

        // Verifica se ci sono oggetti nella categoria corrente
        if (itr.second != 0) {
            // Iterazione attraverso gli oggetti nella lista della spesa
            for (const auto& item : shoppingList) {
                // Verifica se l'oggetto appartiene alla categoria corrente ed è non acquistato
                if (item.second->getItemCategory() == category && !item.second->isBoughtStatus()) {
                    // Stampa il nome della categoria solo alla prima iterazione
                    if (first) {
                        cout << "Categoria: " << category << endl;
                        first = false;
                    }

                    // Stampa il nome e la quantità dell'oggetto non acquistato
                    cout << "- " << item.first << " (" << item.second->getItemQta() << ")" << endl;

                    // Aggiorna il conteggio degli oggetti non acquistati nella categoria
                    categoryNotBought += item.second->getItemQta();
                }
            }
        }

        // Aggiorna il conteggio totale degli oggetti non acquistati
        totalNotBought += categoryNotBought;
    }

    // Stampa del numero totale di oggetti non acquistati nella lista
    cout << "Numero totale di oggetti non acquistati: " << totalNotBought << endl;
    cout << endl;
}


const string& ShoppingList::getShoppingListName() const {
    return shoppingListName;
}

void ShoppingList::setShoppingListName(const string& shoppingListName) {
    this->shoppingListName = shoppingListName;
}


int ShoppingList::getShoppingListSize() const {
    return shoppingList.size();
}

const shared_ptr<Item> ShoppingList::findItem(const string& name) const {
    auto itr = shoppingList.find(name);
    if (itr != shoppingList.end()) {
        return itr->second;
    } else {
        return nullptr; // Se l'elemento non è stato trovato, restituisci un puntatore nullo
    }
}

const map<string, int>& ShoppingList::getCategories() const {
    return categories;
}
