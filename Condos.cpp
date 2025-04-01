#include <iostream>  // Librería para entrada y salida estándar
#include <ctime>     // Librería para funciones relacionadas con el tiempo, como srand(time(0))
#include <string>    // Librería para manejar strings

using namespace std; // Uso del espacio de nombres estándar


// Clase para representar peliculas en la Cine
class WebPelis {
private:
    int pelicula; // Identificador del pelicula
    int calificacion; // calificacion en stock
public:
    // Constructor por defecto
    WebPelis() : pelicula(-1), calificacion(-1) {}

    // Constructor con parámetros
    WebPelis(int firstobj, int secondobj) : pelicula(firstobj), calificacion(secondobj) {}

    // Métodos getter y setter
    int getpelicula() const { return pelicula; }
    void setpelicula(int firstobj) { pelicula = firstobj; }
    int getcalificacion() const { return calificacion; }
    void setcalificacion(int secondobj) { calificacion = secondobj; }

    // Sobrecarga del operador de asignación
    WebPelis& operator=(const WebPelis& f) {
        pelicula = f.pelicula;
        calificacion = f.calificacion;
        return *this;
    }

    // Convertir los datos del pelicula a string
    string to_string() const {
        return "Pelicula: " + std::to_string(pelicula) + ", " +
               "Calificacion: " + std::to_string(calificacion) + "✦";
    }

    // Sobrecarga del operador de salida
    friend std::ostream& operator<<(std::ostream& os, const WebPelis& terminator) {
        return os << terminator.to_string(); // Permite usar cout << WebPelis
    }
};

// Clase Nodo genérica para lista enlazada
template <typename T>
class Nodo {
private:
    T valor; // Valor almacenado en el nodo
    Nodo<T>* siguiente; // Puntero al siguiente nodo
public:
    // Constructor
    Nodo(T _valor) : valor(_valor), siguiente(nullptr) {}

    // Métodos setter y getter
    void setSiguiente(Nodo<T>* _siguiente) { this->siguiente = _siguiente; }
    void setValor(T _valor) { this->valor = _valor; }
    T getValor() const { return valor; }
    Nodo<T>* getSiguiente() const { return siguiente; }
};

// Clase Lista Enlazada genérica
template <typename T>
class ListaEnlazada {
private:
    Nodo<T>* cabeza; // Puntero al primer nodo
    int size;        // Tamañfirstobj de la lista
public:
    // Constructor
    ListaEnlazada() : cabeza(nullptr), size(0) {}

    // Destructor: libera memoria de todos los nodos
    ~ListaEnlazada() {
        Nodo<T>* actual = cabeza;
        Nodo<T>* siguiente = nullptr;
        while(actual != nullptr) {
            siguiente = actual->getSiguiente();
            delete actual;
            actual = siguiente;
        }
    }

    // Insertar un nodo al final de la lista
    void insertar(const T& _valor) {
        Nodo<T>* nuevoNodo = new Nodo<T>(_valor);
        if(cabeza == nullptr) {
            cabeza = nuevoNodo; // Si la lista está vacía
        } else {
            Nodo<T>* actual = cabeza;
            while (actual->getSiguiente()) {
                actual = actual->getSiguiente(); // Buscar el último nodo
            }
            actual->setSiguiente(nuevoNodo); // Agregar al final
        }
        size++; // Aumentar tamañfirstobj
    }

    // Insertar en una posición específica
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

    // Eliminar un nodo por su valor
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

    // Buscar un nodo por su valor
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

    // Obtener tamañfirstobj de la lista
    int get_size() const { return size; }

