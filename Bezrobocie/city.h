#pragma once

/**
*  Struktura reprezentująca miasto. 
*  Zawiera zarówno dane na temat miasta podane w pliku, jak i informacje o położeniu w liście miast.
*/

struct City
{
    std::string name; //!< Nazwa miasta
    int citizensCount; //!< Ilość mieszkańców aktywnych zawodowo
    int workplacesCount; //!< Ilość miejsc 
    float unemploymentRate; //!< Stopa bezrobocia miasta
    
    bool rateIncreased; //!< Flaga ustawiana gdy stopa bezrobocia w mieście wzrośnie

    City * next; //!< Wskaźnik na następne miasto w liście
    City * previous; //!< Wskaźnik na poprzednie miasto w liście


    void imigration(int count); //!< Metoda zmieniająca ilość mieszkańców
    void development(int count); //!< Metoda zmieniająca ilość miejsc pracy

    void print(); //!< Metoda ypisuje informacje na temat miasta

    int unemployed(); //!< Metoda zwraca ilość niezatrudnionych mieszkańców
    int employed(); //!< Metoda zwraca ilość zatrudnionych mieszkańców

};

