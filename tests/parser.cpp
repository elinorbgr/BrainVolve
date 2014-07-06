#include <UnitTest++/UnitTest++.h>

#include "../src/parser.hpp"

SUITE(parser)
{
    TEST(ValidatorTestCase)
    {
        // all these chars must be valid
        CHECK(is_valid_genom("abcdefghijklmnopqrstuvwxyz"));
        CHECK(is_valid_genom("ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
        CHECK(is_valid_genom("0123456789+-"));
        // other chars must not be
        CHECK(!is_valid_genom("_"));
        CHECK(!is_valid_genom("!"));
        CHECK(!is_valid_genom("#"));
        CHECK(!is_valid_genom("§"));
    }

    TEST(NeuronListTestCase)
    {
        auto neurons = neurons_from_genome("-zeKU89+ZH73H7c++9UNZ7e+IOU+u73");
        CHECK_EQUAL(3, neurons.size());
        CHECK_EQUAL("ZHHc", neurons[0].first);
        CHECK_EQUAL(737, neurons[0].second);
        CHECK_EQUAL("UNZe", neurons[1].first);
        CHECK_EQUAL(97, neurons[1].second);
        CHECK_EQUAL("u", neurons[2].first);
        CHECK_EQUAL(0, neurons[2].second);
    }
}
