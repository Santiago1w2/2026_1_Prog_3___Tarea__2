#include <iostream>
#include <concepts>
#include <vector>

using namespace std;

// --- SIMPLIFIED CONCEPTS ---
template <typename T>
concept Addable = requires(T a, T b) {
    { a + b } -> convertible_to<T>;
};

template <typename T>
concept Multipliable = requires(T a, T b) {
    { a * b } -> convertible_to<T>;
};

template <typename T>
concept Divisible = requires(T a, size_t n) {
    { a / n } -> convertible_to<T>;
};

template <typename T>
concept Numeric = Addable<T> && Multipliable<T> && Divisible<T>;

namespace core_numeric {

    template <typename T>
    requires Numeric<T>
    auto mean(const vector<T>& v) {
        if (v.empty()) return 0.0;
        T s = 0;
        for (const auto& x : v) s += x;
        if constexpr (std::is_integral_v<T>) {
            return static_cast<double>(s) / v.size();
        } else {
            return s / v.size();
        }
    }

    template <typename T>
    requires Numeric<T>
    T variance(const vector<T>& v) {
        if (v.empty()) return T{};
        T media = mean(v);
        vector<T> desviacion_cuadrado;
        for (auto x : v) {
            T diff = x - media;
            desviacion_cuadrado.push_back(diff * diff);
        }
        return mean(desviacion_cuadrado);
    }

    template <typename T>
    requires Numeric<T>
    T max(const vector<T>& data) {
        if (data.empty()) return T{};
        T current_max = data[0];
        for (const auto& x : data) {
            if (x > current_max) current_max = x;
        }
        return current_max;
    }

    // --- VARIADIC HELPERS (No type_traits) ---

    template <typename... Args>
    auto mean_variadic(Args... args) {
        // Use decltype with a fold expression to find the common type
        using T = decltype((... + args));
        vector<T> args_copy{ static_cast<T>(args)... };
        return core_numeric::mean(args_copy);
    }

    template <typename... Args>
    auto variance_variadic(Args... args) {
        using T = decltype((... + args));
        vector<T> args_copy{ static_cast<T>(args)... };
        return core_numeric::variance(args_copy);
    }

    template <typename... Args>
    auto max_variadic(Args... args) {
        using T = decltype((... + args));
        vector<T> args_copy{ static_cast<T>(args)... };
        return core_numeric::max(args_copy);
    }

    template <typename... Args>
    auto sum_variadic(Args... args) {
        if constexpr (sizeof...(args) == 0) {
            return 0; 
        } else if constexpr (sizeof...(args) == 1) {
            return (... + args);
        } else {
            return (... + args);
        }
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
    /*
    vector<double> v = {1.0, 2.0, 3.0, 4.0};

    auto r = core_numeric::transform_reduce(v, [](double x) {
        return x * x; // The "multiployable" logic
    });

    std::cout << r << std::endl; // Output: 30
    return 0;
    */
    auto s1 = core_numeric :: sum_variadic (1 ,2 ,33 ,4) ;
    auto s2 = core_numeric :: mean_variadic (0.1 ,2 ,3 ,4) ;
    auto s3 = core_numeric :: variance_variadic (1 ,2 ,3 ,4) ;
    auto s4 = core_numeric :: max_variadic (1 ,2.7 ,3 ,4) ;

    cout << s1 << endl << s2 << endl << s3 << endl << s4 << endl;
}