    // Mostrar la lista completa
    void mostrar() const {
        Nodo<T>* actual = cabeza;
        cout << "Lista de valores: " << endl;
        while (actual != nullptr) {
            cout << actual->getValor() << endl;
            actual = actual->getSiguiente();
        }
        cout << "nullptr" << endl;
    }
    // Intercambia objetos completos
// Bubble Sort
void bubbleSort() {
    if (!cabeza) return;
    for (int step = 0; step < size - 1; ++step) {
        Nodo<T>* actual = cabeza;
        Nodo<T>* siguiente = cabeza->getSiguiente();
        bool swapped = false;

        while (siguiente) {
            if (actual->getValor().getcalificacion() > siguiente->getValor().getcalificacion()) {
                T temp = actual->getValor();
                actual->setValor(siguiente->getValor());
                siguiente->setValor(temp);
                swapped = true;
            }
            actual = siguiente;
            siguiente = siguiente->getSiguiente();
        }

        if (!swapped) break;
    }
}

// Selection Sort
void selectionSort() {
    Nodo<T>* actual = cabeza;
    while (actual) {
        Nodo<T>* minNode = actual;
        Nodo<T>* siguiente = actual->getSiguiente();

        while (siguiente) {
            if (siguiente->getValor().getcalificacion() < minNode->getValor().getcalificacion()) {
                minNode = siguiente;
            }
            siguiente = siguiente->getSiguiente();
        }

        if (minNode != actual) {
            T temp = actual->getValor();
            actual->setValor(minNode->getValor());
            minNode->setValor(temp);
        }

        actual = actual->getSiguiente();
    }
}

// Insertion Sort
void insertionSort() {
    if (!cabeza || !cabeza->getSiguiente()) return;

    Nodo<T>* sorted = nullptr;
    Nodo<T>* actual = cabeza;

    while (actual) {
        Nodo<T>* siguiente = actual->getSiguiente();

        if (!sorted || actual->getValor().getcalificacion() < sorted->getValor().getcalificacion()) {
            actual->setSiguiente(sorted);
            sorted = actual;
        } else {
            Nodo<T>* temp = sorted;
            while (temp->getSiguiente() &&
                   temp->getSiguiente()->getValor().getcalificacion() < actual->getValor().getcalificacion()) {
                temp = temp->getSiguiente();
            }
            actual->setSiguiente(temp->getSiguiente());
            temp->setSiguiente(actual);
        }

        actual = siguiente;
    }

    cabeza = sorted;
}

// Merge Sort
Nodo<T>* split(Nodo<T>* inicio) {
    Nodo<T>* slow = inicio;
    Nodo<T>* fast = inicio->getSiguiente();

    while (fast && fast->getSiguiente()) {
        slow = slow->getSiguiente();
        fast = fast->getSiguiente()->getSiguiente();
    }

    Nodo<T>* medio = slow->getSiguiente();
    slow->setSiguiente(nullptr);
    return medio;
}

Nodo<T>* merge(Nodo<T>* izquierda, Nodo<T>* derecha) {
    Nodo<T>* resultado = nullptr;

    if (!izquierda) return derecha;
    if (!derecha) return izquierda;

    if (izquierda->getValor().getcalificacion() <= derecha->getValor().getcalificacion()) {
        resultado = izquierda;
        resultado->setSiguiente(merge(izquierda->getSiguiente(), derecha));
    } else {
        resultado = derecha;
        resultado->setSiguiente(merge(izquierda, derecha->getSiguiente()));
    }

    return resultado;
}

Nodo<T>* mergeSort(Nodo<T>* inicio) {
    if (!inicio || !inicio->getSiguiente()) return inicio;

    Nodo<T>* medio = split(inicio);
    Nodo<T>* izquierda = mergeSort(inicio);
    Nodo<T>* derecha = mergeSort(medio);

    return merge(izquierda, derecha);
}

void mergeSort() {
    cabeza = mergeSort(cabeza);
}

// Quick Sort
Nodo<T>* getTail(Nodo<T>* nodo) {
    while (nodo && nodo->getSiguiente())
        nodo = nodo->getSiguiente();
    return nodo;
}

Nodo<T>* partition(Nodo<T>* low, Nodo<T>* high) {
    T pivot = high->getValor();
    Nodo<T>* i = low;
    Nodo<T>* j = low;

    while (j != high) {
        if (j->getValor().getcalificacion() <= pivot.getcalificacion()) {
            T temp = i->getValor();
            i->setValor(j->getValor());
            j->setValor(temp);
            i = i->getSiguiente();
        }
        j = j->getSiguiente();
    }

    T temp = i->getValor();
    i->setValor(high->getValor());
    high->setValor(temp);
    return i;
}

Nodo<T>* getAnterior(Nodo<T>* inicio, Nodo<T>* nodo) {
    if (inicio == nodo || !inicio) return nullptr;
    while (inicio->getSiguiente() && inicio->getSiguiente() != nodo)
        inicio = inicio->getSiguiente();
    return (inicio->getSiguiente() == nodo) ? inicio : nullptr;
}


void quickSortRecursivo(Nodo<T>* low, Nodo<T>* high) {
    if (!low || !high || low == high || low == high->getSiguiente()) return;

    Nodo<T>* pivot = partition(low, high);
    Nodo<T>* anterior = getAnterior(cabeza, pivot);

    if (anterior && low != pivot) {
        quickSortRecursivo(low, anterior);
    }

    if (pivot && pivot != high) {
        quickSortRecursivo(pivot->getSiguiente(), high);
    }
}


void quickSort() {
    Nodo<T>* ultimo = getTail(cabeza);
    quickSortRecursivo(cabeza, ultimo);
}

// Heap Sort
void heapify(T arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].getcalificacion() > arr[largest].getcalificacion())
        largest = left;
    if (right < n && arr[right].getcalificacion() > arr[largest].getcalificacion())
        largest = right;
    if (largest != i) {
        T temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void heapSort() {
    if (!cabeza) return;

    T* arr = new T[size];
    Nodo<T>* actual = cabeza;
    for (int i = 0; i < size; i++) {
        arr[i] = actual->getValor();
        actual = actual->getSiguiente();
    }

    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(arr, size, i);
    for (int i = size - 1; i > 0; i--) {
        T temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }

    actual = cabeza;
    for (int i = 0; i < size; i++) {
        actual->setValor(arr[i]);
        actual = actual->getSiguiente();
    }

    delete[] arr;
}
void shellSort() {
    if (!cabeza) return;

    // Paso 1: Copiar los nodos en un arreglo
    T* arr = new T[size];
    Nodo<T>* actual = cabeza;
    for (int i = 0; i < size; i++) {
        arr[i] = actual->getValor();
        actual = actual->getSiguiente();
    }

    // Paso 2: Aplicar Shell Sort sobre el arreglo
    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i++) {
            T temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap].getcalificacion() > temp.getcalificacion(); j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }

    // Paso 3: Volver a copiar los valores ordenados en la lista
    actual = cabeza;
    for (int i = 0; i < size; i++) {
        actual->setValor(arr[i]);
        actual = actual->getSiguiente();
    }

    delete[] arr;
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

