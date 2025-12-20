using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;

namespace numbers {
    template <typename T>
    T inf() {
        assert(false);
    }

    template <>
    int inf<int>() {
        return 0x3f3f3f3f;
    }

    template <>
    uint inf<uint>() {
        return 0x3f3f3f3f;
    }

    template <>
    ll inf<ll>() {
        return 0x3f3f3f3f3f3f3f3f;
    }

    template <>
    ull inf<ull>() {
        return 0x3f3f3f3f3f3f3f3f;
    }
} // namespace numbers