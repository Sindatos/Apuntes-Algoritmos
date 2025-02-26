#include <iostream>
#include <ctime>
#include <string>
#include <climits>

using namespace std;

// Función para crear una matriz dinámica
int** crear_matriz(int filas, int columnas) {
    int** matriz = new int*[filas];
    for (int i = 0; i < filas; i++) {
        matriz[i] = new int[columnas];
        for (int j = 0; j < columnas; j++) {
            matriz[i][j] = 0; // Inicializa en 0
        }
    }
    return matriz;
}

// Función para destruir la matriz dinámica
void destruir_matriz(int** matriz, int filas) {
    for (int i = 0; i < filas; i++) {
        delete[] matriz[i];
    }
    delete[] matriz;
}

// Clase que representa una Ruta
class Ruta {
private:
    int pasajero;
    int vehiculo;
    int codigo_ruta;
public:
    Ruta(int p, int v, int r) : pasajero(p), vehiculo(v), codigo_ruta(r) {}

    int getPasajero() const { return pasajero; }
    void setPasajero(int p) { pasajero = p; }
    
    int getVehiculo() const { return vehiculo; }
    void setVehiculo(int v) { vehiculo = v; }
    
    int getCodigoRuta() const { return codigo_ruta; }
    void setCodigoRuta(int r) { codigo_ruta = r; }
    
    string to_string() const {
        return std::to_string(pasajero) + ", " + std::to_string(vehiculo) + ", " + std::to_string(codigo_ruta);
    }
};

// Clase Nodo para la lista enlazada
template <typename T>
class Nodo {
public:
    T valor;
    Nodo<T>* siguiente;
    Nodo(T _valor) : valor(_valor), siguiente(nullptr) {}
};

// Clase ListaEnlazada para almacenar las rutas
template <typename T>
class ListaEnlazada {
private:
    Nodo<T>* cabeza;
    int size;
public:
    ListaEnlazada() : cabeza(nullptr), size(0) {}
    ~ListaEnlazada() {
        Nodo<T>* actual = cabeza;
        while (actual) {
            Nodo<T>* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
    }

    void insertar(const T& _valor) {
        Nodo<T>* nuevoNodo = new Nodo<T>(_valor);
        if (!cabeza) {
            cabeza = nuevoNodo;
        } else {
            Nodo<T>* actual = cabeza;
            while (actual->siguiente) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevoNodo;
        }
        size++;
    }
    
    void imprimir_lista() const {
        Nodo<T>* actual = cabeza;
        while (actual) {
            cout << actual->valor.to_string() << endl;
            actual = actual->siguiente;
        }
    }

    Nodo<T>* getCabeza() const { return cabeza; }
};

// Clase Empresa de Transporte
class Transporte {
private:
    ListaEnlazada<Ruta> rutas;
    int** matriz_viajes;
    int np, nv, nr, nt;

public:
    Transporte(int p, int v, int r, int t) : np(p), nv(v), nr(r), nt(t) {
        matriz_viajes = crear_matriz(nv, nr);
    }

    ~Transporte() {
        destruir_matriz(matriz_viajes, nv);
    }

    void init_lista() {
        cout << "Generando rutas aleatorias..." << endl;
        for (int i = 0; i < nt; i++) {
            int p = rand() % np;
            int v = rand() % nv;
            int r = rand() % nr;
            rutas.insertar(Ruta(p, v, r));
        }
        rutas.imprimir_lista(); // Imprime las rutas generadas
        calcular_matriz();
    }

    void calcular_matriz() {
        Nodo<Ruta>* actual = rutas.getCabeza();
        while (actual) {
            matriz_viajes[actual->valor.getVehiculo()][actual->valor.getCodigoRuta()]++;
            actual = actual->siguiente;
        }
    }
    
        void imprimir_matriz() {
        cout << "Matriz de viajes (vehículos por rutas):" << endl;
        for (int i = 0; i < nv; i++) {
            for (int j = 0; j < nr; j++) {
                cout << matriz_viajes[i][j] << " ";
            }
            cout << endl;
        }
    }

    int ruta_mas_popular() {
        int max_pasajeros = 0, ruta = -1;
        for (int j = 0; j < nr; j++) {
            int total = 0;
            for (int i = 0; i < nv; i++) {
                total += matriz_viajes[i][j];
            }
            if (total > max_pasajeros) {
                max_pasajeros = total;
                ruta = j;
            }
        }
        return ruta;
    }

    int ruta_menos_popular() {
        int min_pasajeros = INT_MAX, ruta = -1;
        for (int j = 0; j < nr; j++) {
            int total = 0;
            for (int i = 0; i < nv; i++) {
                total += matriz_viajes[i][j];
            }
            if (total < min_pasajeros) {
                min_pasajeros = total;
                ruta = j;
            }
        }
        return ruta;
    }
        int vehiculo_mas_popular() {
        int max_viajes = 0, vehiculo = -1;
        for (int i = 0; i < nv; i++) {
            int total = 0;
            for (int j = 0; j < nr; j++) {
                total += matriz_viajes[i][j];
            }
            if (total > max_viajes) {
                max_viajes = total;
                vehiculo = i;
            }
        }
        return vehiculo;
    }

    int vehiculo_menos_popular() {
        int min_viajes = INT_MAX, vehiculo = -1;
        for (int i = 0; i < nv; i++) {
            int total = 0;
            for (int j = 0; j < nr; j++) {
                total += matriz_viajes[i][j];
            }
            if (total < min_viajes) {
                min_viajes = total;
                vehiculo = i;
            }
        }
        return vehiculo;
    }
    void vehiculo_con_mas_viajes_en_ruta() {
        int ruta;
        cout << "Ingrese el código de la ruta: ";
        cin >> ruta;
        int max_viajes = 0, vehiculo = -1;
        for (int i = 0; i < nv; i++) {
            if (matriz_viajes[i][ruta] > max_viajes) {
                max_viajes = matriz_viajes[i][ruta];
                vehiculo = i;
            }
        }
        cout << "El vehículo que más ha cubierto la ruta " << ruta << " es: " << vehiculo << endl;
    }
};

int main() {
    srand(time(0));
    Transporte empresa(10, 10, 10, 100);
    empresa.init_lista();
    empresa.imprimir_matriz();
    cout << "Vehículo más popular: " << empresa.vehiculo_mas_popular() << endl;
    cout << "Vehículo menos popular: " << empresa.vehiculo_menos_popular() << endl;
    cout << "Ruta más popular: " << empresa.ruta_mas_popular() << endl;
    cout << "Ruta menos popular: " << empresa.ruta_menos_popular() << endl;
    empresa.vehiculo_con_mas_viajes_en_ruta();
    return 0;
}
