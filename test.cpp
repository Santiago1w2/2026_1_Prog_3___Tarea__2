#include "main.cpp"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

// =======================
// CLASE PROPIA
// =======================
class Coordenada2D {
    double x, y;
public:
    Coordenada2D(double x, double y) : x(x), y(y) {}

    Coordenada2D operator+(const Coordenada2D& o) const {
        return Coordenada2D(x + o.x, y + o.y);
    }

    Coordenada2D operator/(size_t n) const {
        return Coordenada2D(x / n, y / n);
    }

    Coordenada2D operator-(const Coordenada2D& o) const {
        return Coordenada2D(x - o.x, y - o.y);
    }

    bool operator>(const Coordenada2D& o) const {
        return (x + y) > (o.x + o.y);
    }

    void print() const {
        cout << "(" << x << "," << y << ")";
    }
};
class Punto {
    int x;
public:
    Punto() : x(0) {}
    Punto(int x) : x(x) {}

    // Para sum (Addable)
    int getX(){return x;}
    Punto operator+(const Punto& other) const {
        return Punto(x + other.x);
    }

    // Para mean (Divisible)
    Punto operator/(size_t n) const {
        return Punto(x / n);
    }

    // Para variance (Subtractable)
    Punto operator-(const Punto& other) const {
        return Punto(x - other.x);
    }

    // Para max (Comparable)
    bool operator>(const Punto& other) const {
        return x > other.x;
    }
};
class Vector3D {
    double x, y, z;
public:
    Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}

    Vector3D operator+(const Vector3D& o) const {
        return Vector3D(x + o.x, y + o.y, z + o.z);
    }

    Vector3D operator/(size_t n) const {
        return Vector3D(x / n, y / n, z / n);
    }

    Vector3D operator-(const Vector3D& o) const {
        return Vector3D(x - o.x, y - o.y, z - o.z);
    }

    bool operator>(const Vector3D& o) const {
        return (x + y + z) > (o.x + o.y + o.z);
    }

    void print() const {
        cout << "(" << x << "," << y << "," << z << ")";
    }
};
class Esfera {
    double radio;
public:
    Esfera(double r) : radio(r) {}

    Esfera operator+(const Esfera& o) const {
        return Esfera(radio + o.radio);
    }

    Esfera operator/(size_t n) const {
        return Esfera(radio / n);
    }

    Esfera operator-(const Esfera& o) const {
        return Esfera(radio - o.radio);
    }

    bool operator>(const Esfera& o) const {
        return radio > o.radio;
    }

    double getRadio() const {
        return radio;
    }
};
int main() {

    // =======================
    // CASOS QUE COMPILAN
    // =======================
    vector<Coordenada2D> c2d{
        {1,2}, {3,4}, {0,1}
    };

    //ERROR AL COMPILAR, NO SE PUEDEN COMPARAR PARES ORDENADOS, YA QUE NO SON VALORES ARITMETICOS
    //auto mc2d = core_numeric::max(c2d);
    //cout << "maximo1 : ";mc2d.print(); cout << endl;


    vector<Esfera> es{
        {2.0}, {5.0}, {3.0}
    };
    //NO COMPILA, YA QUE ES NO TIENE VALORES ARITMETICOS COMPARABLES
    ///auto mes = core_numeric::max(es);
    //cout << mes.getRadio() << endl;

    //PRUEBA EXITOSA DE VECTORES
    vector<int> v1{1,2,3};
    cout << core_numeric::sum(v1) << endl;
    cout << core_numeric::mean(v1) << endl;
    cout << core_numeric::max(v1) << endl;

    //PRUEBA EXITOSA DE VECTORES
    vector<double> v2{1.0,2.0,3.0};
    cout << core_numeric::variance(v2) << endl;

    vector<double> v3{1,2.7,0.3};
    cout << core_numeric::max(v3) << endl;

    //PRUEBA DE TRANSFORMACION DE REDUCCION
    auto r = core_numeric::transform_reduce(v2, [](double x){
        return x * x;
    });
    cout << r << endl;

    //PRUEBAS DE VARIADIC: 
    cout <<"Sum variadic: " << core_numeric::sum_variadic(1,2,3,4) << endl;
    cout << "Max Variadic: " <<core_numeric::max_variadic(1,2.7,3.8) << endl;
    cout << "Mean variadic: " << core_numeric::mean_variadic(2, 3, 4, 5, 2) << endl;
    cout << "Variance variadic: " << core_numeric::variance_variadic(1, 2, 32, 4, 2, 1 , 6) << endl;




    // Clase propia
    vector<Punto> vp{Punto(1), Punto(5), Punto(3)};

    // NO COMPILA YA QUE NO SON VALORES NUMERICOS
    //auto m = core_numeric::max(vp);



    // =======================
    // CASOS QUE NO COMPILAN
    // =======================

    vector<string> vs{"a","b","c"};

    // core_numeric::mean(vs);
    // ERROR: string no cumple Divisible
    // (no se puede hacer string / n)

    // core_numeric::variance(vs);
    // ERROR: string no cumple Subtractable
    // (no existe string - string)

    // core_numeric::max(vs);
    // ERROR: restringido por Comparable
    // (aunque string tiene >, según diseño se restringe)

    vector<char> vc{'a','b','c'};

    // core_numeric::variance(vc);
    // ERROR: char no es adecuado para operaciones numéricas
    // (problema en resta y conversión a double)

    return 0;
}