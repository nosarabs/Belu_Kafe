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
# Se importa el módulo

# Creación de un objeto socket (lado cliente)
obj = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Conexión con el servidor. Parametros: IP (puede ser del tipo 192.168.1.1 o localhost), Puerto
obj.connect((host, port))
print("Conectado al contador")

# Creamos un bucle para retener la conexion
def leer():
    while True:
    # Instanciamos una entrada de datos para que el cliente pueda enviar mensajes
        print('Escriba el mensaje que desea enviar al contador: ')
        mens = input()
        if mens == "1":
            colaMensajes.put(mens)
            break
        else:
            # Con el método send, enviamos el mensaje
            colaMensajes.put(mens)
            # obj.sendall(mens.encode('utf-8'))

def enviar():
    while True:
        if colaMensajes.empty() == False:
            mensaje = colaMensajes.get()
            if mensaje != "1":
                obj.sendall(mensaje.encode('utf-8')) 
            else:
                obj.sendall(mensaje.encode('utf-8'))
                print("Conexión cerrada")
                break


hiloLector = Thread(target=leer, args=())
hiloEnviador = Thread(target=enviar, args=())

hiloLector.start()
hiloEnviador.start()

colaMensajes.join()
