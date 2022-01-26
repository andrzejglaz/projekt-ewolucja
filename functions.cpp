#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <vector>
#include <string>
#include <cmath>
#include<algorithm>
#include "functions.h"
#include "structures.h"

using namespace std;

void adaptation(vector<vector<int>>& individuals)
{
    // selekcja zgodnie z zadaniem
    /*vector<long int> do_skopiowania;
    for (int x = 0; x < osobniki.size(); x++)
    {
        double wartosc_f = f(osobniki[x]);
        if (wartosc_f < w) //jezeli wynik jest mniejszy od progu rozmnazania to osobnik jest usuwany
        {
            osobniki.erase(osobniki.begin() + x);
            x--; // x jest pomniejszany, ¿eby mozna bylo przetestowac osobnika, ktory teraz znajduje siê na miejscu osobnika usnietego
        }
        else if (wartosc_f > r)
            do_skopiowania.push_back(x); // je¿eli wynik jest wiêkszy ni¿ próg rozmna¿ania to osobnik jest zapisywany do wektora osobników do dodania
    }
    for (int x = 0; x < do_skopiowania.size(); x++)
        osobniki.push_back(osobniki[do_skopiowania[x]]);// i dodany do populacji */

    //selekcja ruletka
    vector<sort_by_adaptation> sorting;
    long long int sum = 0;
    int min_rating = 0;
    vector<vector<int>> to_copy; // nowe pokolenie 

    for (int x = 0; x < individuals.size(); x++) 
    {
        if (individuals[x].size() < 2 || individuals[x].size() > 12)
        {
            individuals.erase(individuals.begin() + x);
            continue;
        }
        sort_by_adaptation individual;
        individual.rating = f(individuals[x]);
        if (individual.rating < min_rating)
            min_rating = individual.rating;
        individual.chromosome = individuals[x];
        sorting.push_back(individual);
    }
    double last_result = 0;
    for (int x = 0; x < sorting.size(); x++)
        sum += sorting[x].rating - min_rating;
    for (int x = 0; x < sorting.size(); x++)
    {
        double probability = ((double)(sorting[x].rating - min_rating))/ sum;
        sorting[x].roulette = probability + last_result;
        last_result = sorting[x].roulette;
    }
    srand(time(NULL));
    for (int x = 0; x < sorting.size(); x++)
    {
        int factor = rand() % 1000;
        double random = (double)factor/1000;
        if (random <= sorting[0].roulette)
            to_copy.push_back(sorting[0].chromosome);
        else if (random > sorting[sorting.size() - 1].roulette)
            to_copy.push_back(sorting[sorting.size() - 1].chromosome);
        else {
            int y = 0;
            while (!(random > sorting[y].roulette && random <= sorting[y + 1].roulette))
                y++;
            to_copy.push_back(sorting[y].chromosome);
        }
    }
    individuals.clear();
    individuals = to_copy; // nowe pokolenie do rozmna¿ania

}
void crossing(vector<vector<int>>& individuals, int k)//przekazanie osobników przez referencjê
{
    srand(time(NULL));
    vector<vector<int>> new_generation;
    for (int x = 0; x < k; x++) //dla ka¿dej z k par 
    {
        int random = rand() % individuals.size();
        vector<int> first = individuals[random];
        
        int random2 = rand() % individuals.size();
        while (random2 == random)  //upewnienie siê, ¿e nie zostanie wylosowany 2 razy ten sam osobnik
            random2 = rand() % individuals.size();
        vector<int> second = individuals[random2];

        random = rand() % first.size();
        while (random == 0 || random == first.size()) //upewnienie siê, ¿e przerwanie nie bêdzie przed 1 albo za ostatnim el. chromosomu
            random = rand() % first.size();
        int breakpoint1 = random;

        random = rand() % second.size();
        while (random == 0 || random == second.size())
            random = rand() % second.size();
        int breakpoint2 = random;

        vector<int> new_individual1;
        for (int x = 0; x < breakpoint1; x++)//³¹czenie pierwszej czêœci chromosomu 
            new_individual1.push_back(first[x]);
        for (int x = breakpoint2; x < second.size(); x++)//i drugiej
            new_individual1.push_back(second[x]);
        new_generation.push_back(new_individual1); // nowy osobnik dodawany jest do populalcji


        vector<int> new_individual2;
        for (int x = breakpoint1; x < first.size(); x++)//³¹czenie pierwszej czêœci chromosomu 
            new_individual2.push_back(first[x]);
        for (int x = 0; x < breakpoint2; x++)//i drugiej
            new_individual2.push_back(second[x]);
        new_generation.push_back(new_individual2);

    }
    individuals.clear(); // ¿eby nie by³o wycieków pamiêci
    individuals = new_generation;

}
/*double f(vector<long int> osobnik)
{
    double wynik = 0;
    vector<long int> perfect_alpha =  {1, 2, 3, 4, 5, 6, 7, 8, 9, 0}; // perfekcyjny zestaw chromosomów, do którego d¹¿y ka¿dy osobnik
    if (osobnik.size() > 3 * perfect_alpha.size())
        wynik -= 3;
    if (osobnik.size() < perfect_alpha.size() / 2)
        wynik -= 3;
    int mniejszy = osobnik.size();
    if (perfect_alpha.size() < osobnik.size())
        mniejszy = perfect_alpha.size();
    if (osobnik.size() == perfect_alpha.size())//czy maj¹ taki sam rozmiar
        wynik += 1;
    else if ((osobnik.size() + 3 >= perfect_alpha.size() && osobnik.size() < perfect_alpha.size()) || (osobnik.size() > perfect_alpha.size() && osobnik.size() - 3 >= perfect_alpha.size())) //czy mieœci siê w granicach +- 3
        wynik += 0.75;
    else
        wynik -= 0.25;
    int suma_czesciowa_osobnika = 0;
    int suma_czesciowa_alphy = 0;
    for (int x = 0; x < mniejszy; x++)//dla ka¿dego chromosomu...
    {
        suma_czesciowa_osobnika += osobnik[x];
        suma_czesciowa_alphy += perfect_alpha[x];
        if (osobnik[x] == perfect_alpha[x])// czy s¹ takie same
            wynik += 0.5;
        else if (osobnik[x] % 2 == perfect_alpha[x] % 2)// czy s¹ takiej samej parzystoœci
            wynik += 0.25;
        else
            wynik -= 0.25;
    }
    if (suma_czesciowa_alphy == suma_czesciowa_osobnika)// czy ich sumy chromosomów s¹ takie same
        wynik += 1;
    else if ((suma_czesciowa_osobnika + 10 > suma_czesciowa_alphy && suma_czesciowa_alphy > suma_czesciowa_osobnika) || (suma_czesciowa_osobnika - 10 < suma_czesciowa_alphy && suma_czesciowa_alphy < suma_czesciowa_osobnika))// czy suma chromosomów osobnika mieœci siê w przedziale +-10 alphy
        wynik += 0.25;
    else
        wynik -= 0.25;
    return 1 / (1 + pow(1.71, -wynik)); // wynik wk³adam do sigmoidu 
}*/
vector<vector<int>> read_from_file(string input_file)
{
    vector<vector<int>> individuals;
    ifstream file(input_file);
    if (file)
    {
        string line;
        vector<int> verse;
        while (getline(file, line))
        {
            stringstream ss; // wy³uskanie intów
            ss << line;
            int number;
            while (ss >> number)
                verse.push_back(number);
            individuals.push_back(verse);
            verse.clear();
        }
        file.close();
    }
    else
        cout << "nie udalo sie otworzyc pliku: " << input_file << " z populacja";
        
    return individuals;
}
void save_in_file(vector<vector<int>> individuals, string out_file)
{
    ofstream file(out_file);
    if (file)
    {
        for (int x = 0; x < individuals.size(); x++)
        {
            for (int a : individuals[x])
                file << a << " ";
            file << endl;
        }
        file.close();
    }
    else
        cout << "nie udalo sie otworzyc pliku :(";
}
int f(vector<int> individual) // jakaœ funkcja
{
    //f(x) = (-3)(x^2 - 70)
    int chromosome_decimally = 0;
    int multiply = 1;
    for (int x = individual.size()-1; x >= 0; x--)
    {
        chromosome_decimally += individual[x] * multiply;
        multiply *= 2;
    }
    return -((double)1/20)* (pow(chromosome_decimally, 2));
}
void mutation(vector<vector<int>>& individuals, double m)
{
    srand(time(NULL));
    for (int x = 0; x < individuals.size(); x++)
    {
        for (int y = 0; y < individuals[x].size(); y++)
        {
            double random = (double)(rand() % 1000)/1000;
            if (random <= m)
            {
                if (individuals[x][y] == 0)
                    individuals[x][y] = 1;
                else
                    individuals[x][y] = 0;
            }
        }
   }
}
bool is_parameter_existing(string parameter)
{
    return (parameter[0] != '-');     
}
bool is_string_a_number(string parameter)
{
    for (int x = 0; x < parameter.size(); x++)
    {
        if (isdigit(parameter[x]) == 0 && parameter[x] != '.')
            return false;
    }
    return true;
}
main_params read_main_params(char* params[], int ile)
{
    main_params parameters{ 0, 0, 0 };
    if (ile > 1)
    {

        for (int x = 1; x < ile; x++)
        {
            if (_stricmp(params[x], "-h") == 0)
                message();
            if (_stricmp(params[x], "-i") == 0)
            {
                if (x + 1 < ile)
                {
                    if (is_parameter_existing(params[x + 1]))
                    {

                        parameters.input_file = params[x + 1];
                        x += 1;

                    }
                }
                else
                    cout << "nie podales pliku z wejsciem" << endl;
            }
            else if (_stricmp(params[x], "-o") == 0)
            {
                if (x + 1 < ile)
                {
                    if (is_parameter_existing(params[x + 1]))
                    {

                        parameters.output_file = params[x + 1];
                        x += 1;
                    }
                }
                else
                    cout << "nie podales pliku z wyjsciem" << endl;
            }
            else if (_stricmp(params[x], "-p") == 0)
            {
                if (x + 1 < ile)
                {
                    if (is_parameter_existing(params[x + 1]))
                    {
                        if (is_string_a_number(params[x + 1]))
                        {
                            parameters.p = stoi(params[x + 1]);
                            x += 1;
                        }
                    }
                    else
                        cout << "parametr -p ktory podales: " << params[x + 1] << " nie jest liczba" << endl;
                }
                else
                    cout << "nie podales parametru p" << endl;
            }
            else if (_stricmp(params[x], "-k") == 0)
            {
                if (x + 1 < ile)
                {
                    if (is_parameter_existing(params[x + 1]))
                    {
                        if (is_string_a_number(params[x + 1]))
                        {
                            parameters.k = stoi(params[x + 1]);
                            x += 1;
                        }
                        else
                            cout << "parametr -k ktory podales: " << params[x + 1] << " nie jest liczba" << endl;
                    }
                }
                else
                    cout << "nie podales parametru k" << endl;
            }
            else if (_stricmp(params[x], "-m") == 0)
            {
                if (x + 1 < ile)
                {
                    if (is_parameter_existing(params[x + 1]))
                    {
                        if (is_string_a_number(params[x + 1]))
                        {
                            parameters.m = stod(params[x + 1]);
                            x += 1;
                        }
                        else
                            cout << "parametr -m ktory podales: " << params[x + 1] << " nie jest liczba" << endl;
                    }
                }
                else
                    cout << "nie podales parametru m" << endl;
            }
        }
    }
 
    return parameters;

}
void message()
{
    cout << "Aby uruchomic program nalezy podac odpowiednie parametry z przelacznikami:" << endl;
    cout << "-k ilosc pokolen" << endl;
    cout << "-p ilosc par do krzyzowania" << endl;
    cout << "-m prog mutacji" << endl;
    cout << "-o nazwa pliku wyjsciowego" << endl;
    cout << "-i nazwa pliku wejsciowego" << endl;
}