#ifndef EOP_INTRINSICS_H
#define EOP_INTRINSICS_H

#include "concepts.hpp"

namespace eop
{
    // Template constraints
    #define pointer(_Tp) _Tp*
    #define unique_pointer(_Tp) std::unique_ptr<_Tp>

    // Return addresses.
    template< Pointer _Tp >
    pointer(_Tp) address_of(_Tp& x)
    {
        return &x;
    }
    
    template< Pointer _Tp >
    unique_pointer(_Tp) address_of(_Tp& x)
    {
        return &x;
    }

    template < template< typename, typename... > class ContainerType,
               Constructible _Tp, Constructible... Args >
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
               Constructible _Tp, Constructible... Args, Constructible U >
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

    template < template< typename, typename... > class ContainerType,
               Destructible _Tp, Destructible... Args >
    void destruct(const ContainerType<_Tp, Args...>& p)
    {
        for (const auto& v : p)
        {
                // Precondition: $v$ is in a partially-formed state
                // Postcondition: $v$ refers to raw memory, not an object
            v.~_Tp();
        }
    }

    template< template< typename, typename... > class ContainerType,
              Destructible _Tp, Destructible... Args, Destructible U >
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