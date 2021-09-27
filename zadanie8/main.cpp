#include <iostream>
#include <vector>
#include "Klient.h"
#include "Sprzet.h"
#include "Wypozyczenie.h"
#include <time.h>

#pragma warning(disable:4996)

using namespace std;

/*Funkcja zwraca aktualny czas w formacie DD-MM-YYYY HH-MM-SS jako string*/
string get_current_time() {
	time_t rawtime;
	struct tm* timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", timeinfo);
	string str(buffer);

	return str;
}

void dodaj_sprzet(vector<Sprzet>& sprzet) {
	int ilosc;
	double cena;
	string rodzaj, przeznaczenie;
	cout << "Podaj nazwe sprzetu: ";
	cin >> rodzaj;
	cout << "Podaj przeznaczenie (np stok narciarski): ";
	cin >> przeznaczenie;
	cout << "Podaj ilosc sztuk: ";
	cin >> ilosc;
	cout << "Podaj cene za godzine: ";
	cin >> cena;
	sprzet.push_back(Sprzet(rodzaj, przeznaczenie, cena, ilosc));
	cout << "Nowy sprzet zostal dodany.\n";
}
void wyszukaj(vector<Sprzet>sprzet) {
	string nazwa, przeznaczenie;
	double cena;

	int opcja;
	cout << "Wybierz opcje szukania.\n";
	cout << "1. Nazwa.\n";
	cout << "2. Przeznaczenie.\n";
	cout << "3. Cena.\n";
	cin >> opcja;
	switch (opcja) {
	case 1:
		cout << "Podaj nazwe sprzetu (np narty / kaski): ";
		cin >> nazwa;
		for (Sprzet s : sprzet) {
			if (s.get_rodzaj() == nazwa)
				cout << s;
		}
		break;
	case 2:
		cout << "Podaj przeznaczenie sprzetu (np stok): ";
		cin >> przeznaczenie;
		for (Sprzet s : sprzet) {
			if (s.get_przeznaczenie() == przeznaczenie)
				cout << s;
		}
		break;
	case 3:
		cout << "Podaj cene sprzetu (np 10): ";
		cin >> cena;
		for (Sprzet s : sprzet) {
			if (s.get_cena() == cena)
				cout << s;
		}
		break;
	default:
		cout << "Wyobrano nieprawidlowa opcje.\n";
	}
}
void wypozycz(vector<Klient>& klienci, vector<Sprzet>& sprzety, vector<Wypozyczenie>& wypozyczenia) {
	cout << "1 - Dodaj nowego klienta\n";
	cout << "2 - Wybierz istniejacego klienta\n";
	int opcja, id_klienta, id_sprzetu;
	string imie, nazwisko;
	Klient* klient = NULL;
	Sprzet* sprzet = NULL;
	cin >> opcja;

	/*WYBIERANIE KLIENTA*/
	if (opcja == 1) {
		cout << "Podaj imie: "; cin >> imie;
		cout << "Podaj nazwisko: "; cin >> nazwisko;
		Klient k(imie, nazwisko);
		klienci.push_back(k);
		klient = &k;
		id_klienta = k.get_id();
	}
	else if (opcja == 2) {
		cout << "Wybierz id klienta: "; cin >> id_klienta;

		for (Klient k : klienci) {
			if (k.get_id() == id_klienta) {
				klient = &k;
				break;
			}
		}
	}
	else {
		cout << "Wyobrano nieprawidlowa opcje.\n";
	}

	/*WYBIERANIE SPRZETU*/
	cout << "Witaj w panelu wybierania sprzetu.\n";
	wyszukaj(sprzety);
	cout << "Podaj id sprzetu, ktory chcesz pozyczyc: ";
	cin >> id_sprzetu;
	for (Sprzet& s : sprzety) {
		if (s.get_id() == id_sprzetu) {
			sprzet = &s;
			break;
		}
	}
	if (klient == NULL) cout << "Klient o podanym ID nie istnieje.\n";
	else if (sprzet == NULL) cout << "Sprzet o podanym ID nie istnieje.\n";
	else {
		if (sprzet->pozycz()) {
			wypozyczenia.push_back(Wypozyczenie(klient->get_id(), sprzet->get_id(), get_current_time()));
			cout << "Sprzet zostal pomyslnie wypozyczony.\n";
		}
		else {
			cout << "Produkt jest obecnie niedostepny. Wszystkie sztuki zostaly wypozyczone.\n";
		}

	}

}

