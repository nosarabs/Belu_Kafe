from threading import Thread
import time
from queue import Queue
import threading

class palabra:
    def __init__(self, palabra, cantidad):
        self.palabra = palabra
        self.cantidad = cantidad
 
    def imp(self):
        print("(" +self.palabra+" ,"+ str(self.cantidad)+")")
    def setcant(self,cantidad):
        self.cantidad=cantidad
    def getpalabra(self):
        return self.palabra

semaforo = threading.Semaphore(0) 
my_lista=[ ]

def lector(out_q):
    while True:   
        h = input("Ingrese la oración: ")
        out_q.put(h)
        p=palabra(h,0)
        my_lista.append(p)
        semaforo.release()
        if out_q.get() == "1": 
            break

        
def contador():
    actual=0
    while True:
        semaforo.acquire()
        h = my_lista[actual]
        if h.getpalabra()=="1":
                for i in range(len(my_lista)-1):
                    my_lista[i].imp()
                return 0
            
        x = len(h.getpalabra().split())
        h.setcant(x)
        actual+=1
    
q = Queue()
t1 = Thread(target=lector, args=(q,))
t2 = Thread(target=contador, args=())

t1.start()
t2.start()

q.join()
 
