#include "Lector.h"

Lector::Lector(){
    idParaContratista = 1;
}

Lector::~Lector(){

}

void Lector::obtenerDirectorio(){
    cout << "Por favor ingrese la ruta del directorio de las imágenes" << endl;
    cin >> directorio;
}

void Lector::crearContratista(){
    Contratista * contratista = new Contratista(&directorio[0], idParaContratista); // Crea al contratista
    idParaContratista++;
}
