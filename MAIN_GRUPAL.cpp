#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // Para usar system()

using namespace std;

// Función para limpiar la pantalla
void limpiarPantalla() {
    system("cls");  // Usa "clear" si estás en Linux o Mac
}

// Función para agregar nuevas palabras
void agregarPalabra() {
    ofstream archivo("diccionario.txt", ios::app); // Modo append

    if (archivo.is_open()) {
        string palabra, traduccion, funcionalidad;
        char continuar = 's';

        while (continuar == 's' || continuar == 'S') {
            limpiarPantalla();  // Limpia antes de ingresar nueva palabra

            cout << "\n--- Agregar nueva palabra ---\n";
            cout << "Palabra en ingles: ";
            getline(cin, palabra);

            cout << "Traduccion al español: ";
            getline(cin, traduccion);

            cout << "Explicacion de funcionalidad: ";
            getline(cin, funcionalidad);

            // Guardar en el archivo
            archivo << palabra << "|" << traduccion << "|" << funcionalidad << endl;

            cout << "\n¿Deseas agregar otra palabra? (s/n): ";
            cin >> continuar;
            cin.ignore();  // Limpiar buffer para el próximo getline
        }

        archivo.close();
        cout << "\nPalabra(s) guardada(s) exitosamente!\n";
        system("pause");  // Pausa para que el user vea el mensaje
    } else {
        cout << "Error al abrir el archivo.\n";
    }
}

// Función para buscar palabras
void buscarPalabra() {
    ifstream archivo("diccionario.txt");

    if (archivo.is_open()) {
        string palabraBuscar, linea, palabra, traduccion, funcionalidad;
        bool encontrada = false;

        limpiarPantalla();  // Limpia antes de buscar
        cout << "\n--- Buscar palabra ---\n";
        cout << "Introduce la palabra que deseas buscar: ";
        getline(cin, palabraBuscar);

        while (getline(archivo, linea)) {
            size_t pos1 = linea.find("|");
            size_t pos2 = linea.find("|", pos1 + 1);

            if (pos1 != string::npos && pos2 != string::npos) {
                palabra = linea.substr(0, pos1);
                traduccion = linea.substr(pos1 + 1, pos2 - pos1 - 1);
                funcionalidad = linea.substr(pos2 + 1);

                if (palabra == palabraBuscar) {
                    cout << "\n--- Resultado encontrado ---\n";
                    cout << "Palabra: " << palabra << endl;
                    cout << "Traduccion: " << traduccion << endl;
                    cout << "Funcionalidad: " << funcionalidad << endl;
                    encontrada = true;
                    break;
                }
            }
        }

        if (!encontrada) {
            cout << "\nPalabra no encontrada.\n";
        }

        archivo.close();
        system("pause");  // Pausa para que el user vea el resultado
    } else {
        cout << "Error al abrir el archivo.\n";
    }
}

// Función principal
int main() {
    int opcion;

    do {
        limpiarPantalla();  // Limpia la pantalla antes de mostrar menú

        cout << "\n--- Menu Principal ---\n";
        cout << "1. Ingresar nueva palabra\n";
        cout << "2. Buscar palabra\n";
        cout << "0. Salir\n";
        cout << "Selecciona una opcion: ";
        cin >> opcion;
        cin.ignore(); // Limpiar buffer

        switch (opcion) {
            case 1:
                agregarPalabra();
                break;
            case 2:
                buscarPalabra();
                break;
            case 0:
                cout << "\nSaliendo del programa. ¡Hasta luego!\n";
                break;
            default:
                cout << "\nOpcion invalida. Intenta de nuevo.\n";
                system("pause");
        }

    } while (opcion != 0);

    return 0;
}

