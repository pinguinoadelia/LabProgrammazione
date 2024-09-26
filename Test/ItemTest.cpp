
#include "gtest/gtest.h"
#include "../Item.h"

class ItemSuite : public ::testing::Test {
protected:
    Item item = Item("Mela", "Frutta", 2);
};

TEST_F(ItemSuite, Costructor){
    ASSERT_EQ("Mela", item.getName());
    ASSERT_EQ("Frutta", item.getCategory());
    ASSERT_EQ(2, item.getQuantity());
    ASSERT_FALSE(item.isPurchasedStatus());
}

TEST_F(ItemSuite, Setter) {
    item.setName("Cavolo");
    item.setCategory("Verdura");
    item.setQuantity(4);
    item.markItem(true);
    ASSERT_EQ("Cavolo", item.getName());
    ASSERT_EQ("Verdura", item.getCategory());
    ASSERT_EQ(4, item.getQuantity());
    ASSERT_TRUE(item.isPurchasedStatus());
}

TEST_F(ItemSuite, toString) {
    ASSERT_EQ("Mela (Frutta) qnt. 2 [da comprare]", item.to_string());
}
