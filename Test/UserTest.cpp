
#include "gtest/gtest.h"
#include "../Item.h"
#include "../ShoppingList.h"
#include "../User.h"

class UserSuite : public ::testing::Test {
protected:
    User utente = User("Cbum");
    ShoppingList lista1 = ShoppingList("Lunedì");
    ShoppingList lista2 = ShoppingList("Martedì");
    Item a1 = Item("Mela", "Frutta", 2);
    Item a2 = Item("Pera", "Frutta", 3);
    Item a3 = Item("Cavolo", "Verdura", 5);
    Item a4 = Item("Pollo", "Carne", 5);
    Item a5 = Item("Bresaola", "Affettato", 5);

    virtual void SetUp(){
        lista1.insertItem(a1);
        lista1.insertItem(a2);
        lista1.insertItem(a3);
        lista2.insertItem(a4);
        lista2.insertItem(a5);
        utente.addList(lista1);
        utente.addList(lista2);
    }
};

TEST_F(UserSuite, Costructor){
    ASSERT_EQ("Cbum", utente.getName());
    ASSERT_EQ(2, utente.getNumLists());
    ASSERT_EQ(lista1.notBoughtLenght(), utente.getRemainedItems("Lunedì"));
    ASSERT_EQ(lista2.notBoughtLenght(), utente.getRemainedItems("Martedì"));
}

TEST_F(UserSuite, Setter){
    utente.setName("Cris");
    utente.removeList("Martedì");
    Item a("Orata", "Pesce", 2);
    utente.addItem("Lunedì", a);
    ASSERT_EQ("Cris", utente.getName());
    ASSERT_EQ(1, utente.getNumLists());
    ASSERT_EQ(lista1.notBoughtLenght()+1, utente.getRemainedItems("Lunedì"));
    utente.removeItem("Lunedì", a);
    ASSERT_EQ(lista1.notBoughtLenght(), utente.getRemainedItems("Lunedì"));
}

