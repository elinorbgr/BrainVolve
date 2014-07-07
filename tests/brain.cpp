#include <UnitTest++/UnitTest++.h>

#include "../src/brain.hpp"

SUITE(brain)
{
    TEST(BasicBrainTestCase)
    {
        // Basic Brain test, with only hardcoded inputs and outputs
        // all biases will be 0
        Brain brain("-MAMaS1Ex-P2UbSEx",{"MAMa", "PUb"},{"SEx"});
        auto out = brain.answer({2.0,1.0});
        CHECK_EQUAL(1, out.size());
        CHECK_CLOSE(0.5, out[0], 0.001);
    }
}
