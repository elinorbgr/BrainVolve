#include "environment.hpp"

#include <cmath>

Pheromone::Pheromone(int channel_id, double xpos, double ypos, double ampl):
    m_ampl(M_PI*ampl), m_radius(1.0), id(channel_id), x(xpos), y(xpos)
{}

void Pheromone::grow()
{
    double r = m_radius/(m_radius + 1.0);
    m_ampl *= r*r;
    m_radius += 1.0;
}

double Pheromone::distance_to(double ox, double oy) const
{
    return std::sqrt(std::pow(ox-x, 2) + std::pow(oy-y, 2));
}

double Pheromone::get_ampl() const
{
    return m_ampl;
}

double Pheromone::radius() const
{
    return m_radius;
}
