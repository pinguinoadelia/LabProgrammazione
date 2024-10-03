
#include "gtest/gtest.h"
#include "../Item.h"
#include "../ShoppingList.h"

class ShoppingListSuite : public ::testing::Test {
protected:
    ShoppingList lista = ShoppingList("Lunedì");
    Item a1 = Item("Mela", "Frutta", 2);
    Item a2 = Item("Pera", "Frutta", 3);
    Item a3 = Item("Cavolo", "Verdura", 5);

    virtual void SetUp() {
        lista.insertItem(a1);
        lista.insertItem(a2);
        lista.insertItem(a3);
    }
};

TEST_F(ShoppingListSuite, Costructor) {
    ASSERT_EQ("Lunedì", lista.getListName());
    ASSERT_EQ(3, lista.notBoughtLenght());
}

TEST_F(ShoppingListSuite, InOut) {
    lista.setListName("Martedì");
    ASSERT_EQ("Martedì", lista.getListName());
    ASSERT_EQ(3, lista.notBoughtLenght());
    ASSERT_EQ(8, lista.getListSize());
    lista.markItemAsBought(a2.getName());
    ASSERT_EQ(2, lista.notBoughtLenght());
    lista.removeItem(a1.getName());
    ASSERT_EQ(1, lista.notBoughtItems().size());
}

TEST_F(ShoppingListSuite, Ricerca) {
    Item a5 = Item("Pollo", "Carne", 2);
    Item a6 = Item("Pera", "Frutta", 3);
    ASSERT_FALSE(lista.findItem(a5.getName()));
    ASSERT_TRUE(lista.findItem(a6.getName()));
    ASSERT_EQ(2, lista.getItemsByCategory("Frutta").size());
}