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
const int ASIENTOS = 2; //# de sillas en la puerta

class ControlParejas {
public:
  //Constructor de la clase ControlParejas
  ControlParejas();
  //Deconstructor de la case ControlParejas
  ~ControlParejas();
  //Await silla < 2
  void sillasVacias(int nip);
  //Await hayFila = true
  void filaDisponible(int &miFila, int nip, int &miPareja);
  //Await examen_fin[miPareja] = true
  void compaTerminado(int miFila, int nip);
  //Await true
  void heTerminado(int miFila, int nip);
  //Await silla = 2
  void dosSentados(int i);
  //Await levantado = 2
  void almsLevantados();
  //Await termiando = 60
  void todosTerminado();

private:
  int fila;     // indicará a cada pareja su fila correspondiente
  int silla;    // 0 = 0 sillas ocupadas , 1 = una silla ocupada, 2 = 2 sillas ocupadas
  int silla1;   // su valor es el del estudiante sentado
  int silla2;   // su valor es el del estudiante sentado
  int pareja[N_EST];  // pareja[i] será la pareja asignada a cada alumno
  bool hayFila; 
  int miPareja;
  bool examen_fin[N_FIL];
  int terminado; //contador de estudiantes terminados 
  int levantado; // indica el # de estudiantes que se han levantado tras asignarle la pareja y fila
  mutex mtxMonitor;
  condition_variable haySillasVacias;
  condition_variable hayFilaDisponible;
  condition_variable haTerminadoCompa;
  condition_variable hayDosSentados;
  condition_variable seHanLevantado;
  condition_variable todosHanTerminado;
  
};