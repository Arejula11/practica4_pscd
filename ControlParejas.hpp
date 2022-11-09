#include <mutex>
#include <condition_variable>

using namespace std;

const int N_EST = 60; //# de estudiantes
const int N_FIL = N_EST/2; //# de filas en la matriz 
const int N_COL = 1000; //# de columnas

class ControlParejas{
    public:
        ControlParejas();
        void sillasVacias(int silla);
        void filaDisponible(bool hayFila);
        void compaTerminado();
        void heTerminado();
        void dosSentados();
        void almsLevantados();
        void todosTerminado();
    private:
        int silla;
        bool hayFila;
        int miPareja;
        bool examen_fin(N_EST);
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