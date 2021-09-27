#include "Klient.h"
int Klient::id_static = 0;
Klient::Klient()
	:imie(""), nazwisko("")
{
	id = id_static++;
}
Klient::Klient(string imie, string nazwisko)
	: imie(imie), nazwisko(nazwisko)
{
	id = id_static++;
}
ostream& operator<<(ostream& wy, const Klient& k) {
	return wy << "ID: " << k.id << " " << k.imie << " " << k.nazwisko << endl;
}