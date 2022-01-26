#pragma once
#include <vector>
#include "structures.h"

//using namespace std;
/**
 * @file functions.h
 */
/**
 * @fn int f(vector<long int> individual);
 * @brief funkcja ustawiajaca wartosc osobnika wzgledem funkcji przystosowania
 * 
 *		 funkcja zamienia binarny zapis chromosomu osobnika na dziesietny, nastepnie zwraca wartosc oceny(f) wstawiajac otrzymana liczbe we wzor funkcji 
 * @param individual wektor zawierajacy kolejne chromosomy danego osobnika
 */
int f(std::vector<int> individual);

/**
 * @fn void adaptation(vector<vector<long int>>& individuals)
 * @brief funkcja sprawdzajaca przystosowanie osobnikow 
 * 
 *  	  funkcja na podstawie oceny zwroconej przez funkcje f ustala prawdopodobienstwo pozostania kazdego osobnika w populacji, 
 *		  nastepnie umieszcza proporcjonalnie wzgledem tego prawdopodobienstwa osobniki w "kole ruletkowym" i losuje, ktore z n ich przetrwaja, a ktore nie
 * @param individuals wektor wektorow zawierajacy chromosomy wszytskich osobnikow w obecnym pokoleniu
 */
void adaptation(std::vector<std::vector<int>>& individuals);

/**
 * @fn void crossing(vector<vector<long int>>& individuals, int k)
 * @brief funkcja krzyzujaca osobniki
 * 
 *		 funkcja losuje k par osobnikow, ktore nastepnie krzyzuje tzn. przerywa chromosom kazdego w losowym miejscu i laczy poczatek pierwszego osobnika,
 *		 z koncem drugiego i odpowiednio tak samo dla 2 osobnika, nastepnie czysci wektor ze starym pokoleniem i kopiuje do niego nowe, wlasnie utworzone
 * @param individuals wektor wektorow zawierajacy chromosomy wszytskich osobnikow w obecnym pokoleniu
 * @param k ilosc par losowanych do krzyzowania
 */
void crossing(std::vector<std::vector<int>>& individuals, int k);

/**
 * @fn vector<vector<long int>> read_from_file(string input_file)
 * @brief funkcja odczytuj¹ca dane z liku wejsciowego
 * 
 *		 funkcja pobiera dane w wersach i zapisuje je do wektora, wszystkie wiersze s¹ nastepnie zapisywane do wektora wektorow
 * @param input_file plik z populacja wejsciowa
 */
std::vector<std::vector<int>> read_from_file(std::string input_file);

/**
 * @fn void save_in_file(vector<vector<long int>> individuals, string output_file)
 * @brief funkcja zapisujaca dane do pliku wyjsciowego
 * 
 *		 funkcja zapisuje obence pokolenie do pliku wyjsciowego podanego przez uzytkownika
 * @param individuals wektor wektorow zawierajacy chromosomy wszytskich osobnikow w obecnym pokoleniu
 * @param output_file plik do zapisu populacji wyjsciowej
 */
void save_in_file(std::vector<std::vector<int>> individuals, std::string output_file);

/**
 * @fn void mutation(vector<vector<long int>>& individuals, double m)
 * @brief funkcja odpowiadajaca za mutacje wsrod osobnikow
 * 
 *		funkcja dla kazdego allelu losuje liczbe z przedzialu <0,1>, jezeli jest ona nie wieksza od wspolczynnika mutacji,
 *		to zamienia go z 0 na 1, badz odwrotnie 
 * @param individuals wektor wektorow zawierajacy chromosomy wszytskich osobnikow w obecnym pokoleniu
 * @param m prog mutacji
 */
void mutation(std::vector<std::vector<int>>& individuals, double m);

/**
 * @fn bool is_parameter_existing(string parameter)
 * @brief funkcja sprawdzajaca czy podany parametr funkcji main zostal wpisany
 * 
 *		 funkcja na podstawie tego czy pierwszym znakiem nie jest '-' sprawdza czy parametr zostal wpisany
 * @param parameter parametr, ktory funkcja analizuje
 */
bool is_parameter_existing(std::string parameter);

/**
 * @fn bool is_string_a_number(string parameter)
 * @brief funkcja sprawdzajaca czy podany parametr (string) jest liczba
 * 
 *		 funkcja uzywajac funkcji isdigit(), sprawdza dla kazdego znaku w stringu czy jest on cyfra, dodatkowo funkcja akceptuje wystepowanie
 *		 symbolu kropki (dla liczb zmiennoprzecinkowych)
 * @param paremter parametr (string), ktory funkcja analizuje
 */
bool is_string_a_number(std::string parameter);

/**
 * @fn main_params read_main_params(char* params[], int ile)
 * @brief funkcja odczytuj¹ca parametry funkcji main()
 *
 *		 funkcja odczytuje po koleiparametry wprowadzone przez u¿ytkownika i sprawdza ich poprawnoœæ (czy s¹ odpowiedniego typu oraz czy u¿ytkownik w ogóle je wprowadzi³)
 * @param params[] tablica parametrów i ich etykiet
 * @param ile d³ugoœæ tablicy params[]
 */
main_params read_main_params(char* params[], int ile);

/**
 * @fn void message()
 * @brief funkcja wyœwietlajaca komunikat jak uzywac programu
 */
void message();