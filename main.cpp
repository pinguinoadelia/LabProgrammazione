#include <iostream>
#include <string>
#include <stdexcept>
#include "ShoppingList.h"
#include "User.h"
#include "Item.h"

// Funzione per stampare una ShoppingList
void printItems(const ShoppingList& sl) {

    std::cout << "Nome della lista della spesa: " << sl.getListName() << std::endl << std::endl;

    // Itera attraverso le categorie di articoli
    for (const auto& objectCategory : sl.getItemCategories()) {
        const std::string& category = objectCategory.first;
        int categoryNotPurchased = 0;

        if (objectCategory.second != 0) {
            std::cout << "Categoria: " << category << std::endl;

            // Itera attraverso tutti gli articoli della lista
            for (const auto& itemType : sl.getItems()) {  // Usa il metodo corretto che restituisce la collezione di articoli
                const std::shared_ptr<Item> &item = itemType.second;

                // Verifica che l'articolo appartenga alla categoria corrente e che non sia stato acquistato
                if (item->getCategory() == category && !item->isPurchasedStatus()) {
                    std::cout << "- " << item->getName() << " (" << item->getQuantity() << ")";
                    std::cout << (item->isPurchasedStatus() ? " Comprato" : " Non comprato") << std::endl;
                    categoryNotPurchased += item->getQuantity();
                }
            }
            std::cout << std::endl;
        }
    }

    // Supponiamo che esista un metodo per ottenere il numero totale di articoli non acquistati
    std::cout << "Numero totale degli articoli non comprati:  " << sl.markItemsAsNotBought() << std::endl << std::endl;
}

