#include <UnitTest++/UnitTest++.h>

#include "neural/network.hpp"
#include "neural/neuron.hpp"

using namespace neural;

SUITE(Network)
{
    struct BasicContainedNetworkFixture
    {
        Network net;
        BasicContainedNetworkFixture()
        {
            // 7 neurons : 3 -2 -2
            Neuron input1 = Neuron::input_neuron();
            Neuron input2 = Neuron::input_neuron();
            Neuron input3 = Neuron::input_neuron();
            Neuron internal1(&af::linear);
            Neuron internal2(&af::linear);
            Neuron out1(&af::linear);
            Neuron out2(&af::linear);
            // build the network
            internal1.set_bias(1.0);
            internal1.link(input1, 1.0);
            internal1.link(input2, 3.0);
            internal2.set_bias(1.0);
            internal2.link(input2, 2.0);
            internal2.link(input3, 1.0);
            out1.set_bias(-1.0);
            out1.link(internal1, 2.0);
            out1.link(internal2, 1.0);
            out2.set_bias(0.0);
            out2.link(internal2, 2.0);
            // offer them to the network container
            net.emplace_input_neuron(input1);
            net.emplace_input_neuron(input2);
            net.emplace_input_neuron(input3);
            net.emplace_internal_neuron(internal1);
            net.emplace_internal_neuron(internal2);
            net.emplace_output_neuron(out1);
            net.emplace_output_neuron(out2);
        }
    };

    TEST_FIXTURE(BasicContainedNetworkFixture, BasicNetworkTestCase)
    {
        // run the network
        net.set_inputs({-2.0, 1.0, 2.0});
        // output should be stabilized after second run
        CHECK_ARRAY_CLOSE(std::vector<double>({ 0.0,  0.0}), net.get_outputs(), 2, 0.01);
        net.step();
        CHECK_ARRAY_CLOSE(std::vector<double>({-1.0,  0.0}), net.get_outputs(), 2, 0.01);
        net.step();
        CHECK_ARRAY_CLOSE(std::vector<double>({ 8.0, 10.0}), net.get_outputs(), 2, 0.01);
        net.step();
        CHECK_ARRAY_CLOSE(std::vector<double>({ 8.0, 10.0}), net.get_outputs(), 2, 0.01);
    }

    TEST_FIXTURE(BasicContainedNetworkFixture, BasicLearninNetworkTestCase)
    {
        // stabilize the network to its output
        net.set_inputs({-2.0, 1.0, 2.0});
        net.step();
        net.step();
        // output is {8.0, 10.0} lets give à feedback to {0.0, 0.0}
        net.add_errors({-8.0, -10.0});
        // acknoledge error
        net.step();
        CHECK_ARRAY_CLOSE(std::vector<double>({ 8.0,  10.0}), net.get_outputs(), 2, 0.01);
        // update out layer
        net.step();
        CHECK_ARRAY_CLOSE(std::vector<double>({ 8.0,  10.0}), net.get_outputs(), 2, 0.01);
        // update intermediate layer
        net.step();
        CHECK_ARRAY_CLOSE(std::vector<double>({ -232.0,  -250.0}), net.get_outputs(), 2, 0.01);
        // progatae new values
        net.step();
        CHECK_ARRAY_CLOSE(std::vector<double>({ -232.0,  -250.0}), net.get_outputs(), 2, 0.01);
        // linear activation funcs are sure a bad idea !
        net.step();
        CHECK_ARRAY_CLOSE(std::vector<double>({ 7664.0,  7814.0}), net.get_outputs(), 2, 0.01);
    }
}
