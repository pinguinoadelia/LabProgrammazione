//
// Created by Michelino De Laurentiis on 19/09/24.
//

#ifndef LABPROGRAMMAZIONE_ITEM_H
#define LABPROGRAMMAZIONE_ITEM_H

#include <string>
#include <exception>
#include <stdexcept>

using namespace std;

class Item {
public:
    // Costruttore della classe Item
    Item(string s, string c, int q = 1) : itemName(move(s)), itemCategory(move(c)) {
        // Controllo se la quantità è positiva o zero, altrimenti lancio un'eccezione
        if (q >= 0)
            itemQta = q;
        else
            throw std::out_of_range("La quantità dell'oggetto non è positiva");

        // Imposto lo stato dell'oggetto come non acquistato
        isBought = false;
    }

    // Restituisce il nome dell'oggetto
    const string& getItemName() const {
        return itemName;
    }

    // Restituisce la categoria dell'oggetto
    const string& getItemCategory() const {
        return itemCategory;
    }

    // Restituisce la quantità dell'oggetto
    int getItemQta() const {
        return itemQta;
    }

    // Imposta la quantità dell'oggetto
    void setItemQta(int itemQta) {
        if (itemQta >= 0)
            Item::itemQta = itemQta;
        else
            throw std::out_of_range("La quantità dell'oggetto non è positiva");
    }

    // Segna l'oggetto come acquistato
    void buy() {
        isBought = true;
    }

    // Segna l'oggetto come non acquistato
    void sell() {
        isBought = false;
    }

    // Restituisce lo stato dell'acquisto dell'oggetto
    bool isBoughtStatus() const {
        return isBought;
    }

private:
    string itemName;        // Nome dell'oggetto
    string itemCategory;    // Categoria dell'oggetto
    int itemQta;            // Quantità dell'oggetto
    bool isBought;          // Stato dell'acquisto dell'oggetto
};


#endif //LABPROGRAMMAZIONE_ITEM_H
