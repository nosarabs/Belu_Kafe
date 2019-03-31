#include "Lector.h"

Lector::Lector(){

}

Lector::~Lector(){

}

void Lector::obtenerDirectorio(){
    cout << "Por favor ingrese la ruta del directorio de las imágenes" << endl;
    cin >> directorio;
}

void Lector::crearContratista(char * archivo, int id){
   Contratista * contratista = new Contratista(archivo, id); // Crea al contratista, el id se debería manejar desde el main con un contador
                                                            // para aumentarlo y que nunca se repeita a la hora de crear un contratista
}
