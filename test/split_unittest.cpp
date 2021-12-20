#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"
#include "zfish.h"

using namespace std;
namespace zf = zfish;

TEST(zfish__Test, split__Test) {
    vector<string_view> ws1{"a", "b", "c"};
    EXPECT_EQ(ws1, zf::split("a b c"));
    EXPECT_EQ(ws1, zf::split("a,b,c", ","));
    EXPECT_EQ(ws1, zf::split(",a,b,c,", ","));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

    return 0;
}