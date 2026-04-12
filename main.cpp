#include <iostream>
#include <concepts>
#include <iterator>
#include <vector>
using namespace std;
template < typename C >
concept Iterable = requires ( C c ) {
    begin ( c ) ;
    end ( c ) ;
};
template < typename T >
concept Addable = requires ( T a , T b ) {
    { a + b } -> same_as <T >;
};
template < typename T >
concept Divisible = requires ( T a , std::size_t n ) {
    { a / n } -> same_as <T>;
};

template <typename T>
concept Multipliable = requires (T a, T b) {
    { a * b } -> same_as<T>;
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
    template <typename T>
    requires Iterable<T>
        T max(vector<T>& data) {
        T max = data[0];
        for (auto x : data) {
            if (x > max) {
                max = x;
            }
        }
        return max;
    }
    template <typename c, typename f>
    auto transform_reduce(const c& v, f transform) {
        using T = decltype(transform(*v.begin()));

        T result = 0;

        for (const auto& element : v) {
            result += transform(element);
        }

        return result;
    }


}


int main() {
    /*vector<string> v{"2", "2", "3"};
    auto m = core_numeric::sum(v);
    cout << m << endl;*/
    /*
    vector<double> v{9, 8,10,11,12};
    auto m = core_numeric::variance(v);
    cout << m << endl;
    */

    //Prueba 2
    /*
    vector<string> data = {"a", "b", "c"};

    cout << core_numeric::max(data) << endl;
    */
    std::vector<double> v = {1.0, 2.0, 3.0, 4.0};

    // Usage as seen in your image:
    auto r = core_numeric::transform_reduce(v, [](double x) {
        return x * x; // The "multiployable" logic
    });

    std::cout << r << std::endl; // Output: 30
    return 0;
}