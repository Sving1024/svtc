#include <array>

using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;

namespace fastio {
template <ull BUFFER_SIZE>
struct fast_istream {
    std::array<char, BUFFER_SIZE> buffer;
    uint index;

    char get() {
        if (index == BUFFER_SIZE) {
            std::fread(buffer.data(), sizeof(char), BUFFER_SIZE, stdin);
            index = 0;
        }
        return buffer[index++];
    }

    fast_istream &operator>>(ll &val) {
        char c = get();
        ll f = 1;
        while (!isdigit(c)) {
            if (c == '-') {
                f = -1;
            }
            c = get();
        }

        val = 0;

        while (isdigit(c)) {
            val *= 10;
            val += c - '0';
            c = get();
        }

        val *= f;
        return *this;
    }

    fast_istream &operator>>(int &val) {
        char c = get();
        ll f = 1;
        while (!isdigit(c)) {
            if (c == '-') {
                f = -1;
            }
            c = get();
        }

        val = 0;

        while (isdigit(c)) {
            val *= 10;
            val += c - '0';
            c = get();
        }

        val *= f;
        return *this;
    }

    fast_istream &operator>>(uint &val) {
        char c = get();

        while (isspace(c)) {
            c = get();
        }

        val = 0;

        while (isdigit(c)) {
            val *= 10;
            val += c - '0';
            c = get();
        }

        return *this;
    }

    fast_istream &operator>>(ull &val) {
        char c = get();

        while (isspace(c)) {
            c = get();
        }

        val = 0;

        while (isdigit(c)) {
            val *= 10;
            val += c - '0';
            c = get();
        }

        return *this;
    }

    fast_istream() : index(0) {
        std::fread(buffer.data(), sizeof(char), BUFFER_SIZE, stdin);
    }
};
} // namespace fastio
