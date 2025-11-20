#include <array>
#include <string>
#include <vector>

namespace string_utils {
    using std::string;

    const std::vector<char> charset{'0', '1'};
    const size_t charset_size = 2;

    const size_t npos = static_cast<size_t>(-1);

    std::vector<size_t> calculate_nxt(const string &s) {
        std::vector<size_t> nxt(s.size() + 1);
        nxt[0] = npos;
        size_t nxt_pos = nxt[0];
        for (size_t i = 0; i < s.size(); i++) {
            while (nxt_pos != npos && s[nxt_pos] != s[i]) {
                nxt_pos = nxt[nxt_pos];
            }
            nxt_pos++;
            nxt[i + 1] = nxt_pos;
        }
        return nxt;
    }

    std::vector<std::array<size_t, charset_size>>
    kmp_automaton(const string &s, const std::vector<size_t> &nxt) {
        std::vector<std::array<size_t, charset_size>> res(s.size());
        for (size_t i = 0; i < s.size(); i++) {
            for (size_t j = 0; j < charset.size(); j++) {
                auto nxt_char = charset[j];
                if (nxt_char == s[i]) {
                    res[i][j] = i + 1;
                }
                else {
                    if (nxt[i] == npos) {
                        res[i][j] = 0;
                    }
                    else {
                        res[i][j] = res[nxt[i]][j];
                    }
                }
            }
        }
        return res;
    }

    std::vector<size_t> match(const string &s, const string &t,
                              const std::vector<size_t> &nxt) {
        std::vector<size_t> ret(t.size() + 1);
        size_t nxt_pos = 0;
        for (size_t i = 0; i < t.size(); i++) {
            while (nxt_pos == s.size() ||
                   (nxt_pos != npos && s[nxt_pos] != t[i])) {
                nxt_pos = nxt[nxt_pos];
            }
            nxt_pos++;
            ret[i + 1] = nxt_pos;
        }
        return ret;
    }
}; // namespace string_utils
