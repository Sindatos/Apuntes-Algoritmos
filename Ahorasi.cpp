#include <iostream>  // Librería para entrada y salida estándar
#include <ctime>     // Librería para funciones relacionadas con el tiempo, como srand(time(0))
#include <string>    // Librería para manejar strings

using namespace std; // Uso del espacio de nombres estándar


// Clase para representar productos en la tienda
class Productotienda {
private:
    int producto; // Identificador del producto
    int cantidad; // Cantidad en stock
    int precio;   // Precio del producto
public:
    // Constructor por defecto
    Productotienda() : producto(-1), cantidad(-1), precio(-1) {}

    // Constructor con parámetros
    Productotienda(int t, int c, int p) : producto(t), cantidad(c), precio(p) {}

    // Métodos getter y setter
    int getproducto() const { return producto; }
    void setproducto(int t) { producto = t; }
    int getcantidad() const { return cantidad; }
    void setcantidad(int c) { cantidad = c; }
    int getprecio() const { return precio; }
    void setprecio(int p) { precio = p; }

    // Sobrecarga del operador de asignación
    Productotienda& operator=(const Productotienda& f) {
        producto = f.producto;
        cantidad = f.cantidad;
        precio = f.precio;
        return *this;
    }

    // Convertir los datos del producto a string
    string to_string() const {
        return "Producto: " + std::to_string(producto) + ", " +
               "En Stock: " + std::to_string(cantidad) + ", " +
               "Precio: " + std::to_string(precio) + "$";
    }

    // Sobrecarga del operador de salida
    friend std::ostream& operator<<(std::ostream& os, const Productotienda& z) {
        return os << z.to_string(); // Permite usar cout << productotienda
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
    int size;        // Tamaño de la lista
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
        size++; // Aumentar tamaño
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

    // Obtener tamaño de la lista
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
    void swap(T& a, T& b) {
        T temp = a;
        a = b;
        b = temp;
    }
    
    // Bubble Sort adaptado
    void bubbleSort() {
        if (!cabeza) return;
        for (int step = 0; step < size - 1; ++step) {
            Nodo<T>* actual = cabeza;
            Nodo<T>* siguiente = cabeza->getSiguiente();
            bool swapped = false;
    
            while (siguiente) {
                if (actual->getValor().getprecio() > siguiente->getValor().getprecio()) {
                    swap(actual->getValor(), siguiente->getValor());
                    swapped = true;
                }
                actual = siguiente;
                siguiente = siguiente->getSiguiente();
            }
    
            if (!swapped) break;
        }
    }
    
    // Selection Sort adaptado
    void selectionSort() {
        Nodo<T>* actual = cabeza;
        while (actual) {
            Nodo<T>* minNode = actual;
            Nodo<T>* siguiente = actual->getSiguiente();
    
            while (siguiente) {
                if (siguiente->getValor().getprecio() < minNode->getValor().getprecio()) {
                    minNode = siguiente;
                }
                siguiente = siguiente->getSiguiente();
            }
    
            if (minNode != actual) {
                swap(minNode->getValor(), actual->getValor());
            }
            actual = actual->getSiguiente();
        }
    }
    
    // Insertion Sort adaptado
    void insertionSort() {
        if (!cabeza || !cabeza->getSiguiente()) return;
    
        Nodo<T>* sorted = nullptr;
        Nodo<T>* actual = cabeza;
    
        while (actual) {
            Nodo<T>* siguiente = actual->getSiguiente();
    
            if (!sorted || actual->getValor().getprecio() < sorted->getValor().getprecio()) {
                actual->setSiguiente(sorted);
                sorted = actual;
            } else {
                Nodo<T>* temp = sorted;
                while (temp->getSiguiente() && temp->getSiguiente()->getValor().getprecio() < actual->getValor().getprecio()) {
                    temp = temp->getSiguiente();
                }
                actual->setSiguiente(temp->getSiguiente());
                temp->setSiguiente(actual);
            }
    
            actual = siguiente;
        }
    
        cabeza = sorted;
    }
    
    // Merge Sort adaptado
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

    if (!izquierda)
        return derecha;
    else if (!derecha)
        return izquierda;

    if (izquierda->getValor().getprecio() <= derecha->getValor().getprecio()) {
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
    
    // Quick Sort adaptado
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
            if (j->getValor().getprecio() <= pivot.getprecio()) {
                swap(i->getValor(), j->getValor());
                i = i->getSiguiente();
            }
            j = j->getSiguiente();
        }
        swap(i->getValor(), high->getValor());
        return i;
    }
    
