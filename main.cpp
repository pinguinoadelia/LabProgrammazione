#include <iostream>
#include <string>
#include <stdexcept>
#include "Subject.h"
#include "ShoppingList.h"
#include "User.h"
#include "Item.h"
#include "Observer.h"

// Funzione per stampare una ShoppingList
void print(const ShoppingList& sl) {
    std::cout << "Name of the shopping list: " << sl.getListName() << std::endl << std::endl;

    // Itera attraverso le categorie di articoli
    for (const auto& categoryEntry : sl.getItemCategories()) {
        const std::string& category = categoryEntry.first;
        int categoryNotBought = 0;

        if (categoryEntry.second != 0) {
            std::cout << "Category: " << category << std::endl;

            // Itera attraverso tutti gli articoli della lista
            for (const auto& itemEntry : sl.getItems()) {  // Usa il metodo corretto che restituisce la collezione di articoli
                const std::shared_ptr<Item> &item = itemEntry.second;

                // Verifica che l'articolo appartenga alla categoria corrente e che non sia stato acquistato
                if (item->getCategory() == category && !item->isPurchasedStatus()) {
                    std::cout << "- " << item->getName() << " (" << item->getQuantity() << ")";
                    std::cout << (item->isPurchasedStatus() ? "       Bought" : "       Not bought") << std::endl;
                    categoryNotBought += item->getQuantity();
                }
            }
            std::cout << std::endl;
        }
    }

    // Supponiamo che esista un metodo per ottenere il numero totale di articoli non acquistati
    std::cout << "Total number of items not bought: " << sl.markItemsAsNotBought() << std::endl << std::endl;
}

