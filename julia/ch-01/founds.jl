################################################################################
#
#  Abstract Types/Structs
#
################################################################################

# Generic Type
abstract type _Tp end

# Object Type
abstract type _Op <: _Tp end

# Regular Type
abstract type _Rp <: _Tp end

struct equal{_Rp}
    x::_Rp
    y::_Rp
    
    function operator(x::_Rp, y::_Rp)
        return x == y
    end
end

struct input_type{equal, Void} end
    
