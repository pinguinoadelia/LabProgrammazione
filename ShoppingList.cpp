//
// Created by Michelino De Laurentiis on 19/09/24.
//

#include "ShoppingList.h"

void ShoppingList::addObserver(Observer* observer) {
    observers.push_back(observer);
}

void ShoppingList::removeObserver(Observer* observer) {
    observers.remove(observer);
}

void ShoppingList::notifyObservers() {
    for (auto observer : observers) {
        observer->onUpdate(listName);
    }
}

void ShoppingList::insertItem(const Item& item) {
    auto itr = items.find(item.getName());
    if (itr != items.end() && itr->second->getCategory() == item.getCategory()) {
        // L'oggetto è già presente, aggiorno la quantità
        int result = itr->second->getQuantity() + item.getQuantity();
        itr->second->setQuantity(result);
    } else {
        // L'oggetto non è ancora presente, lo inserisco
        auto ptr = std::make_shared<Item>(item);
        items.insert(std::make_pair(item.getName(), ptr));
    }

    std::string itemCategory = item.getCategory();
    bool found = false;
    for (auto& it : itemCategories) {
        if (it.first == itemCategory) {
            // Categoria già presente, aggiorno il numero di oggetti nella categoria
            it.second++;
            found = true;
            break;
        }
    }
    if (!found) {
        itemCategories.insert(std::make_pair(itemCategory, 1));
    }

    // Notifico gli osservatori della modifica nella lista della spesa
    notifyObservers();
}


void ShoppingList::removeItem(const std::string& itemName) {
    // Trovo l'oggetto con il nome specificato nella mappa shoppingList
    auto itr = items.find(itemName);

    if (itr == items.end()) {
        throw std::invalid_argument("Invalid item name");
    } else {
        // Trovo la categoria dell'oggetto nella mappa categories
        auto& category = itr->second->getCategory();
        auto itCategory = itemCategories.find(category);

        // Decremento il conteggio degli oggetti nella categoria corrispondente
        itCategory->second--;

        // Se il conteggio degli oggetti nella categoria diventa 0, rimuovo la categoria dalla mappa categories
        if (itCategory->second == 0) {
            itemCategories.erase(itCategory);
        }

        // Imposto la quantità dell'oggetto a 0 e lo rimuovo dalla mappa shoppingList
        itr->second->setQuantity(0);
        items.erase(itr);

        // Notifico gli osservatori della modifica alla lista della spesa
        notifyObservers();
    }
}


void ShoppingList::markItemAsBought(const std::string& itemName) {
    auto itr = items.find(itemName);

    if (itr != items.end()) {
        bool isBought = itr->second->isPurchasedStatus();
        if (isBought) {
            itr->second->markAsNotPurchased(); // Cambia da completato a non completato
        } else {
            itr->second->markAsPurchased(); // Cambia da non completato a completato
        }

        notifyObservers();
    } else {
        throw std::invalid_argument("Invalid item name");
    }
}


int ShoppingList::markItemsAsNotBought() const {
    int count = 0;
    for (const auto& item : items) {
        if (!item.second->isPurchasedStatus()) {
            count += item.second->getQuantity();
        }
    }
    return count;
}

// Implementazione del metodo per stampare gli oggetti non acquistati nella lista
void ShoppingList::printNotBoughtItems() const {
    // Variabile per tenere traccia del totale degli oggetti non acquistati
    int total = 0;

    // Stampa dell'intestazione con il nome della lista della spesa
    std::cout << "Oggetti non acquistati in " << listName << ":" << std::endl;

    // Iterazione attraverso le categorie degli oggetti
    for (const auto& itr : itemCategories) {
        // Estrai il nome della categoria corrente
        const std::string& category = itr.first;

        // Variabile per conteggiare gli oggetti non acquistati nella categoria corrente
        int categoryNotBought = 0;

        // Flag per controllare se è il primo oggetto nella categoria corrente
        bool first = true;

        // Verifica se ci sono oggetti nella categoria corrente
        if (itr.second != 0) {
            // Iterazione attraverso gli oggetti nella lista della spesa
            for (const auto& item : items) {
                // Verifica se l'oggetto appartiene alla categoria corrente ed è non acquistato
                if (item.second->getCategory() == category && !item.second->isPurchasedStatus()) {
                    // Stampa il nome della categoria solo alla prima iterazione
                    if (first) {
                        std::cout << "Categoria: " << category << std::endl;
                        first = false;
                    }

                    // Stampa il nome e la quantità dell'oggetto non acquistato
                    std::cout << "- " << item.first << " (" << item.second->getQuantity() << ")" << std::endl;

                    // Aggiorna il conteggio degli oggetti non acquistati nella categoria
                    categoryNotBought += item.second->getQuantity();
                }
            }
        }

        // Aggiorna il conteggio totale degli oggetti non acquistati
        total += categoryNotBought;
    }

    // Stampa del numero totale di oggetti non acquistati nella lista
    std::cout << "Numero totale di oggetti non acquistati: " << total << std::endl;
    std::cout << std::endl;
}


const std::string& ShoppingList::getListName() const {
    return listName;
}

void ShoppingList::setListName(const std::string& name) {
    this->listName = name;
}


int ShoppingList::getListSize() const {
    return listName.size();
}

const std::shared_ptr<Item> ShoppingList::findItem(const std::string& name) const {
    auto itr = items.find(name);
    if (itr != items.end()) {
        return itr->second;
    } else {
        return nullptr; // Se l'elemento non è stato trovato, restituisci un puntatore nullo
    }
}

const std::map<std::string, int>& ShoppingList::getItemCategories() const {
    return itemCategories;
}
