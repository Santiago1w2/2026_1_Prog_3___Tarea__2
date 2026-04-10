#include <iostream>
#include <concepts>
#include <iterator>
#include <vector>
using namespace std;
template < typename C >
concept Iterable = requires ( C c ) {
    std::begin ( c ) ;
    std::end ( c ) ;
};
template < typename T >
concept Addable = requires ( T a , T b ) {
    { a + b } -> std::same_as <T >;
};
template < typename T >
concept Divisible = requires ( T a , std::size_t n ) {
    { a / n } -> std::same_as <T>;
};

template <typename T>
concept Multipliable = requires (T a, T b) {
    { a * b } -> std::same_as<T>;
};
namespace core_numeric {
    template <typename T>
    T sum(const vector<T>& v) {
        T s = 0;
        for (auto x : v) {
            s += x;
        }
        return s;
    }
    template <typename T>
    requires Divisible<T>
    T mean(const vector<T>& v) {
        return sum(v) / v.size();
    }

    template <typename T>
    requires Divisible<T> and Addable<T> and Multipliable<T>
    T variance(const vector<T>& v) {
        T media = mean(v);
        vector<T> desviacion_cuadrado;
        for (auto x : v) {
            T diff = x - media;
            desviacion_cuadrado.push_back(diff * diff);
        }
        return mean(desviacion_cuadrado);
    }


}

int main() {
    /*vector<string> v{"2", "2", "3"};
    auto m = core_numeric::sum(v);
    cout << m << endl;*/

    vector<double> v{9, 8,10,11,12};
    auto m = core_numeric::variance(v);
    cout << m << endl;

    return 0;
}