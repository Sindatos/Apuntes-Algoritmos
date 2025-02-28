#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Clase Nodo para lista enlazada
template <typename T>
class Nodo {
public:
    T valor;
    Nodo<T>* siguiente;
    Nodo(T _valor) : valor(_valor), siguiente(nullptr) {}
};

// Clase ListaEnlazada
template <typename T>
class ListaEnlazada {
private:
    Nodo<T>* cabeza;
public:
    ListaEnlazada() : cabeza(nullptr) {}
    ~ListaEnlazada() {
        Nodo<T>* actual = cabeza;
        while (actual) {
            Nodo<T>* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
    }
    void insertar(T valor) {
        Nodo<T>* nuevo = new Nodo<T>(valor);
        if (!cabeza) cabeza = nuevo;
        else {
            Nodo<T>* temp = cabeza;
            while (temp->siguiente) temp = temp->siguiente;
            temp->siguiente = nuevo;
        }
    }
    void imprimir() {
        Nodo<T>* actual = cabeza;
        while (actual) {
            cout << actual->valor << " ";
            actual = actual->siguiente;
        }
        cout << endl;
    }
};

// Función para verificar si un número es primo
bool esPrimo(int num) {
    if (num < 2) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

// Programa 1: Matriz 4x5 con listas enlazadas para no primos y múltiplos de 5
void programa1() {
    int M[4][5];
    ListaEnlazada<int> listaNoPrimos, listaMultiplos5;
    int suma = 0;
    srand(time(0));
    
    cout << "Matriz 4x5:" << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            M[i][j] = rand() % 100 + 1;
            cout << M[i][j] << " ";
            suma += M[i][j];
            if (!esPrimo(M[i][j])) listaNoPrimos.insertar(M[i][j]);
            if (M[i][j] % 5 == 0) listaMultiplos5.insertar(M[i][j]);
        }
        cout << endl;
    }
    
    cout << "Lista de valores no primos: "; listaNoPrimos.imprimir();
    cout << "Lista de valores múltiplos de 5: "; listaMultiplos5.imprimir();
    cout << "Suma de la matriz: " << suma << endl;
}

// Programa 5: Sumar valores en posiciones pares y contar impares en una lista
void programa5() {
    ListaEnlazada<int> lista;
    int sumaPares = 0, contadorImpares = 0;
    
    cout << "Ingrese 7 valores: ";
    for (int i = 0; i < 7; i++) {
        int valor;
        cin >> valor;
        lista.insertar(valor);
        if (i % 2 == 0) sumaPares += valor;
        else contadorImpares++;
    }
    
    cout << "Lista ingresada: "; lista.imprimir();
    cout << "Suma de posiciones pares: " << sumaPares << endl;
    cout << "Cantidad de valores en posiciones impares: " << contadorImpares << endl;
}

int main() {
    programa1();
    programa5();
    return 0;
}
