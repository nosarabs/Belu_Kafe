#include "Cola.h"

    Cola::Cola(){
        this->clave = 0xB60442;
        if (this->clave == (key_t)-1)
        {
            cout << "Error al obtener clave para cola mensajes" << endl;
            exit(-1);
        }

        this->id_Cola = msgget (clave, 0600 | IPC_CREAT);
        if (this->id_Cola == -1)
        {
            cout << "Error al obtener identificador para cola mensajes" << endl;
            exit (-1);
        }
    }

    void Cola::encolar_Mensaje(long id, char * msj, int tamano){
        memcpy((void *)un_Mensaje.mensaje, (void*)msj, tamano);
        un_Mensaje.id_Mensaje = id;
        un_Mensaje.tamano=tamano;
        msgsnd (this->id_Cola, (struct msgbuf *)&un_Mensaje, 
        sizeof(un_Mensaje.mensaje)+ sizeof(un_Mensaje.tamano), 0);
    }

    int Cola::desencolar_Mensaje(long id){
        int recibido = msgrcv (this->id_Cola, (struct msgbuf *)&un_Mensaje,
        sizeof(un_Mensaje.mensaje)+ sizeof(un_Mensaje.tamano), id, 0);
        //cout << "Recibido mensaje tipo "<< id<< endl;
        //cout << "Mensaje = " << un_Mensaje.mensaje << endl;
        return recibido;
    }

    Cola::~Cola(){
        msgctl (this->id_Cola, IPC_RMID, (struct msqid_ds *)NULL);
    }
 
