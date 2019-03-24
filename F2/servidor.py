
# Se importa el módulo
import socket
from threading import Thread
import time
from queue import Queue
import threading

class palabra:
    def __init__(self, palabra, cantidad, IP, puerto):
        self.palabra = palabra
        self.cantidad = cantidad
        self.IP=IP
        self.puerto=puerto
 
    def imp(self):
        print("(" +self.palabra+" ,"+ str(self.cantidad)+" ,"+ str(self.IP)+" ,"+ str(self.puerto)+")")
    def setcant(self,cantidad):
        self.cantidad=cantidad
    def getpalabra(self):
        return self.palabra

my_lista=[ ]

def consola():
    print("si desea que se desplieguen los resultados almacenados hasta el momento de una direccion IP y un puerto dato") 
    print("digite una direccion IP y posteriormente se le solicitará un puerto ")
    while True:
        direccion= input()
        if direccion == "1":
            break
        print("ud ha digitado la dirección: "+str(direccion)+" digite un puerto: ")
        puerto= input()
        print("resultados... ")
        resultados=0
        for i in range(len(my_lista)):
                    if str(my_lista[i].IP)==direccion and str(my_lista[i].puerto)==puerto: 
                         my_lista[i].imp()
                         resultados+=1
        if resultados ==0:
            print("No se encontraron resultados, verifique que la dirección IP y el puerto dado son correctos")
        
# instanciamos un objeto para trabajar con el socket
ser = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Puerto y servidor que debe escuchar
ser.bind(("localhost", 8050))

# Aceptamos conexiones entrantes con el metodo listen. Por parámetro las conexiones simutáneas.
ser.listen(1)

# Instanciamos un objeto cli (socket cliente) para recibir datos
cli, addr = ser.accept()
hiloConsola = Thread(target=consola, args=())
hiloConsola.start()

seguir = True
while seguir:
    # Recibimos el mensaje, con el metodo recv recibimos datos. Por parametro la cantidad de bytes para recibir
    recibido = cli.recv(1024)
    if recibido.decode() != "1":
        # Si se reciben datos nos muestra la IP y el mensaje recibido
        print("Recibo conexion de la IP: " + str(addr[0]) + " Puerto: " + str(addr[1]))
        print(recibido.decode())
        p=palabra(recibido.decode(),0,addr[0], addr[1])
        my_lista.append(p)
        # Devolvemos el mensaje al cliente
        cli.send(recibido)
    if recibido.decode() == "1":
        print("conexion de la IP: " + str(addr[0]) + " Puerto: " + str(addr[1]) + " ha sido cerrada")
        seguir = False

#cli.close()
#ser.close()
