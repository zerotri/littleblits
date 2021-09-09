#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <rockit/platform/platform.h>

TEST_CASE("main") {
    Rockit::Platform::LogInfo("Main", "Called from main function");
}
