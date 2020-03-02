#ifndef EOP_CONCEPTS_HPP
#define EOP_CONCEPTS_HPP

#include "precomp.hpp"

namespace eop
{
    /**
     * @brief Primitive semantic requirements for 
     * type construction, destruction, and assignment
     * 
     */
    #define constructible typename
    #define destructible typename
    #define copy_constructible typename
    #define copy_assignable typename
    #define move_constructible typename
    #define move_assignable typename

    /**
     * @brief Types for pointers, either
     * raw or smart, which are type
     * constructors
     * 
     */
    #define pointer typename
    #define unique_pointer typename

    /**
     * @brief Concept for linear/substructural types
     * 
     * linear = move_constructible + move_assignable
     * 
     * A unique pointer is "almost" a linear type in 
     * that it is move assignable but not copy assignable.
     * 
     */
    #define linear typename
    
    /**
     * @brief Naive implementation for nothrow
     * convertible type checking
     * 
     * @tparam From 
     * @tparam To 
     */
    template< class From, class To >
    struct is_nothrow_convertible : std::conjunction<std::is_void<From>, std::is_void<To>> {};
    
    /**
     * @brief Variable helper method for nothrow
     * convertibility
     * 
     * @tparam From 
     * @tparam To 
     */
    template< class From, class To >
    inline
    constexpr
    bool is_nothrow_convertible_v = is_nothrow_convertible<From, To>::value;

    /**
     * @brief 
     * 
     * @tparam T 
     * @tparam U 
     */
    template< typename T, typename U >
    inline
    constexpr
    bool linear_usable_as_v =
        std::is_nothrow_constructible_v<T, U> &&
        std::is_nothrow_assignable_v<T&, U> &&
        eop::is_nothrow_convertible_v<T, U>;

    /**
     * @brief 
     * 
     * @tparam T 
     * @tparam U 
     */
    template< typename T, typename U >
    inline
    constexpr
    bool linear_unusable_as_v =
        !(std::is_constructible_v<T, U> ||
        std::is_assignable_v<T&, U> ||
        std::is_convertible_v<T, U>);

    /**
     * @brief Wrapper object around a linear type
     * 
     * @tparam T A linear Type
     */
    template< linear T >
    class linear_wrapper
    {
    private:
        T _val;

    public:
        linear_wrapper(T&& value) : _val(std::move(value)) {}

        // Remove copy construction and assignment
        linear_wrapper(const linear_wrapper&) = delete;
        linear_wrapper &operator=(const linear_wrapper&) = delete;

        linear_wrapper(linear_wrapper&&) = default;
        linear_wrapper &operator=(linear_wrapper&&) = default;

        [[nodiscard]]
        T&& get(T&& value) && noexcept
        {
            return std::move(value);
        }

        [[nodiscard]]
        T&& operator*(T&& value) noexcept
        {
            return std::move(value);
        }
    };

    /**
     * @brief Concept for semiregular types
     * 
     * semiregular = constructible + destructible
     * + copy_constructible + copy_assignable + move_constructible
     * + move_assignable
     * 
     */
    #define semiregular typename

    /**
     * @brief Concept for types with an
     * equality semantic
     * 
     */
    #define equality typename

    /**
     * @brief Concept for regular types
     * 
     * regular = semiregular + equality
     * 
     */
    #define regular typename



    /**
     * @brief Operations of specified
     * or general arity
     * 
     */
    #define NullaryOperation typename
    #define UnaryOperation typename
    #define BinaryOperation typename
    #define NaryOperation typename

    /**
     * @brief Models for data structures,
     * iterators, and containers
     *
     */
    #define container typename
    #define linear_structure typename
    #define coordinate_structure typename
    #define iterator typename
    #define forward_iterator typename
    #define reverse_iterator typename
    #define bidirectional_iterator typename
    #define random_access_iterator typename

    /**
     * @brief Aliases for types
     * 
     * @tparam C A container
     * @tparam I An iterator
     */
    template< container C >
    using size_type = typename C::size_type;

    template< container C >
    using value_type = typename C::value_type;
    
    template< iterator I >
    using iterator_value_type = typename std::iterator_traits<I>::value_type;

    template< iterator I >
    using iterator_difference_type = typename std::iterator_traits<I>::difference_type;
} // namespace eop

#endif // !EOP_CONCEPTS_HPP