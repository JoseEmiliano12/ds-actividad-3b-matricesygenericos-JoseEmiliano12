#ifndef MATRIZ_DINAMICA_H
#define MATRIZ_DINAMICA_H

#include <stdexcept> // invalid_argument, out_of_range
#include <type_traits> // common_type

template <typename T>
class MatrizDinamica {
private:
    T **datos;
    int f;
    int c;

    void reservar(int nf, int nc, const T& init = T{}) {
        if (nf < 0 || nc < 0) throw std::invalid_argument("dimensiones negativas");
        f = nf; c = nc;
        if (f == 0 || c == 0) { datos = nullptr; return; }

        datos = new T*[f];
        for (int i = 0; i < f; ++i) {
            datos[i] = new T[c];
            for (int j = 0; j < c; ++j) datos[i][j] = init;
        }
    }

    void liberar() {
        if (!datos) return;
        for (int i = 0; i < f; ++i) delete[] datos[i];
        delete[] datos;
        datos = nullptr; f = c = 0;
    }

public:
    // constructor con regla de 3 
    MatrizDinamica() : datos(nullptr), f(0), c(0) {}
    MatrizDinamica(int nf, int nc, const T& init = T{}) : datos(nullptr), f(0), c(0) { reservar(nf, nc, init); }
    ~MatrizDinamica() { liberar(); }

    MatrizDinamica(const MatrizDinamica& o) : datos(nullptr), f(0), c(0) {
        reservar(o.f, o.c);
        for (int i = 0; i < f; ++i)
            for (int j = 0; j < c; ++j)
                datos[i][j] = o.datos[i][j];
    }

    MatrizDinamica& operator=(const MatrizDinamica& o) {
        if (this == &o) return *this;
        liberar();
        reservar(o.f, o.c);
        for (int i = 0; i < f; ++i)
            for (int j = 0; j < c; ++j)
                datos[i][j] = o.datos[i][j];
        return *this;
    }

    // getters
    int filas() const { return f; }
    int columnas() const { return c; }

    // acceso 
    T& at(int i, int j) {
        if (i < 0 || i >= f || j < 0 || j >= c) throw std::out_of_range("indice fuera de rango");
        return datos[i][j];
    }
    const T& at(int i, int j) const {
        if (i < 0 || i >= f || j < 0 || j >= c) throw std::out_of_range("indice fuera de rango");
        return datos[i][j];
    }

    // redimensionar
    void redimensionar(int nf, int nc) {
        if (nf < 0 || nc < 0) throw std::invalid_argument("dimensiones negativas");
        MatrizDinamica tmp(nf, nc, T{});
        int fm = (nf < f ? nf : f);
        int cm = (nc < c ? nc : c);
        for (int i = 0; i < fm; ++i)
            for (int j = 0; j < cm; ++j)
                tmp.datos[i][j] = datos[i][j];
        *this = tmp; // usa asignación por copia
    }

    // --- imprimir simple -
    void imprimir() const {
        for (int i = 0; i < f; ++i) {
            std::cout << "| ";
            for (int j = 0; j < c; ++j) {
                std::cout << datos[i][j];
                if (j + 1 < c) std::cout << " ";
            }
            std::cout << " |\n";
        }
    }

    // --- multiplicacion: A(T) x B(U) -> common_type<T,U> ---
    template <typename U>
    static MatrizDinamica<typename std::common_type<T,U>::type>
    Multiplicar(const MatrizDinamica<T>& A, const MatrizDinamica<U>& B) {
        if (A.columnas() != B.filas())
            throw std::invalid_argument("dimensiones incompatibles");
        using R = typename std::common_type<T,U>::type;
        MatrizDinamica<R> C(A.filas(), B.columnas(), R{});
        for (int i = 0; i < A.filas(); ++i) {
            for (int j = 0; j < B.columnas(); ++j) {
                R s = R{};
                for (int k = 0; k < A.columnas(); ++k)
                    s += static_cast<R>(A.at(i,k)) * static_cast<R>(B.at(k,j));
                C.at(i,j) = s;
            }
        }
        return C;
    }
};

#endif
