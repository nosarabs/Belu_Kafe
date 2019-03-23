#!/usr/bin/env python

#Variables
host = 'localhost'
port = 8050
#Se importa el módulo
import socket
 
#Creación de un objeto socket (lado cliente)
obj = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
 
#Conexión con el servidor. Parametros: IP (puede ser del tipo 192.168.1.1 o localhost), Puerto
obj.connect((host, port))
print("Conectado al servidor")
 
#Creamos un bucle para retener la conexion
while True:
    #Instanciamos una entrada de datos para que el cliente pueda enviar mensajes
    print("Escriba el mensaje que desea enviar al servidor>> ")
    mens = input()
    if mens=="1":
        obj.sendall(mens.encode('utf-8'))
        obj.close()
        break
    else:
    #Con el método send, enviamos el mensaje
        obj.sendall(mens.encode('utf-8'))

#Cerramos la instancia del objeto servidor

#Imprimimos la palabra Adios para cuando se cierre la conexion
print("Conexión cerrada") 
