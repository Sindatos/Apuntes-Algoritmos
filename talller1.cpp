#include <iostream>
#include <ctime>  // Para srand(time(0))

using namespace std;

// Función para crear una matriz dinámica
int** crear_mat(int f, int c) {
    int** m = new int*[f];
    for (int i = 0; i < f; i++) {
        m[i] = new int[c];
        for (int j = 0; j < c; j++) {
            m[i][j] = 0;
        }
    }
    return m;
}

// Función para destruir la matriz
void destruir_mat(int** m, int f) {
    for (int i = 0; i < f; i++) {
        delete[] m[i];
    }
    delete[] m;
}

// Función para imprimir la matriz
void print_mat(int** m, int f, int c) {
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            cout << m[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

class Pelicula {
private:
    int titulo;
    int categoria;
    int puntuacion;
public:
    Pelicula() : titulo(-1), categoria(-1), puntuacion(-1) {}
    Pelicula(int t, int c, int p) : titulo(t), categoria(c), puntuacion(p) {}
    
    // Getters y setters
    int gettitulo() const { return titulo; }
    void settitulo(int t) { titulo = t; }
    int getcategoria() const { return categoria; }
    void setcategoria(int c) { categoria = c; }
    int getpuntuacion() const { return puntuacion; }
    void setpuntuacion(int p) { puntuacion = p; }

    Pelicula& operator=(const Pelicula& f) {
        titulo = f.titulo;
        categoria = f.categoria;
        puntuacion = f.puntuacion;
        return *this;
    }

    string to_string() const {
        return std::to_string(titulo) + ", " + std::to_string(categoria) + ", " + std::to_string(puntuacion);
    }

    friend std::ostream& operator<<(std::ostream& os, const Pelicula& z) {
        return os << z.to_string();
    }
};

// Clase nodo con plantilla
template <typename T>
class Nodo {
private:
    T valor;
    Nodo<T>* siguiente;
public:
    Nodo(T _valor) : valor(_valor), siguiente(nullptr) {}

    void setSiguiente(Nodo<T>* _siguiente) { this->siguiente = _siguiente; }
    void setValor(T _valor) { this->valor = _valor; }
    T getValor() const { return valor; }
    Nodo<T>* getSiguiente() const { return siguiente; }
};

// Clase lista enlazada con plantilla
template <typename T>
class ListaEnlazada {
private:
    Nodo<T>* cabeza;
    int size;
public:
    ListaEnlazada() : cabeza(nullptr), size(0) {}

    ~ListaEnlazada() {
        Nodo<T>* actual = cabeza;
        Nodo<T>* siguiente = nullptr;
        while(actual != nullptr) {
            siguiente = actual->getSiguiente();
            delete actual;
            actual = siguiente;
        }
    }

    void insertar(const T& _valor) {
        Nodo<T>* nuevoNodo = new Nodo<T>(_valor);
        if(cabeza == nullptr) {
            cabeza = nuevoNodo;
        } else {
            Nodo<T>* actual = cabeza;
            while (actual->getSiguiente()) {
                actual = actual->getSiguiente();
            }
            actual->setSiguiente(nuevoNodo);
        }
        size++;
    }

    void insertarEnPosicion(int posicion, const T& _valor) {
        Nodo<T>* nuevoNodo = new Nodo<T>(_valor);

        if (posicion == 0) {
            nuevoNodo->setSiguiente(cabeza);
            cabeza = nuevoNodo;
            return;
        }

        Nodo<T>* actual = cabeza;
        int contador = 0;
        while (actual != nullptr && contador < (posicion - 1)) {
            actual = actual->getSiguiente();
            contador++;
        }

        if (actual == nullptr) {
            std::cout << "Posición inválida" << std::endl;
            delete nuevoNodo;
            return;
        }

        nuevoNodo->setSiguiente(actual->getSiguiente());
        actual->setSiguiente(nuevoNodo);
    }

    bool eliminar(const T& _valor) {
        Nodo<T>* actual = cabeza;
        Nodo<T>* anterior = nullptr;
        while (actual) {
            if (actual->getValor() == _valor) {
                if (anterior) {
                    anterior->setSiguiente(actual->getSiguiente());
                } else {
                    cabeza = actual->getSiguiente();
                }
                delete actual;
                return true;
            }
            anterior = actual;
            actual = actual->getSiguiente();
        }
        return false;
    }

    Nodo<T>* buscarPorValor(const T& _valor) const {
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            if (actual->getValor() == _valor) {
                return actual;
            }
            actual = actual->getSiguiente();
        }
        return nullptr;
    }

    int get_size() const { return size; }

    void mostrar() const {
        Nodo<T>* actual = cabeza;
        cout << "Lista de valores: " << endl;
        while (actual != nullptr) {
            cout << actual->getValor() << endl;
            actual = actual->getSiguiente();
        }
        cout << "nullptr" << endl;
    }

    void bubbleSort() {
        Nodo<T>* actual = cabeza;
        Nodo<T>* siguiente = nullptr;
        T aux;
        while (actual != nullptr) {
            siguiente = actual->getSiguiente();
            while (siguiente != nullptr) {
                // Comparar las puntuaciones de los Peliculas
                if (actual->getValor().getpuntuacion() > siguiente->getValor().getpuntuacion()) {
                    aux = actual->getValor();
                    actual->setValor(siguiente->getValor());
                    siguiente->setValor(aux);
                }
                siguiente = siguiente->getSiguiente();
            }
            actual = actual->getSiguiente();
        }
    }

    Nodo<T>* get(int i) const {
        if (i >= 0 && i < size) {
            int j = 0;
            Nodo<T>* actual = cabeza;
            while (j < i) {
                actual = actual->getSiguiente();
                j++;
            }
            return actual;
        }
        return nullptr;
    }

    

    
};

// Clase ListaPeliculas
class ListaPeliculas {
private:
    ListaEnlazada<Pelicula> Peliculas;
    int** matriz;
    int nt; // Número de títulos
    int nc; // Número de categorías
    int np; // Número de géneros
    int nz; // Número de préstamos

public:
    ListaPeliculas(int t = 20, int c = 20, int p = 20, int z = 200) : nt(t), nc(c), np(p), nz(z) {
        matriz = crear_mat(nc, np);
    }

    ~ListaPeliculas() {
        destruir_mat(matriz, nc);
    }

    void init_lista() {
        int t, c, p;
        for (int i = 0; i < nz; i++) {
            t = rand() % nt;
            c = rand() % nc;
            p = rand() % np;
            Pelicula* z = new Pelicula(t, c, p);
            Peliculas.insertar(*z);
        }
        cout << "Se han generado " << Peliculas.get_size() << " préstamos." << endl;
        Peliculas.mostrar();
    }

    
    void bubbleSort() {
        Peliculas.bubbleSort();
    }

    void print() {
        Peliculas.mostrar();
    }
};

int main() {
    srand(time(0));  // Inicialización del generador de números aleatorios con el tiempo actual
    int t = 10;
    int c = 10;
    int p = 10;
    int z = 20;
    ListaPeliculas bib = ListaPeliculas(t, c, p, z);
    bib.init_lista();
    cout << endl;
    cout << "Lista de Peliculas ordenada por puntuación de mayor a menor:" << endl;
    bib.bubbleSort();

    bib.print();


    return 0;
}
