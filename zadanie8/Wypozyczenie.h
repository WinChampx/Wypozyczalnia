#pragma once
#include <string.h>
#include <iostream>
#include <string>
using namespace std;

class Wypozyczenie
{
private:
	static int id_static;
	int id;
	int id_klienta;
	int id_sprzetu;
	string data_pozyczenia;
	string data_zwrotu;
	bool czy_wypozyczone;
	double kwota_za_pozyczenie;

public:
	Wypozyczenie();
	Wypozyczenie(int id_klienta, int id_sprzetu, string data_pozyczenia);
	friend ostream& operator<<(ostream& wy, const Wypozyczenie& w);
	int get_id_klienta()
	{
		return id_klienta;
	}
	int get_id_sprzetu()
	{
		return id_sprzetu;
	}
	int get_id()
	{
		return id;
	}
	void set_data_zwrotu(string data)
	{
		data_zwrotu = data;
	}
	void oblicz_koszt_wypozyczenia(double cena_za_godzine);
	bool czy_zwrocone()
	{
		return data_zwrotu != "";
	}
};