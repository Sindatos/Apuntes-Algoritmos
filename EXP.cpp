¿Quieres que lo conecte luego con búsquedas o filtros por sucursal, o lo dejamos como ejemplo de prueba por ahora?






Tú dijiste:
Quiero que sucursal se genere en medio de las 2 que ya tenemos en medio de todas que sea un numero no nos pongamos a complicarnos con strings



2/2

ChatGPT Plus
Perfecto. Vamos a hacer que el atributo sucursal:

Sea un número entero.

Esté entre grupo y calificacion tanto en los atributos como en la impresión.

Se genere aleatoriamente junto con los demás valores cuando se crea un WebHotel.

✅ PASO 1: Modificar la clase WebHotel
Actualiza tu clase así:

cpp
Copiar
Editar
class WebHotel {
private:
    int grupo;
    int sucursal;     // nuevo campo numérico
    int calificacion;
public:
    WebHotel(int g = -1, int s = -1, int c = -1) : grupo(g), sucursal(s), calificacion(c) {}

    int gethotel() const { return grupo; }
    int getSucursal() const { return sucursal; }
    int getcalificacion() const { return calificacion; }

    void sethotel(int g) { grupo = g; }
    void setSucursal(int s) { sucursal = s; }
    void setcalificacion(int c) { calificacion = c; }

    string to_string() const {
        return "(" + to_string(grupo) + "," + to_string(sucursal) + "," + to_string(calificacion) + ")";
    }

    friend ostream& operator<<(ostream& os, const WebHotel& h) {
        return os << h.to_string();
    }
};
✅ PASO 2: Modificar simularEvaluaciones() para generar sucursal aleatoria
Ubica este bloque:

cpp
Copiar
Editar
int grupo = rand() % 4;
int calif = rand() % 10;
Y entre ellos agrega:

cpp
Copiar
Editar
int sucursal = rand() % 5; // por ejemplo 0 a 4
Y modifica la línea que crea el WebHotel:

cpp
Copiar
Editar
evaluadores.get(evaluadorIndex)->getValor()->agregar(WebHotel(grupo, sucursal, calif));
✅ ¿Qué efecto tiene esto?
Ahora, cada registro se verá impreso como por ejemplo:

scss
Copiar
Editar
(1,3,7), (2,0,9), (0,4,5), ...
Donde:

1 = grupo

3 = sucursal (nuevo campo)

7 = calificación


¿Te gustaría más adelante ordenar también por sucursal o dejarlo solo para mostrar? como se haria eso?


ChatGPT Plus
¡Buena pregunta! Si en el futuro quieres ordenar también por sucursal, sí se puede perfectamente. Aquí te explico cómo hacerlo y qué cambios mínimos harías:

🔧 1. Primero asegúrate que la clase WebHotel tenga el atributo sucursal
Ahora solo tiene grupo y calificación:

cpp
Copiar
Editar
int grupo;
int calificacion;
Pero si quieres incluir sucursal, por ejemplo un número entero (como mencionaste), podrías modificarla así:

✅ Cambia la definición de WebHotel:
cpp
Copiar
Editar
class WebHotel {
private:
    int grupo;
    int sucursal;
    int calificacion;
public:
    WebHotel(int g = -1, int s = -1, int c = -1) : grupo(g), sucursal(s), calificacion(c) {}

    int gethotel() const { return grupo; }
    int getSucursal() const { return sucursal; }
    int getcalificacion() const { return calificacion; }

    void sethotel(int g) { grupo = g; }
    void setSucursal(int s) { sucursal = s; }
    void setcalificacion(int c) { calificacion = c; }

    string to_string() const {
        return "(" + std::to_string(grupo) + "," + std::to_string(sucursal) + "," + std::to_string(calificacion) + ")";
    }

    friend ostream& operator<<(ostream& os, const WebHotel& h) {
        return os << h.to_string();
    }
};
🔄 2. Luego puedes agregar una función ordenarPorSucursal en Evaluador
cpp
Copiar
Editar
void ordenarPorSucursal() {
    // Puedes usar insertionSort, selectionSort o mergeSort
    // Primero modifica un algoritmo de orden para que compare por sucursal
    // Por ejemplo, selectionSort adaptado:
    ListaEnlazada<WebHotel>& lista = getLista();
    Nodo<WebHotel>* actual = lista.get(0);
    while (actual) {
        Nodo<WebHotel>* minNode = actual;
        Nodo<WebHotel>* siguiente = actual->getSiguiente();

        while (siguiente) {
            if (siguiente->getValor().getSucursal() < minNode->getValor().getSucursal()) {
                minNode = siguiente;
            }
            siguiente = siguiente->getSiguiente();
        }

        if (minNode != actual) {
            WebHotel temp = actual->getValor();
            actual->setValor(minNode->getValor());
            minNode->setValor(temp);
        }

        actual = actual->getSiguiente();
    }
}
🎯 3. ¿Y cómo generar valores aleatorios para sucursal?
Al generar evaluaciones en simularEvaluaciones() podrías hacer algo como:

cpp
Copiar
Editar
int grupo = rand() % 4;
int sucursal = rand() % 5; // Ejemplo: 5 sucursales
int calif = rand() % 10;
...
evalNodo->getValor()->agregar(WebHotel(grupo, sucursal, calif));
✅ Conclusión
Sí se puede ordenar por sucursal, y solo necesitas:

Agregar sucursal a la clase WebHotel.

Adaptar uno de tus algoritmos de orden para comparar por getSucursal().

Crear un método en Evaluador que lo llame, como ordenarPorSucursal().

¿Quieres que te entregue ahora el código con sucursal ya agregado y listo para ordenar también por él?
