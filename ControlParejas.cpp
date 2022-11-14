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
 ControlParejas::~ControlParejas() { }
void ControlParejas::sillasVacias(int nip) {
  unique_lock<mutex> lck(mtxMonitor);
  while (silla >= 2) {
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
};
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
void ControlParejas::compaTerminado(int miFila, int nip) {
  unique_lock<mutex> lck(mtxMonitor);
  while (!examen_fin[miFila]) {
    haTerminadoCompa.wait(lck);
  }
};
void ControlParejas::heTerminado(int miFila, int nip) {
  unique_lock<mutex> lck(mtxMonitor);
  examen_fin[miFila] = true;
  terminado++;
  todosHanTerminado.notify_all();
  haTerminadoCompa.notify_all();
};
void ControlParejas::dosSentados(int i) {
  unique_lock<mutex> lck(mtxMonitor);
  while (silla != 2) {
    hayDosSentados.wait(lck);
  }
  pareja[silla1] = silla2;
  pareja[silla2] = silla1;
  fila = i;
  hayFila = true;
  hayFilaDisponible.notify_all();
  // hayFilaDisponible.notify_one();
};
void ControlParejas::almsLevantados() {
  unique_lock<mutex> lck(mtxMonitor);
  while (levantado != 2) {
    seHanLevantado.wait(lck);
  }
  silla = 0;
  hayFila = false;
  levantado = 0;
  haySillasVacias.notify_all();
  
};
void ControlParejas::todosTerminado() {
  unique_lock<mutex> lck(mtxMonitor);
  while (terminado != 60) {
    todosHanTerminado.wait(lck);
  }
};
