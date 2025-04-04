#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

// -------------------- Clase WebHotel --------------------
class WebHotel {
private:
    int grupo;
    int calificacion;
public:
    WebHotel(int g = -1, int c = -1) : grupo(g), calificacion(c) {}

    int gethotel() const { return grupo; }
    int getcalificacion() const { return calificacion; }
    void sethotel(int g) { grupo = g; }
    void setcalificacion(int c) { calificacion = c; }

    string to_string() const {
        return "(" + std::to_string(grupo) + "," + std::to_string(calificacion) + ")";
    }

    friend ostream& operator<<(ostream& os, const WebHotel& h) {
        return os << h.to_string();
    }
};

// -------------------- Clase Nodo --------------------
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

// -------------------- Clase ListaEnlazada --------------------
template <typename T>
class ListaEnlazada {
private:
    Nodo<T>* cabeza;
    int size;
public:
    ListaEnlazada() : cabeza(nullptr), size(0) {}

    ~ListaEnlazada() {
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            Nodo<T>* siguiente = actual->getSiguiente();
            delete actual;
            actual = siguiente;
        }
    }

    void insertar(const T& _valor) {
        Nodo<T>* nuevoNodo = new Nodo<T>(_valor);
        if (!cabeza) {
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

    void mostrar() const {
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            cout << actual->getValor() << ", ";
            actual = actual->getSiguiente();
        }
        cout << endl;
    }

    int get_size() const { return size; }

    Nodo<T>* get(int i) const {
        int j = 0;
        Nodo<T>* actual = cabeza;
        while (actual && j < i) {
            actual = actual->getSiguiente();
            j++;
        }
        return actual;
    }

    int sumaCalificaciones() const {
        int suma = 0;
        Nodo<T>* actual = cabeza;
        while (actual) {
            suma += actual->getValor().getcalificacion();
            actual = actual->getSiguiente();
        }
        return suma;
    }

    // Métodos de ordenamiento -------------------

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

    void selectionSort() {
        Nodo<T>* actual = cabeza;
        while (actual) {
            Nodo<T>* minNode = actual;
            Nodo<T>* siguiente = actual->getSiguiente();

            while (siguiente) {
                if (siguiente->getValor().gethotel() < minNode->getValor().gethotel()) {
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
        if (!izquierda) return derecha;
        if (!derecha) return izquierda;

        Nodo<T>* resultado = nullptr;
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
    
    // -------------------- QuickSort por puntaje --------------------
Nodo<T>* getTail(Nodo<T>* nodo) {
    while (nodo && nodo->getSiguiente())
        nodo = nodo->getSiguiente();
    return nodo;
}

Nodo<T>* getAnterior(Nodo<T>* inicio, Nodo<T>* nodo) {
    if (!inicio || inicio == nodo) return nullptr;
    while (inicio->getSiguiente() && inicio->getSiguiente() != nodo)
        inicio = inicio->getSiguiente();
    return inicio;
}

Nodo<T>* partition(Nodo<T>* low, Nodo<T>* high) {
    T pivot = high->getValor();
    Nodo<T>* i = low;
    Nodo<T>* j = low;

    while (j != high) {
        if (j->getValor()->puntajeTotal() >= pivot->puntajeTotal()) {
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

void quickSortRecursivo(Nodo<T>* low, Nodo<T>* high) {
    if (!low || !high || low == high || low == high->getSiguiente()) return;

    Nodo<T>* pivot = partition(low, high);
    Nodo<T>* anterior = getAnterior(low, pivot);

    if (anterior && low != pivot) {
        quickSortRecursivo(low, anterior);
    }

    if (pivot && pivot != high) {
        quickSortRecursivo(pivot->getSiguiente(), high);
    }
}

void quickSortPorPuntaje() {
    Nodo<T>* ultimo = getTail(cabeza);
    quickSortRecursivo(cabeza, ultimo);
}

    void ordenarEvaluadoresPorPuntajeDesc() {
        quickSortPorPuntaje();
    }
};

// -------------------- Clase Evaluador --------------------
class Evaluador {
private:
    ListaEnlazada<WebHotel> lista;
public:
    void agregar(const WebHotel& wh) {
        lista.insertar(wh);
    }

    void ordenarPorGrupo() {
        lista.selectionSort(); // Ordenar por grupo (hotel) con selectionSort
    }

    void ordenarPorCalificacion() {
        lista.mergeSort(); // Ordenar por calificación con mergeSort
    }

    void mostrar() const {
        if (lista.get_size() == 0) {
            cout << "La lista de Registros está vacía" << endl;
            return;
        }
        lista.mostrar();
    }

    int puntajeTotal() const {
        return lista.sumaCalificaciones();
    }

    ListaEnlazada<WebHotel>& getLista() {
        return lista;
    }
};

// -------------------- Clase SistemaEvaluacion --------------------
class SistemaEvaluacion {
private:
    ListaEnlazada<Evaluador*> evaluadores;
    int numEvaluadores;
public:
    SistemaEvaluacion(int n) : numEvaluadores(n) {}

    void inicializar() {
        for (int i = 0; i < numEvaluadores; ++i) {
            evaluadores.insertar(new Evaluador());
        }
    }

    void simularEvaluaciones(int totalCalificaciones) {
        int sinNotas = rand() % numEvaluadores;
        for (int i = 0; i < totalCalificaciones; ++i) {
            int grupo = rand() % 4;
            int calif = rand() % 10;
            int evaluadorIndex;
            do {
                evaluadorIndex = rand() % numEvaluadores;
            } while (evaluadorIndex == sinNotas);
            evaluadores.get(evaluadorIndex)->getValor()->agregar(WebHotel(grupo, calif));
        }
    }

    void mostrarPorGrupo() {
        for (int i = 0; i < numEvaluadores; ++i) {
            cout << i << " -> ";
            Nodo<Evaluador*>* nodo = evaluadores.get(i);
            nodo->getValor()->ordenarPorGrupo();
            nodo->getValor()->mostrar();
        }
    }

int obtenerIndiceEvaluador(Evaluador* ptr) const {
    for (int i = 0; i < evaluadores.get_size(); ++i) {
        if (evaluadores.get(i)->getValor() == ptr)
            return i;
    }
    return -1; // No encontrado
}
    void mostrarPorCalificacion() {
        for (int i = 0; i < numEvaluadores; ++i) {
            cout << i << " -> ";
            Nodo<Evaluador*>* nodo = evaluadores.get(i);
            nodo->getValor()->ordenarPorCalificacion();
            nodo->getValor()->mostrar();
        }
    }

    void mostrarPuntajesOrdenados() {
    evaluadores.ordenarEvaluadoresPorPuntajeDesc();
    for (int i = 0; i < evaluadores.get_size(); ++i) {
        Nodo<Evaluador*>* nodo = evaluadores.get(i);
        int indice = obtenerIndiceEvaluador(nodo->getValor());
        cout << "Evaluador " << indice << " con " << nodo->getValor()->puntajeTotal() << " puntos: ";
        nodo->getValor()->mostrar();
    }
}

void mostrarPuntajes() {
    for (int i = 0; i < evaluadores.get_size(); ++i) {
        Nodo<Evaluador*>* nodo = evaluadores.get(i);
        int indice = obtenerIndiceEvaluador(nodo->getValor());
        cout << "Evaluador " << indice << " con " << nodo->getValor()->puntajeTotal() << " puntos: ";
        nodo->getValor()->mostrar();
    }
}
    
};

// -------------------- Main --------------------
int main() {
    srand(time(0));
    int n;
    do {
        cout << "Ingrese el número de Evaluadores (3 a 6): ";
        cin >> n;
    } while (n < 3 || n > 6);

    SistemaEvaluacion sistema(n);
    sistema.inicializar();

    int totalNotas;
    cout << "Ingrese la cantidad de evaluaciones (calificaciones a asignar): ";
    cin >> totalNotas;

    sistema.simularEvaluaciones(totalNotas);

    cout << "\nResultado por evaluador (grupo, calificación) ordenado por grupo:\n";
    sistema.mostrarPorGrupo();

    cout << "\nResultado con la suma de calificaciones por evaluador:\n";
    sistema.mostrarPuntajes();
    
    cout << "\nResultado por evaluador (grupo, calificación) ordenado por calificación:\n";
    sistema.mostrarPorCalificacion();

    cout << "\nResultado de puntos por evaluador ordenados de mayor a menor:\n";
    sistema.mostrarPuntajesOrdenados();



    return 0;
}
