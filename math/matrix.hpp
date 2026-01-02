#include <array>
#include <functional>

namespace maths {
    template <size_t N, size_t M, typename T = int,
              typename plus_op_t = std::plus<>,
              typename multiply_op_t = std::multiplies<>>
    struct matrix {
        const plus_op_t plus_op;
        const multiply_op_t multiply_op;
        const T id_plus, id_multiplies;

        std::array<std::array<T, M>, N> mat;

        matrix clear() {
            for (size_t i = 0; i < N; i++) {
                mat[i].fill(id_plus);
            }
            return *this;
        }

        matrix reset() {
            clear();
            for (size_t i = 0; i < std::min(N, M); i++) {
                mat[i][i] = id_multiplies;
            }
            return *this;
        }

        matrix(const plus_op_t _plus_op = plus_op_t(),
               const multiply_op_t _multiply_op = multiply_op_t(),
               const T _id_plus = T(), const T _id_multiplies = T(1))
            : plus_op(_plus_op), multiply_op(_multiply_op), id_plus(_id_plus),
              id_multiplies(_id_multiplies) {
            clear();
        }

        matrix(const std::array<std::array<T, N>, M> &_mat,
               const plus_op_t _plus_op = plus_op_t(),
               const multiply_op_t _multiply_op = multiply_op_t(),
               const T _id_plus = T(), const T _id_multiplies = T(1))
            : plus_op(_plus_op), multiply_op(_multiply_op), id_plus(_id_plus),
              id_multiplies(_id_multiplies), mat(_mat) {}

        template <size_t K>
        friend matrix<K, M, T> operator*(const matrix<K, N, T> &lhs,
                                         const matrix<N, M, T> &rhs) {
            matrix<K, M, T, plus_op_t, multiply_op_t> ret(
                rhs.plus_op, rhs.multiply_op, rhs.id_plus, rhs.id_multiplies);
            ret.clear();
            for (size_t i = 0; i < N; i++) {
                for (size_t k = 0; k < K; k++) {
                    for (size_t j = 0; j < M; j++) {
                        ret.mat[k][j] = ret.plus_op(
                            ret.mat[k][j],
                            ret.multiply_op(lhs.mat[k][i], rhs.mat[i][j]));
                    }
                }
            }
            return ret;
        }

        friend matrix operator+(const matrix &lhs, const matrix &rhs) {
            matrix ret(rhs.plus_op, rhs.multiply_op, rhs.id_plus,
                       rhs.id_multiplies);
            ret.clear();
            for (size_t i = 0; i < N; i++) {
                for (size_t j = 0; j < M; j++) {
                    ret.mat[i][j] = ret.plus_op(lhs.mat[i][j], rhs.mat[i][j]);
                }
            }
            return ret;
        }

        matrix &operator=(const matrix &rhs) {
            mat = rhs.mat;
            return *this;
        }
    };

} // namespace maths
