#pragma once
#include <vector>
#include <string>


/**
*\struct sort_by_adaptation
*\brief struktura reprezentujaca podstawowe wlasnosci osobnikow
*/
struct sort_by_adaptation
{
    long int rating;/**< wartosc przystosowania danego osobnika rowna wartosci zwroconej z funkcji f() */
    std::vector<int> chromosome; /**< chromosom danego osobnika */
    double roulette; /**< pozycja w kole ruletkowym */
};

/**
*\struct main_params
*\brief struktura reprezentuj¹ca parametry funkcji main()
*/
struct main_params
{
    int p; /**<  iloœæ pokolen */
    int k; /**<  ilosc par do krzyzowania*/
    double m;/**<  prog mutacji*/
    std::string input_file; /**<  nazwa pliku wejsciowego z populacja */
    std::string output_file; /**<  nazwa pliku z wyjsciowego populacja */
    bool is_ok()
    {
        return!(p == 0 || k == 0 || m == 0 || input_file.empty() == 1 || output_file.empty() == 1);
    }
};