// Clase Cine que usa la lista enlazada de peliculas
class Cine {
private:
    ListaEnlazada<WebPelis> peliculass; // Lista de peliculas
    int nf, ns, nz; // Parámetros para generación aleatoria

public:
    Cine(int firstobj = 20, int secondobj = 20, int terminator = 200) : nf(firstobj), ns(secondobj), nz(terminator) {}

    ~Cine() {}

    // Inicializa la lista con peliculas aleatorios
    void init_lista() {
        int firstobj, secondobj;
        for (int i = 0; i < nz; i++) {
            firstobj = rand() % nf;
            secondobj = rand() % ns;
            WebPelis* terminator = new WebPelis(firstobj, secondobj);
            peliculass.insertar(*terminator); // Insertar pelicula en la lista
        }
        cout << "Se han generado " << peliculass.get_size() << " préstamos." << endl;
        peliculass.mostrar(); // Mostrar peliculas
    }

    // Ordenar la lista por calificacion usando merge sort
    void metodoorde() {
        peliculass.mergeSort();
    }
    
    
    // Mostrar la lista de peliculas
    void print() {
        peliculass.mostrar();
    }
};

// Función principal
int main() {
    srand(time(0)); // Semilla aleatoria para rand()

    // Parámetros de la Cine
    int firstobj = 10;
    int secondobj = 10;
    int terminator = 0;
    
    cout<<"Ingrese el numero de peliculas que quiere generar: ";
    cin >> terminator;
    // Crear objeto Cine
    Cine store = Cine(firstobj, secondobj, terminator);
    store.init_lista(); // Generar peliculas

    cout << endl;
    cout << "Lista de peliculas ordenada por calificacion de menor a mayor:" << endl;
    store.metodoorde();  // Ordenar peliculas
    store.print();      // Mostrar peliculas

    

    return 0; // Fin del programa
}
