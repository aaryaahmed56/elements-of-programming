#ifndef EOP_TRANSFORMATIONS_ORBITS_HPP
#define EOP_TRANSFORMATIONS_ORBITS_HPP

#include "../ch-01/founds.hpp"
namespace eop
{
    /**
     * @brief Helper function for L2 norm, computing
     * the squared distance of the arguments
     * 
     * @tparam _Tp A well-formed object type
     * @tparam Args Other well-formed object types
     * @param x A well-formed object
     * @param args Other well-formed objects
     * @return _Tp The squared distance
     */
    template< well_formed _Tp, well_formed... Args >
    _Tp squared_distance(const _Tp& x, const Args&&... args)
    {
        return pow(x, 2) + squared_distance(args...);
    }

    /**
     * @brief Variadic template struct for euclidean (L2) norm
     * as an n-ary operation
     * 
     * @tparam _Tp A well-formed object type
     * @tparam arity Argument count, i.e. n
     * @tparam Args Other well-formed object types
     */
    template< well_formed _Tp,
              const unsigned arity,
              well_formed... Args >
    struct euclidean_norm
    {
        inline
        _Tp operator()(const Args&&... args) const noexcept
        {
            return sqrt(squared_distance(args...));
        }
    };
    /**
     * @brief Specialization of L2 norm as a binary
     * operation
     * 
     * @tparam _Tp A well-formed object type
     */
    template< well_formed _Tp >
    struct euclidean_norm<_Tp, 2>
    {
        inline
        _Tp operator()(const _Tp& x0, const _Tp& x1) const noexcept
        {
            return sqrt(squared_distance(x0, x1));
        }
    };
} // namespace eop

#endif // !EOP_TRANSFORMATIONS_ORBITS_HPP