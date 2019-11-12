#ifndef EOP_INTRINSICS
#define EOP_INTRINSICS

#include <new>

namespace EOP
{

    // Template constraints

    // This treats the requires clause as documentation only.
    #define requires(...)

    #define pointer(_Tp) _Tp*

    // Return addresses.
    template< typename _Tp >
    pointer(_Tp) address_of(_Tp& x)
    {
        return &x;
    }

    // In-place construction and destruction.
    template < template< typename, typename... > class ContainerType,
               typename _Tp, typename... Args >
    void construct(const ContainerType<_Tp, Args...>& p)
    {
        for (const auto& v : p)
        {
                // Precondition: $v$ refers to raw memory, not an object
                // Postcondition: $v$ is in a default-constructed state
            new (&v) _Tp();
        }
    }

    template < template< typename, typename... > class ContainerType,
               typename _Tp, typename... Args, typename U >
        requires(Regular(_Tp) && Constructible(_Tp, U))
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
               typename _Tp, typename... Args >
        requires(Regular(_Tp))
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
              typename _Tp, typename... Args, typename U >
        requires(Regular(_Tp))
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

    
} // namespace EOP


#endif