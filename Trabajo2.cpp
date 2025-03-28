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

class Productotienda {
private:
    int producto;
    int cantidad;
    int precio;
public:
    Productotienda() : producto(-1), cantidad(-1), precio(-1) {}
    Productotienda(int t, int c, int p) : producto(t), cantidad(c), precio(p) {}
    
    // Getters y setters
    int getproducto() const { return producto; }
    void setproducto(int t) { producto = t; }
    int getcantidad() const { return cantidad; }
    void setcantidad(int c) { cantidad = c; }
    int getprecio() const { return precio; }
    void setprecio(int p) { precio = p; }

    Productotienda& operator=(const Productotienda& f) {
        producto = f.producto;
        cantidad = f.cantidad;
        precio = f.precio;
        return *this;
    }

    string to_string() const {
        return "Producto: " + std::to_string(producto) + ", " + "En Stock: " + std::to_string(cantidad) + ", " + "Precio: " + std::to_string(precio) + "$";
    }

    friend std::ostream& operator<<(std::ostream& os, const Productotienda& z) {
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

    Nodo<T>* merge(Nodo<T>* left, Nodo<T>* right) {
        if (!left) return right;
        if (!right) return left;

        if (left->getValor().getprecio() <= right->getValor().getprecio()) {
            left->setSiguiente(merge(left->getSiguiente(), right));
            return left;
        } else {
            right->setSiguiente(merge(left, right->getSiguiente()));
            return right;
        }
    }

    Nodo<T>* mergeSort(Nodo<T>* head) {
        if (!head || !head->getSiguiente()) {
            return head;
        }

        Nodo<T>* mid = getMiddle(head);
        Nodo<T>* left = head;
        Nodo<T>* right = mid->getSiguiente();
        mid->setSiguiente(nullptr);

        left = mergeSort(left);
        right = mergeSort(right);

        return merge(left, right);
    }

    Nodo<T>* getMiddle(Nodo<T>* head) {
        if (!head) return head;

        Nodo<T>* slow = head;
        Nodo<T>* fast = head;

        while (fast->getSiguiente() && fast->getSiguiente()->getSiguiente()) {
            slow = slow->getSiguiente();
            fast = fast->getSiguiente()->getSiguiente();
        }
        return slow;
    }

    // Función que ordena la lista
    void mergeSort() {
        cabeza = mergeSort(cabeza);
    }

    void busquedabinaria(int precioMin, int precioMax) {
        if (precioMin > precioMax) {
            cout << "Rango inválido: el precio mínimo no puede ser mayor que el precio máximo." << endl;
            return;
        }

        ListaEnlazada<T> resultados;
        Nodo<T>* actual = cabeza;

        while (actual != nullptr) {
            int precioActual = actual->getValor().getprecio();
            if (precioActual >= precioMin && precioActual <= precioMax) {
                resultados.insertar(actual->getValor());
            }
            actual = actual->getSiguiente();
        }

        if (resultados.get_size() == 0) {
            cout << "No se encontraron productos en el rango de precios especificado." << endl;
        } else {
            cout << "Productos encontrados en el rango de precios [" << precioMin << ", " << precioMax << "]:" << endl;
            resultados.mostrar();
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

// Clase Tienda
class Tienda {
private:
    ListaEnlazada<Productotienda> Productoss;
    int** matriz;
    int no; // Número de producto
    int nc; // Número de cantidad
    int np; // Número de precio
    int nz; // Número de tienda

public:
    Tienda(int o = 20, int c = 20, int p = 20, int z = 200) : no(o), nc(c), np(p), nz(z) {
        matriz = crear_mat(nc, np);
    }

    ~Tienda() {
        destruir_mat(matriz, nc);
    }

    void init_lista() {
        int o, c, p;
        for (int i = 0; i < nz; i++) {
            o = rand() % no;
            c = rand() % nc;
            p = rand() % np;
            Productotienda* z = new Productotienda(o, c, p);
            Productoss.insertar(*z);
        }
        cout << "Se han generado " << Productoss.get_size() << " préstamos." << endl;
        Productoss.mostrar();
    }

    
    void mergeSort() {
        Productoss.mergeSort();
    }
    
   void busquedabinaria(int precioMin, int precioMax) {
        Productoss.busquedabinaria(precioMin, precioMax);
    }

    void print() {
        Productoss.mostrar();
    }
};

int main() {
    srand(time(0));  // Inicialización del generador de números aleatorios con el tiempo actual
    int o = 10;
    int c = 10;
    int p = 100;
    int z = 20;
    Tienda store = Tienda(o, c, p, z);
    store.init_lista();
    cout << endl;
    cout << "Lista de Productos ordenada por precio de menor a mayor:" << endl;
    store.mergeSort();
    store.print();
    cout << "Busqueda: ";
    int precioMin, precioMax;
    cout << "Ingrese el rango minimo de precio: "<<endl;
    cin >> precioMin;
    cout << "Ingrese el rango maximo de precio: "<<endl;  
    cin >> precioMax;
    store.busquedabinaria(precioMin, precioMax);
    cout << endl;  
    return 0;
}
