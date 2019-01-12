#include "stdafx.h"
#include "cityList.h"


City * CityList::findByName(std::string name)
{
    City * result = NULL;
    for (City *city = first; city != nullptr; city = city->next)
    {
        if (city->name == name)
        {
            result = city;
            break;
        }
    }
    return result;
}


City * CityList::highestRate()
{

    City * result = first;
    float rate = result->unemploymentRate;
    for (City *i = result->next; i != nullptr; i = i->next)
    {
        if (i->unemploymentRate > rate)
        {
            rate = i->unemploymentRate;
            result = i;
        }
    }
    //if (result != nullptr) std::cout << "Najwyzsza stope ma " << result->name;
    return result;
}

City * CityList::lowestRate()
{
    City * result = first;
    float rate = result->unemploymentRate;
    for (City * i = result->next; i != nullptr; i = i->next)
    {
        //std::cout << "Checking " << i << " " << i->name << std::endl;
        if (i->unemploymentRate < rate)
        {
            rate = i->unemploymentRate;
            result = i;
        }
    }
    //if (result != nullptr) std::cout << "Najnizsza stope ma " << result->name;
    return result;
}

void CityList::deleteSmallCities()
{
    for (City *city = first; city != nullptr; city = city->next)
    {
        if (city->citizensCount < 1000)
        {
            deleteCity(city);
        }
    }
}

void CityList::deleteCity(City *m)
{
    std::cout << "Usuniecie miasta " << m->name << std::endl;
    if (m == first) 
        first = m->next;
    else
        m->previous->next = m->next;

    if (m == last) 
        last = m->previous;
    else
        m->next->previous = m->previous;
    
    size -= 1;
}

void CityList::addCity(City *m)
{   
    if (size == 0)
    {
        first = last = m;
    }
    else
    {
        last->next = m;
        m->previous = last;
        last = m;
    }
    size += 1;
    
    //std::cout << "Dodaje miasto " << m->name << " pod adres " << m << std::endl << "Nowy rozmiar to: " << size << "\n\n";
}

void CityList::swap(City *m1, City *m2)
{
    City *m1n, *m1p, *temp;

    /*
    std::cout << "m1 to " << m1->name << std::endl;
    std::cout << "first to " << first->name << std::endl;
    std::cout << "m2 to " << m2->name << std::endl;
    std::cout << "last to " << last->name << std::endl;
    */

    if (m1 != last)  m1->next->previous = m2;
    if (m1 != first) m1->previous->next = m2;

    if (m2 != last)  m2->next->previous = m1;
    if (m2 != first) m2->previous->next = m1;

    if (m1 == first)
        first = m2;
    else if (m2 == first)
        first = m1;

    if (m2 == last)
        last = m1;
    else if (m1 == last)
        last = m2;

    m1n = m1->next;
    m1p = m1->previous;
    m1->next = m2->next;
    m1->previous = m2->previous;
    m2->next = m1n;
    m2->previous = m1p;
}

void CityList::sortByRate()
{
    for (City *one = first; one != nullptr; one = one->next)
    {
        for (City *two = one->next; two != nullptr; two = two->next)
        {
            if (two->unemploymentRate < one->unemploymentRate)
            {
                swap(one, two);
            }
        }
    }
}

void CityList::transfer(int N)
{
    City *m1 = highestRate();
    City *m2 = lowestRate();

    int maxN1 = (int)(0.3 * m1->unemployed());
    int maxN2 = (int)(0.8 * (m2->workplacesCount - m2->employed()));

    N = std::min(std::min(maxN1, maxN2), N);

    std::cout << "Przeplyw " << N << " osob bezrobotnych z miasta " << m1->name << " do miasta " << m2->name << std::endl;

    m1->imigration(-N);
    m2->imigration(N);

    m1->development(-0.05 * m1->workplacesCount);
    m2->development(+0.05 * m2->workplacesCount);
}


bool CityList::empty()
{
    return first == nullptr;
}