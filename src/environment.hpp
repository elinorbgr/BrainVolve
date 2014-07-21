#ifndef ALIFE_ENVIRONMENT_HPP
#define ALIFE_ENVIRONMENT_HPP

class Pheromone
{
    private:
        double m_ampl;
        double m_radius;

    public:
        const int id;
        const double x;
        const double y;

        Pheromone(int channel_id, double xpos, double ypos, double ampl);
        void grow();

        double distance_to(double ox, double oy)  const;
        double get_ampl() const;
        double radius() const;
};

#endif // ALIFE_ENVIRONMENT_HPP
