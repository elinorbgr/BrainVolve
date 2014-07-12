#include <UnitTest++/UnitTest++.h>

#include "neural/neuron.hpp"

using namespace neural;

SUITE(Neuron)
{
    struct BasicNetworkFixture
    {
        /*
         * A basic Network with two inputs and 1 linear neuron output
         * Structure is :
         *
         * In1 -- 2.0 -->  ------
         *                | -4.0 | --> Out
         * In2 -- 3.0 -->  ------
         */
        Neuron input1;
        Neuron input2;
        Neuron out;

        BasicNetworkFixture():
            input1(Neuron::input_neuron()),
            input2(Neuron::input_neuron()),
            out(neural::af::linear)
        {
            out.link(input1, 2.0);
            out.link(input2, 3.0);
            out.set_bias(-4.0);
        }
    };

    TEST_FIXTURE(BasicNetworkFixture, BasicNeuronTestCase)
    {
        // Input : { 1.0, -1.0}
        input1.set_value(1.0);
        input2.set_value(-1.0);
        out.compute();
        out.sync();
        CHECK_CLOSE(-5.0, out.get_value(), 0.01);
        // Input : { 3.0, 5.0}
        input1.set_value(3.0);
        input2.set_value(5.0);
        out.compute();
        out.sync();
        CHECK_CLOSE(17.0, out.get_value(), 0.01);
    }

    TEST_FIXTURE(BasicNetworkFixture, BasicLearningTestCase)
    {
        // Input : { 1.0, -1.0}
        input1.set_value(1.0);
        input2.set_value(-1.0);
        out.compute();
        out.sync();
        // output value is -5.0, we want 0 !
        out.add_error(5.0);
        out.compute();
        out.sync();
        // no learning is done yet, the error has only be acknoledged
        CHECK_CLOSE(-5.0, out.get_value(), 0.01);
        out.compute();
        out.sync();
        // now, it should have learned, new layout should be :
        // In1 --- 7.0 -->  ------
        //                 | +1.0 | --> Out
        // In2 -- -2.0 -->  ------
        CHECK_CLOSE(1.0, out.get_bias(), 0.01);
        // one more compute pass is needed to update end value
        out.compute();
        out.sync();
        CHECK_CLOSE(10.0, out.get_value(), 0.01);

    }
}
