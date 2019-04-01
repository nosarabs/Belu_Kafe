#include "Lector.h"

Lector::Lector(){
    idParaContratista = 1;
    actual=0;
}

Lector::~Lector(){

}

int Lector::obtenerDirectorio(char *path){
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

		}
		 // agregar el directorio al path
            char relative_path[PATH_MAX];
            sprintf(relative_path, "%s/%s", path, entry->d_name);
            directorios.push_back(relative_path);
	}
	/*esta impresion prueba que se estan leyendo los archivos del directorio, se podria crear otro hilo 
     * que saque archivos del vector de directorios mientras exista la direccion actual controlada por semaforos, este hilo puede ser hecho en pthreads
     * o bien esperar que se lean las imagenes del directorio y luego empezar a crear contratistas. Existe un problema al crear contratistas con fork() 
     * pues necesitamos que sea de memoria compartida el vector de archivos y tambien el idParaContratista.
     */
	for(int i=0; i<directorios.size();++i)
        cout<<directorios[i]<<endl;

	// Sucess
	closedir(dir);
}

void Lector::crearContratista(char *  directorio, int idParaContratista){
    Contratista * contratista = new Contratista(directorio, idParaContratista); // Crea al contratista
    contratista->leerArchivo();
    contratista->~Contratista();
}
