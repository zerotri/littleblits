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

    SUBCASE("Removing from the array decreases Count") {
        testArray.Remove(0);

        REQUIRE(testArray.Count() == 0);
        REQUIRE(testArray.AllocatedSize() >= 10);
    }

    SUBCASE("Adding many elements to the array increases AllocatedSize") {
        REQUIRE(testArray.AllocatedSize() >= 10);
        REQUIRE(testArray.AllocatedSize() < 14);

        REQUIRE(testArray.Add("This") == 1);
        REQUIRE(testArray.Add("is") == 2);
        REQUIRE(testArray.Add("a") == 3);
        REQUIRE(testArray.Add("test") == 4);
        REQUIRE(testArray.Add("attempting") == 5);
        REQUIRE(testArray.Add("to") == 6);
        REQUIRE(testArray.Add("increase") == 7);
        REQUIRE(testArray.Add("AllocatedSize") == 8);
        REQUIRE(testArray.Add("of") == 9);
        REQUIRE(testArray.Add("MutableArray") == 10);
        REQUIRE(testArray.Add("by") == 11);
        REQUIRE(testArray.Add("adding") == 12);
        REQUIRE(testArray.Add("14") == 13);
        REQUIRE(testArray.Add("elements") == 14);

        REQUIRE(testArray.Count() == 14);
        REQUIRE(testArray.AllocatedSize() >= 14);
        REQUIRE(testArray[11] == "adding");
        REQUIRE(testArray[13] == "elements");
    }
}
