import sys # Para pasar argumentos
import re # Para usar RegEx (Expresiones Regulares)
import socket
from threading import Thread
import time
from queue import Queue
import threading
import sys

host=""
port=0
if len(sys.argv) > 2:
    ip = str(sys.argv[1])
    puerto= str(sys.argv[2])
    regex = r"\b(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\b"
    x = re.search(regex, ip)
    try:
        if ip=="localhost":
           host=ip
           port=int(puerto)
        else:   
           print("Dirección IP: ", x.group())
           host=ip
           port=int(puerto)
    except:
        print("Dirección IP Invalida")
        sys.exit(0)
else:
    print("No ingresó argumentos: ")
    print("Debe ingresar ip y puerto en los argumentos")
    sys.exit(0)
    
colaMensajes = Queue()
semaforo = threading.Semaphore(0)

# Creación de un objeto socket (lado cliente)
obj = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Conexión con el servidor
try:
    obj.connect((host, port))
    print("Conectado al Contador")
except:
    print("Error en Connect")
    sys.exit(0)

# Creamos un bucle para seguir obteniendo datos, se sale cuando se digite un "1"
def leer():
    while True:
    # Instanciamos una entrada de datos para que el cliente pueda enviar mensajes
        print('Escriba el mensaje que desea enviar al contador: ')
        mens = input()
        if mens == "1":
            # Con el método put, encolamos el mensaje            
            colaMensajes.put(mens)
            #Luego liberamos el semáforo
            semaforo.release()
            break
        else:
            # Con el método put, encolamos el mensaje
            colaMensajes.put(mens)
            #Luego liberamos el semáforo
            semaforo.release()

def enviar():
    while True:
        #Adquirimos el semáforo
        semaforo.acquire()
        mensaje = colaMensajes.get()
        if mensaje != "1":
            obj.sendall(mensaje.encode('utf-8')) 
        else:
            obj.sendall(mensaje.encode('utf-8'))
            
            recibido = obj.recv(1024)
            print("Ahora se presentaran los resultados en el siguiente orden: \n")
            print("(Frase, cantidad palabras) \n\n")
            while(True):
                if recibido.decode()[recibido.decode().find("(1, 0)") : len(recibido.decode())]=="(1, 0)":
                    break
                print(recibido.decode() + "\n")
                time.sleep(0.5)
                recibido = obj.recv(1024)
                   
            print("Conexión cerrada")
            break


hiloLector = Thread(target=leer, args=())
hiloEnviador = Thread(target=enviar, args=())

hiloLector.start()
hiloEnviador.start()

colaMensajes.join()