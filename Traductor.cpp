#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <stack>
#include <string>
#include <cctype>
using namespace std;

map<string, string> cargarDiccionario(const string& nombreArchivo) {
    map<string, string> diccionario;
    ifstream archivo("diccionario.txt");

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo de diccionario." << endl;
        exit(1);
    }

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string clave, traduccion, descripcion;

        getline(ss, clave, '|');
        getline(ss, traduccion, '|');
        getline(ss, descripcion, '|'); 

        diccionario[clave] = traduccion;
    }

    archivo.close();
    return diccionario;
}

bool esFuncion(const string& linea) {
    return (linea.find("main") != string::npos || (linea.find("(") != string::npos && linea.find(")") != string::npos));
}

int main() {
    map<string, string> diccionario = cargarDiccionario("diccionario.txt");

    cout << "Ingrese el codigo que desea traducir (finalice con una linea vacia): " << endl;

    string linea;
    vector<string> codigoOriginal;
    while (getline(cin, linea) && !linea.empty()) {
        codigoOriginal.push_back(linea);
    }

    stack<string> estructuras;
    cout << "___ CODIGO TRADUCIDO ____" << endl << endl;
    string ultimaEstructura = "";

   for (size_t i = 0; i < codigoOriginal.size(); ++i) {
    string linea = codigoOriginal[i];
    bool esFunc = esFuncion(linea);
    bool llaveAbierta = false;

    stringstream nuevaLinea;
    string palabraActual;

    for (size_t j = 0; j < linea.length(); ++j) {
        char c = linea[j];

        if (isspace(c) || ispunct(c)) {
            if (!palabraActual.empty()) {
                string limpio = palabraActual;
                limpio.erase(remove_if(limpio.begin(), limpio.end(), ::ispunct), limpio.end());

                if (diccionario.count(limpio)) {
                    nuevaLinea << diccionario[limpio];
                    if (limpio == "if" || limpio == "else" || limpio == "while" || limpio == "for" || limpio == "switch") {
                        ultimaEstructura = diccionario[limpio];
                        estructuras.push(ultimaEstructura);

                    }
                } else {
                    nuevaLinea << palabraActual;
                }

                palabraActual.clear();
            }


