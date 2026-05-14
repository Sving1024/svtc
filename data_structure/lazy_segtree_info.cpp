namespace data_structure {
namespace add_multiply {
template <typename T>
struct tag_t {
    T a;
    T b;

    tag_t(T _a = 1, T _b = 0) : a(_a), b(_b) {}

    friend tag_t operator+(const tag_t &lhs, const tag_t &rhs) {
        return {rhs.a * lhs.a, rhs.b * lhs.a + lhs.b};
    }
};

template<typename T>
struct info_t {
    T sum;
    size_t len;

    info_t(T _sum = 0, size_t _len = 0) : sum(_sum), len(_len) {}

    friend info_t operator+(const info_t &lhs, const info_t &rhs) {
        return {lhs.sum + rhs.sum, lhs.len + rhs.len};
    }

    friend info_t operator*(const tag_t &lhs, const info_t &rhs) {
        return {rhs.sum * lhs.a + lhs.b * rhs.len, rhs.len};
    }
};
} // namespace add_multiply
} // namespace data_structure
