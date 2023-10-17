#include <iostream>
#include <fstream>
#include <list>
#include <ctime>
#include <windows.h>

struct Puntaje {
    std::string nombre;
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
    gotoxy(80, 0);
    std::cout << "SCORE" << std::endl;
    std::ifstream archivoPuntajes("punteo.txt");
    std::string linea;
    std::list<Puntaje> puntajes;
    while (std::getline(archivoPuntajes, linea)) {
        size_t separador = linea.find('|');
        Puntaje p = {linea.substr(0, separador), std::stoi(linea.substr(separador + 1))};
        puntajes.push_back(p);
    }
    
    puntajes.sort(compararPuntajes);

    int y = 1;
    for (const auto& p : puntajes) {
        if (y > 5) break;
        gotoxy(50, y++);
        std::cout << p.nombre << " " << p.puntaje << std::endl;
    }
}

int main() {
    std::string nombre;
    std::cout << "Ingrese su nombre: ";
    std::cin >> nombre;

    imprimirPuntajes();

    std::ifstream archivoPalabras("palabras.txt");
    std::list<std::string> palabras;
    std::string palabra;

    while (archivoPalabras >> palabra) {
        palabras.push_back(palabra);
    }

    srand(time(0));
    auto it = palabras.begin();
    std::advance(it, rand() % palabras.size());
    std::string palabraSeleccionada = *it;

    std::string palabraAdivinada(palabraSeleccionada.size(), '_');
    int intentos = 5;

    while (intentos > 0 && palabraAdivinada != palabraSeleccionada) {
        gotoxy(0, 2);
        std::cout << "Palabra: " << palabraAdivinada << std::endl;
        char letra;
        std::cout << "Ingrese una letra: ";
        std::cin >> letra;

        bool letraEncontrada = false;
        for (size_t i = 0; i < palabraSeleccionada.size(); ++i) {
            if (palabraSeleccionada[i] == letra) {
                palabraAdivinada[i] = letra;
                letraEncontrada = true;
            }
        }

        if (!letraEncontrada) {
            --intentos;
            std::cout << "Letra no encontrada. Intentos restantes: " << intentos << std::endl;
        }

        imprimirPuntajes();
    }

    int puntaje = 0;
    if (palabraAdivinada == palabraSeleccionada) {
        puntaje = 20 * intentos;
        std::ofstream archivoPuntajes("punteo.txt", std::ios_base::app);
        archivoPuntajes << nombre << "|" << puntaje << "\n";
        std::cout << "¡Has adivinado la palabra!" << std::endl;
    } else {
        std::cout << "No has adivinado la palabra." << std::endl;
    }

    std::cout << "Presiona ENTER para continuar...";
    std::cin.ignore();
    std::cin.get();

    return 0;
}