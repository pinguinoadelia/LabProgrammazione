
#include "gtest/gtest.h"
#include "../Item.h"
#include "../ShoppingList.h"
#include "../User.h"

class ObserverSuite : public ::testing::Test, public Observer {
protected:
    User* utente = new User("Cbum");
    ShoppingList lista = ShoppingList("Lunedì");
    Item articolo = Item("Pollo", "Carne", 5);
    bool control = false;

    void onUpdate(const std::string& listName) override {
        control = true;
    }

    virtual void SetUp(){
        lista.insertItem(articolo);
        lista.addObserver(this);
    }

    virtual void TearDown(){
        lista.removeObserver(this);
    }
};

TEST_F(ObserverSuite, Costructor){
    utente->addList(lista);
    lista.markItemAsBought(articolo.getName());
    ASSERT_TRUE(control);
}



