

#include "ControlParejas.hpp"

using namespace std;

ControlParejas::ControlParejas(){
    silla=0;
    hayFila=false;
    miPareja=0;

}
void sillasVacias(int silla);
void filaDisponible(bool hayFila);
void compaTerminado();
void heTerminado();
void dosSentados();
void almsLevantados();
void todosTerminado();