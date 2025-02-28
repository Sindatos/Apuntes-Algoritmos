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
    Nodo<T>* getCabeza() { return cabeza; }
};

// Funciones de operaciones entre listas enlazadas
ListaEnlazada<int> sumarListas(ListaEnlazada<int>& lista1, ListaEnlazada<int>& lista2) {
    ListaEnlazada<int> resultado;
    Nodo<int>* nodo1 = lista1.getCabeza();
    Nodo<int>* nodo2 = lista2.getCabeza();
    
    while (nodo1 && nodo2) {
        resultado.insertar(nodo1->valor + nodo2->valor);
        nodo1 = nodo1->siguiente;
        nodo2 = nodo2->siguiente;
    }
    return resultado;
}

ListaEnlazada<int> restarListas(ListaEnlazada<int>& lista1, ListaEnlazada<int>& lista2) {
    ListaEnlazada<int> resultado;
    Nodo<int>* nodo1 = lista1.getCabeza();
    Nodo<int>* nodo2 = lista2.getCabeza();
    
    while (nodo1 && nodo2) {
        resultado.insertar(nodo1->valor - nodo2->valor);
        nodo1 = nodo1->siguiente;
        nodo2 = nodo2->siguiente;
    }
    return resultado;
}

ListaEnlazada<int> multiplicarListas(ListaEnlazada<int>& lista1, ListaEnlazada<int>& lista2) {
    ListaEnlazada<int> resultado;
    Nodo<int>* nodo1 = lista1.getCabeza();
    Nodo<int>* nodo2 = lista2.getCabeza();
    
    while (nodo1 && nodo2) {
        resultado.insertar(nodo1->valor * nodo2->valor);
        nodo1 = nodo1->siguiente;
        nodo2 = nodo2->siguiente;
    }
    return resultado;
}

ListaEnlazada<int> dividirListas(ListaEnlazada<int>& lista1, ListaEnlazada<int>& lista2) {
    ListaEnlazada<int> resultado;
    Nodo<int>* nodo1 = lista1.getCabeza();
    Nodo<int>* nodo2 = lista2.getCabeza();
    
    while (nodo1 && nodo2) {
        resultado.insertar((nodo2->valor != 0) ? nodo1->valor / nodo2->valor : 0);
        nodo1 = nodo1->siguiente;
        nodo2 = nodo2->siguiente;
    }
    return resultado;
}

// Programa 3: Operaciones con listas enlazadas
void programa3() {
    ListaEnlazada<int> lista1, lista2, resultado;
    
    cout << "Ingrese 5 valores para la primera lista: ";
    for (int i = 0; i < 5; i++) {
        int valor;
        cin >> valor;
        lista1.insertar(valor);
    }
    
    cout << "Ingrese 5 valores para la segunda lista: ";
    for (int i = 0; i < 5; i++) {
        int valor;
        cin >> valor;
        lista2.insertar(valor);
    }
    
    cout << "Lista Resultante (Suma): ";
    resultado = sumarListas(lista1, lista2);
    resultado.imprimir();
    
    cout << "Lista Resultante (Resta): ";
    resultado = restarListas(lista1, lista2);
    resultado.imprimir();
    
    cout << "Lista Resultante (Multiplicación): ";
    resultado = multiplicarListas(lista1, lista2);
    resultado.imprimir();
    
    cout << "Lista Resultante (División): ";
    resultado = dividirListas(lista1, lista2);
    resultado.imprimir();
}

int main() {
    programa3();
    return 0;
}
