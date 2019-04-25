make: leer.cpp Lector.cpp Buzon.cpp Contratista.cpp emitir.cpp Emisor.cpp  Recibir.cpp Receptor.cpp Cola.cpp
	g++ leer.cpp Lector.cpp Buzon.cpp Contratista.cpp -o leer
	g++ emitir.cpp Emisor.cpp Buzon.cpp -pthread -o emi
	g++ Recibir.cpp Receptor.cpp Cola.cpp -pthread -o Recv
recv: Recibir.cpp Receptor.cpp Cola.cpp
	g++ Recibir.cpp Receptor.cpp Cola.cpp -pthread -o Recv
local:  leer.cpp Lector.cpp Buzon.cpp Contratista.cpp emitir.cpp Emisor.cpp
	g++ leer.cpp Lector.cpp Buzon.cpp Contratista.cpp -o leer
	g++ emitir.cpp Emisor.cpp Buzon.cpp -pthread -o emi

.PHONY : clean
clean :
	-rm leer
	-rm emi
	-rm Recv
