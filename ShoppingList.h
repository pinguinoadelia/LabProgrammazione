
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
    //Costruttore della classe ShoppingList che inizializza il nome della lista
    explicit ShoppingList(std::string name) : listName(std::move(name)) {}

    //implementazione del pattern Observer: aggiunge un osservatore
    void addObserver(Observer* observer) override;

    //implementazione del pattern Observer: rimuove un osservatore
    void removeObserver(Observer* observer) override;

    //implementazione del pattern Observer: notifica tutti gli osservatori
    void notifyObservers() override;

    //aggiunge un nuovo articolo alla lista della spesa
    void insertItem(const Item& item);

    //rimuove un articolo dalla lista della spesa ricercandolo per nome
    void removeItem(const std::string& itemName);

    //segna l'articolo come acquistato, ricercando l'articolo per nome
    void markItemAsBought(const std::string& itemName);

    //restituisce il numero di articoli non ancora acquistati nella lista
    int markItemsAsNotBought() const;

    //stampa gli articoli non acquistati nella lista
    void printNotBoughtItems() const;

    //stampa gli articoli non acquistati nella lista
    std::map<std::string, std::shared_ptr<Item>> notBoughtItems() const;

    // Restituisce tutti gli articoli di una categoria nella lista
    std::map<std::string, std::shared_ptr<Item>> getItemsByCategory(const std::string &category) const;

    //restituisce il nome della lista della spesa
    const std::string& getListName() const;

    //imposta il nome della lista della spesa
    void setListName(const std::string& name);

    // Restituisce una mappa che associa le categorie degli articoli alla loro quantità
    const std::map<std::string, int>& getItemCategories() const;

    // Restituisce il numero totale di articoli nella lista della spesa
    int getListSize() const;

    // Trova e restituisce un articolo in base al nome, se esiste
    const std::shared_ptr<Item> findItem(const std::string& name) const;

    //distruttore della classe dichiarato come virtuale per poter gestire correttamente la memoria
    ~ShoppingList() override = default;

    const std::map<std::string, std::shared_ptr<Item>>& getItems() const{
        return items;
    }

private:
    std::list<Observer*> observers; //elenco degli osservatori registrati
    std::map<std::string, std::shared_ptr<Item>> items; //mappa che contiene gli articoli nella lista, indicizzati per nome
    std::map<std::string, int> itemCategories; //mappa delle categorie degli articoli con il conteggio degli articoli per categoria
    std::string listName; //nome della lista
};


#endif //LABPROGRAMMAZIONE_SHOPPINGLIST_H
