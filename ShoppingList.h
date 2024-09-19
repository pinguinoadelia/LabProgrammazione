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

using namespace std;

class ShoppingList: public Subject {
public:
    // Costruttore della classe ShoppingList
    ShoppingList(const string& shoppingListName) : shoppingListName(shoppingListName) {}

    // Metodi per l'implementazione dell'Observer pattern
    void attach(Observer* o) override;
    void detach(Observer* o) override;
    void notify() override;

    // Aggiunge un oggetto alla lista della spesa
    void addItem(const Item& item);

    // Rimuove un oggetto dalla lista della spesa
    void removeItem(const string& name);

    // Imposta uno stato di acquisto per un oggetto nella lista
    void setBought(const string& name);

    // Restituisce il numero di oggetti non acquistati nella lista
    int getNotBoughtCount() const;

    // Stampa gli oggetti non acquistati nella lista
    void printNotBought() const;

    // Restituisce il nome della lista della spesa
    const string& getShoppingListName() const;

    // Imposta il nome della lista della spesa
    void setShoppingListName(const string& shoppingListName);

    // Restituisce la mappa delle categorie degli oggetti
    const map<string, int>& getCategories() const;

    int getShoppingListSize() const;

    const shared_ptr<Item> findItem(const string& name) const;


    // Distruttore virtuale della classe ShoppingList
    virtual ~ShoppingList() = default;

private:
    list<Observer*> observers;                  // Lista degli osservatori
    map<string, shared_ptr<Item>> shoppingList; // Mappa degli oggetti nella lista
    map<string, int> categories;                // Mappa delle categorie degli oggetti
    string shoppingListName;                    // Nome della lista della spesa
};


#endif //LABPROGRAMMAZIONE_SHOPPINGLIST_H
