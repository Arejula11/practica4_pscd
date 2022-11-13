#------------------------------------------------------------------------------
# File:   Makefile
# Author: Miguel Aréjula Aisa y Pablo Angusto Delgado
# Date:   noviembre 2022
# Coms:   Makefile de la práctica 3 de PSCD
#        
#------------------------------------------------------------------------------

#---------------------------------------------------------
#definición de variables
CC=g++
CPPFLAGS=-I. -g -std=c++11      #opciones de compilación
LDFLAGS=-pthread             #opciones de enlazado (linkado)
RM=rm -f


all:  practica4
#-----------------------------------------------------------

# Compilacion
practica4.o: practica4.cpp
	${CC} -c practica4.cpp ${CPPFLAGS} 

ControlParejas.o: ControlParejas.hpp ControlParejas.cpp
	${CC} -c ControlParejas.cpp -o ControlParejas.o ${CPPFLAGS} 
#linkado
practica4: practica4.o ControlParejas.o
	${CC} practica4.o ControlParejas.o -o practica4 ${LDFLAGS}


#-----------------------------------------------------------	
# LIMPIEZA de todo lo generado. OjO: se borrarán sin preguntar
# RM es una de las variables predefinidas en make: invoca borrado de fichero del SO
clean:
	
	${RM} main_p2_ej2.o main_p2_ej2