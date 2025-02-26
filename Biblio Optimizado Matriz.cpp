#include <iostream>
#include <ctime>  // Para srand(time(0))

using namespace std;

// Función para crear una matriz dinámica
int** crear_mat(int f, int c) {
    int** m = new int*[f];  // Se asigna memoria para las filas
    for (int i = 0; i < f; i++) {
        m[i] = new int[c];  // Se asigna memoria para cada columna
        for (int j = 0; j < c; j++) {
            m[i][j] = 0;  // Inicializamos la matriz en 0
        }
    }
    return m;
}

// Función para destruir la matriz
void destruir_mat(int** m, int f) {
    for (int i = 0; i < f; i++) {
        delete[] m[i];  // Liberamos cada fila
    }
    delete[] m;  // Liberamos la cabecera de la matriz
}

// Función para imprimir la matriz
void print_mat(int** m, int f, int c) {
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            cout << m[i][j] << "\t";  // Imprime los valores de la matriz
        }
        cout << endl;  // Salto de línea para separar filas
    }
    cout << endl;
}

// Clase Prestamo para almacenar los datos de cada préstamo
class Prestamo {
private:
    int usuario;
    int libro;
    int genero;
public:
    Prestamo(int u = -1, int l = -1, int g = -1) : usuario(u), libro(l), genero(g) {}  // Constructor optimizado

    int getUsuario() const { return usuario; }
    void setUsuario(int u) { usuario = u; }

    int getLibro() const { return libro; }
    void setLibro(int l) { libro = l; }

    int getGenero() const { return genero; }
    void setGenero(int g) { genero = g; }

    string to_string() const {
        return std::to_string(usuario) + ", " + std::to_string(libro) + ", " + std::to_string(genero);
    }

    friend ostream& operator<<(ostream& os, const Prestamo& p) {
        return os << p.to_string();  // Permite imprimir la clase directamente
    }
};

// Clase Nodo para la lista enlazada
template <typename T>
class Nodo {
public:
    T valor;
    Nodo<T>* siguiente;
    Nodo(T _valor) : valor(_valor), siguiente(nullptr) {}  // Constructor
};

// Clase ListaEnlazada para almacenar los préstamos
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

// Clase Biblioteca para gestionar préstamos
class Biblioteca {
private:
    ListaEnlazada<Prestamo> prestamos;
    int** matriz;
    int nu, nl, ng, np;

public:
    Biblioteca(int u, int l, int g, int p) : nu(u), nl(l), ng(g), np(p) {
        matriz = crear_mat(nl, ng);  // Se crea la matriz
    }

    ~Biblioteca() {
        destruir_mat(matriz, nl);  // Se destruye la matriz al finalizar
    }

    void init_lista() {
        for (int i = 0; i < np; i++) {
            prestamos.insertar(Prestamo(rand() % nu, rand() % nl, rand() % ng));
        }
        cout << "Se han generado " << np << " préstamos." << endl;
    }

    void calcular_matriz() {
        Nodo<Prestamo>* ptr = prestamos.getCabeza();
        while (ptr) {
            matriz[ptr->valor.getLibro()][ptr->valor.getGenero()]++;
            ptr = ptr->siguiente;
        }
        cout << "Matriz de libros por género: " << endl;
        print_mat(matriz, nl, ng);
    }

    int libro_mas_prestado() {
        int max_libro = 0, libro = 0;
        for (int i = 0; i < nl; i++) {
            int total = 0;
            for (int j = 0; j < ng; j++) {
                total += matriz[i][j];
            }
            if (total > max_libro) {
                max_libro = total;
                libro = i;
            }
        }
        return libro;
    }

    int libro_menos_prestado() {
        int min_libro = INT_MAX, libro = 0;
        for (int i = 0; i < nl; i++) {
            int total = 0;
            for (int j = 0; j < ng; j++) {
                total += matriz[i][j];
            }
            if (total < min_libro) {
                min_libro = total;
                libro = i;
            }
        }
        return libro;
    }

    float promedio_prestamos_por_libro() {
        int total = 0;
        for (int i = 0; i < nl; i++) {
            for (int j = 0; j < ng; j++) {
                total += matriz[i][j];
            }
        }
        return static_cast<float>(total) / nl;
    }
};

int main() {
    srand(time(0));  // Inicialización de la semilla aleatoria
    Biblioteca bib(10, 10, 10, 100);
    
    bib.init_lista();
    bib.calcular_matriz();

    cout << "El libro con más préstamos es: " << bib.libro_mas_prestado() << endl;
    cout << "El libro con menos préstamos es: " << bib.libro_menos_prestado() << endl;
    cout << "El promedio de préstamos por libro es: " << bib.promedio_prestamos_por_libro() << endl;

    return 0;
}
