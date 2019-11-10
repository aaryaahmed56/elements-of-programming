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

function euclidean_norm(x::Float64, y::Float64)
    return sqrt(x * x + y * y)
end