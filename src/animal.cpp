#include "animal.hpp"

#include <cmath>

Animal::Animal(const std::string &genome, double x, double y, double dir):
    m_brain(genome, {"Ea"}, {"Mx", "My"}),
    m_genome(genome), m_energy(50.0), m_x(x), m_y(y), m_dir(dir)
{
}

void Animal::step(std::list<Pheromone> &env)
{
    // setup input vector
    std::vector<int> input_ids = m_brain.get_input_channels();
    std::vector<double> inputs(input_ids.size()+1, 0.0);
    inputs[0] = m_energy;

    auto inputs_it = input_ids.begin() + 1;
    for(int id : input_ids)
    {
        if(id > 0)
        {
            // this is an amplitude entry
            for(auto& p : env)
                if(p.id == id && p.distance_to(m_x, m_y) <= p.radius())
                    *inputs_it += p.get_ampl();
        }
        else //(in < 0)
        {
            // this is a direction entry
        double gx = 0.0, gy = 0.0;
            for(auto &p : env)
                if(p.id == -id)
                {
                    double distance = p.distance_to(m_x, m_y);
                    if (distance <= p.radius())
                    {
                        gx += (p.x - m_x) * p.get_ampl() / distance;
                        gy += (p.y - m_y) * p.get_ampl() / distance;
                    }
                }
            // tangent half-angle formula
            double vx = std::cos(m_dir), vy = std::sin(m_dir);
            *inputs_it = (vx*gy - vy*gx) / (vx*gx + vy*gy + std::sqrt(gx*gx+gy*gy));
        }
        inputs_it++;
    }

    // feed it to brain
    std::vector<double> outputs = m_brain.answer(inputs);

    // create new pheromones
    std::vector<int> output_ids = m_brain.get_output_channels();
    auto outputs_it = outputs.begin() + 2;
    for(int id : output_ids)
    {
        if(*outputs_it > 0.0)
            env.push_back(Pheromone(id, m_x, m_y, *outputs_it));
    }

    // move the animal
    double va = outputs[0];
    double vb = outputs[1];
    double speed = (va + vb) * 0.5;
    m_dir += (vb - va) * 0.5;
    m_x += speed * std::cos(m_dir);
    m_y += speed * std::sin(m_dir);
    m_energy -= std::abs(speed) * 0.01;
}

void Animal::feed(double amount)
{
    m_energy += amount;
}

void Animal::hurt(double amount)
{
    m_energy -= amount;
}
