Guía para almacenar elementos en una matriz con Listas Enlazadas en C++
Si quieres almacenar datos en una matriz dinámica y usar listas enlazadas, aquí tienes varias formas de hacerlo.

1️⃣ Opción 1: Usar una lista enlazada para cada fila de la matriz
Puedes representar cada fila de la matriz como una lista enlazada. Es decir, la matriz sería un arreglo de punteros a listas enlazadas.

📌 Implementación
cpp
Copiar
Editar
ListaEnlazada<int>* matriz[4]; // Arreglo de punteros a listas enlazadas

// Inicializar cada fila con una lista enlazada
for (int i = 0; i < 4; i++) {
    matriz[i] = new ListaEnlazada<int>;
}

// Insertar valores aleatorios en la matriz/listas
srand(time(0));
for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 5; j++) {
        int valor = rand() % 100 + 1;
        matriz[i]->insertar(valor);
    }
}

// Imprimir la matriz almacenada en listas enlazadas
cout << "Matriz almacenada en listas enlazadas:" << endl;
for (int i = 0; i < 4; i++) {
    matriz[i]->imprimir();
}
✅ Explicación
Cada fila de la matriz es una lista enlazada.
Puedes acceder a una celda M[i][j] como el j-ésimo elemento de la lista matriz[i].
Ventaja: Permite manejar listas de tamaño variable por fila si fuera necesario.
2️⃣ Opción 2: Matriz completamente en una Lista Enlazada
Si quieres almacenar la matriz completa en una única lista enlazada, podrías hacerlo recorriendo la matriz en orden.

📌 Implementación
cpp
Copiar
Editar
ListaEnlazada<int> matrizLista; // Lista que representa toda la matriz

// Insertar valores aleatorios en la lista
srand(time(0));
for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 5; j++) {
        matrizLista.insertar(rand() % 100 + 1);
    }
}

// Imprimir la matriz simulando su estructura
cout << "Matriz representada en una única lista enlazada:" << endl;
Nodo<int>* actual = matrizLista.getCabeza();
int contador = 0;
while (actual) {
    cout << actual->valor << " ";
    actual = actual->siguiente;
    contador++;
    if (contador % 5 == 0) cout << endl; // Nueva línea cada 5 elementos
}
✅ Explicación
En vez de usar un arreglo 2D, todos los valores están en una sola lista enlazada.
Se imprime con formato de matriz cada 5 elementos, haciendo un salto de línea.
Ventaja: Se puede recorrer la matriz de manera secuencial con punteros.
3️⃣ Opción 3: Listas enlazadas anidadas (Nodos con punteros a filas y columnas)
Otra opción más avanzada es crear una estructura de Nodos con dos punteros: uno al siguiente nodo de la fila y otro al siguiente nodo de la columna.

📌 Estructura del Nodo para Matriz Enlazada
cpp
Copiar
Editar
template <typename T>
class NodoMatriz {
public:
    T valor;
    NodoMatriz<T>* derecha;
    NodoMatriz<T>* abajo;
    NodoMatriz(T _valor) : valor(_valor), derecha(nullptr), abajo(nullptr) {}
};
Con esto, puedes construir una matriz enlazada en dos direcciones.
