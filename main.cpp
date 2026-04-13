#include <iostream>
#include <concepts>
#include <vector>

using namespace std;

template<typename C>
concept Iterable = requires(C c) {
    begin(c);
    end(c);
};
template <typename T>
concept Addable = requires(T a, T b) {
    { a + b } -> same_as<T>;
};

template <typename T>
concept Subtractable = requires(T a, T b) {
    { a - b } -> same_as<T>;
};

template <typename T>
concept Divisible = requires(T a, size_t n) {
    { a / n } -> same_as<T>;
};
template <typename T>
concept Comparable = requires(T a, T b) {
    { a > b } -> same_as<bool>;
};


namespace core_numeric {
    template <Iterable C>
    auto sum(const C& v) {
        auto i=begin(v);
        auto result =*i;
        ++i;
        for (;i!=end(v);++i) {
            result = result + *i;
        }
        return result;
     }
    template <Iterable C>
    auto mean(const C& v) {
        if (v.empty())
            return 0.0;
        auto s = sum(v);
        int n = v.size();
        return (double)s / n;
    }

    template <Iterable C>
    requires Subtractable<double>
    double variance(const C& v) {
        if (v.empty()) return 0.0;
        double m = mean(v);
        vector<double> temp;
        for (auto x : v) {
            // Requiere que los elementos soporten resta
            double diff = x - m;
            temp.push_back(diff * diff);
        }
        return mean(temp);
    }

    template <typename T>
    requires Comparable<T>
    T max(const vector<T>& data) {
        if (data.empty()) {
            throw runtime_error("Empty container");
        };
        T current_max = data[0];
        for (const auto& x : data) {
            if (x > current_max) current_max = x;
        }
        return current_max;
    }

    template <Iterable C, typename f>
    auto transform_reduce(const C& v, f transform) {
        auto i = begin(v);
        auto result = transform(*i);
        ++i;
        for (;i!=end(v);++i) {
            result = result + transform(*i);
        }
        return result;
    }

    //Variadic

    template <typename... Args>
        auto mean_variadic(Args... args) {
        double total = (... + args);
        return total / sizeof...(args);
    }


    template <typename... Args>
    auto variance_variadic(Args... args) {
        double m = mean_variadic(args...);
        vector<double> temp = { ((args - m) * (args - m))... };
        return mean(temp);
    }

    template <typename... Args>
    auto max_variadic(Args... args) {
        vector<double> v = { (double)args... };
        return max(v);
    }

    template <typename... Args>
    auto sum_variadic(Args... args) {
        if constexpr (sizeof...(args) == 0) {
            return 0; 
        } else {
            return (... + args);
        }
    }
}

/*int main() {
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


   /* auto s1 = core_numeric :: sum_variadic (1 ,2 ,33 ,4) ;
    auto s2 = core_numeric :: mean_variadic (0.1 ,2 ,3 ,4) ;
    auto s3 = core_numeric :: variance_variadic (1 ,2 ,3 ,4) ;
    auto s4 = core_numeric :: max_variadic (1 ,2.7 ,3 ,4) ;

    cout << s1 << endl << s2 << endl << s3 << endl << s4 << endl;
}*/