#ifndef EOP_CH1_FOUNDATIONS
#define EOP_CH1_FOUNDATIONS

#include "../intrinsics.h"

namespace eop
{

// Variadic template struct for equality.
// Checks pair-wise.
template< typename _Tp, typename... Args >
    requires(Regular(_Tp))
struct equal
{
    bool operator()(const _Tp& x, const _Tp& y, const Args&&... args)
    {
        return (x == y) && operator()(args...);
    }
};

} // namespace eop

#endif