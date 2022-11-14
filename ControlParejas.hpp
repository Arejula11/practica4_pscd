/* ----------------------------------------------------------------------------
 * File:   ControlParejas.hpp
 * Author: Pablo Angusto Delgado 842255 y Miguel Aréjula Aisa 850068
 * Date:   noviembre 2022
 * Coms:   Práctica 4 de PSCD declaración de la clase monitor
 *         Compilar mediante
 *          make 
 * -----------------------------------------------------------------------------
 */

#include <condition_variable>
#include <mutex>
using namespace std;

const int N_EST = 60;        // # de estudiantes
const int N_FIL = N_EST / 2; // # de filas en la matriz
const int N_COL = 1000;      // # de columnas

class ControlParejas {
public:
  ControlParejas();
  //   ~ControlParejas();
  void sillasVacias(int nip);
  void filaDisponible(int &miFila, int nip, int &miPareja);
  void compaTerminado(int miFila, int nip);
  void heTerminado(int miFila, int nip);
  void dosSentados(int i);
  void almsLevantados();
  void todosTerminado();

private:
  int fila;
  int silla;
  int silla1;
  int silla2;
  int pareja[N_EST];
  bool hayFila;
  int miPareja;
  bool examen_fin[N_FIL];
  int terminado;
  int levantado;
  mutex mtxMonitor;
  condition_variable haySillasVacias;
  condition_variable hayFilaDisponible;
  condition_variable haTerminadoCompa;
  condition_variable hayDosSentados;
  condition_variable seHanLevantado;
  condition_variable todosHanTerminado;
  
};