#ifndef EOP_CH1_FOUNDATIONS_H
#define EOP_CH1_FOUNDATIONS_H

#include "../intrinsics.hpp"

namespace eop
{
/**
 * @brief Copy and move construction semantics
 * 
 * @tparam _Tp0 A copy or move constructible type
 * @tparam _Tp1 Another copy or move constructible type
 */
template< CopyConstructible _Tp0, CopyConstructible _Tp1 >
struct copy_constructor
{
    void operator()(const _Tp0& x, const _Tp1& y)
    {
        new(address_of(x)) _Tp0(y);
    }
};

template< MoveConstructible _Tp0, MoveConstructible _Tp1 >
struct move_constructor
{
    void operator()(_Tp0&& x, _Tp1&& y)
    {
        new(address_of(x)) _Tp0(std::move(y));
    }
};

/**
 * @brief Copy and move assignment semantics
 * 
 * @tparam _Tp0 A copy or move assignable type
 * @tparam _Tp1 Another copy or move assignable type
 */
template< CopyAssignable _Tp0, CopyAssignable _Tp1 >
struct copy_assignment
{
    void operator()(const _Tp0& x, const _Tp1& y)
    {
        x = y;
    }
};

template< MoveAssignable _Tp0, MoveAssignable _Tp1 >
struct move_assignment
{
    void operator()(_Tp0&& x, _Tp1&& y)
    {
        x = std::move(y);
    }
};

/**
 * @brief Variadic template for equality comparison
 * 
 * @tparam _Tp0 A regular type
 * @tparam _Tp1 Another regular type, initialized by
 * default as _Tp0
 * @tparam Args Other regular types
 */
template< Regular _Tp0, Regular _Tp1 = _Tp0, Regular... Args >
struct equal
{
    inline
    bool operator()(const _Tp0& x, const _Tp0& y, const Args&&... args) const
    {
        return (x == y) && operator()(args...);
    }
    inline
    bool operator()(const _Tp0& x, const _Tp1& y, const Args&&... args) const
    {
        return (x == y) && operator()(args...);
    }
    inline
    bool operator()(const _Tp1& x, const _Tp0& y, const Args&&... args) const
    {
        return (x == y) && operator()(args...);
    }
    inline
    bool operator()(const _Tp1& x, const _Tp1& y, const Args&&... args) const
    {
        return (x == y) && operator()(args...);
    }
};
template< Regular _Tp >
struct equal<_Tp>
{
    inline
    bool operator()(const _Tp& x, const _Tp& y) const
    {
        return x == y;
    }
};
} // namespace eop

#endif // !EOP_CH1_FOUNDATIONS_H