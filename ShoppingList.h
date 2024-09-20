//
// Created by Michelino De Laurentiis on 19/09/24.
//

#ifndef LABPROGRAMMAZIONE_SHOPPINGLIST_H
#define LABPROGRAMMAZIONE_SHOPPINGLIST_H

#include "Observer.h"
#include "Subject.h"
#include "Item.h"
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <map>
#include <list>
#include <exception>
#include <stdexcept>

class ShoppingList: public Subject {
public:
    // Costruttore della classe ShoppingList
    explicit ShoppingList(const std::string &name) : listName(name) {}

    // Metodi per l'implementazione dell'Observer pattern
    void addObserver(Observer* observer) override;
    void removeObserver(Observer* observer) override;
    void notifyObservers() override;

    // Aggiunge un oggetto alla lista della spesa
    void insertItem(const Item& item);

    // Rimuove un oggetto dalla lista della spesa
    void removeItem(const std::string& itemName);

    // Imposta uno stato di acquisto per un oggetto nella lista
    void markItemAsBought(const std::string& itemName);

    // Restituisce il numero di oggetti non acquistati nella lista
    int markItemsAsNotBought() const;

    // Stampa gli oggetti non acquistati nella lista
    void printNotBoughtItems() const;

    // Restituisce il nome della lista della spesa
    const std::string& getListName() const;

    // Imposta il nome della lista della spesa
    void setListName(const std::string& name);

    // Restituisce la mappa delle categorie degli oggetti
    const std::map<std::string, int>& getItemCategories() const;

    int getListSize() const;

    const std::shared_ptr<Item> findItem(const std::string& name) const;

    // Distruttore virtuale della classe ShoppingList
    virtual ~ShoppingList() = default;

private:
    std::list<Observer*> observers;                  // Lista degli osservatori
    std::map<std::string, std::shared_ptr<Item>> items; // Mappa degli oggetti nella lista
    std::map<std::string, int> itemCategories;                // Mappa delle categorie degli oggetti
    std::string listName;                    // Nome della lista della spesa
};


#endif //LABPROGRAMMAZIONE_SHOPPINGLIST_H
