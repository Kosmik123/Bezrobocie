#include "stdafx.h"
#include "city.h"

using namespace std;


void City::imigration(int count)
{
    // Increases amount of unemployed citizens in the city
    float lastRate = unemploymentRate;
    int un = unemployed();
    citizensCount += count;
    unemploymentRate = 1.0 * un / citizensCount;
    if (unemploymentRate > lastRate) rateIncreased = true;
    
    cout << "Imigracja do miasta " << name << " w ilosci " << count << " ludzi. \n";
}


void City::development(int count)
{
    float lastRate = unemploymentRate;
    workplacesCount += count;
    if (unemploymentRate > lastRate) rateIncreased = true;

    cout << "Rozwoj miasta " << name << " o " << count << " miejsc pracy. \n";
}

void City::print()
{
    cout << name << " ma " << citizensCount << " mieszkancow aktywnych zawodowo i "
        << workplacesCount << " miejsc pracy. Stopa bezrobocia wynosi " << unemploymentRate << endl;
}


int City::unemployed()
{
    return (int)citizensCount * unemploymentRate;
}

int City::employed()
{
    return citizensCount - unemployed();
}


