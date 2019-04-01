#include "Emisor.h"
#include <list>
#include <queue>
#include "Buzon.h"
using namespace std;

Emisor::Emisor(){

}

Emisor::~Emisor(){

}

void Emisor::Recibir(){
	buzon.recibir_Mensaje(1);
	Desempaquetar(mi_Mensaje.encabezado, mi_Mensaje.mensaje);
}

void Emisor::Desempaquetar(char * encabezado, char * mensaje){
	char encabezado = mi_Mensaje.encabezado[0];
	Guardar(encabezado, mensaje);
}

void Emisor::Guardar(char numArchivo, char * mensaje){ // en alguna ED conforme se va desempaquetando
	if(archivos.size() < numArchivo){
		queue < char * > cola;
		cola.push(mensaje);
		archivos.push_back(cola);
	}else{
		list< queue < char * > > i = std::next(archivos.begin(), numArchivo);
		(*i).push(mensaje);
	}
}

void Emisor::ReconstruirArchivo(){

}
