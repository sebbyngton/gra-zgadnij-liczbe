#include <iostream>
#include <vector>
#include <string>

using namespace std;

// dane
vector<string> nameList;           // imiona graczy
vector<int> attemptList;           // liczba prob
vector<string> difficultyList;     // poziom trudnosci

// rng
int randSeed;

int randomInt(int min, int max) {
    randSeed = (randSeed * 67676767676767 + 123456789) % 100;
    return min + (randSeed % (max - min + 1));
}

// sortowanie wynikow
void sortResults() {
    for (int i = 0; i < attemptList.size(); i++) {
        for (int j = i + 1; j < attemptList.size(); j++) {
            if (attemptList[j] < attemptList[i]) {
                swap(attemptList[i], attemptList[j]);
                swap(nameList[i], nameList[j]);
                swap(difficultyList[i], difficultyList[j]);
            }
        }
    }
}

// naglowek
void header(string title) {
    cout << "\n+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n";
    cout << "+-+-+-ZGADNIJ LICZBE: THE GAME+-+-+-+\n";
    cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n";
    cout << "+-+-+-+-BY SEBASTIAN RYPOLC-+-+-+-+-+\n";
    cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n";
    cout << title << "\n\n";
}

// top 5
void showTop(string difficulty) {
    header("TOP 5 - " + difficulty);

    int shown = 0;
    for (int i = 0; i < attemptList.size(); i++) {
        if (difficultyList[i] == difficulty) {
            cout << shown + 1 << ". ";
            cout << nameList[i] << "  proby: " << attemptList[i] << endl;
            shown++;
            if (shown == 5) break;
        }
    }

    if (shown == 0)
        cout << "Brak wynikow dla tego poziomu.\n";

    cout << "\nKliknij enter aby wrocic";
    cin.ignore();
    cin.get();
}

// zeby nie bylo nieskonczonej petli po wpisaniu czegos dziwnego do cin'a
void readInt(int &x) {
    while (!(cin >> x)) {
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

void readChar(char &c) {
    while (!(cin >> c)) {
        cin.clear();
        cin.ignore(10000, '\n');
    }
}


// menu wynikow
void resultsMenu() {
    while (true) {
        header("Wyniki:");
        cout << "1. Latwy\n2. Sredni\n3. Trudny\n4. Powrot\n";
        char choice;
        readChar(choice);

        if (choice == '1') showTop("Latwy");
        else if (choice == '2') showTop("Sredni");
        else if (choice == '3') showTop("Trudny");
        else if (choice == '4') return;
    }
}

// rozpocznij gre
void startGame() {
    header("Wybierz poziom:");
    cout << "1. Latwy (1-50)\n2. Sredni (1-100)\n3. Trudny (1-250)\n";

    char choice;
    readChar(choice);

    int maxNumber;
    string difficulty;

    if (choice == '1') { maxNumber = 50; difficulty = "Latwy"; }
    else if (choice == '2') { maxNumber = 100; difficulty = "Sredni"; }
    else { maxNumber = 250; difficulty = "Trudny"; }

    cout << "\nChcesz zaklad (limit prob)? (t/n): ";
    char bet;
    readChar(bet);

    int limit = -1;
    if (bet == 't' || bet == 'T') {
        cout << "Podaj maksymalna liczbe prob: ";
        readInt(limit);
    }

    int secretNumber = randomInt(1, maxNumber);

    string tooLow[3] = {"Za malo", "Sprobuj wiecej!", "Jeszcze wyzej"};
    string tooHigh[3] = {"Za duzo", "Sprobuj mniej", "Za wysoko"};

    int attempt = 0;
    int guess;

    while (true) {
        attempt++;
        cout << "\nProba numer " << attempt << ". Podaj liczbe: ";
        readInt(guess);

        if (guess < secretNumber) {
            cout << tooLow[randomInt(0, 2)] << endl;
        } else if (guess > secretNumber) {
            cout << tooHigh[randomInt(0, 2)] << endl;
        } else {
            cout << "\nGRATULACJE! Odgadles liczbe!\n";
            cout << "Podaj swoje imie: ";
            string name;
            cin >> name;

            // dodanie wyniku do list
            nameList.push_back(name);
            attemptList.push_back(attempt);
            difficultyList.push_back(difficulty);

            sortResults();

            cout << "\nWynik zapisany. Nacisnij enter aby wrocic";
            cin.ignore();
            cin.get();
            return;
        }

        if (limit != -1 && attempt >= limit) {
            cout << "\nPrzegrales! Limit prob zostal przekroczony.\n";
            cout << "Szukana liczba: " << secretNumber << endl;
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
        header("MENU GLOWNE");
        cout << "1. Nowa gra\n";
        if (!attemptList.empty())
            cout << "2. TOP 5\n";
        cout << "3. Wyjscie\n";

        char choice;
        readChar(choice);

        if (choice == '1') startGame();
        else if (choice == '2' && !attemptList.empty()) resultsMenu();
        else if (choice == '3') break;
    }
    return 0;
}
