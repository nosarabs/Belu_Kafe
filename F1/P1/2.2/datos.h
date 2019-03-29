#include <vector>
#include "pares.h"
#include <semaphore.h>

using namespace std;

class datos{
   public:
      int retardo;	
      sem_t semaforo;
       vector<pares *> palabras;
       int actual;
      // Funciones miembro de la clase "pares"
      datos(){
          sem_init(&semaforo, 0, 0);
          actual=0;
          retardo = 5;
      }
      ~datos(){

      }
}; 