int main() {

    std::cout << "Benvenuto nell'app della lista della spesa!" <<  std::endl <<  std::endl <<  std::endl;

    bool isProcessing = true;
    int userOption;
    std::map < std::string,User> users;
    std::map < std::string, ShoppingList> shoppingLists;
    std::map < std::string, Item> items;


    //------------------------------------------------------------------------------------------------------------------

    std::cout<<"1) CREAZIONE DELLA LISTA DELLA SPESA "<< std::endl<< std::endl;

    while(isProcessing)
    {
        std::cout <<  std::endl << "Scegli: " <<  std::endl;
        std::cout << "1. Crea una nuova lista della spesa" <<  std::endl;
        std::cout << "2. Vai avanti" <<  std::endl;
        std::cin>>userOption;
        std::cout<< std::endl;

        switch (userOption) {
            case 1 : {
                std::string shoppingListName;
                std::cout << "Inserisci il nome della lista della spesa: ";
                std::cin >> shoppingListName;

                ShoppingList newShoppingList(shoppingListName);
                shoppingLists.insert(make_pair(shoppingListName, newShoppingList));

                std::cout << "Lista della spesa \"" << shoppingListName << "\" creata." <<  std::endl;
                break;
            }

            case 2 : {
                isProcessing = false;
                break;
            }

            default: {
                std::cout << "L'input è invalido, Perfavore riprova." <<  std::endl;
                break;
            }
        }
    }

    //------------------------------------------------------------------------------------------------------------------

    std::cout <<  std::endl << "2) CREAZIONE DEGLI ARTICOLI" <<  std::endl <<  std::endl;

    isProcessing = true;

    while (isProcessing) {
        std::cout <<  std::endl << "Scegli:" <<  std::endl;
        std::cout << "1. Crea un nuovo articolo" <<  std::endl;
        std::cout << "2. Vai avanti" <<  std::endl;

        std::cin >> userOption;

        switch (userOption) {
            case 1: {
                std::string productName;
                int initialQuantity = 1;
                std::string quantityInput;
                int quantityValue;
                std::string productCategory;

                std::cout << "Inserisci il nome dell'articolo: ";
                std::cin >> productName;
                std::cout << std::endl;

                std::cout << "Inserisci la categoria dell'articolo: ";
                std::cin >> productCategory;
                std::cout << std::endl;

                std::cout << "Inserisci la quantità: ";
                std::cin >> quantityInput;
                std::cout <<  std::endl;

                if (quantityInput == "default") {
                    quantityValue = initialQuantity;
                } else {
                    try {
                        quantityValue = std::stoi(quantityInput);
                    } catch ( std::invalid_argument &e) {
                        quantityValue = initialQuantity; // imposta una quantità di default se l'input è invalido.
                    }
                }

                try {
                    Item i(productName, productCategory, quantityValue);
                    items.insert(make_pair(productName, i));
                } catch (std::out_of_range &e2) {
                    std::cerr << e2.what() <<  std::endl;
                }
                break;
            }

            case 2: {
                isProcessing = false;
                break;
            }

            default: {
                std::cout << "Scelta non valida, perfavore riprova." <<  std::endl;
                break;
            }
        }
    }


    //------------------------------------------------------------------------------------------------------------------

    std::cout <<  std::endl << "3) CREAZIONE DEGLI UTENTI" <<  std::endl <<  std::endl;

    isProcessing = true;

    while (isProcessing) {
        std::cout <<  std::endl << "Scegli:" <<  std::endl
             << "1. Crea un nuovo utente" <<  std::endl
             << "2. Vai avanti" <<  std::endl;

        std::cin >> userOption;
        std::cout <<  std::endl;

        switch (userOption) {
            case 1: {
                std::string userName;
                std::cout << "Inserisci il nome dell'utente: ";
                std::cin >> userName;

                std::cout <<  std::endl;

                User newUser(userName);
                users.insert(make_pair(userName, newUser));
                break;
            }

            case 2: {
                isProcessing = false;
                break;
            }

            default: {
                std::cout << "Scelta non valida, perfavore riprova." <<  std::endl;
                break;
            }
        }
    }


    //------------------------------------------------------------------------------------------------------------------

    std::cout <<  std::endl <<  std::endl << "4) ORA PUOI ESEGUIRE OPERAZIONI SULLE LISTE, SUGLI OGGETTI E SUGLI UTENTI PRECEDENTEMENTE CREATI"<< std::endl;

    bool operations = true;
    while(operations)
    {
        std::cout <<  std::endl;
        std::cout << "Hai le seguenti opzioni: " <<  std::endl;
        std::cout << "1) Aggiungi un articolo alla lista" <<  std::endl;
        std::cout << "2) Rimuovi un oggetto da una lista (fornisci nome della lista e dell'articolo)" <<  std::endl;
        std::cout << "3) Marca un oggetto come comprato" <<  std::endl;
        std::cout << "4) Aggiungi una lista della spesa alla collezione dell'utente" <<  std::endl;
        std::cout << "5) Rimuovi una lista della spesa dalla collezione dell'utente" <<  std::endl;
        std::cout << "6) Nessun'altra operazione" <<  std::endl;
        std::cout <<  std::endl;

        std::cin>>userOption;
        std::cout<< std::endl;

        switch (userOption) {
            case 1 :{
                std::string listName;
                std::string productName;
                std::cout<<"Inserisci il nome della lista:"<< std::endl;
                std::cin>>listName;
                std::cout<<"Inserisci il nome dell'articolo:"<< std::endl;
                std::cin>>productName;

                auto itrl=shoppingLists.find(listName);
                auto itrn=items.find(productName);

                try {
                    if(itrl==shoppingLists.end()||itrn==items.end())
                        throw std::invalid_argument("Nome della lista o dell'articolo non valido");
                    else
                    {
                        itrl->second.insertItem(itrn->second);
                    }
                }catch(std::invalid_argument& e){
                    std::cerr<<e.what()<< std::endl;
                }
                break;
            }

            case 2: {
                std::string productName;
                std::string listName;

                std::cout<<"Inserisci il nome della lista:"<< std::endl;
                std::cin>>listName;
                std::cout<<"Inserisci il nome dell'articolo:"<< std::endl;
                std::cin>>productName;

                auto itrl=shoppingLists.find(listName);
                auto itrn=items.find(productName);

                try {
                    if (itrl == shoppingLists.end() || itrn == items.end())
                        throw std::invalid_argument("Nome della lista o dell'articolo non valido");
                    else
                        itrl->second.removeItem(productName);

                }catch(std::invalid_argument& e){
                    std::cerr<<e.what()<< std::endl;
                }
                break;
            }

            case 3: {
                std::string productName;
                std::string listName;

                std::cout<<"Inserisci il nome della lista:"<< std::endl;
                std::cin>>listName;
                std::cout<<"Inserisci il nome dell'articolo:"<< std::endl;
                std::cin>>productName;

                auto itrl=shoppingLists.find(listName);
                auto itrn=items.find(productName);

                try {
                    if (itrl == shoppingLists.end() || itrn == items.end())
                        throw std::invalid_argument("Nome della lista o dell'articolo non valido");
                    else
                        itrl->second.markItemAsBought(productName);

                }catch(std::invalid_argument& e){
                    std::cerr<<e.what()<< std::endl;
                }
                break;
            }

            case 4: {
                std::string listName;
                std::string userName;

                std::cout<<"Inserisci il nome della lista:"<< std::endl;
                std::cin>>listName;
                std::cout<<"Inserisci il nome dell'utente:"<< std::endl;
                std::cin>>userName;

                auto itrl=shoppingLists.find(listName);
                auto itru=users.find(userName);

                try {
                    if(itrl==shoppingLists.end() || itru==users.end())
                        throw std::invalid_argument("Nome della lista o dell'utente non valido.");
                    else
                    {
                        itru->second.addList(itrl->second);
                    }
                }catch(std::invalid_argument& e){
                    std::cerr<<e.what()<< std::endl;
                }
                break;
            }

            case 5: {
                std::string listName;
                std::string userName;

                std::cout<<"Inserisci il nome della lista:"<< std::endl;
                std::cin>>listName;
                std::cout<<"Inserisci il nome dell'utente:"<< std::endl;
                std::cin>>userName;

                auto itrl=shoppingLists.find(listName);
                auto itru=users.find(userName);

                try {
                    if (itrl == shoppingLists.end() || itru == users.end())
                        throw std::invalid_argument("Nome della lista o dell'utente non valido");
                    else {
                        itru->second.removeList(listName);
                    }
                } catch (std::invalid_argument &e) {
                    std::cerr << e.what() << std::endl;
                }
                break;
            }

            case 6: {
                operations = false;
                break;
            }

            default: {
                std::cout << "Scelta non valida, perfavore riprova." <<  std::endl;
                break;
            }
        }
    }

    //------------------------------------------------------------------------------------------------------------------

    std::cout <<  std::endl <<  std::endl << "5) RIVEDI LE TUE CREAZIONI (UTENTI, LISTE, ARTICOLI)" <<  std::endl;

    for (const auto &user : users) {
        std::cout <<  std::endl;
        std::cout << "User name: " << user.first <<  std::endl;

        for (const auto &list : user.second.getLists()) {
            std::cout <<  std::endl;
            printItems(*list.second);

            const std::string &listName = list.second->getListName();

            auto itrl = shoppingLists.find(listName);

            if (itrl != shoppingLists.end()) {
                const ShoppingList &shoppingList = itrl->second;

                std::cout <<  std::endl << "Articoli nella lista \"" << listName << "\":" <<  std::endl;

                for (const auto &itemType : shoppingList.getItems()) {
                    const std::shared_ptr<Item> &item= itemType.second;
                    std::cout << "- " << item->getName() << " (" << item->getQuantity() << ")";
                    std::cout << (item->isPurchasedStatus() ? " Comprato" : " Non comprato") <<  std::endl;
                }
                std::cout <<  std::endl;
            }
        }
    }

    //------------------------------------------------------------------------------------------------------------------

     return 0;


}
