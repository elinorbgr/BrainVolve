#include "objects.hpp"

//
// Object
//

Object::Object(double xpos, double ypos):
    x(xpos), y(ypos)
{
}

//
// SingleSmellObject
//

SingleSmellObject::SingleSmellObject(double xpos, double ypos,
                                     int smell_id, double smell_intensity):
    Object(xpos, ypos),
    m_smell_id(smell_id), m_smell_intensity(smell_intensity)
{
}

std::vector<Pheromone> SingleSmellObject::pheromones() const
{
    return {Pheromone(m_smell_id, x, y, m_smell_intensity)};
}


//
// ConsumableFeed
//

ConsumableFeed::ConsumableFeed(double xpos, double ypos,
                               double feeding_power,
                               int smell_id, double smell_intensity):
    SingleSmellObject(xpos, ypos, smell_id, smell_intensity),
    m_consumed(false), m_energy_amount(feeding_power)
{
}

void ConsumableFeed::interact(Animal& animal)
{
    animal.feed(m_energy_amount);
    m_consumed = true;
}

bool ConsumableFeed::is_consumed() const
{
    return m_consumed;
}

//
// Permanentrap
//

PermanentTrap::PermanentTrap(double xpos, double ypos,
                             double damage_power,
                             int smell_id, double smell_intensity):
    SingleSmellObject(xpos, ypos, smell_id, smell_intensity),
    m_damage_amount(damage_power)
{
}

void PermanentTrap::interact(Animal& animal)
{
    animal.hurt(m_damage_amount);
}

bool PermanentTrap::is_consumed() const
{
    return false;
}
