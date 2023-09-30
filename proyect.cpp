#include <iostream>
#include <fstream>
#include <list>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

string palabra_a_jugar(){
    ifstream archivo("palabras.txt");
    list<string> palabras;
    string palabra;
    while (archivo >> palabra) {
        palabras.push_back(palabra);
    }
    archivo.close();
    srand(static_cast<unsigned int>(time(nullptr)));
    int indexAleatorio = rand() % palabras.size();
    auto iterador = palabras.begin();
    advance(iterador, indexAleatorio);
    string palabra_elegida = *iterador;
    return palabra_elegida;
}

void mostrarPalabra(string palabra, vector<bool>& adivinadas) {
    for (size_t i = 0; i < palabra.size(); ++i) {
        if (adivinadas[i]) {
            cout << palabra[i];
        } else {
            cout << "_";
        }
    }
    cout << endl;
}

main(){
    string palabra = palabra_a_jugar();

    // Limpiamos el input para futuras entradas
    cin.ignore(1000, '\n');

    vector<bool> adivinadas(palabra.size(), false);
    int intentos = 5;

    while (intentos > 0) {
        system("cls");
        cout << palabra << endl;
        cout << "Intentos restantes: " << intentos << endl;
        mostrarPalabra(palabra, adivinadas);

        char letra;
        cout << "Introduce una letra: ";
        cin >> letra;

        bool acierto = false;
        for (size_t i = 0; i < palabra.size(); ++i) {
            if (palabra[i] == letra && !adivinadas[i]) {
                adivinadas[i] = true;
                acierto = true;
            }
        }

        if (!acierto) {
            --intentos;
        }
        
        bool haGanado = true;
        for (bool adivinada : adivinadas) {
            if (!adivinada) {
                haGanado = false;
                break;
            }
        }

        if (haGanado) {
            system("cls");
            cout << "¡Felicidades! Has adivinado la palabra: " << palabra << endl;
            char dato;
            cin >> dato;
            return 0;
        }
    }
    char dato;
    cout << "Lo siento, se acabaron los intentos. La palabra era: " << palabra << endl;
    cin >> dato;
    return 0;
}