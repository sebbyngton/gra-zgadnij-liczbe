#include <iostream>
#include <vector>
#include <string>

using namespace std;

// dane
vector<string> listaImion;     // imiona graczy
vector<int> listaProb;         // liczba prob
vector<string> listaPoziomow;  // poziom trudnosci

// rng
int los;

int losuj(int min, int max) {
    los = (los * 67676767676767 + 123456789) % 100;
    return min + (los % (max - min + 1));
}

// sortowanie wynikow
void sortujWyniki() {
    for (int i = 0; i < listaProb.size(); i++) {
        for (int j = i + 1; j < listaProb.size(); j++) {
            if (listaProb[j] < listaProb[i]) {
                swap(listaProb[i], listaProb[j]);
                swap(listaImion[i], listaImion[j]);
                swap(listaPoziomow[i], listaPoziomow[j]);
            }
        }
    }
}

// naglowek
void naglowek(string tytul) {
    cout << "\n+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n";
    cout << "+-+-+-ZGADNIJ LICZBE: THE GAME+-+-+-+\n";
    cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n";
    cout << "+-+-+-+-BY SEBASTIAN RYPOLC-+-+-+-+-+\n";
    cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n";
    cout << tytul << "\n\n";
}

// top 5
void pokazTop(string poziom) {
    naglowek("TOP 5 - " + poziom);

    int pokazane = 0;
    for (int i = 0; i < listaProb.size(); i++) {
        if (listaPoziomow[i] == poziom) {
            cout << pokazane + 1 << ". ";
            cout << listaImion[i] << "  proby: " << listaProb[i] << endl;
            pokazane++;
            if (pokazane == 5) break;
        }
    }

    if (pokazane == 0)
        cout << "Brak wynikow dla tego poziomu.\n";

    cout << "\nKliknij enter aby wrocic";
    cin.ignore();
    cin.get();
}
// menu wynikow
void menuWynikow() {
    while (true) {
        naglowek("Wyniki:");
        cout << "1. Latwy\n2. Sredni\n3. Trudny\n4. Powrot\n";
        char wybor;
        cin >> wybor;

        if (wybor == '1') pokazTop("Latwy");
        else if (wybor == '2') pokazTop("Sredni");
        else if (wybor == '3') pokazTop("Trudny");
        else if (wybor == '4') return;
    }
}

// rozpocznij gre
void rozpocznijGre() {
    naglowek("Wybierz poziom:");
    cout << "1. Latwy (1-50)\n2. Sredni (1-100)\n3. Trudny (1-250)\n";

    char wybor;
    cin >> wybor;

    int maksLiczba;
    string poziom;

    if (wybor == '1') { maksLiczba = 50; poziom = "Latwy"; }
    else if (wybor == '2') { maksLiczba = 100; poziom = "Sredni"; }
    else { maksLiczba = 250; poziom = "Trudny"; }

    cout << "\nChcesz zaklad (limit prob)? (t/n): ";
    char zaklad;
    cin >> zaklad;

    int limit = -1;
    if (zaklad == 't' || zaklad == 'T') {
        cout << "Podaj maksymalna liczbe prob: ";
        cin >> limit;
    }

    int tajna = losuj(1, maksLiczba);

    string male[3] = {"Za malo", "Sprobuj wiecej!", "Jeszcze wyzej"};
    string duze[3] = {"Za duzo", "Sprobuj mniej", "Za wysoko"};

    int proba = 0;
    int strzal;

    while (true) {
        proba++;
        cout << "\nProba numer " << proba << ". Podaj liczbe: ";
        cin >> strzal;

        if (strzal < tajna) {
            cout << male[losuj(0, 2)] << endl;
        } else if (strzal > tajna) {
            cout << duze[losuj(0, 2)] << endl;
        } else {
            cout << "\nGRATULACJE!!!!!!!!!!!!!! Odgadles liczbe :DDDDD\n";
            cout << "Podaj swoje imie: ";
            string imie;
            cin >> imie;

            // dodanie wyniku do list
            listaImion.push_back(imie);
            listaProb.push_back(proba);
            listaPoziomow.push_back(poziom);

            sortujWyniki();

            cout << "\nWynik zapisany. Nacisnij enter aby wrocic";
            cin.ignore();
            cin.get();
            return;
        }

        if (limit != -1 && proba >= limit) {
            cout << "\nPrzegrales! Limit prob zostal przekroczony.\n";
            cout << "Szukana liczba: " << tajna << endl;
            cout << "Nacisnij enter aby wrocic";
            cin.ignore();
            cin.get();
            return;
        }
    }
}

// menu glowne
int main() {
    while (true) {
        naglowek("MENU GLOWNE");
        cout << "1. Nowa gra\n";
        if (!listaProb.empty())
            cout << "2. TOP 5\n";
        cout << "3. Wyjscie\n";

        char wybor;
        cin >> wybor;

        if (wybor == '1') rozpocznijGre();
        else if (wybor == '2' && !listaProb.empty()) menuWynikow();
        else if (wybor == '3') break;
    }
    return 0;
}
