#ifndef EOP_INTRINSICS_H
#define EOP_INTRINSICS_H

#include "precomp.hpp"
#include "concepts.hpp"

namespace eop
{

    // Template constraints

    #define pointer(_Tp) _Tp*

    // Return addresses.
    template< Pointer _Tp >
    pointer(_Tp) address_of(_Tp& x)
    {
        return &x;
    }

    // In-place construction and destruction.
    template < template< Regular, Regular... > class ContainerType,
               Regular _Tp, Regular... Args >
    void construct(const ContainerType<_Tp, Args...>& p)
    {
        for (const auto& v : p)
        {
                // Precondition: $v$ refers to raw memory, not an object
                // Postcondition: $v$ is in a partially-formed state
            new (&v) _Tp();
        }
    }

    template < template< typename, typename... > class ContainerType,
               Regular _Tp, Regular... Args, Constructible U >
    void construct(const ContainerType<_Tp, Args...>& p, const U& initializer)
    {
        for (const auto& v : p)
        {
                // Precondition: $v$ refers to raw memory, not an object
                // Postcondition: Default makes $v = initializer$
                // Override $\func{construct}$ to specialize construction of a part of a 
            new (&v) _Tp(initializer);
        }
    }

    template < template< Regular, Regular... > class ContainerType,
               Regular _Tp, Regular... Args >
    void destruct(const ContainerType<_Tp, Args...>& p)
    {
        for (const auto& v : p)
        {
                // Precondition: $v$ is in a partially-formed state
                // Postcondition: $v$ refers to raw memory, not an object
            v.~_Tp();
        }
    }

    template< template< Regular, Regular... > class ContainerType,
              Regular _Tp, Regular... Args, typename U >
    void destruct(const ContainerType<_Tp, Args...>& p, U& finalizer)
    {
        for (const auto& v : p)
        {
                // Precondition: $v$ is in a partially-formed state
                // Postcondition: $v$ refers to raw memory, not an object
                // Override $\func{destruct}$ to specialize destruction of a part of a container
            destruct(v);
        }
    }

} // namespace eop

#endif // !EOP_PRECOMP_H