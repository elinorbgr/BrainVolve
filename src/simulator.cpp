#include "simulator.hpp"

#include <cmath>

Simulator::Simulator(int width, int height):
    scene_width(width), scene_height(height)
{
}

void Simulator::step()
{
    // update animals
    std::list<Pheromone> created_pheromones;
    for(auto& ani : m_animals)
    {
        auto created = ani.step(m_pheromones);
        created_pheromones.insert(created_pheromones.end(),
                                  std::make_move_iterator(created.begin()),
                                  std::make_move_iterator(created.end()));
        for(auto it = m_objects.begin(); it != m_objects.end();)
        {
            if(std::pow(ani.get_x() - (*it)->x, 2) + std::pow(ani.get_y() - (*it)->y, 2) <= 0.01)
            {
                // interaction
                (*it)->interact(ani);
            }
            if((*it)->is_consumed())
                it = m_objects.erase(it);
            else
                ++it;
        }
    }
    m_pheromones.insert(m_pheromones.end(),
                        std::make_move_iterator(created_pheromones.begin()),
                        std::make_move_iterator(created_pheromones.end()));
    // pheromones of remaining objects
    for(auto& ph : m_objects)
    {
        auto created = ph->pheromones();
        m_pheromones.insert(m_pheromones.end(),
                            std::make_move_iterator(created.begin()),
                            std::make_move_iterator(created.end()));
    }
    // update pheromones
    for(auto it = m_pheromones.begin(); it != m_pheromones.end();)
    {
        (*it).grow();
        if((*it).get_ampl() < 0.001)
            it = m_pheromones.erase(it);
        else
            ++it;
    }
}
