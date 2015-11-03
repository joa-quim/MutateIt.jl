module MutateIt

function mutateit(t_type, member::ASCIIString, val)
	# Mutate the member 'member' of an immutable type whose pointer is T_TYPE
	# VAL is the new value of the MEMBER field.
	# It's up to the user to guarantie that MEMBER and VAL have the same data type
	# T_TYPE can actually be either a variable of a certain type or a pointer to it.
	# In latter case, we fish the specific DataType from it.
	if (isa(t_type, Ptr))
		x_type = unsafe_load(t_type)
		p_type = t_type
	else
		x_type = t_type
		p_type = pointer([t_type])	# We need the pointer to type to later send to blind_change
	end
	dt  = typeof(x_type)			# Get the specific DataType. That's what we'll need for next inquires
	fo  = fieldoffsets(dt);		ft = dt.types
	ind = findfirst(fieldnames(dt), symbol(member))	# Find the index of the "is_continuous" member
	# This would work too
	# ind = ccall(:jl_field_index, Cint, (Any, Any, Cint), dt, symbol(member), 1) + 1
	p_val = pointer([val])
	blind_change_struct(p_type, p_val, @sprintf("%s",ft[ind]), fo[ind])
	typeof(p_type); 	typeof(p_val)		# Just to be sure that GC doesn't kill them before their due time
end

end # module
