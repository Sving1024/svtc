#include "math/modular.hpp"

namespace string_utils {
    template <ull base, ull mod>
    struct hash_string {
        std::vector<maths::modular<mod>> prime_pow, h;
        std::string s;
        static const size_t npos = -1;
        hash_string(const std::string &_s) : s(_s) {
            prime_pow.resize(s.size() + 1);
            prime_pow[0] = 1;
            for (size_t i = 1; i < prime_pow.size(); i++) {
                prime_pow[i] = base * prime_pow[i - 1];
            }
            h.resize(s.size() + 1);
            h[0] = 0;
            for (size_t i = 1; i < s.size(); i++) {
                h[i] = h[i - 1] * base + s[i - 1] - 'A';
            }
            return;
        }

        maths::modular<mod> substr(size_t pos, size_t len) {
            return h[pos + len] - h[pos] * prime_pow[len];
        }

        size_t size() const { return s.size(); }

        size_t find(const hash_string &str, size_t pos = 0) {
            for (size_t i = pos; i + str.size() <= s.size(); i++) {
                if (substr(i, str.size()) == str.h.back()) {
                    return pos;
                }
            }
            return npos;
        }
    };
} // namespace string_utils