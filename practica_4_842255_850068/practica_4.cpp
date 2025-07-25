/* ----------------------------------------------------------------------------
 * File:   practica_4.cpp
 * Author: Pablo Angusto Delgado 842255 y Miguel Aréjula Aisa 850068
 * Date:   noviembre 2022
 * Coms:   Práctica 4 de PSCD
 *         Compilar mediante
 *          make
 * -----------------------------------------------------------------------------
 */

#include "ControlParejas.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <thread>
#include <cstdlib>

using namespace std;

//----------------------------------------------------
// Pre: <fila> es un  índice de fila de <D>
// Post: devuelve el máximo de la fila <fila>
int maxFila(int D[N_FIL][N_COL], int fila) {
  int max = D[fila][0];
  for (int i = 1; i < N_COL; i++) {
    if (max < D[fila][i]) {
      max = D[fila][i];
    }
  }
  return max;
}

// Pre: <fila> es un  índice de fila de <D>
// Post: devuelve la suma de los els. de la fila <fila>
int sumaFila(int D[N_FIL][N_COL], int fila) {
  int sum = 0;
  for (int i = 0; i < N_COL; i++) {
    sum += D[fila][i];
  }

  return sum;
}

//----------------------------------------------------
void Estudiante(ControlParejas &monControlParejas, int nip, int D[N_FIL][N_COL],
                int resultado[N_EST]) {
  // esperar por una silla libre
  int miFila;
  int miPareja;
  //<await (silla<2) // una de las dos esté libre
  monControlParejas.sillasVacias(nip);
  // >

  // esperar me sea asignada pareja y fila
  //  <await (hayFila = true)
  monControlParejas.filaDisponible(miFila, nip, miPareja);
  //>
  if (nip < miPareja) {
    // calcular máx de mi fila
    resultado[nip] = maxFila(D, miFila);
  } else {
    // calcular la suma de mi fila
    resultado[nip] = sumaFila(D, miFila);
    // coger info de max (de mi pareja)
    //  <await(examen_fin[miPareja]= true)>
    monControlParejas.compaTerminado(miFila, nip);
    // mostrar resultados
    cout << to_string(miFila) + "|  " + to_string(miPareja) + "-" +
                to_string(nip) + "|  " + to_string(resultado[miPareja]) +
                "|  " + to_string(resultado[nip]) + '\n';
  }
  // hacérselo llegar a mi pareja
  monControlParejas.heTerminado(miFila, nip);
}

//----------------------------------------------------
void Profesor(ControlParejas &monControlParejas) {
  for (int i = 0; i < N_FIL; i++) {
    // esperar a que haya dos
    //<await silla = 2
    monControlParejas.dosSentados(i);
    //>
    //<await (levantado == 2)
    monControlParejas.almsLevantados();
    //>
  }
  // esperar que todos hayan terminado
  //<await terminado == 60
  monControlParejas.todosTerminado();
  // fin examen
  //>
}
// Inserta los datos del fichero "datos.txt" en la matriz D
bool leerFich(int D[N_FIL][N_COL]) {
  ifstream f("datos.txt");
  if (f.is_open()) {
    for (int i = 0; i < N_FIL; i++) {
      for (int j = 0; j < N_COL; j++) {
        f >> D[i][j];
      }
    }
    f.close();
    return true;
  } else {
    cout << "No se ha podido abrir el fichero datos.txt" << endl;
    return false;
  }
}

int main() {
  int D[N_FIL][N_COL]; // para almacenar los datos
  ControlParejas monControlParejas;
  int resultado[N_EST]; // vector que almacena los resultados de cada estudiante

  // cargar "datos.txt" en "D"
  if (leerFich(D)) {
    thread Estu[60]; // declaración de los procesos estudiantes
    thread Profe;  // declaración del proceso profesor
    Profe = thread(&Profesor, ref(monControlParejas));

    for (int i = 0; i < N_EST; i++) {
      Estu[i] = thread(&Estudiante, ref(monControlParejas), i, ref(D),
                       ref(resultado));
    }

    Profe.join(); // me bloqueo hasta que "Profe" termine
    for (int i = 0; i < N_EST; i++) {
      Estu[i].join(); // me bloqueo hasta que "Estu[i]" termine
    }

    cout << '\n';
    cout << "Prueba finalizada\n"; // Indica finalización del programa 
    return 0;
  } else {
    cerr << "Error\n"; // en caso de que no se haya podido leer el fichero muestra mensaje de error
    return 1;
  }
}