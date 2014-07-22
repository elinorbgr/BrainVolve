#ifndef ALIFE_SIMULATOR_HPP
#define ALIFE_SIMULATOR_HPP

#include <list>

#include "animal.hpp"
#include "environment.hpp"
#include "objects.hpp"

class Simulator
{
    private:
        std::list<Animal> m_animals;
        std::list<std::unique_ptr<Object> > m_objects;
        std::list<Pheromone> m_pheromones;
    public:
        const unsigned int scene_width;
        const unsigned int scene_height;

        Simulator(int width, int height);

        void step();
};

#endif // ALIFE_SIMULATOR_HPP
