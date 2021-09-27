#include "Sprzet.h"
int Sprzet::id_static = 0;
Sprzet::Sprzet()
	:cena_za_godzine(0.0), rodzaj(""), przeznaczenie(""), dostepna_ilosc(0)
{
	id = id_static++;
}
Sprzet::Sprzet(string rodzaj, string przeznaczenie, double cena_za_godzine, int dostepna_ilosc)
	: cena_za_godzine(cena_za_godzine), przeznaczenie(przeznaczenie), rodzaj(rodzaj), dostepna_ilosc(dostepna_ilosc)
{
	id = id_static++;
}
ostream& operator<<(ostream& wy, const Sprzet& s)
{
	return wy << "ID: " << s.id << "| Rodzaj: " << s.rodzaj << " | Cena za godzine: " << s.cena_za_godzine << " | Dostepnca ilosc: " << s.dostepna_ilosc << endl;
}

bool Sprzet::pozycz() {
	if (dostepna_ilosc > 0) 
	{
		dostepna_ilosc--;
		return true;
	}
	else
	{
		return false;
	}
}

void Sprzet::oddaj()
{
	dostepna_ilosc++;
}