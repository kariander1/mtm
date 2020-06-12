#include <vector>

class Road
{
    private:
    double len;
    int sped;  
public:
    double length()
    {
        return len;
    } // km
    int speed()
    {
        return sped;
    }     // km per hour
};

class Car
{
public:
    virtual double getFuelConsumption(const int speed) const = 0;
};

class Toytoa : public Car
{
public:
    double getFuelConsumption(const int speed) const override
    {
        double km_to_fuel = 33.3;
        if (speed > 90)
            km_to_fuel *(90 / speed);
        return km_to_fuel;
    }
};

double getPetrol(std::vector<Road> roads, const Car &car)
{
    double petrol_sum = 0;
    for (std::vector<Road>::iterator road = roads.begin(); road != roads.end(); ++road)
    {        
        double cur_length = road->length();
        double petrol_km_ratio = car.getFuelConsumption(road->speed());
        petrol_sum += (cur_length * speed_km_ratio);
    }
    return petrol_sum;
}
int main()
{
    return 0;
}

