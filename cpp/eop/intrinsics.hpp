#ifndef EOP_INTRINSICS_H
#define EOP_INTRINSICS_H

#include "concepts.hpp"

namespace eop
{
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
               constructible _Tp, constructible... Args >
    void construct(const ContainerType<_Tp, Args...>& p)
    {
        static_assert(std::is_constructible_v<_Tp>
            && std::is_constructible_v<Args...>);
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
               constructible _Tp, constructible... Args, constructible U >
    void construct(const ContainerType<_Tp, Args...>& p, const U& initializer)
    {
        static_assert(std::is_constructible_v<_Tp>
            && std::is_constructible_v<Args...>);
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
               destructible _Tp, destructible... Args >
    void destruct(const ContainerType<_Tp, Args...>& p)
    {
        static_assert(std::is_destructible_v<_Tp>
            && std::is_destructible_v<Args...>);
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
              destructible _Tp, destructible... Args, destructible U >
    void destruct(const ContainerType<_Tp, Args...>& p, U& finalizer)
    {
        static_assert(std::is_destructible_v<_Tp>
            && std::is_destructible_v<Args...>);
        for (const auto& v : p)
        {
            destruct(v);
        }
    }

    /**
     * @brief Prefix notation for a raw pointer
     * 
     */
    template< typename _Tp >
    using raw_ptr = _Tp*;

    /**
     * @brief Address method to construct a raw
     * pointer from a memory location
     * 
     * @tparam _Tp A partially formed object type from 
     * which a pointer type is constructed
     */
    template< partially_formed _Tp >
    eop::raw_ptr<_Tp> ptr_construct(_Tp&& x)
    {
        static_assert(eop::is_partially_formed_v<_Tp>);
        return &x;
    }

    /**
     * @brief Forwarding method to construct a unique
     * pointer
     * 
     * @tparam _Tp An arbitrary type from which a unique
     * pointer is constructed
     * @tparam Args Argument types
     * @param args Arguments
     * @return std::unique_ptr<_Tp> 
     */
    template< partially_formed _Tp, partially_formed... Args >
    std::unique_ptr<_Tp> ptr_construct(Args&&... args)
    {
        static_assert(eop::is_partially_formed_v<_Tp>);
        return std::unique_ptr<_Tp>(construct(_Tp(std::forward<Args>(args)...)));
    }

    /**
     * @brief Forwarding method to construct a shared
     * pointer
     * 
     * @tparam _Tp An arbitrary type from which a shared
     * pointer is constructed
     * @tparam Args Argument types
     * @param args Arguments
     * @return std::shared_ptr<_Tp> 
     */
    template< partially_formed _Tp, partially_formed... Args >
    std::shared_ptr<_Tp> ptr_construct(Args&&... args)
    {
        static_assert(eop::is_partially_formed_v<_Tp>);
        return std::shared_ptr<_Tp>(construct(_Tp(std::forward<Args>(args)...)));
    }
} // namespace eop

#endif // !EOP_PRECOMP_H