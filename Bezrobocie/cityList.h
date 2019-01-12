#pragma once
#include "city.h"

/**
*  Struktura reprezentująca listę miast
*  Zawiera wskaźnik do pierwszego i ostatniego elementu listy oraz rozmiar listy.
*/

struct CityList
{
    int size; //!< Ilość miast w liście
    City * first; //!< Wskaźnik do pierwszego miasta w liście
    City * last; //!< Wskaźnik do ostatniego miasta w liście


    City * findByName(std::string name); //!< Metoda zwracająca wskaźnik do miasta na podstawie nazwy
    City * highestRate(); //!< Metoda zwraca miasto o największej stopie bezrobocia
    City * lowestRate(); //!< Metoda zwraca miasto o najmniejszej stopie bezrobocia

    void deleteSmallCities(); //!< Metoda usuwa z listy miasta o liczbie mieszkańców mniejszej niż 1000
    void deleteCity(City * m); //!< Metoda usuwa z listy miasto
    void addCity(City *m); //!< Metoda dodaje do listy miast

    void swap(City *m1, City *m2); //!< Metoda zamienia miejscami 2 miasta w liście
    void sortByRate(); //!< Metoda sortuje miasta według stopy bezrobocia

    void transfer(int N); //!< Metoda przeprowadza przepływ osób między miastami

    bool empty(); //!< Metoda sprawdza czy lista jest pusta

};

