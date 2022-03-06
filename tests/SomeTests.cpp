//
// Created by David Mrnustik on 6/3/22.
//
#include "gtest/gtest.h"
#include "../utils.h"

TEST(SomeSuite, SomeTest) {
    map_table_type ttype { {"A", {{ "1", "2", "3" }}}, { "B", {{ "4", "5" }}}};
    table_type result {{ "4", "5" }};
    ASSERT_EQ(getList(&ttype, "B"), result);
}