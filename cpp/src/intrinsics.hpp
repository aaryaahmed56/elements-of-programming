#ifndef EOP_INTRINSICS_H
#define EOP_INTRINSICS_H

#include "concepts.hpp"

namespace eop
{
    /**
     * @brief Prefix notation for pointers
     * 
     */
    #define pointer(_Tp) _Tp*
    #define unique_pointer(_Tp) std::unique_ptr<_Tp>

    /**
     * @brief Address method for raw
     * pointers
     * 
     * @tparam _Tp An arbitrary type from which a
     * pointer type is constructed
     */
    template< typename _Tp >
    pointer(_Tp) address_of(_Tp& x)
    {
        return &x;
    }

    /**
     * @brief Address method for a unique pointer
     * 
     * @tparam _Tp An arbitrary type from which a
     * pointer type is constructed
     */
    template< typename _Tp >
    unique_pointer(_Tp) address_of(_Tp& x)
    {
        return &x;
    }

    /**
     * @brief Method for construction
     * 
     * Precondition: $v$ refers to raw memory, not an object
     * Postcondition: $v$ is in a partially-formed state
     * 
     * @tparam ContainerType A container to store heterogeneous
     * constructible types
     * @tparam _Tp A constructible type
     * @tparam Args Other constructible types
     * @param p The container, passed by constant lvalue reference
     */
    template < template< typename, typename... > class ContainerType,
               Constructible _Tp, Constructible... Args >
    void construct(const ContainerType<_Tp, Args...>& p)
    {
        for (const auto& v : p)
        {
            new (&v) _Tp();
        }
    }

    /**
     * @brief Method for construction, with an initializer for
     * members
     * 
     * Precondition: $v$ refers to raw memory, not an object
     * Postcondition: Default makes $v = initializer$
     * Override $\func{construct}$ to specialize construction
     * of part of a container
     * 
     * @tparam ContainerType A container to store heterogeneous
     * constructible types
     * @tparam _Tp A constructible type
     * @tparam Args Other constructible types
     * @tparam U An
     * @param p The container, passed by constant lvalue reference
     * @param initializer The initializer, passed by constant lvalue
     * reference
     */
    template < template< typename, typename... > class ContainerType,
               Constructible _Tp, Constructible... Args, Constructible U >
    void construct(const ContainerType<_Tp, Args...>& p, const U& initializer)
    {
        for (const auto& v : p)
        {
            new (&v) _Tp(initializer);
        }
    }

    /**
     * @brief Method for destruction
     * 
     * Precondition: $v$ is in a partially-formed state
     * Postcondition: $v$ refers to raw memory, not an object
     * 
     * @tparam ContainerType A container to store heterogeneous
     * destructible types
     * @tparam _Tp A destructible type
     * @tparam Args Other destructible types
     * @param p The container, passed by constant lvalue reference
     */
    template < template< typename, typename... > class ContainerType,
               Destructible _Tp, Destructible... Args >
    void destruct(const ContainerType<_Tp, Args...>& p)
    {
        for (const auto& v : p)
        {
            v.~_Tp();
        }
    }

    /**
     * @brief Method for destruction, with a finalizer for members
     * 
     * Precondition: $v$ is in a partially-formed state
     * Postcondition: $v$ refers to raw memory, not an object
     * Override $\func{destruct}$ to specialize destruction of
     * part of a container
     * 
     * @tparam ContainerType A container to store heterogeneous
     * destructible types
     * @tparam _Tp A destructible type
     * @tparam Args Other destructible types
     * @tparam U A finalizer
     * @param p The container, passed by constant lvalue reference
     * @param finalizer The finalizer, passed by lvalue reference
     */
    template< template< typename, typename... > class ContainerType,
              Destructible _Tp, Destructible... Args, Destructible U >
    void destruct(const ContainerType<_Tp, Args...>& p, U& finalizer)
    {
        for (const auto& v : p)
        {
            destruct(v);
        }
    }
} // namespace eop

#endif // !EOP_PRECOMP_H