#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Función para verificar si un número es primo
bool esPrimo(int num) {
    if (num < 2) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

// Programa 1: Matriz 4x5 con valores no primos y múltiplos de 5 a arreglos
void programa1() {
    int filas = 4, columnas = 5;
    int **M = new int*[filas];
    int *A = new int[filas * columnas]; // No primos
    int *B = new int[filas * columnas]; // Múltiplos de 5
    int suma = 0, indexA = 0, indexB = 0;
    
    srand(time(0));
    
    // Llenar y procesar la matriz
    for (int i = 0; i < filas; i++) {
        M[i] = new int[columnas];
        for (int j = 0; j < columnas; j++) {
            M[i][j] = rand() % 100 + 1;
            suma += M[i][j];
            if (!esPrimo(M[i][j])) A[indexA++] = M[i][j];
            if (M[i][j] % 5 == 0) B[indexB++] = M[i][j];
        }
    }
    
    // Imprimir la matriz
    cout << "Matriz 4x5:" << endl;
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            cout << M[i][j] << " ";
        }
        cout << endl;
    }
    
    // Imprimir arreglos
    cout << "Arreglo A (No primos): ";
    for (int i = 0; i < indexA; i++) cout << A[i] << " ";
    cout << endl;
    
    cout << "Arreglo B (Múltiplos de 5): ";
    for (int i = 0; i < indexB; i++) cout << B[i] << " ";
    cout << endl;
    
    cout << "Suma de la matriz: " << suma << endl;
    
    delete[] A;
    delete[] B;
    for (int i = 0; i < filas; i++) delete[] M[i];
    delete[] M;
}

// Programa 2: Suma de dos matrices 3x3
void programa2() {
    int filas = 3, columnas = 3;
    int **M1 = new int*[filas], **M2 = new int*[filas], **M3 = new int*[filas];
    
    srand(time(0));
    
    for (int i = 0; i < filas; i++) {
        M1[i] = new int[columnas];
        M2[i] = new int[columnas];
        M3[i] = new int[columnas];
        for (int j = 0; j < columnas; j++) {
            M1[i][j] = rand() % 100;
            M2[i][j] = rand() % 100;
            M3[i][j] = M1[i][j] + M2[i][j];
        }
    }
    
    cout << "Matriz Resultante (M1 + M2):" << endl;
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            cout << M3[i][j] << " ";
        }
        cout << endl;
    }
    
    for (int i = 0; i < filas; i++) {
        delete[] M1[i]; delete[] M2[i]; delete[] M3[i];
    }
    delete[] M1; delete[] M2; delete[] M3;
}

// Programa 3: Identificar números palíndromos en una matriz 2x3
bool esPalindromo(int num) {
    int original = num, reverso = 0;
    while (num > 0) {
        reverso = reverso * 10 + num % 10;
        num /= 10;
    }
    return original == reverso;
}

void programa3() {
    int filas = 2, columnas = 3;
    int **M = new int*[filas], *A = new int[filas * columnas], *B = new int[filas * columnas];
    int indexA = 0, indexB = 0;
    
    srand(time(0));
    for (int i = 0; i < filas; i++) {
        M[i] = new int[columnas];
        for (int j = 0; j < columnas; j++) {
            M[i][j] = rand() % 900 + 100;
            if (esPalindromo(M[i][j])) A[indexA++] = M[i][j];
            else B[indexB++] = M[i][j];
        }
    }
    
    cout << "Arreglo A (Palíndromos): ";
    for (int i = 0; i < indexA; i++) cout << A[i] << " ";
    cout << endl;
    
    cout << "Arreglo B (No Palíndromos): ";
    for (int i = 0; i < indexB; i++) cout << B[i] << " ";
    cout << endl;
    
    delete[] A; delete[] B;
    for (int i = 0; i < filas; i++) delete[] M[i];
    delete[] M;
}

// Programa 5: Sumar valores en posiciones pares y contar impares en un arreglo
void programa5() {
    int *A = new int[7];
    int suma = 0, contador = 0;
    
    cout << "Ingrese 7 valores: ";
    for (int i = 0; i < 7; i++) {
        cin >> A[i];
        if (i % 2 == 0) suma += A[i];
        else contador++;
    }
    
    cout << "Suma de posiciones pares: " << suma << endl;
    cout << "Cantidad de valores en posiciones impares: " << contador << endl;
    
    delete[] A;
}

int main() {
    programa1();
    programa2();
    programa3();
    programa5();
    return 0;
}
