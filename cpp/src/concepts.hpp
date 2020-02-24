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
    #define Constructible typename
    #define Destructible typename
    #define CopyConstructible typename
    #define CopyAssignable typename
    #define MoveConstructible typename
    #define MoveAssignable typename

    /**
     * @brief Types for pointers, either
     * raw or smart, which are type
     * constructors
     * 
     */
    #define Pointer typename
    #define UniquePointer typename

    /**
     * @brief Concept for linear/substructural types
     * 
     * Linear = MoveConstructible + MoveAssignable
     * 
     * A unique pointer is "almost" a linear type in 
     * that it is move assignable but not copy assignable.
     * 
     */
    #define Linear typename
    
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
        std::is_nothrow_constructible_v<T, U> and
        std::is_nothrow_assignable_v<T&, U> and
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
        not std::is_constructible_v<T, U> and
        not std::is_assignable_v<T&, U> and
        not std::is_convertible_v<T, U>;

    /**
     * @brief Wrapper object around a linear type
     * 
     * @tparam T A Linear Type
     */
    template< Linear T >
    class linear
    {
    private:
        T _val;

    public:
        linear(T&& value) : _val(std::move(value)) {}

        // Remove copy construction and assignment
        linear(const linear&) = delete;
        linear &operator=(const linear&) = delete;

        linear(linear&&) = default;
        linear &operator=(linear&&) = default;

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
     * Semiregular = Constructible + Destructible
     * + CopyConstructible + CopyAssignable + MoveConstructible
     * + MoveAssignable
     * 
     */
    #define Semiregular typename

    /**
     * @brief Concept for types with an
     * Equality semantic
     * 
     */
    #define Equality typename

    /**
     * @brief Concept for regular types
     * 
     * Regular = Semiregular + Equality
     * 
     */
    #define Regular typename



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
    #define Container typename
    #define LinearStructure typename
    #define CoordinateStructure typename
    #define Iterator typename
    #define ForwardIterator typename
    #define ReverseIterator typename
    #define BidirectionalIterator typename
    #define RandomAccessIterator typename

    /**
     * @brief Aliases for types
     * 
     * @tparam C A container
     * @tparam I An iterator
     */
    template< Container C >
    using SizeType = typename C::size_type;

    template< Container C >
    using ValueType = typename C::value_type;
    
    template< Iterator I >
    using IteratorValueType = typename std::iterator_traits<I>::value_type;

    template< Iterator I >
    using IteratorDifferenceType = typename std::iterator_traits<I>::difference_type;
} // namespace eop

#endif // !EOP_CONCEPTS_HPP