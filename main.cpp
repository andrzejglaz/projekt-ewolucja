#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <sstream>
#include <string>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <algorithm>
#include "functions.h"
#include "structures.h"

using namespace std;
/**
 * @file main.cpp
 */



int main(int ile, char* params[])
{

   main_params parameters = read_main_params(params, ile);
   if (parameters.is_ok() == 0)
   {
       message();
       return 0;
   }
   const int p = parameters.p; /**<  ilość pokolen */
   const int k = parameters.k; /**<  ilosc par do krzyzowania*/
   const double m = parameters.m;/**<  prog mutacji*/
   const string input_file = parameters.input_file; /**<  plik wejsciowy z populacja */
   const string output_file = parameters.output_file; /**<  plik z wyjsciową populacja */
    
    vector<vector<int>> individuals = read_from_file(input_file); /**< wektor wektorow zawierajacy obecne pokolenie osobnikow */
    if (individuals.size() == 0) //jeżeli nie uda się otowrzyć pliku albo plik jest pusty
        return 0;
    adaptation(individuals);
    for (int x = 0; x < p; x++)
    {
       if (individuals.size() < 2)
       {
            cout << "niestety wszystkie osobniki umarly";
            break;
       }
       
        crossing(individuals, k);
        mutation(individuals, m);
        adaptation(individuals);

       
    }
    
    save_in_file(individuals, output_file);
  
    return 0;

}

