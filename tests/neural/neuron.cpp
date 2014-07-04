#include <UnitTest++/UnitTest++.h>

#include "neural/neuron.hpp"

using namespace neural;

SUITE(Neuron)
{

    TEST(BasicNeuronTestCase)
    {
        Neuron input1 = Neuron::input_neuron();
        Neuron input2 = Neuron::input_neuron();
        Neuron out = Neuron(&neural::af::linear);

        out.link(&input1, 2.0);
        out.link(&input2, 3.0);
        out.set_bias(-4.0);

        input1.set_value(1.0);
        input2.set_value(-1.0);

        out.compute();
        out.sync();

        CHECK_CLOSE(-5.0, out.get_value(), 0.01);
    }

}
