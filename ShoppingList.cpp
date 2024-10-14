
#include "ShoppingList.h"

//aggiunge un osservatore alla lista degli osservatori
void ShoppingList::addObserver(Observer *observer) {
    observers.push_back(observer);
}

//rimuove un osservatore dalla lista degli osservatori
void ShoppingList::removeObserver(Observer *observer) {
    observers.remove(observer);
}

//notifica tutti gli osservatori di un cambiamento nella lista della spesa
void ShoppingList::notifyObservers() {
    for (auto observer: observers) {
        observer->onUpdate(listName);
    }
}

void ShoppingList::insertItem(const Item &item) {
    //cerca l'articolo nella mappa items in base al nome
    auto itr = items.find(item.getName());
    if (itr != items.end() && itr->second->getCategory() == item.getCategory()) {
        //se l'oggetto esiste già, aggiorna la quantità esistente
        int result = itr->second->getQuantity() + item.getQuantity();
        itr->second->setQuantity(result);
    } else {
        //se l'oggetto non esiste, lo aggiunge come nuovo
        auto ptr = std::make_shared<Item>(item);
        items.insert(std::make_pair(item.getName(), ptr));
    }
    // Cerca la categoria dell'articolo nella mappa delle categorie
    std::string itemCategory = item.getCategory();
    bool found = false;
    for (auto &it: itemCategories) {
        if (it.first == itemCategory) {
            // Se la categoria esiste già, incrementa il conteggio
            it.second++;
            found = true;
            break;
        }
    }
    if (!found) {
        // Aggiunge una nuova categoria alla mappa se non esiste già
        itemCategories.insert(std::make_pair(itemCategory, 1));
    }
    notifyObservers();
}

void ShoppingList::removeItem(const std::string &itemName) {
    // Trovo l'articolo nella mappa items in base al nome
    auto itr = items.find(itemName);

    if (itr == items.end()) {
        // Se l'articolo non esiste, lancia un'eccezione
        throw std::invalid_argument("Invalid item name");
    } else {
        // Trova la categoria corrispondente nella mappa itemCategories
        auto &category = itr->second->getCategory();
        auto itCategory = itemCategories.find(category);

        // Decrementa il conteggio degli articoli nella categoria
        itCategory->second--;

        // Se la categoria non contiene più articoli, la rimuove
        if (itCategory->second == 0) {
            itemCategories.erase(itCategory);
        }
        // Rimuove l'oggetto dalla mappa items
        itr->second->setQuantity(0);
        items.erase(itr);
        notifyObservers();
    }
}

void ShoppingList::markItemAsBought(const std::string &itemName) {
    // Trova l'articolo nella mappa items in base al nome
    auto itr = items.find(itemName);

    if (itr != items.end()) {
        // Se l'oggetto è acquistato, lo segna come non acquistato e viceversa
        bool isBought = itr->second->isPurchasedStatus();
        if (isBought) {
            itr->second->markItem(false);
        } else {
            itr->second->markItem(true);
        }
        notifyObservers();
    } else {
        // Se l'articolo non è presente, lancia un'eccezione
        throw std::invalid_argument("Invalid item name");
    }
}

int ShoppingList::notBoughtLenght() const {
    // Conta il numero di articoli non acquistati nella lista
    int count = 0;
    for (const auto &item: items) {
        if (!item.second->isPurchasedStatus()) {
            //count += item.second->getQuantity();
            count++;
        }
    }
    return count;
}

