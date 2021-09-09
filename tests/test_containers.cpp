#include <doctest/doctest.h>
#include <rockit/core/array.h>
#include <string>

TEST_CASE("MutableArray") {
    Rockit::MutableArray<std::string> testArray(10);

    REQUIRE(testArray.Count() == 0);
    REQUIRE(testArray.AllocatedSize() >= 10);

    SUBCASE("Adding to the array increases Count") {
        testArray.Add("This is a test string");

        REQUIRE(testArray.Count() == 1);
        REQUIRE(testArray.AllocatedSize() >= 10);
        REQUIRE(testArray[0] == "This is a test string");
    }
}
