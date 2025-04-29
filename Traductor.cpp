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


