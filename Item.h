//
// Created by Michelino De Laurentiis on 19/09/24.
//

#ifndef LABPROGRAMMAZIONE_ITEM_H
#define LABPROGRAMMAZIONE_ITEM_H

#include <exception>
#include <stdexcept>

class Item {
public:
    // Costruttore della classe Item
    Item(std::string name, string type, int count = 1) : name(std::move(name)), category(std::move(type)) {
        // Controllo se la quantità è positiva o zero, altrimenti lancio un'eccezione
        if (count >= 0)
            quantity = count;
        else
            throw std::out_of_range("The Item quantity is not positive");

        // Imposto lo stato dell'oggetto come non acquistato
        isPurchased = false;
    }

    // Restituisce il nome dell'oggetto
    const std::string& getName() const {
        return name;
    }

    // Restituisce la categoria dell'oggetto
    const std::string& getCategory() const {
        return category;
    }

    // Restituisce la quantità dell'oggetto
    int getQuantity() const {
        return quantity;
    }

    // Imposta la quantità dell'oggetto
    void setQuantity(int count) {
        if (count >= 0)
            Item::quantity = count;
        else
            throw std::out_of_range("The item quantity is not positive");
    }

    // Segna l'oggetto come acquistato
    void markAsPurchased() {
        isPurchased = true;
    }

    // Segna l'oggetto come non acquistato
    void markAsNotPurchased() {
        isPurchased = false;
    }

    // Restituisce lo stato dell'acquisto dell'oggetto
    bool isPurchasedStatus() const {
        return isPurchased;
    }

private:
    std::string name;        // Nome dell'oggetto
    std::string category;    // Categoria dell'oggetto
    int quantity;            // Quantità dell'oggetto
    bool isPurchased;          // Stato dell'acquisto dell'oggetto
};


#endif //LABPROGRAMMAZIONE_ITEM_H
