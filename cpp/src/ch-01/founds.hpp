#ifndef EOP_CH1_FOUNDATIONS_H
#define EOP_CH1_FOUNDATIONS_H

#include "../intrinsics.hpp"
#include "../concepts.hpp"
namespace eop
{
template< CopyConstructible _Tp0, CopyConstructible _Tp1 >
struct copy_constructor
{
    void operator()(const _Tp0& x, const _Tp1& y)
    {
        new(std::addressof(x)) _Tp0(y);
    }
};

template< MoveConstructible _Tp0, MoveConstructible _Tp1 >
struct move_constructor
{
    void operator()(_Tp0&& x, _Tp1&& y)
    {
        new(std::addressof(x)) _Tp0(std::move_if_noexcept(y));
    }
};

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
        x = std::move_if_noexcept(y);
    }
};

template< Regular _Tp, Regular... Args >
struct equal
{
    bool operator()(const _Tp& x, const _Tp& y, const Args&&... args)
    {
        return (x == y) && operator()(args...);
    }
};
} // namespace eop

#endif // !EOP_CH1_FOUNDATIONS_H