int main() {

    std::cout << "Welcome to the Shopping List App!" <<  std::endl <<  std::endl <<  std::endl;

    bool isCreationProcessing=true;
    int userChoice;
    std::map < std::string,User> users;
    std::map < std::string, ShoppingList> shoppingLists;
    std::map < std::string, Item> items;


    //------------------------------------------------------------------------------------------------------------------

    std::cout<<"1) CREATION OF THE SHOPPING LIST "<< std::endl<< std::endl;

    while(isCreationProcessing)
    {
        std::cout <<  std::endl << "Choose:" <<  std::endl;
        std::cout << "1. Create a new shopping list" <<  std::endl;
        std::cout << "2. Move on" <<  std::endl;
        std::cin>>userChoice;
        std::cout<< std::endl;

        switch (userChoice) {
            case 1 : {
                std::string shoppingListName;
                std::cout << "Enter the name of the new shopping list: ";
                std::cin >> shoppingListName;

                ShoppingList newShoppingList(shoppingListName);
                shoppingLists.insert(make_pair(shoppingListName, newShoppingList));

                std::cout << "Shopping list \"" << shoppingListName << "\" created." <<  std::endl;
                break;
            }

            case 2 : {
                isCreationProcessing=false;
                break;
            }

            default: {
                std::cout << "Invalid input. Please try again." <<  std::endl;
                break;
            }
        }
    }

    //------------------------------------------------------------------------------------------------------------------

    std::cout <<  std::endl << "2) CREATION OF THE ITEMS" <<  std::endl <<  std::endl;

    isCreationProcessing = true;

    while (isCreationProcessing) {
        std::cout <<  std::endl << "Choose:" <<  std::endl;
        std::cout << "1. Create a new item" <<  std::endl;
        std::cout << "2. Move on" <<  std::endl;

        std::cin >> userChoice;

        switch (userChoice) {
            case 1: {
                std::string itemName;
                int defaultQuantity = 1;
                std::string quantityString;
                int quantityInt;
                std::string itemCategory;

                std::cout << "Insert item name: ";
                std::cin >> itemName;
                std::cout <<  std::endl;

                std::cout << "Insert item category: ";
                std::cin >> itemCategory;
                std::cout <<  std::endl;

                std::cout << "Insert quantity";
                std::cin >> quantityString;
                std::cout <<  std::endl;

                if (quantityString == "default") {
                    quantityInt = defaultQuantity;
                } else {
                    try {
                        quantityInt = std::stoi(quantityString);
                    } catch ( std::invalid_argument &e) {
                        quantityInt = defaultQuantity; // Set default quantity if invalid input
                    }
                }

                try {
                    Item i(itemName, itemCategory, quantityInt);
                    items.insert(make_pair(itemName, i));
                } catch (std::out_of_range &e2) {
                    std::cerr << e2.what() <<  std::endl;
                }
                break;
            }

            case 2: {
                isCreationProcessing = false;
                break;
            }

            default: {
                std::cout << "Invalid choice. Please try again." <<  std::endl;
                break;
            }
        }
    }


    //------------------------------------------------------------------------------------------------------------------

    std::cout <<  std::endl << "3) CREATION OF THE USERS" <<  std::endl <<  std::endl;

    isCreationProcessing = true;

    while (isCreationProcessing) {
        std::cout <<  std::endl << "Choose:" <<  std::endl
             << "1. Create a new user" <<  std::endl
             << "2. Move on" <<  std::endl;

        std::cin >> userChoice;
        std::cout <<  std::endl;

        switch (userChoice) {
            case 1: {
                std::string userName;
                std::cout << "Insert User name: ";
                std::cin >> userName;

                std::cout <<  std::endl;

                User newUser(userName);
                users.insert(make_pair(userName, newUser));
                break;
            }

            case 2: {
                isCreationProcessing = false;
                break;
            }

            default: {
                std::cout << "Invalid choice. Please try again." <<  std::endl;
                break;
            }
        }
    }


    //------------------------------------------------------------------------------------------------------------------

    std::cout <<  std::endl <<  std::endl << "4) YOU CAN NOW EXECUTE OPERATIONS ON THE PREVIOUSLY CREATED LISTS, OBJECTS AND USERS"<< std::endl;

    bool operations=true;
    while(operations)
    {
        std::cout <<  std::endl;
        std::cout << "You have the following options:" <<  std::endl;
        std::cout << "1) Add an item to a list" <<  std::endl;
        std::cout << "2) Remove an item from a list (provide list name and item name)" <<  std::endl;
        std::cout << "3) Mark an item as purchased" <<  std::endl;
        std::cout << "4) Add a shopping list to a user's collection" <<  std::endl;
        std::cout << "5) Remove a shopping list from a user's collection" <<  std::endl;
        std::cout << "6) No more operations" <<  std::endl;
        std::cout <<  std::endl;

        std::cin>>userChoice;
        std::cout<< std::endl;

        switch (userChoice) {
            case 1 :{
                std::string listName;
                std::string itemName;
                std::cout<<"Insert list name:"<< std::endl;
                std::cin>>listName;
                std::cout<<"Insert item name:"<< std::endl;
                std::cin>>itemName;

                auto itrl=shoppingLists.find(listName);
                auto itrn=items.find(itemName);

                try {
                    if(itrl==shoppingLists.end()||itrn==items.end())
                        throw std::invalid_argument("Invalid list name or invalid item name");
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
                std::string itemName;
                std::string listName;

                std::cout<<"Insert list name:"<< std::endl;
                std::cin>>listName;
                std::cout<<"Insert item name:"<< std::endl;
                std::cin>>itemName;

                auto itrl=shoppingLists.find(listName);
                auto itrn=items.find(itemName);

                try {
                    if (itrl == shoppingLists.end() || itrn == items.end())
                        throw std::invalid_argument("Invalid list name or invalid item name");
                    else
                        itrl->second.removeItem(itemName);

                }catch(std::invalid_argument& e){
                    std::cerr<<e.what()<< std::endl;
                }
                break;
            }

            case 3: {
                std::string itemName;
                std::string listName;

                std::cout<<"Insert list name:"<< std::endl;
                std::cin>>listName;
                std::cout<<"Insert item name:"<< std::endl;
                std::cin>>itemName;

                auto itrl=shoppingLists.find(listName);
                auto itrn=items.find(itemName);

                try {
                    if (itrl == shoppingLists.end() || itrn == items.end())
                        throw std::invalid_argument("Invalid list name or invalid item name");
                    else
                        itrl->second.markItemAsBought(itemName);

                }catch(std::invalid_argument& e){
                    std::cerr<<e.what()<< std::endl;
                }
                break;
            }

            case 4: {
                std::string listName;
                std::string userName;

                std::cout<<"Insert list name:"<< std::endl;
                std::cin>>listName;
                std::cout<<"Insert user name:"<< std::endl;
                std::cin>>userName;

                auto itrl=shoppingLists.find(listName);
                auto itru=users.find(userName);

                try {
                    if(itrl==shoppingLists.end() || itru==users.end())
                        throw std::invalid_argument("Invalid list name or invalid user name");
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

                std::cout<<"Insert list name:"<< std::endl;
                std::cin>>listName;
                std::cout<<"Insert user name:"<< std::endl;
                std::cin>>userName;

                auto itrl=shoppingLists.find(listName);
                auto itru=users.find(userName);

                try {
                    if (itrl == shoppingLists.end() || itru == users.end())
                        throw std::invalid_argument("Invalid list/user name");
                    else {
                        itru->second.removeList(listName);
                    }
                } catch (std::invalid_argument &e) {
                    std::cerr << e.what() << std::endl;
                }
                break;
            }

            case 6: {
                operations=false;
                break;
            }

            default: {
                std::cout << "Invalid choice. Please try again." <<  std::endl;
                break;
            }
        }
    }

    //------------------------------------------------------------------------------------------------------------------

    std::cout <<  std::endl <<  std::endl << "5) REVIEW YOUR CREATIONS (USERS, LISTS, ITEMS)" <<  std::endl;

    for (const auto &userPair : users) {
        std::cout <<  std::endl;
        std::cout << "User name: " << userPair.first <<  std::endl;

        for (const auto &listPair : userPair.second.getLists()) {
            std::cout <<  std::endl;
            print(*listPair.second);

            const std::string &listName = listPair.second->getListName();

            auto itrl = shoppingLists.find(listName);

            if (itrl != shoppingLists.end()) {
                const ShoppingList &shoppingList = itrl->second;

                std::cout <<  std::endl << "Items in list \"" << listName << "\":" <<  std::endl;

                for (const auto &itemEntry : shoppingList.getItems()) {
                    const std::shared_ptr<Item> &item= itemEntry.second;
                    std::cout << "- " << item->getName() << " (" << item->getQuantity() << ")";
                    std::cout << (item->isPurchasedStatus() ? "       Bought" : "       Not bought") <<  std::endl;
                }
                std::cout <<  std::endl;
            }
        }
    }

    //------------------------------------------------------------------------------------------------------------------

    return 0;
}
