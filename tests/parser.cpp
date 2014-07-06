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
        auto neurons = neurons_from_genome("-zeKU89+ZH73H7c++9UNZ7e-+IOU+u73");
        CHECK_EQUAL(3, neurons.size());
        CHECK_EQUAL("ZHHc", neurons[0].first);
        CHECK_EQUAL(737, neurons[0].second);
        CHECK_EQUAL("UNZe", neurons[1].first);
        CHECK_EQUAL(97, neurons[1].second);
        CHECK_EQUAL("u", neurons[2].first);
        CHECK_EQUAL(0, neurons[2].second);
    }

    TEST(LinkListTestCase)
    {
        // Yeah, a big part of the genome is not parsed at all
        auto links = links_from_genome("+ehnc675Nai-YH8e76zhdoTID-879h+-7TkU8Jk--ZE3GKXJ7nh+BCnany-UZ867YEnrz++eZEcxuDHgnkzc");
        CHECK_EQUAL(4, links.size());
        CHECK_EQUAL("YHe", links[0].first.first);
        CHECK_EQUAL("z", links[0].first.second);
        CHECK_EQUAL(-68, links[0].second);
        CHECK_EQUAL("Tk", links[1].first.first);
        CHECK_EQUAL("UJk", links[1].first.second);
        CHECK_EQUAL(-1, links[1].second);
        CHECK_EQUAL("ZEGKXJn", links[2].first.first);
        CHECK_EQUAL("h", links[2].first.second);
        CHECK_EQUAL(37, links[2].second);
        CHECK_EQUAL("UZYEn", links[3].first.first);
        CHECK_EQUAL("r", links[3].first.second);
        CHECK_EQUAL(867, links[3].second);
    }
}
