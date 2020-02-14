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
    #define MoveConstructible typename
    #define CopyAssignable typename
    #define MoveAssignable typename

    /**
     * @brief A type satisfying all primitive
     * semantic requirements above
     * 
     */
    #define Semiregular typename

    /**
     * @brief A semiregular type with an equality
     * semantic
     * 
     */
    #define Regular typename

    /**
     * @brief Pointers, either
     * raw or smart
     * 
     */
    #define Pointer typename
    #define UniquePointer typename

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
     * @tparam C -- A container
     * @tparam I -- An iterator
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