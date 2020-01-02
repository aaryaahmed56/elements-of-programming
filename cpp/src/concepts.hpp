#ifndef EOP_CONCEPTS_HPP
#define EOP_CONCEPTS_HPP

namespace eop
{

    // This treats the requires clause as documentation only
    #define requires(...)
    
    // A type that is constructible
    #define Constructible typename
    
    // A type that is default constructible and destructible,
    // copyable, movable, and assignable
    #define Semiregular typename
    
    // A semiregular type with an equality semantic
    #define Regular typename

    // A type constructor of the kind
    // T -> (T)*
    #define Pointer typename

    // An operation with arity two,
    // i.e. T x T -> T
    #define BinaryOperation typename
    
} // namespace eop

#endif // !EOP_CONCEPTS_HPP