#include "Lector.h"
#include <unistd.h>


Lector::Lector(){
    idParaContratista = 1;
    actual=0;
    contratistasActuales = 0;
}

Lector::~Lector(){

}

int Lector::obtenerDirectorio(char *&path){
    Buzon * buzon= new Buzon();
    DIR* dir = opendir(path);

    if ( dir == NULL ){
		cout<<"error: no se pudo abrir el directorio"<<endl;
        return 0;
    }
	// cargar las entradas del directorio una a una
	struct dirent* entry;
	while ( (entry = readdir(dir)) != NULL )
	{
		// si es un directorio
		if ( entry->d_type == DT_DIR )
		{
			// ignorar archivos ocultos y directorios
			if ( *entry->d_name == '.' )
				continue;
 

		}else{
            //Controlador para que solo existan dos contratistas
            if(contratistasActuales >= 2){
                buzon->recibir_Mensaje(9999); //Señal recibida de algún contratista
                --contratistasActuales;
            }
            // agregar el directorio al pat
            char relative_path[PATH_MAX];
            sprintf(relative_path, "%s/%s",path, entry->d_name);
            if (!fork()) {
                crearContratista(&relative_path[0], idParaContratista);
                return 0;
            } else {
                ++contratistasActuales;
                ++idParaContratista;
            }
        }
	}
    //Esperamos a que terminen los últimos contratistas
    while(contratistasActuales!=0){
        buzon->recibir_Mensaje(9999);
        --contratistasActuales;
    }
  //  delete buzon;
	closedir(dir);
    return 0;
}

void Lector::crearContratista(char *  directorio, int idParaContratista){
    Contratista * contratista = new Contratista(directorio, idParaContratista); // Crea al contratista
    contratista->leerArchivo();
    delete contratista;
}
