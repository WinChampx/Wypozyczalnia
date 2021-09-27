#pragma once
#include <string.h>
#include <iostream>
using namespace std;

class Sprzet
{
private:
	static int id_static;
	int id;
	int dostepna_ilosc;
	string rodzaj;
	string przeznaczenie;
	double cena_za_godzine;

public:
	Sprzet();
	Sprzet(string rodzaj, string przeznaczenie, double cena_za_godzine, int dostepna_ilosc);
	friend ostream& operator<<(ostream& wy, const Sprzet& s);
	int get_id()
	{
		return id; 
	}
	string get_rodzaj()
	{
		return rodzaj;
	}
	string get_przeznaczenie()
	{ 
		return przeznaczenie;
	}
	double get_cena()
	{
		return cena_za_godzine;
	}
	bool pozycz();
	void oddaj();
};
