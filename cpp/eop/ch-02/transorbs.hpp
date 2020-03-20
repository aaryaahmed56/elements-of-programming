#ifndef EOP_TRANSFORMATIONS_ORBITS_HPP
#define EOP_TRANSFORMATIONS_ORBITS_HPP

#include "../ch-01/founds.hpp"
namespace eop
{
    /**
     * @brief Helper function for L2 norm, computing
     * the squared distance of the arguments
     * 
     * @tparam _Tp An arithmetic type
     * @tparam Args Other arithmetic types
     * @param x A point
     * @param args Other points
     * @return _Tp The squared distance
     */
    template< arithmetic _Tp, arithmetic... Args >
    _Tp squared_distance(const _Tp& x, const Args&&... args)
    {
        static_assert(std::is_arithmetic_v<_Tp>
            && std::is_arithmetic_v<Args...>);
        return pow(x, 2) + squared_distance(args...);
    }

    /**
     * @brief Variadic template struct for euclidean (L2) norm
     * as an n-ary operation
     * 
     * @tparam _Tp An arithmetic type
     * @tparam arity Argument count, i.e. n
     * @tparam Args Other arithmetic types
     */
    template< arithmetic _Tp,
              const unsigned arity,
              arithmetic... Args >
    struct euclidean_norm
    {
        inline
        _Tp operator()(const Args&&... args) const noexcept
        {
            static_assert(std::is_arithmetic_v<Args...>);
            return sqrt(squared_distance(args...));
        }
    };
    /**
     * @brief Specialization of L2 norm as a binary
     * operation
     * 
     * @tparam _Tp An arithmetic type
     */
    template< arithmetic _Tp >
    struct euclidean_norm<_Tp, 2>
    {
        inline
        _Tp operator()(const _Tp& x0, const _Tp& x1) const noexcept
        {
            static_assert(std::is_arithmetic_v<_Tp>);
            return sqrt(squared_distance(x0, x1));
        }
    };

    /**
     * @brief Computes the n-th iterate of a transformation
     * applied to some domain element
     * 
     * @tparam F A type for transformation,like a homogeneous
     * predicate or operation type
     * @tparam N An arithmetic type
     * @param x An element of the domain of F
     * @param n The iterate number
     * @param f Some transformation
     * @return eop::domain<F> 
     */
    template< transformation F, arithmetic N >
    constexpr
    eop::domain<F> power_unary(eop::domain<F> x, N n, F f) noexcept
    {
        static_assert(std::is_arithmetic_v<N>);
        while (n != N(0))
        {
            n = n - N(1);
            x = f(x);
        }
        return x;
    }

    template< transformation F >
    constexpr
    eop::distance_type<F> orbit_distance(eop::domain<F> x, eop::domain<F> y,
        F f) noexcept
    {
        using N = eop::distance_type<F>;
        N n(0);
        while (x != y)
        {
            x = f(x);
            n = n + N(1);
        }
        return n;
    }
} // namespace eop

#endif // !EOP_TRANSFORMATIONS_ORBITS_HPP