    Nodo<T>* getAnterior(Nodo<T>* inicio, Nodo<T>* nodo) {
        if (inicio == nodo) return nullptr;
        while (inicio && inicio->getSiguiente() != nodo) {
            inicio = inicio->getSiguiente();
        }
        return inicio;
    }
    
    void quickSortRecursivo(Nodo<T>* low, Nodo<T>* high) {
        if (!low || low == high || low == high->getSiguiente()) return;
    
        Nodo<T>* pivot = partition(low, high);
        quickSortRecursivo(low, getAnterior(low, pivot));
        quickSortRecursivo(pivot->getSiguiente(), high);
    }
    
    void quickSort() {
        Nodo<T>* ultimo = getTail(cabeza);
        quickSortRecursivo(cabeza, ultimo);
    }
    
    // HeapSort adaptado
    void heapify(T arr[], int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
    
        if (left < n && arr[left].getprecio() > arr[largest].getprecio())
            largest = left;
        if (right < n && arr[right].getprecio() > arr[largest].getprecio())
            largest = right;
        if (largest != i) {
            swap(arr[i], arr[largest]);
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
            swap(arr[0], arr[i]);
            heapify(arr, i, 0);
        }
    
        actual = cabeza;
        for (int i = 0; i < size; i++) {
            actual->setValor(arr[i]);
            actual = actual->getSiguiente();
        }
    
        delete[] arr;
    }
    
    // ShellSort adaptado
    void shellSort() {
        if (!cabeza) return;
    
        T* arr = new T[size];
        Nodo<T>* actual = cabeza;
        for (int i = 0; i < size; i++) {
            arr[i] = actual->getValor();
            actual = actual->getSiguiente();
        }
    
        for (int gap = size / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < size; i++) {
                T temp = arr[i];
                int j = i;
                while (j >= gap && arr[j - gap].getprecio() > temp.getprecio()) {
                    arr[j] = arr[j - gap];
                    j -= gap;
                }
                arr[j] = temp;
            }
        }
    
        actual = cabeza;
        for (int i = 0; i < size; i++) {
            actual->setValor(arr[i]);
            actual = actual->getSiguiente();
        }
    
