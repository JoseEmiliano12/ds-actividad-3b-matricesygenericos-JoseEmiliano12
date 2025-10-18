#include <iostream>
#include "MatrizDinamica.h"

int main() {
    std::cout << "--- Sistema de Análisis de Transformaciones Lineales ---\n\n";
    try {
        // A: matriz int 2x3
        std::cout << ">> Prueba de Matriz ENTERA (Matriz A) <<\n";
        std::cout << "Creando Matriz A (Tipo INT) de 2x3...\n\n";
        MatrizDinamica<int> A(2, 3, 0);

        std::cout << "Ingresar valores para A (2x3):\n";
        for (int i = 0; i < A.filas(); ++i) {
            for (int j = 0; j < A.columnas(); ++j) {
                std::cout << "A[" << i << "," << j << "]: ";
                int v; std::cin >> v;
                A.at(i, j) = v;
            }
        }

        std::cout << "\n>> Redimensionando Matriz A <<\n";
        std::cout << "Redimensionando A a 3x3. Datos conservados:\n";
        A.redimensionar(3, 3);
        A.imprimir();
        std::cout << "\n";

        // B: matriz float 3x2
        std::cout << ">> Prueba de Multiplicación (Tipo FLOAT) <<\n";
        std::cout << "Creando Matriz B (Tipo FLOAT) de 3x2...\n";
        MatrizDinamica<float> B(3, 2, 0.0f);
        for (int i = 0; i < B.filas(); ++i) {
            for (int j = 0; j < B.columnas(); ++j) {
                std::cout << "B[" << i << "," << j << "]: ";
                float v; std::cin >> v;
                B.at(i, j) = v;
            }
        }

        std::cout << "\nMatriz C = A(3x3) x B(3x2) ...\n\n";
        auto C = MatrizDinamica<int>::Multiplicar(A, B); // int x float -> common_type float
        std::cout << "Matriz C (Resultado 3x2, Tipo FLOAT):\n";
        C.imprimir();
        std::cout << "\nLiberando memoria de todas las matrices...\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
