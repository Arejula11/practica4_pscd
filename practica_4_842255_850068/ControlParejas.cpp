/* ----------------------------------------------------------------------------
 * File:   ControlParejas.cpp
 * Author: Pablo Angusto Delgado 842255 y Miguel Aréjula Aisa 850068
 * Date:   noviembre 2022
 * Coms:   Práctica 4 de PSCD implementación de la clase monitor
 *         Compilar mediante
 *          make 
 * -----------------------------------------------------------------------------
 */

#include "ControlParejas.hpp"
#include <iostream>

using namespace std;
//Constructor de la clase ControlParejas
ControlParejas::ControlParejas() {
  silla = 0;
  hayFila = false;
  miPareja = 0;
  terminado = 0;
  levantado = 0;
  fila = 0;
  for (int i = 0; i < N_FIL; i++) {
    examen_fin[i] = false; // inicializar vector
  }
}

//Deconstructor de la case ControlParejas
ControlParejas::~ControlParejas() { }

//Await silla < 2
void ControlParejas::sillasVacias(int nip) {
  unique_lock<mutex> lck(mtxMonitor);
  while (silla >= ASIENTOS) {
    haySillasVacias.wait(lck);
  }
  if (silla == 0) {
    silla1 = nip;
    silla++;
  } else if (silla == 1) {
    silla2 = nip;
    silla++;
  }
  hayDosSentados.notify_one();
};//no se si es necesario estos puntos y comas

//Await hayFila = true
void ControlParejas::filaDisponible(int &miFila, int nip, int &miPareja) {
  unique_lock<mutex> lck(mtxMonitor);
  while (!hayFila) {
    hayFilaDisponible.wait(lck);
  }
  miFila = fila;
  miPareja = pareja[nip];
  levantado++;
  seHanLevantado.notify_one();
};

//Await examen_fin[miPareja] = true
void ControlParejas::compaTerminado(int miFila, int nip) {
  unique_lock<mutex> lck(mtxMonitor);
  while (!examen_fin[miFila]) {
    haTerminadoCompa.wait(lck);
  }
};

//Await true
void ControlParejas::heTerminado(int miFila, int nip) {
  unique_lock<mutex> lck(mtxMonitor);
  examen_fin[miFila] = true;
  terminado++;
  todosHanTerminado.notify_one();
   haTerminadoCompa.notify_all(); // revisar con línea de abajo
  // haTerminadoCompa.notify_one(); //no estoy seguro
};

//Await silla = 2
void ControlParejas::dosSentados(int i) {
  unique_lock<mutex> lck(mtxMonitor);
  while (silla != ASIENTOS) {
    hayDosSentados.wait(lck);
  }
  pareja[silla1] = silla2;
  pareja[silla2] = silla1;
  fila = i;
  hayFila = true;
  // hayFilaDisponible.notify_all();
  hayFilaDisponible.notify_one();
  hayFilaDisponible.notify_one();
};

//Await levantado = 2
void ControlParejas::almsLevantados() {
  unique_lock<mutex> lck(mtxMonitor);
  while (levantado != ASIENTOS) {
    seHanLevantado.wait(lck);
  }
  silla = 0;
  hayFila = false;
  levantado = 0;
  // haySillasVacias.notify_all();
  haySillasVacias.notify_one();
  haySillasVacias.notify_one();
  
};

//Await termiando = 60
void ControlParejas::todosTerminado() {
  unique_lock<mutex> lck(mtxMonitor);
  while (terminado != 60) {
    todosHanTerminado.wait(lck);
  }
};
