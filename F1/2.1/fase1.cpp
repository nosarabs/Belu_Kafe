#include <mpi.h>
#include <iostream>
#include <string.h>
#define MAXSIZE 100

using namespace std;

//Pide una hilera de caracteres al usuario y la retorna
char* lector(){
    char * cadena= new char[MAXSIZE];
    cout<<"Escriba: "<<endl;
    cin.getline(cadena,MAXSIZE);
    return cadena;
}

//Cuenta total de palabras en la oración dada como parámetro
void contador(char * hilera){
    int cantidad=0;
    int contador=0;
    while(hilera[contador]!='\0'){ //Mientras no lleguemos al final
        while(hilera[contador]==' '){ //Mientras haya espacios
            ++contador;
        }
        if(hilera[contador]!='\0'){ //Si no estamos al final de la hilera 
            ++cantidad; //+1 a la cantidad de palabras
            while(hilera[contador]!=' ' && hilera[contador]!='\0'){ //Mientras haya letras
                contador++; //Nos saltamos el resto de la palabras
            }
        }
    }
        cout<<"cantidad: "<<cantidad<<endl;
        cout<<"hilera: "<<hilera<<endl;
}

int main(int argc, char *argv[]){

	int my_rank = -1;
	int process_count = -1;
	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &process_count);

	char hilera[MAXSIZE ];
	for(int i=0;i<MAXSIZE ;++i)
		hilera[i]=' ';

	if (my_rank==0){ //El proceso 0 
                char * cadena= lector(); //Se le pide la oración al usuario
                strcpy(hilera,cadena);
		MPI_Send(&hilera[0],MAXSIZE ,MPI_CHAR,1, 0,MPI_COMM_WORLD); //Y se le envía al proceso 1
                delete cadena;
        }

	MPI_Barrier(MPI_COMM_WORLD);

	if(my_rank!=0){ //El proceso 1
		MPI_Recv(&hilera[0],MAXSIZE,MPI_CHAR,0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE ); //Recibe la hilera
                contador(hilera); //Cuenta las palabras y imprime la información
	}

	MPI_Finalize();
        return 0;
}
