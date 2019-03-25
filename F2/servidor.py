import sys 
import socket
from threading import Thread
import time
from queue import Queue
import threading
import re # Para usar RegEx (Expresiones Regulares)

class frase:
    def __init__(self, palabra, cantidad, Ip, puerto):
        self.palabra = palabra
        self.cantidad = cantidad
        self.Ip=Ip
        self.puerto=puerto
 
    def imp(self): 
        return "(" +self.palabra+", "+ str(self.cantidad)+", "+ str(self.Ip)+", "+ str(self.puerto)+")"
    def impForClient(self): 
        return "(" +self.palabra+", "+ str(self.cantidad) + ")"
    def setcant(self,cantidad):
        self.cantidad=cantidad
    def getpalabra(self):
        return self.palabra

my_lista=[]

# instanciamos un objeto para trabajar con el socket
ser = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Puerto y servidor que debe escuchar
try:
    ser.bind(("localhost", 9999))
except:
    print("Error en Binding")
    sys.exit(0)

# Aceptamos conexiones entrantes con el metodo listen. Por parámetro las conexiones simutáneas.
try:
    ser.listen(1)
except:
    print("Error en Listen")
    sys.exit(0)


def consola():
    print("Si desea que se desplieguen los resultados almacenados hasta el momento de una direccion IP y un puerto dato") 
    print("Digite una direccion IP y posteriormente se le solicitará un puerto ")
    print("O ingrese 0 para cerrar el servidor")
    while True:
        direccion = input()
        if direccion == "0":
            ser.close()
            sys.exit(0)

        valido = False
        if direccion == "localhost":
            print("Se ha digitado la dirección: " + direccion + "\nDigite un puerto: ")
            direccion = "127.0.0.1"
            puerto = input()
            valido = True
        else:
            regex = r"\b(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\b"
            x = re.search(regex, direccion)
            try:
                direccion = x.group()
                print("Se ha digitado la dirección: " + direccion + "\nDigite un puerto: ")
                puerto = input()
                valido = True
            except:
                print("Dirección IP Inválida")

        if valido:
            print("Buscando Resultados... ")
            resultados = 0
            for i in range(len(my_lista)):
                        if str(my_lista[i].Ip)==direccion and str(my_lista[i].puerto)==puerto:
                             print(my_lista[i].imp())
                             resultados+=1

            if resultados == 0:
                print("No se encontraron resultados, verifique que la dirección IP y el puerto dado son correctos.")


# Instanciamos un objeto cli (socket cliente) para recibir datos
try:
    cli, addr = ser.accept()
except:
    print("Error en Accept")
    sys.exit(0)

hiloConsola = Thread(target=consola, args=())
hiloConsola.start()

continuar: bool
semaforo = threading.Semaphore(0)

def recibir():
    continuar=True
    while True:
        # Recibimos el mensaje, con el metodo recv recibimos datos. Por parametro la cantidad de bytes para recibir
        recibido = cli.recv(1024)
        if recibido.decode() != "1":
            # Si se reciben datos nos muestra la IP y el mensaje recibido
            print("Recibo conexion de la IP: " + str(addr[0]) + " Puerto: " + str(addr[1]) + ", " + "--> " + recibido.decode())
            p=frase(recibido.decode(),0,addr[0], addr[1])
            my_lista.append(p)
            
        if recibido.decode() == "1":
            p=frase(recibido.decode(),0,addr[0], addr[1])
            my_lista.append(p)
            continuar = False
            
        semaforo.release()
        if continuar == False:
            break


def contador():
    actual = 0
    
    while True:
        semaforo.acquire()
        h = my_lista[actual]
        if h.getpalabra()=="1":
            for i in range(len(my_lista)):
                cli.send(my_lista[i].impForClient().encode('utf-8'))
                time.sleep(0.8)
            print("conexion de la IP: " + str(addr[0]) + " Puerto: " + str(addr[1]) + " ha sido cerrada")
            break
        x = len(h.getpalabra().split())
        h.setcant(x)
        actual+=1

hiloRecibidor = Thread(target=recibir, args=())
hiloContador = Thread(target=contador, args=())

hiloRecibidor.start()
hiloContador.start()