        delete[] arr;
    }


    void countingSort() {
        if (!cabeza) return;
        int* precios = new int[size];
        Nodo<T>* actual = cabeza;
        int index = 0;
        int max = actual->getValor().getprecio();
        while (actual) {
            precios[index++] = actual->getValor().getprecio();
            if (precios[index - 1] > max) max = precios[index - 1];
            actual = actual->getSiguiente();
        }
        int* count = new int[max + 1]{};
        for (int i = 0; i < size; i++) count[precios[i]]++;
        for (int i = 1; i <= max; i++) count[i] += count[i - 1];
        int* output = new int[size];
        for (int i = size - 1; i >= 0; i--) output[--count[precios[i]]] = precios[i];
        actual = cabeza;
        for (int i = 0; i < size; i++) {
            Productotienda temp = actual->getValor();
            temp.setprecio(output[i]);
            actual->setValor(temp);
            actual = actual->getSiguiente();
        }
        delete[] precios;
        delete[] count;
        delete[] output;
    }

    void radixSort() {
        if (!cabeza) return;
        int* precios = new int[size];
        Nodo<T>* actual = cabeza;
        int i = 0, max = actual->getValor().getprecio();
        while (actual) {
            precios[i++] = actual->getValor().getprecio();
            if (precios[i - 1] > max) max = precios[i - 1];
            actual = actual->getSiguiente();
        }
        for (int place = 1; max / place > 0; place *= 10)
            countingSortForRadix(precios, size, place);
        actual = cabeza;
        for (int i = 0; i < size; i++) {
            Productotienda temp = actual->getValor();
            temp.setprecio(precios[i]);
            actual->setValor(temp);
            actual = actual->getSiguiente();
        }
        delete[] precios;
    }

    void countingSortForRadix(int arr[], int n, int place) {
        const int max = 10;
        int* output = new int[n];
        int count[max] = {0};
        for (int i = 0; i < n; i++) count[(arr[i] / place) % 10]++;
        for (int i = 1; i < max; i++) count[i] += count[i - 1];
        for (int i = n - 1; i >= 0; i--)
            output[--count[(arr[i] / place) % 10]] = arr[i];
        for (int i = 0; i < n; i++) arr[i] = output[i];
        delete[] output;
    }

    // Buscar productos en un rango de precios usando búsqueda binaria
    void busquedaBinariaRango(int precioMin, int precioMax) {
        if (precioMin > precioMax || size == 0) {
            cout << "Rango inválido o lista vacía." << endl;
            return;
        }

        int low = 0;
        int high = size - 1;
        ListaEnlazada<T> resultados;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            Nodo<T>* midNode = get(mid);
            int precioMid = midNode->getValor().getprecio();

            if (precioMid >= precioMin && precioMid <= precioMax) {
                int left = mid;
                while (left >= 0 && get(left)->getValor().getprecio() >= precioMin) {
                    resultados.insertar(get(left)->getValor());
                    left--;
                }
                int right = mid + 1;
                while (right < size && get(right)->getValor().getprecio() <= precioMax) {
                    resultados.insertar(get(right)->getValor());
                    right++;
                }
                break;
            } else if (precioMid < precioMin) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        if (resultados.get_size() == 0) {
            cout << "No se encontraron productos en el rango de precios especificado." << endl;
        } else {
            cout << "Productos encontrados en el rango de precios [" << precioMin << ", " << precioMax << "]:" << endl;
            resultados.mergeSort();
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

// Clase Tienda que usa la lista enlazada de productos
class Tienda {
private:
    ListaEnlazada<Productotienda> Productoss; // Lista de productos
    int no, nc, np, nz; // Parámetros para generación aleatoria

public:
    Tienda(int o = 20, int c = 20, int p = 20, int z = 200) : no(o), nc(c), np(p), nz(z) {}

    ~Tienda() {}

    // Inicializa la lista con productos aleatorios
    void init_lista() {
        int o, c, p;
        for (int i = 0; i < nz; i++) {
            o = rand() % no;
            c = rand() % nc;
            p = rand() % np;
            Productotienda* z = new Productotienda(o, c, p);
            Productoss.insertar(*z); // Insertar producto en la lista
        }
        cout << "Se han generado " << Productoss.get_size() << " préstamos." << endl;
        Productoss.mostrar(); // Mostrar productos
    }

    // Ordenar la lista por precio usando merge sort
    void mergeSort() {
        Productoss.shellSort();
    }

    // Realizar búsqueda binaria en rango de precios
    void busquedabinaria(int precioMin, int precioMax) {
        Productoss.busquedaBinariaRango(precioMin, precioMax);
    }

    // Mostrar la lista de productos
    void print() {
        Productoss.mostrar();
    }
};

// Función principal
int main() {
    srand(time(0)); // Semilla aleatoria para rand()

    // Parámetros de la tienda
    int o = 10;
    int c = 10;
    int p = 100;
    int z = 20;

    // Crear objeto Tienda
    Tienda store = Tienda(o, c, p, z);
    store.init_lista(); // Generar productos

    cout << endl;
    cout << "Lista de Productos ordenada por precio de menor a mayor:" << endl;
    store.mergeSort();  // Ordenar productos
    store.print();      // Mostrar productos

    // Solicitar al usuario un rango de precios
    int opcion = 1; // Variable de control

    while (opcion == 1) {
        cout << "Busqueda de productos por rango de precio" << endl;
        int precioMin, precioMax;
        cout << "Ingrese el rango minimo de precio: " << endl;
        cin >> precioMin;
        cout << "Ingrese el rango maximo de precio: " << endl;
        cin >> precioMax;
    
        // Realizar búsqueda por rango de precios
        store.busquedabinaria(precioMin, precioMax);
        cout << endl;
    
        // Preguntar al usuario si desea buscar otra vez
        cout << "¿Desea realizar otra búsqueda? (1 = Sí, 0 = No): ";
        cin >> opcion;
        cout << endl;
    }

    return 0; // Fin del programa
}
