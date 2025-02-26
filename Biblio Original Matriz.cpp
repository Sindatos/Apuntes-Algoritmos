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

class Prestamo {
private:
    int usuario;
    int libro;
    int genero;
public:
    Prestamo() {
        usuario=-1; 
        libro=-1;
        genero=-1;
    }
    Prestamo(int u, int l, int g){
        usuario=u;
        libro=l;
        genero=g;
    }
    
    //Getters
    int getUsuario() const { 
        return usuario; 
    }
    void setUsuario(int u) { 
        usuario = u; 
    }
    int getLibro() const { 
        return libro; 
    }
    void setLibro(int l) { 
        libro = l; 
    }

    int getGenero() const { 
        return genero; 
    }
    void setGenero(int g) { 
        genero = g; 
    }

    Prestamo& operator=(const Prestamo& f) {
        usuario = f.usuario;
        libro = f.libro;
        genero = f.genero;
        return *this;
    }

    string to_string() const {
        return std::to_string(usuario) + ", " + std::to_string(libro) + ", " + std::to_string(genero);
    }

    friend std::ostream& operator<<(std::ostream& os, const Prestamo& p) {
        return os << p.to_string();
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

// Clase Biblioteca
class Biblioteca {
private:
    ListaEnlazada<Prestamo> prestamos;
    int** matriz;
    int nu; // Número de usuarios
    int nl; // Número de libros
    int ng; // Número de géneros
    int np; // Número de préstamos

public:
    Biblioteca(int u = 100, int l = 100, int g = 100, int p = 1000) : nu(u), nl(l), ng(g), np(p) {
        matriz = crear_mat(nl, ng);
    }

    ~Biblioteca() {
        destruir_mat(matriz, nl);
    }

    void init_lista() {
        Prestamo* t;
        int u, l, g;
        for (int i = 0; i < np; i++) {
            u = rand() % nu;
            l = rand() % nl;
            g = rand() % ng;
            t=new Prestamo(u, l, g);
            prestamos.insertar(*t);
        }
        cout << "Se han generado " << prestamos.get_size() << " préstamos." << endl;
        prestamos.mostrar();
    }
     void print(){
        prestamos.mostrar();
    }


    void calcular_matriz() {
        Nodo<Prestamo>* ptr = prestamos.get(0);
        for (int i = 0; i < np; i++) {
            matriz[ptr->getValor().getLibro()][ptr->getValor().getGenero()]++;
            ptr = ptr->getSiguiente();
        }
        cout << "Matriz de libros por género: " << endl;
        print_mat(matriz, nl, ng);
    }
    
    
    int genero_mas_solicitado() {
        int max = 0;
        int genero = -1;
        for (int i = 0; i < ng; i++) {
            int total = 0;
            for (int j = 0; j < nl; j++) {
                total += matriz[j][i];
            }
            if (total > max) {
                max = total;
                genero = i;
            }
        }
        return genero;
    }

    int genero_menos_solicitado() {
        int min = 1000000;
        int genero = -1;
        for (int i = 0; i < ng; i++) {
            int total = 0;
            for (int j = 0; j < nl; j++) {
                total += matriz[j][i];
            }
            if (total < min) {
                min = total;
                genero = i;
            }
        }
        return genero;
    }

    int libro_mas_prestado() {
        int max = 0;
        int librom = -1;
        for (int i = 0; i < nl; i++) {
            int total = 0;
            for (int j = 0; j < ng; j++) {
                total += matriz[i][j];
            }
            if (total > max) {
                max = total;
                librom = i;
            }
        }
        return librom;
    }

    int libro_menos_prestado() {
        int min = 1000000;
        int libromen = -1;
        for (int i = 0; i < nl; i++) {
            int total = 0;
            for (int j = 0; j < ng; j++) {
                total += matriz[i][j];
            }
            if (total < min) {
                min = total;
                libromen = i;
            }
        }
        return libromen;
    }

    float promedio_prestamos_por_libro() {
        int total = 0;
        for (int i = 0; i < nl; i++) {
            for (int j = 0; j < ng; j++) {
                total += matriz[i][j];
            }
        }
        return (float)total / nl;
    }

    int libro_con_mas_prestamos_por_genero(int genero) {
        int max = 0;
        int librom = -1;
        for (int i = 0; i < nl; i++) {
            if (matriz[i][genero] > max) {
                max = matriz[i][genero];
                librom = i;
            }
        }
        return librom;
    }
};

int main() {
    srand(time(0));  // Inicialización del generador de números aleatorios con el tiempo actual
    int u = 10;
    int l = 10;
    int g = 10;
    int p = 100;
    Biblioteca bib=Biblioteca(u, l, g, p);
    bib.init_lista();
    cout<<endl;
    bib.calcular_matriz();
    cout << "El género más solicitado es: " << bib.genero_mas_solicitado() << endl;
    cout << "El género menos solicitado es: " << bib.genero_menos_solicitado() << endl;
    cout << "El libro con más préstamos es: " << bib.libro_mas_prestado() << endl;
    cout << "El libro con menos préstamos es: " << bib.libro_menos_prestado() << endl;
    cout << "El promedio de préstamos por genero es: " << bib.promedio_prestamos_por_libro() << endl;
    for (int i = 0; i < g; i++) {
        cout << "El libro con más préstamos en el género " << i << " es: " 
        << bib.libro_con_mas_prestamos_por_genero(i) << endl;
    }
    return 0;
}
