#include <chrono>
#include <unordered_map>

using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;

struct data_structure {
    template <class T>
    struct custom_hash {
        static ull splitmix64(T x) {
            // http://xorshift.di.unimi.it/splitmix64.c
            x += 0x9e3779b97f4a7c15;
            x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
            x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
            return x ^ (x >> 31);
        }

        size_t operator()(T x) const {
            static const uint64_t FIXED_RANDOM =
                std::chrono::steady_clock::now().time_since_epoch().count();
            return splitmix64(x + FIXED_RANDOM);
        }
    };

    template <class T, class V>
    using unordered_map = std::unordered_map<T, V, custom_hash<T>>;
};
