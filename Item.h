//
// Created by Michelino De Laurentiis on 19/09/24.
//

#ifndef LABPROGRAMMAZIONE_ITEM_H
#define LABPROGRAMMAZIONE_ITEM_H

#include <exception>
#include <stdexcept>
#include <string>

class Item {
public:
    // Costruttore della classe Item che inizializza il nome, la categoria e la quantità
    Item(std::string name, std::string type, int count = 1) : name(std::move(name)), category(std::move(type)) {
        // verifica che la quantità non sia negativa altrimenti, in caso contrario, lancia un'eccezione
        if (count >= 0)
            quantity = count;
        else
            throw std::out_of_range("The Item quantity is not positive");

        // L'oggetto viene inizialmente segnato come non acquistato
        isPurchased = false;
    }

    // Restituisce il nome dell'articolo
    const std::string& getName() const {
        return name;
    }

    // Restituisce la categoria dell'articolo
    const std::string& getCategory() const {
        return category;
    }

    // Restituisce la quantità corrente dell'articolo
    int getQuantity() const {
        return quantity;
    }

    // Imposta una nuova quantità dell'articolo
    void setQuantity(int count) {
        if (count >= 0)
            Item::quantity = count;
        else
            throw std::out_of_range("The item quantity is not positive");
    }

    // Imposta lo stato dell'articolo come acquistato
    void markAsPurchased() {
        isPurchased = true;
    }

    // Imposta lo stato dell'articolo come non acquistato
    void markAsNotPurchased() {
        isPurchased = false;
    }

    // Verifica se l'articolo sia stato acquistato o meno
    bool isPurchasedStatus() const {
        return isPurchased;
    }

private:
    std::string name;        // Nome dell'articolo
    std::string category;    // Categoria dell'articolo
    int quantity;            // Quantità dell'articolo
    bool isPurchased;        // Flag che indica se l'articolo sia stato acquistato oppure no
};


#endif //LABPROGRAMMAZIONE_ITEM_H
