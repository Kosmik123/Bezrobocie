// Bezrobocie.cpp : Program manages cities employment.
//

#include "stdafx.h"
#include "city.h"
#include "cityList.h"

using namespace std;

// functions
void loadCitiesFromFile(string fname); //!< Funkcja wczytuje dane z pliku do struktury
void saveCitiesToFile(string fname); //!< Funkcja zapisuje dane ze struktury do pliku
void printAll(); //!< Funkcja wypisuje dane każdego miasta w liście
void generateReport(string fname); //!< Funkcja generuje plik raportu

// Command switches
const string s_fin = "-fin";
const string s_sb = "-sb";
const string s_imi = "-imigracja";
const string s_rozw = "-rozwoj";
const string s_p = "-p";
const string s_u = "-u";
const string s_fr = "-frozwoj";
const string s_w = "-w";

CityList cities; //!< Lista miast

int main(int argc, char ** argv)
{
    string filename = "";
    cities.size = 0;
    
    int i = 1;
    while (i < argc)
    {
        if (*argv[i] == '-') // check if command
        {
            // which command
            if (argv[i] == s_fin)
            {
                filename = argv[i + 1];
                loadCitiesFromFile(filename);
                if (cities.empty())
                {
                    cout << "Error loading file!" << endl;
                    filename = "";
                    break;
                }
                i += 1;
            }
            else if (argv[i] == s_sb)
            {
                /*
                cout << "Before sort:" << endl;
                for (City *c = cities.first; c != nullptr; c = c->next)
                {
                    cout << "Miasto " << k << " to " << c->name << " " << c->unemploymentRate << endl;
                    k++;
                }*/
                cities.sortByRate();
                /*cout << endl << "After sort:" << endl;
                for (City *c = cities.first; c != nullptr; c = c->next)
                {
                    cout << "Miasteczko " << k << " to " << c->name << " " << c->unemploymentRate << endl;
                    k++;
                }*/
            }
            else if (argv[i] == s_imi)
            {
                string cn = argv[i + 1];
                int pn = atoi(argv[i + 2]);
                cities.findByName(cn)->imigration(pn);
                i += 2;
            }
            else if (argv[i] == s_rozw)
            {
                string cn = argv[i + 1];
                int pn = atoi(argv[i + 2]);
                cities.findByName(cn)->development(pn);
                i += 2;
            }
            else if (argv[i] == s_p)
            {
                cities.transfer(atoi(argv[i + 1]));
                i += 1;
            }
            else if (argv[i] == s_u)
            {
                cities.deleteSmallCities();
            }
            else if (argv[i] == s_fr)
            {
                if (argv[i + 1] != nullptr)
                    generateReport(argv[i + 1]);
                else
                    generateReport("Rozwoj_" + filename);
                i += 1;
            }
            else if (argv[i] == s_w)
            {
                if (argv[i + 1] == nullptr)
                {
                    printAll();
                }
                else
                {
                    City *cn = cities.findByName(argv[i + 1]);
                    if (cn != nullptr)
                        cn->print();
                    else
                        cout << "No city: " << argv[i + 1] << endl;
                }
                i += 1;
            }
            else
            {
                cout << "Unknown command " << string(argv[i]);
            }
        }
        else
        {
            cout << "Wrong usage!";
        }
        i++;
    }

    saveCitiesToFile(filename);

    return 0;
}

void loadCitiesFromFile(string fname)
{
    string dataName;
    int dataPeople;
    int dataWork;
    float dataRate;

    City *currentCity;

    ifstream file;
    file.open(fname);
    if (file.is_open())
    {
        while ( !file.eof() )
        {
            file >> dataName;
            file >> dataPeople;
            file >> dataWork;
            file >> dataRate;
         
            //cout << dataName << endl;

            City *newCity = new City();
            newCity->name = dataName;
            newCity->citizensCount = dataPeople;
            newCity->workplacesCount = dataWork;
            newCity->unemploymentRate = dataRate;
            newCity->rateIncreased = false;

            cities.addCity(newCity);
        }
        file.close();
    }
    else
    {
        cities.first = NULL;
    }
}

void saveCitiesToFile(string fname)
{
    if (fname != "")
    {
        ofstream file;
        file.open(fname);
        if (file.is_open())
        {
            for (City *c = cities.first; c != nullptr; c = c->next)
            {
                file << c->name << "\t" << c->citizensCount << "\t" << c->workplacesCount << "\t" << c->unemploymentRate;
                if (c != cities.last) file << "\n";
                //cout << "Dopisuje miasto " << c->name << endl;
            }
            file.close();
        }
        else
        {
            cout << "Saving file error!" << endl;
        }
    }
}

void printAll()
{
    for (City *c = cities.first; c != nullptr; c = c->next)
    {
        c->print();
    }
}

void generateReport(string fname)
{
    ofstream file;
    for (City *c = cities.first; c != nullptr; c = c->next)
    {
        file.open(fname);
        if (file.is_open())
        {
            file << "Miasta odznaczajace sie stalym rozwojem \n\n";
            file << "Nazwa" << "\t" << "Ludnosc" << "\t" << "Miejsca" << "\t" << "Stopa" << endl;
            for (City *c = cities.first; c != nullptr; c = c->next)
            {
                if (!c->rateIncreased)
                {
                    file << c->name << "\t" << c->citizensCount << "\t" << c->workplacesCount << "\t" << c->unemploymentRate;
                    if (c != cities.last) file << "\n";
                }
            }
            file.close();
        }
        else
        {
            cout << "Saving file error!" << endl;
        }
    }
}