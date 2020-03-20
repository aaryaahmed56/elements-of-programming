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
     * @brief Concept for an object type of
     * a partially-formed object
     * 
     * partially_formed = move_assignable + destructible
     * 
     */
    #define partially_formed typename
    
    /**
     * @brief Concept for an object type of
     * a well-formed object
     * 
     * well_formed = partially_formed + ...
     * 
     */
    #define well_formed typename

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

    template< class _Tp, class U >
    inline
    constexpr
    bool linear_usable_as_v =
        std::is_nothrow_constructible_v<_Tp, U> &&
        std::is_nothrow_assignable_v<_Tp&, U> &&
        eop::is_nothrow_convertible_v<_Tp, U>;

    template< class _Tp, class U >
    inline
    constexpr
    bool linear_unusable_as_v =
        !(std::is_constructible_v<_Tp, U> ||
        std::is_assignable_v<_Tp&, U> ||
        std::is_convertible_v<_Tp, U>);

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
     * semiregular = default constructible && destructible
     * && copy_constructible && copy_assignable &&
     * move_constructible && move_assignable
     * 
     */
    #define semiregular typename
    template< class _Tp >
    inline
    constexpr
    bool is_semiregular_v =
        std::is_default_constructible_v<_Tp>
        && std::is_destructible_v<_Tp>
        && std::is_copy_constructible_v<_Tp>
        && std::is_copy_assignable_v<_Tp>
        && std::is_move_constructible_v<_Tp>
        && std::is_move_assignable_v<_Tp>
        && std::is_swappable_v<_Tp>;

    /**
     * @brief Concept for types with an
     * equality comparability semantic
     * 
     */
    #define equality_comparable typename
    template< class _Tp, class=void >
    struct is_equality_comparable : std::false_type{};
    template< class _Tp>
    struct is_equality_comparable<_Tp,
        typename std::enable_if<
            true,
            decltype(std::declval<_Tp&>() == std::declval<_Tp&>(),
                (void)0)>::type
            > : std::true_type {};
    
    template< class _Tp >
    inline
    constexpr
    bool is_equality_comparable_v =
        eop::is_equality_comparable<_Tp>::value;

    /**
     * @brief Concept for regular types
     * 
     * regular = semiregular && equality
     * 
     */
    #define regular typename
    template< class _Tp >
    inline
    constexpr
    bool is_regular_v =
        eop::is_semiregular_v<_Tp>
        && eop::is_equality_comparable_v<_Tp>;

    /**
     * @brief Concepts for functional procedures and 
     * their input and output objects
     * 
     */
    #define functional_procedure typename
    template< functional_procedure F, const unsigned I >
    struct input {};

    template< functional_procedure F >
    struct output {};
    
    /**
     * @brief Concepts for operations and
     * (homogeneous) predicates of specified
     * or general arity
     * 
     * n_ary_predicate = functional_procedure
     * && codomain(functional_procedure) = bool
     * 
     * n_ary_operation = functional_procedure
     * && codomain(functional_procedure) =
     * 
     */
    #define nullary_operation typename
    #define nullary_predicate typename
    #define unary_operation typename
    #define unary_predicate typename
    #define binary_operation typename
    #define binary_predicate typename
    #define n_ary_operation typename
    #define n_ary_predicate typename

    /**
     * @brief Concept for transformations
     * 
     * transformation = n_ary_operation
     * || n_ary_predicate
     * 
     */
    #define transformation typename
    template< transformation F >
    struct distance {};
    template<>
    struct distance<int>
    {
        using type = unsigned int;
    };
    template<>
    struct distance<long long>
    {
        using type = unsigned long long;
    };

    /**
     * @brief Concept for types on which
     * arithmetic can be performed
     * 
     */
    #define arithmetic typename

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
     * @tparam F A functional procedure
     * @tparam I An iterator
     */
    template< container C >
    using size_type = typename C::size_type;

    template< container C >
    using value_type = typename C::value_type;
    
    template< functional_procedure F, const unsigned I >
    using input_type = typename input<F, I>::type;
    
    template< functional_procedure F >
    using domain = input_type<F, 0>;

    template< functional_procedure F >
    using codomain = typename output<F>::type;

    template< transformation F >
    using distance_type = typename distance<F>::type;

    template< iterator I >
    using iterator_value_type = typename std::iterator_traits<I>::value_type;

    template< iterator I >
    using iterator_difference_type = typename std::iterator_traits<I>::difference_type;
} // namespace eop

#endif // !EOP_CONCEPTS_HPP