Sprzet* znajdz_sprzet_po_id(vector<Sprzet>& sprzety, int id) {
	Sprzet* sprzet = NULL;
	for (Sprzet& s : sprzety) {
		if (s.get_id() == id) {
			sprzet = &s;
			break;
		}
	}

	return sprzet;
}

void zwroc(vector<Sprzet>& sprzety, vector<Wypozyczenie>& wypozyczenia) {
	int id, id_sprzetu, id_klenta;
	bool istnieje = false;
	cout << "Podaj id wypozyczenia, ktore chcesz zwrocic: "; cin >> id;
	for (Wypozyczenie& w : wypozyczenia) {
		if (id == w.get_id()) {
			istnieje = true;
			if (w.czy_zwrocone()) {
				cout << "Ten sprzet juz zostal zwrocony.\n";
				break;
			}
			id_sprzetu = w.get_id_sprzetu();
			id_klenta = w.get_id_klienta();
			w.set_data_zwrotu(get_current_time());
			Sprzet* sprzet = znajdz_sprzet_po_id(sprzety, id_sprzetu);
			if (sprzet != NULL) {
				sprzet->oddaj();
				w.oblicz_koszt_wypozyczenia(sprzet->get_cena());
			}
			cout << "Sprzet zostal pomyslnie oddany.\n";
			break;
		}
	}
	if (!istnieje) {
		cout << "Wypozyczenie o podanym ID nie istnieje.\n";
	}
}

void wypisz_wypozyczenia(vector<Wypozyczenie>& wypozyczenia) {
	for (Wypozyczenie w : wypozyczenia)
		cout << w;
}

/*Rysowanie menu w konsoli*/
void rysuj_menu() {
	cout << "1 - Wprowadzenie sprzetu\n";
	cout << "2 - Wyszukanie sprzetu\n";
	cout << "3 - Wypozyczenie sprzetu\n";
	cout << "4 - Zwrocenie sprzetu sprzetu\n";
	cout << "5 - Wyjscie\n";
	cout << "6 - ADMIN zobacz liste wypozyczen\n";
}

/*funkcja stopujaca program aby uzytkownik mogl odczytac informacje na ekranie*/
void stop() {
	cout << "\n\n\n\n\n\n\n\n";
	system("pause");
}

void init(vector<Klient>& lista_klientow, vector<Sprzet>& lista_sprzetu, vector<Wypozyczenie>& lista_wypozyczen) {
	lista_klientow.push_back(Klient("Jan", "Kowalski"));
	lista_klientow.push_back(Klient("Marcin", "Nowak"));
	lista_sprzetu.push_back(Sprzet("narty", "stok", 10, 1));
	lista_sprzetu.push_back(Sprzet("kaski", "stok", 2, 3));
	lista_wypozyczen.push_back(Wypozyczenie(0, 0, get_current_time()));
	lista_wypozyczen.push_back(Wypozyczenie(1, 1, get_current_time()));
}

int main() 
{
	vector<Klient> lista_klientow;
	vector<Sprzet> lista_sprzetu;
	vector<Wypozyczenie> lista_wypozyczen;
	init(lista_klientow, lista_sprzetu, lista_wypozyczen);

	bool koniec = false;
	int opcja_szukania;
	char akcja;
	while (!koniec) {
		rysuj_menu();
		cout << "Podaj akcje: ";
		cin >> akcja;
		akcja = tolower(akcja);
		switch (akcja) {
		case '1':
			dodaj_sprzet(lista_sprzetu);
			break;
		case '2':
			wyszukaj(lista_sprzetu);
			break;
		case '3':
			wypozycz(lista_klientow, lista_sprzetu, lista_wypozyczen);
			break;
		case '4':
			zwroc(lista_sprzetu, lista_wypozyczen);
			break;
		case '5':
			koniec = true;
			lista_klientow.clear();
			lista_sprzetu.clear();
			lista_wypozyczen.clear();
			break;
		case '6':
			wypisz_wypozyczenia(lista_wypozyczen);
			break;
		default:
			cout << "Nieprawidlowa komenda. Wcisnij dowolny klawisz.";
			break;
		}
		stop();
		cin.clear(); //czyszczenie bufora
		system("cls"); //czyszczenie konsoli
	}



	return 0;
}