// Stampa a schermo tutti gli articoli non acquistati nella lista della spesa
void ShoppingList::printNotBoughtItems() const {
    // Conteggio totale degli articoli non acquistati
    int total = 0;
    std::string strOut = "Oggetti non acquistati in " + listName + ":\n";

    // Itera attraverso le categorie di articoli nella mappa itemCategories
    for (const auto &itr: itemCategories) {
        // Nome della categoria corrente
        const std::string &category = itr.first;

        // Numero di oggetti non acquistati nella categoria
        int categoryNotBought = 0;

        // Flag per stampare la categoria solo una volta
        bool first = true;

        // Verifica se ci sono articoli nella categoria corrente
        if (itr.second != 0) {
            // Itera attraverso gli articoli nella lista della spesa
            for (const auto &item: items) {
                // Se l'articolo appartiene alla categoria e non è acquistato, lo stampa
                if (item.second->getCategory() == category && !item.second->isPurchasedStatus()) {
                    // Stampa il nome della categoria solo alla prima iterazione
                    if (first) {
                        strOut += "Categoria: " + category + "\n";
                        first = false;
                    }

                    // Stampa il nome e la quantità dell'articolo non acquistato
                    strOut += "- " + item.first + " (" + std::to_string(item.second->getQuantity()) + ")" "\n";
                    categoryNotBought++;
                }
            }
        }

        // Aggiorna il conteggio totale degli articoli non acquistati
        total += categoryNotBought;
    }

    if (total > 0) {
        std::cout << strOut;
        // Stampa del numero totale di articoli non acquistati nella lista
        std::cout << "Numero totale di articoli non acquistati: " << total << std::endl;
        std::cout << std::endl;
    }
}

// Restituisce gli articoli non acquistati nella lista della spesa
std::map<std::string, std::shared_ptr<Item>> ShoppingList::notBoughtItems() const {
    std::map<std::string, std::shared_ptr<Item>> retItems;

    // Conteggio totale degli articoli non acquistati
    int total = 0;

    // Itera attraverso le categorie di articoli nella mappa itemCategories
    for (const auto &itr: itemCategories) {

        // Nome della categoria corrente
        const std::string &category = itr.first;

        // Numero di oggetti non acquistati nella categoria
        int categoryNotBought = 0;

        // Verifica se ci sono articoli nella categoria corrente
        if (itr.second != 0) {
            // Itera attraverso gli articoli nella lista della spesa
            for (const auto &item: items) {
                // Se l'articolo appartiene alla categoria e non è acquistato
                if (item.second->getCategory() == category && !item.second->isPurchasedStatus()) {
                    // Crea il nuovo oggetto e lo inserisce nella lista di ritorno
                    Item item2(item.second->getName(), item.second->getCategory(), item.second->getQuantity(),
                               item.second->isPurchasedStatus());
                    auto ptr = std::make_shared<Item>(item2);
                    retItems.insert(std::make_pair(item2.getName(), ptr));
                    categoryNotBought += item.second->getQuantity();
                }
            }
        }

        // Aggiorna il conteggio totale degli articoli non acquistati
        total += categoryNotBought;
    }

    return retItems;
}

// Restituisce tutti gli articoli di una categoria nella lista
std::list<Item> ShoppingList::getItemsByCategory(const std::string &category) const {
    std::list<Item> retItems;
    // Itera attraverso gli articoli nella lista della spesa
    for (const auto &item: items) {
        // Se l'articolo appartiene alla categoria
        if (item.second->getCategory() == category) {
            // Crea il nuovo oggetto e lo inserisce nella lista di ritorno
            Item item2(item.second->getName(), item.second->getCategory(), item.second->getQuantity(), item.second->isPurchasedStatus());
            retItems.push_back(item2);
        }
    }

    return retItems;
}

// Restituisce il nome della lista della spesa
const std::string &ShoppingList::getListName() const {
    return listName;
}

// Modifica il nome della lista della spesa
void ShoppingList::setListName(const std::string &name) {
    this->listName = name;
}

// Restituisce il numero di articoli nel nome della lista della spesa
int ShoppingList::getListSize() const {
    return listName.size();
}

const std::shared_ptr<Item> ShoppingList::findItem(const std::string &name) const {
    // Trova un articolo nella mappa items in base al nome
    auto itr = items.find(name);
    if (itr != items.end()) {
        return itr->second;
    } else {
        // Restituisce nullptr se l'articolo non viene trovato
        return nullptr;
    }
}

// Restituisce la mappa delle categorie di articoli e le loro quantità
const std::map<std::string, int> &ShoppingList::getItemCategories() const {
    return itemCategories;
}

