#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct DaneNaDysk
{
	int id;
	int czasPrzyjscia;
	int miejsce;
	int czasDoZaglodzenia;
};
bool porownajCzasWykonania(const DaneNaDysk& a, const DaneNaDysk& b) {
	return a.czasPrzyjscia < b.czasPrzyjscia;
}
bool porownajPoMiejscu(const DaneNaDysk& a, const DaneNaDysk& b) {
	return a.miejsce < b.miejsce;
}
void wypelnienieDanymi(vector<DaneNaDysk>& a)
{
	for (int i = 0; i < 10000; i++)
	{
		int c = rand() % 100 + 1;
		if (c < 90)
		{
			c = -c;
		}
		a.push_back({ i + 1, rand() % 100000 + 1, rand() % 2000 + 1, c });
	}
}
// DZIALA
int FCFS(vector<DaneNaDysk> a, int start)
{
	sort(a.begin(), a.end(), porownajCzasWykonania);
	int niewykonane = a.size();
	// sprawdza czy zostalo wykonane jakies zadanie w przejsciu calej petli jesli nie to potem sprawdzam i powiekszam czas o 1 wiecej
	int czyZmieniloWartosc;
	int czas = 0;
	while (niewykonane > 0)
	{
		for (int i = 0; i < niewykonane; i++)
		{
			czyZmieniloWartosc = niewykonane;
			if (czas >= a[i].czasPrzyjscia)
			{
				//cout << "czas: " << czas << " ";
				czas += abs(start - a[i].miejsce);
				//cout << a[i].miejsce << " czas: " << czas << endl;
				start = a[i].miejsce;
				a.erase(a.begin() + i);
				niewykonane--;
				break;
			}
		}
		if (a.size() > 0 && czyZmieniloWartosc == niewykonane)
		{
			czas++;
		}
	}
	return czas;
}
// DZIALA
int SSTF(vector<DaneNaDysk> a, int start)
{
	int niewykonane = a.size();
	// sprawdza czy zostalo wykonane jakies zadanie w przejsciu calej petli jesli nie to potem sprawdzam i powiekszam czas o 1 wiecej
	int czyZmieniloWartosc;
	int czas = 0;
	int index = 0;
	int minimum = 1000000;

	while (niewykonane > 0)
	{
		czyZmieniloWartosc = niewykonane;
		for (int i = 0; i < niewykonane; i++)
		{
			if ((czas >= a[i].czasPrzyjscia) && (minimum >= abs(a[i].miejsce - start)))
			{
				minimum = abs(a[i].miejsce - start);
				index = i;
			}
		}
		if (czas >= a[index].czasPrzyjscia)
		{
			niewykonane--;
			//cout << "czas: " << czas << " ";
			czas += abs(start - a[index].miejsce);

			//cout << a[index].miejsce << "czas: " << czas << endl;

			start = a[index].miejsce;
			minimum = 1000000;

			a.erase(a.begin() + index);
		}
		else if (a.size() > 0 && czyZmieniloWartosc == niewykonane)
		{
			czas++;
		}

	}
	return czas;
}
// DZIALA
int Scan(vector<DaneNaDysk> a, int start)
{
	sort(a.begin(), a.end(), porownajCzasWykonania);
	int czas = a[0].czasPrzyjscia;
	sort(a.begin(), a.end(), porownajPoMiejscu);
	int niewykonane = a.size();
	// sprawdza czy zostalo wykonane jakies zadanie w przejsciu calej petli jesli nie to potem sprawdzam i powiekszam czas o 1 wiecej
	int czyZmieniloWartosc;
	int max = start;
	int maksimum = max;
	int min = 2001;
	int minimum = min;
	int przejscia = 0;
	while (niewykonane > 0)
	{
		for (int i = 0; i < niewykonane; i++)
		{
			czyZmieniloWartosc = niewykonane;
			if (czas >= a[i].czasPrzyjscia && a[i].miejsce >= max)
			{
				//cout << "czas: " << czas << " ";
				czas += abs(maksimum - a[i].miejsce);
				max = maksimum = minimum = a[i].miejsce;
				//cout << a[i].miejsce << "czas: " << czas << endl;
				niewykonane--;
				a.erase(a.begin() + i);
			}

		}
		if (czyZmieniloWartosc == niewykonane)
		{
			czas++;
			//cout << "zwiekszono czas: " << czas << endl;
		}
		max = 0;
		for (int i = niewykonane; i > 0; i--)
		{
			czyZmieniloWartosc = niewykonane;
			if (czas >= a[i - 1].czasPrzyjscia && a[i - 1].miejsce < min)
			{
				//cout << "czas: " << czas << " ";
				czas += abs(minimum - a[i - 1].miejsce);
				min = minimum = a[i - 1].miejsce;
				//cout << a[i-1].miejsce << "czas: " << czas << endl;
				niewykonane--;
				a.erase(a.begin() + i - 1);
			}
		}
		if (czyZmieniloWartosc == niewykonane)
		{
			czas++;
			//cout << "zwiekszono czas: " << czas << endl;
		}
		min = 201;
		przejscia++;
	}
	return przejscia;
}
// DZIALA
int CScan(vector<DaneNaDysk> a, int start)
{
	sort(a.begin(), a.end(), porownajCzasWykonania);
	int czas = a[0].czasPrzyjscia;
	sort(a.begin(), a.end(), porownajPoMiejscu);
	int niewykonane = a.size();
	// sprawdza czy zostalo wykonane jakies zadanie w przejsciu calej petli jesli nie to potem sprawdzam i powiekszam czas o 1 wiecej
	int czyZmieniloWartosc = -1;
	int max = start;
	int maksimum = max;
	int czyInneDoWykoania;
	while (niewykonane > 0)
	{
		czyInneDoWykoania = -1;
		for (int i = 0; i < niewykonane; i++)
		{
			czyZmieniloWartosc = niewykonane;
			if (czas >= a[i].czasPrzyjscia && a[i].miejsce >= max)
			{
				//cout << "czas: " << czas << " ";
				czas += abs(maksimum - a[i].miejsce);
				max = maksimum = a[i].miejsce;
				//cout << a[i].miejsce << "czas: " << czas << endl;
				niewykonane--;
				a.erase(a.begin() + i);
			}
		}
		if (czyZmieniloWartosc == niewykonane)
		{
			czas++;
			//cout << "zwiekszono czas: " << czas << endl;
		}
		max = 0;
	}
	return czas;
}
// DZIALA
int FCFSzEDF(vector<DaneNaDysk> a, int start) {
	// Sortujemy tablicę a według czasu wykonania
	sort(a.begin(), a.end(), porownajCzasWykonania);

	int niewykonane = a.size();
	int czyZmieniloWartosc;
	int czas = a[0].czasPrzyjscia;
	int zaglodzenia = 0;

	while (niewykonane > 0) {
		czyZmieniloWartosc = niewykonane;
		// Zmienna przechowująca indeks zadania z największym zagrożeniem głodem
		int indeksZagrozenia = -1;

		for (int i = 0; i < niewykonane; i++) {
			// Sprawdzamy, czy czas do zagłodzenia danego zadania jest dodatni
			if (a[i].czasDoZaglodzenia > 0) {
				// Jeśli tak, aktualizujemy indeks zagrożenia
				indeksZagrozenia = i;
				break;
			}
		}
		// Jeśli znaleźliśmy zadanie z zagrożeniem głodem
		if (indeksZagrozenia != -1) {
			// Sprawdzamy, czy czas do przyjścia zadania z zagrożeniem głodem 
			// jest mniejszy niż czas do rozpoczęcia wykonywania obecnego zadania

			if (a[indeksZagrozenia].czasPrzyjscia <= czas)
			{
				// Jeśli tak, wywłaszczamy obecne zadanie i obsługujemy zadanie z zagrożeniem głodem
				if (czas - start - a[indeksZagrozenia].miejsce > a[indeksZagrozenia].czasDoZaglodzenia)
				{
					zaglodzenia++;
					// cout << "zaglodzono" << endl;
				}
			//	cout << "czas: " << czas << " ";
				czas += abs(start - a[indeksZagrozenia].miejsce);
				start = a[indeksZagrozenia].miejsce;
			//	cout << "Wywlaszczenie z powodu zagrozenia glodem: " << "czas: " << czas << " miejsce: " << a[indeksZagrozenia].miejsce << endl;
				a.erase(a.begin() + indeksZagrozenia);
				niewykonane--;
				indeksZagrozenia = -1;
			}
			else if (a[indeksZagrozenia].czasPrzyjscia <= czas + a[0].miejsce - start)
			{
				int przyjscie = a[0].czasPrzyjscia - a[indeksZagrozenia].czasPrzyjscia;

				if (przyjscie > 0 && a[0].miejsce > a[indeksZagrozenia].miejsce)
				{
					start = start + przyjscie;
				}
				else if (przyjscie > 0 && a[0].miejsce < a[indeksZagrozenia].miejsce)
				{
					start = start - przyjscie;
				}

				// Jeśli tak, wywłaszczamy obecne zadanie i obsługujemy zadanie z zagrożeniem głodem
				if (czas - start - a[indeksZagrozenia].miejsce > a[indeksZagrozenia].czasDoZaglodzenia)
				{
					zaglodzenia++;
					//cout << "zaglodzono" << endl;
				}
				if (czas < a[indeksZagrozenia].czasPrzyjscia)
				{
					czas = a[indeksZagrozenia].czasPrzyjscia;
				}
			//	cout << "czas: " << czas << " ";
				czas += abs(start - a[indeksZagrozenia].miejsce);
				start = a[indeksZagrozenia].miejsce;
			//	cout << "Wywlaszczenie z powodu zagrozenia glodem: " << "czas: " << czas << " miejsce: " << a[indeksZagrozenia].miejsce << endl;
				a.erase(a.begin() + indeksZagrozenia);
				niewykonane--;
				indeksZagrozenia = -1;
			}
		}
		else if (czas >= a[0].czasPrzyjscia) {
			/// Jeśli nie znaleźliśmy zadania z zagrożeniem głodem, obsługujemy kolejne zadanie w kolejce
		//	cout << "czas: " << czas << " ";
			czas += abs(start - a[0].miejsce);
		//	cout << a[0].miejsce << "czas: " << czas << endl;
			start = a[0].miejsce;
			a.erase(a.begin());
			niewykonane--;
		}

		// Sprawdzamy, czy w tablicy pozostały jakieś zadania
		if (a.size() > 0 && czyZmieniloWartosc == niewykonane) {
			czas++;
		}
	}
	cout << "Liczba zaglodzen: " << zaglodzenia << endl;
	return czas;
}
int testFCFS(vector<DaneNaDysk> a, int start)
{
	sort(a.begin(), a.end(), porownajCzasWykonania);

	int niewykonane = a.size();
	int czyZmieniloWartosc;
	int czas = a[0].czasPrzyjscia;
	int zaglodzenia = 0;

	while (niewykonane > 0) {
		czyZmieniloWartosc = niewykonane;
		// Zmienna przechowująca indeks zadania z największym zagrożeniem głodem
		int indeksZagrozenia = -1;

		for (int i = 0; i < niewykonane; i++) {
			// Sprawdzamy, czy czas do zagłodzenia danego zadania jest dodatni
			if (a[i].czasDoZaglodzenia > 0) {
				// Jeśli tak, aktualizujemy indeks zagrożenia
				indeksZagrozenia = i;
				break;
			}
		}
		// Jeśli znaleźliśmy zadanie z zagrożeniem głodem
		if (indeksZagrozenia != -1) {
			// Sprawdzamy, czy czas do przyjścia zadania z zagrożeniem głodem 
			// jest mniejszy niż czas do rozpoczęcia wykonywania obecnego zadania

			if (a[indeksZagrozenia].czasPrzyjscia <= czas)
			{
				// Jeśli tak, wywłaszczamy obecne zadanie i obsługujemy zadanie z zagrożeniem głodem
				if (czas - start - a[indeksZagrozenia].miejsce > a[indeksZagrozenia].czasDoZaglodzenia)
				{
					zaglodzenia++;
					a.erase(a.begin() + indeksZagrozenia);
					niewykonane--;
					indeksZagrozenia = -1;
				//	cout << "zaglodzono" << endl;
				}
				else {

				//cout << "czas: " << czas << " ";
				czas += abs(start - a[indeksZagrozenia].miejsce);
				start = a[indeksZagrozenia].miejsce;
			//	cout << "Wywlaszczenie z powodu zagrozenia glodem: " << "czas: " << czas << " miejsce: " << a[indeksZagrozenia].miejsce << endl;
				a.erase(a.begin() + indeksZagrozenia);
				niewykonane--;
				indeksZagrozenia = -1;
				}
				
			}
			else if (a[indeksZagrozenia].czasPrzyjscia <= czas + a[0].miejsce - start)
			{
				int przyjscie = a[0].czasPrzyjscia - a[indeksZagrozenia].czasPrzyjscia;

				if (przyjscie > 0 && a[0].miejsce > a[indeksZagrozenia].miejsce)
				{
					start = start + przyjscie;
				}
				else if (przyjscie > 0 && a[0].miejsce < a[indeksZagrozenia].miejsce)
				{
					start = start - przyjscie;
				}

				// Jeśli tak, wywłaszczamy obecne zadanie i obsługujemy zadanie z zagrożeniem głodem
				if (czas - start - a[indeksZagrozenia].miejsce > a[indeksZagrozenia].czasDoZaglodzenia)
				{
					zaglodzenia++;
					//cout << "zaglodzono" << endl;
				}
				if (czas < a[indeksZagrozenia].czasPrzyjscia)
				{
					czas = a[indeksZagrozenia].czasPrzyjscia;
				}
				for (int i = start; i < a[indeksZagrozenia].miejsce; i++)
				{
					for (int j = 0; j < niewykonane; j++)
					{
						if (czas >= a[j].czasPrzyjscia && i == a[j].miejsce)
						{
						//	cout << "wykonano w przejsciu do zaglodzenia" << endl;
							if (a[j].miejsce < a[indeksZagrozenia].miejsce)
							{
								indeksZagrozenia--;
							}
							niewykonane--;
							a.erase(a.begin() + j);
						}
					}
				}
			//	cout << "czas: " << czas << " ";
				czas += abs(start - a[indeksZagrozenia].miejsce);
				start = a[indeksZagrozenia].miejsce;
			//	cout << "Wywlaszczenie z powodu zagrozenia glodem: " << "czas: " << czas << " miejsce: " << a[indeksZagrozenia].miejsce << endl;
				a.erase(a.begin() + indeksZagrozenia);
				niewykonane--;
				indeksZagrozenia = -1;
			}
		}
		else if (czas >= a[0].czasPrzyjscia) {
			/// Jeśli nie znaleźliśmy zadania z zagrożeniem głodem, obsługujemy kolejne zadanie w kolejce
			//cout << "czas: " << czas << " ";
			czas += abs(start - a[0].miejsce);
		//	cout << a[0].miejsce << "czas: " << czas << endl;
			start = a[0].miejsce;
			a.erase(a.begin());
			niewykonane--;
		}

		// Sprawdzamy, czy w tablicy pozostały jakieś zadania
		if (a.size() > 0 && czyZmieniloWartosc == niewykonane) {
			czas++;
		}
	}
	cout << "Liczba zaglodzen: " << zaglodzenia << endl;
	return czas;
}

	int main()
	{
		vector<DaneNaDysk> test;
		wypelnienieDanymi(test);

		for (int i = 0; i < test.size(); i++)
		{
			//cout << test[i].id << " " << test[i].czasPrzyjscia << " " << test[i].miejsce << " " << test[i].czasDoZaglodzenia << endl;
		}

		cout << endl << endl << endl << FCFS(test, 5);
		cout << endl << endl << endl << SSTF(test, 5);
		cout << endl << endl << endl << "Przejscia " << Scan(test, 5);
		cout << endl << endl << endl << CScan(test, 5);
		cout << endl << endl << endl << FCFSzEDF(test, 5);
		cout << endl << endl << endl << testFCFS(test, 5);

	}