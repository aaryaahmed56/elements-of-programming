#ifndef EOP_CH1_FOUNDATIONS_H
#define EOP_CH1_FOUNDATIONS_H

#include "../intrinsics.hpp"
#include "../concepts.hpp"
namespace eop
{

// Variadic template struct for equality.
// Checks pair-wise.
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