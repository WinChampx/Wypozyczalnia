#include "Wypozyczenie.h"
int Wypozyczenie::id_static = 0;
Wypozyczenie::Wypozyczenie()
	:id_klienta(-1), id_sprzetu(-1), data_pozyczenia(""), data_zwrotu(""), czy_wypozyczone(1)
{
	id = id_static++;
	kwota_za_pozyczenie = 0;
}
Wypozyczenie::Wypozyczenie(int id_klienta, int id_sprzetu, string data_pozyczenia)
	: id_klienta(id_klienta), id_sprzetu(id_sprzetu), data_pozyczenia(data_pozyczenia), data_zwrotu(""), czy_wypozyczone(1)
{
	id = id_static++;
	kwota_za_pozyczenie = 0;
}
ostream& operator<<(ostream& wy, const Wypozyczenie& w) {
	return wy << "ID: " << w.id << " | Sprzet: " << w.id_sprzetu << " | Klient: " << w.id_klienta
		<< " | Data wypozyczenia: " << w.data_pozyczenia << " | Data zwrotu: " << w.data_zwrotu << " | Do zaplaty: " << w.kwota_za_pozyczenie << endl;
}
void Wypozyczenie::oblicz_koszt_wypozyczenia(double cena_za_godzine) {
	int dzien = stoi(data_zwrotu.substr(0, 2)) - stoi(data_pozyczenia.substr(0, 2));
	int miesiac = stoi(data_zwrotu.substr(3, 2)) - stoi(data_pozyczenia.substr(3, 2));
	int rok = stoi(data_zwrotu.substr(6, 4)) - stoi(data_pozyczenia.substr(6, 4));
	int godziny = stoi(data_zwrotu.substr(11, 2)) - stoi(data_pozyczenia.substr(11, 2));
	int minuty = stoi(data_zwrotu.substr(14, 2)) - stoi(data_pozyczenia.substr(14, 2));
	int sekundy = stoi(data_zwrotu.substr(17, 2)) - stoi(data_pozyczenia.substr(17, 2));
	cout << "Czas uzytkowania DD-MM-RRRR GG:MM:SS:     " << dzien << "-" << miesiac << "-" << rok << " " << godziny << ":" << minuty << ":" << sekundy << endl;
	kwota_za_pozyczenie = (rok * 365 * 24 + miesiac * 30 * 24 + dzien * 24 + godziny + minuty / 60.0 + sekundy / 3600.0) * cena_za_godzine;
}