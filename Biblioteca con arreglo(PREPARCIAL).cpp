#include <iostream>
#include <ctime>
#include <string>

using namespace std;

// Función para crear un arreglo dinámico unidimensional
int* crear_arreglo(int size) {
    int* arr = new int[size];
    for (int i = 0; i < size; i++) {
        arr[i] = 0;
    }
    return arr;
}

// Función para destruir el arreglo dinámico
void destruir_arreglo(int* arr) {
    delete[] arr;
}

// Clase que representa un préstamo
class Prestamo {
private:
    int usuario;
    int libro;
    int genero;
public:
    Prestamo(int u, int l, int g) : usuario(u), libro(l), genero(g) {}

    int getUsuario() const { return usuario; }
    void setUsuario(int u) { usuario = u; }
    
    int getLibro() const { return libro; }
    void setLibro(int l) { libro = l; }
    
    int getGenero() const { return genero; }
    void setGenero(int g) { genero = g; }
    
    string to_string() const {
        return std::to_string(usuario) + ", " + std::to_string(libro) + ", " + std::to_string(genero);
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

// Clase ListaEnlazada
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

    void mostrar() const {
        Nodo<T>* actual = cabeza;
        while (actual) {
            cout << actual->valor.to_string() << endl;
            actual = actual->siguiente;
        }
        cout << "nullptr" << endl;
    }

    Nodo<T>* getCabeza() const { return cabeza; }
};

// Clase Biblioteca
class Biblioteca {
private:
    ListaEnlazada<Prestamo> prestamos;
    int* libros_prestados;
    int nu, nl, np;

public:
    Biblioteca(int u, int l, int p) : nu(u), nl(l), np(p) {
        libros_prestados = crear_arreglo(nl);
    }

    ~Biblioteca() {
        destruir_arreglo(libros_prestados);
    }

    void init_lista() {
        for (int i = 0; i < np; i++) {
            int u = rand() % nu;
            int l = rand() % nl;
            int g = rand() % 10; // Suponiendo 10 géneros
            prestamos.insertar(Prestamo(u, l, g));
        }
        calcular_arreglo();
        cout << "Se han generado " << np << " préstamos." << endl;
    }

    void calcular_arreglo() {
        Nodo<Prestamo>* actual = prestamos.getCabeza();
        while (actual) {
            libros_prestados[actual->valor.getLibro()]++;
            actual = actual->siguiente;
        }
    }

    void mostrar_prestamos() {
        prestamos.mostrar();
    }

    void mostrar_libros_prestados() {
        cout << "Arreglo de libros prestados:" << endl;
        for (int i = 0; i < nl; i++) {
            cout << libros_prestados[i] << " ";
        }
        cout << endl;
    }

    void libro_mas_solicitado() {
        int max_libro = 0, libro = -1;
        for (int i = 0; i < nl; i++) {
            if (libros_prestados[i] > max_libro) {
                max_libro = libros_prestados[i];
                libro = i;
            }
        }
        cout << "Libro más solicitado: " << libro << " con " << max_libro << " préstamos." << endl;
    }
};

int main() {
    srand(time(0));
    Biblioteca bib(10, 10, 100);
    bib.init_lista();
    bib.mostrar_prestamos();
    bib.mostrar_libros_prestados();
    bib.libro_mas_solicitado();
    return 0;
}
