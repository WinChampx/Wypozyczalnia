#pragma once
#include <string.h>
#include <iostream>
using namespace std;
class Klient
{
private:
	static int id_static;
	int id;
	string imie;
	string nazwisko;
public:
	Klient();
	Klient(string imie, string nazwisko);
	friend ostream& operator<<(ostream& wy, const Klient& k);
	int get_id()
	{
		return id;
	}
};