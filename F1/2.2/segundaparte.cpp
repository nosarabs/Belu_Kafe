#include <iostream>
#include <string.h>
#include <pthread.h>
#include "datos.h"
#include <thread> 
#include <chrono>
#include <stdlib.h>

using namespace std;

void lector(vector<pares *> &palabras){
    cout<<"Digite una hilera: "<<endl;
    string hilera;
    getline(cin, hilera);
    pares* par=new pares(hilera,0);
    palabras.push_back(par);
}

void imprimir(vector<pares *> &palabras){
  for(size_t i = 0; i<palabras.size()-1; i++){
    cout << "(" << palabras[i]->palabra << ", " << palabras[i]->cantidad << ")" << endl;
  }
}

void * contador(void * dato){
    datos * mydata= static_cast<datos *> (dato);
    while(true){
       sem_wait(&mydata->semaforo);
       if(mydata->palabras[mydata->actual]->palabra.compare("1")==0){
         imprimir(mydata->palabras);
         return NULL;
       }
       this_thread::sleep_for(chrono::seconds(mydata->retardo));
       int cantidad=mydata->palabras[mydata->actual]->cantidad_palabras();//llama al método de pares que cuenta las palabras
       mydata->palabras[mydata->actual]->cantidad=cantidad;
       ++mydata->actual;
    }
}

int main(int argc, char *argv[]){

       datos * dato= new datos();
       if(argc>1){
         dato->retardo = atoi(argv[1]);
       }
       pthread_t  pthread; //se crea el hilo        
       dato->actual = 0; //el actual del contador  que comience en 0
       pthread_create(&pthread, NULL, contador, (void *)dato);

        int cont = -1;
        do{
          lector(dato->palabras); //para que escriba en la pocisión 0 del vector palabras
          cont++;
          sem_post(&dato->semaforo);
        }while(dato->palabras[cont]->palabra.compare("1"));
        
        pthread_join(pthread, NULL);//une el proceso principal y el secundario 
        for(size_t i=0; i<dato->palabras.size();++i){
            delete dato->palabras[i];
            
        }
        delete dato;
        return 0;
}


