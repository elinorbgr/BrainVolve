#include <UnitTest++/UnitTest++.h>

#include "../src/brain.hpp"

SUITE(brain)
{
    TEST(MinimalBrainTestCase)
    {
        // Basic Brain test, with only hardcoded inputs and outputs
        // all biases will be 0
        Brain brain("-MAMaS1Ex-P2UbSEx",
                    {"MAMa", "PUb"},
                    {"SEx"});
        auto out = brain.answer({2.0, 1.0});
        CHECK_EQUAL(1, out.size());
        CHECK_CLOSE(0.5, out[0], 0.001);
    }

    TEST(CustomIOBrainTestCase)
    {
        // A simple brain with genetic IO
        Brain brain("+P34Ub-P2UbSEx-MAMaS1Ex+Y22Ay-P1UbTAz+42TAz",
                    {"MAMa"},
                    {"SEx"});
        CHECK_EQUAL(1, brain.get_input_channels().size());
        CHECK_EQUAL(34, brain.get_input_channels()[0]);
        CHECK_EQUAL(2, brain.get_output_channels().size());
        CHECK_ARRAY_EQUAL(std::vector<size_t>({22, 42}),
                          brain.get_output_channels(), 2);
        auto out = brain.answer({2.0, 1.0});
        CHECK_EQUAL(3, out.size());
        CHECK_ARRAY_CLOSE(std::vector<double>({0.5, 0.0, 1.0}),
                          out, 3, 0.001);

    }

    TEST(OffsetOverrideBrainTestCase)
    {
        Brain brain("+3TAz-MAM1aTAz",
                    {"MAMa"},
                    {"TAz"});
        // TAz should have an offset of 3, so putting MAMa to -3 should
        // still yield 1.0
        auto out = brain.answer({-3.0});
        CHECK_CLOSE(1.0, out[0], 0.001);
        // but if it is at -3.1, it should yield 0.0
        out = brain.answer({-3.1});
        CHECK_CLOSE(0.0, out[0], 0.001);
    }

    TEST(MultilayeredBrainTestCase)
    {
        // a brain with two layers
        Brain brain("-MAM1aYOu+YO2u-YOuTA3z+TA1z",
                    {"MAMa"},
                    {"TAz"});
        auto out = brain.answer({-1.0});
        // propagation not effective
        CHECK_CLOSE(1.0, out[0], 0.001);
        out = brain.answer({-3.0});
        // propagated {-1.0}
        CHECK_CLOSE(0.0, out[0], 0.001);
        out = brain.answer({-3.0});
        // propagated {-3.0}
        CHECK_CLOSE(1.0, out[0], 0.001);
    }
}
