################################################################################
#
#  Abstract Types/Structs
#
################################################################################

# Generic Type
mutable struct _Tp end

# Regular Type
mutable struct _Rp{_Tp} <: _Tp where _Tp end

################################################################################
#
#  Methods
#
################################################################################

@inline function pointer(_Tp) return Ptr{_Tp} end

@inline function address_of(x::_Tp)
    return repr(UInt64(pointer_from_objref(x)))
end

function construct(p::Tuple{Vararg{_Tp, N} where N})
    for v in p
        return v::_Tp()
    end
end

function construct(p::_Rp, initializer::U) where U
    return p::_Rp(initializer)
end
    

