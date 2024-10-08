
#ifndef LABPROGRAMMAZIONE_USER_H
#define LABPROGRAMMAZIONE_USER_H

#include "ShoppingList.h"
#include "Observer.h"
#include <string>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <list>
#include <map>
#include <memory>
#include <algorithm>

class User: public Observer{
public:
    // Costruttore di default della classe User
    User();

    // Costruttore che inizializza l'utente con un nome
    explicit User(const std::string& name);

    // Distruttore virtuale per gestire correttamente la memoria
    ~User() override;

    // Metodo chiamato quando una lista della spesa osservata subisce modifiche
    void onUpdate(const std::string& list) override;

    // Aggiunge una lista della spesa all'elenco delle liste dell'utente
    void addList(ShoppingList& list);

    // Rimuove una lista della spesa dall'elenco delle liste dell'utente in base al nome
    void removeList(const std::string& name);

    // Restituisce la mappa delle liste della spesa associate all'utente
    const std::map<std::string, std::shared_ptr<ShoppingList>>& getLists() const;

    // Restituisce il nome dell'utente
    const std::string &getName() const;

    // Restituisce il numero delle liste
    int getNumLists();

    // Imposta il nome dell'utente
    void setName(const std::string &name);

    // Aggiunge un articolo alla lista associata all'utente
    void addItem(const std::string &ln, const Item &item);

    // Rimuove un articolo dalla lista associata all'utente
    void removeItem(const std::string &ln, const Item &item);

    // Restituisce il numero degli articoli ancora da comprare
    int getRemainedItems(const std::string &ln);

private:
    std::string name; // Nome dell'utente
    // Mappa delle liste della spesa (ShoppingList) associate all'utente; un utente può gestire più liste della spesa
    std::map<std::string, std::shared_ptr<ShoppingList>> lists;
};


#endif //LABPROGRAMMAZIONE_USER_H
