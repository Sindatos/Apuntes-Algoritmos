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
    int* generos_prestados;
    int nu, nl, np, ng;

public:
    Biblioteca(int u, int l, int g, int p) : nu(u), nl(l), np(p), ng(g) {
        libros_prestados = crear_arreglo(nl);
        generos_prestados = crear_arreglo(ng);
    }

    ~Biblioteca() {
        destruir_arreglo(libros_prestados);
        destruir_arreglo(generos_prestados);
    }

    void init_lista() {
        for (int i = 0; i < np; i++) {
            int u = rand() % nu;
            int l = rand() % nl;
            int g = rand() % ng;
            prestamos.insertar(Prestamo(u, l, g));
            libros_prestados[l]++;
            generos_prestados[g]++;
        }
    }

    void calcular_arreglo() {
        Nodo<Prestamo>* actual = prestamos.getCabeza();
        while (actual) {
            libros_prestados[actual->valor.getLibro()]++;
            generos_prestados[actual->valor.getGenero()]++;
            actual = actual->siguiente;
        }
    }

    void mostrar_prestamos() {
        cout << "Arreglo de libros prestados:" << endl;
        for (int i = 0; i < nl; i++) {
            cout << "Libro " << i << ": " << libros_prestados[i] << " préstamos" << endl;
        }
        cout << "Arreglo de géneros prestados:" << endl;
        for (int i = 0; i < ng; i++) {
            cout << "Género " << i << ": " << generos_prestados[i] << " préstamos" << endl;
        }
        cout << endl;
    }

    int genero_mas_solicitado() {
        int max_genero = 0, genero = -1;
        for (int i = 0; i < ng; i++) {
            if (generos_prestados[i] > max_genero) {
                max_genero = generos_prestados[i];
                genero = i;
            }
        }
        return genero;
    }

    int genero_menos_solicitado() {
        int min_genero = INT_MAX, genero = -1;
        for (int i = 0; i < ng; i++) {
            if (generos_prestados[i] < min_genero) {
                min_genero = generos_prestados[i];
                genero = i;
            }
        }
        return genero;
    }
};

int main() {
    srand(time(0));
    Biblioteca bib(10, 10, 10, 100);
    bib.init_lista();
    bib.calcular_arreglo();
    bib.mostrar_prestamos();

    cout << "Género más solicitado: " << bib.genero_mas_solicitado() << endl;
    cout << "Género menos solicitado: " << bib.genero_menos_solicitado() << endl;
    
    return 0;
}
