#include <iostream>
#include <fstream>
#include <list>
#include <ctime>
#include <windows.h>

using namespace std;

struct Puntaje {
    string nombre;
    int puntaje;
};

bool compararPuntajes(const Puntaje& a, const Puntaje& b) {
    return a.puntaje > b.puntaje;
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void imprimirPuntajes() {
    gotoxy(90, 0);
    cout << "SCORE" << endl;
    ifstream archivoPuntajes("punteo.txt");
    string linea;
    list<Puntaje> puntajes;
    while (getline(archivoPuntajes, linea)) {
        size_t separador = linea.find('|');
        Puntaje p = {linea.substr(0, separador), stoi(linea.substr(separador + 1))};
        puntajes.push_back(p);
    }
    
    puntajes.sort(compararPuntajes);

    int y = 1;
    for (const auto& p : puntajes) {
        if (y > 5) break;
        gotoxy(90, y++);
        cout << p.nombre << " " << p.puntaje << endl;
    }
}

int main() {
    string nombre;
    cout << "Ingrese su nombre: ";
    cin >> nombre;

    imprimirPuntajes();

    ifstream archivoPalabras("palabras.txt");
    list<string> palabras;
    string palabra;

    while (archivoPalabras >> palabra) {
        palabras.push_back(palabra);
    }

    srand(time(0));
    auto it = palabras.begin();
    advance(it, rand() % palabras.size());
    string palabraSeleccionada = *it;

    string palabraAdivinada(palabraSeleccionada.size(), '_');
    int intentos = 5;

    while (intentos > 0 && palabraAdivinada != palabraSeleccionada) {
        system("cls");
        imprimirPuntajes(); 
        gotoxy(0, 2);
        cout << "Palabra: " << palabraAdivinada << endl;
        char letra;
        cout << "Ingrese una letra: ";
        cin >> letra;

        bool letraEncontrada = false;
        for (size_t i = 0; i < palabraSeleccionada.size(); ++i) {
            if (palabraSeleccionada[i] == letra) {
                palabraAdivinada[i] = letra;
                letraEncontrada = true;
            }
        }
        if (!letraEncontrada) {
            --intentos;
            cout << "Letra no encontrada. Intentos restantes: " << intentos << endl;
        }

        imprimirPuntajes();
    }

    int puntaje = 0;
    if (palabraAdivinada == palabraSeleccionada) {
        puntaje = 20 * intentos;
        ofstream archivoPuntajes("punteo.txt", ios_base::app);
        archivoPuntajes << nombre << "|" << puntaje << "\n";
        system("cls");
        cout << "¡Felicidades ha adivinado la palabra " << palabraSeleccionada << "!" << endl;

    } else {
        system("cls");
        cout << "No has adivinado la palabra. La palabra era: " << palabraSeleccionada << endl;
    }

    cout << "Presiona ENTER para continuar...";
    cin.ignore();
    cin.get();

    return 0;
}