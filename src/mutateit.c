#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

#ifndef CPL_DLL
#	if defined(_MSC_VER) && !defined(CPL_DISABLE_DLL)
#		define CPL_DLL     __declspec(dllexport)
#	else
#		if defined(USE_GCC_VISIBILITY_FLAG)
#			define CPL_DLL __attribute__ ((visibility("default")))
#		else
#			define CPL_DLL
#		endif
#	endif
#endif

CPL_DLL int blind_change_struct(void *ptr, void *what, char *type, size_t off) {
	/* This is a magic backdoor to change static members of C structures that had to be declared as
	   immutables types in Julia and therefore impossible to change from there.
	   *ptr  -> structure pointer whose member identified by the offset 'off' is to be changed.
	   *what -> pointer to the new value of the struct member that will be changed.
	   *type -> string with the type description, using the Julia types names. e.g. 'UInt32' or 'Float64'
	   The offset value 'off' is that obtained with the Julia's fieldoffsets() function, which is
	   equivalent to the 'offsetof()' C macro.
	*/
	if (!strcmp(type, "Int32"))
		*(int *)((char *)ptr + off) = *(int *)what;
	else if (!strcmp(type, "UInt32"))
		*(unsigned int *)((char *)ptr + off) = *(unsigned int *)what;
	else if (!strcmp(type, "Int64"))
		*(int64_t *)((char *)ptr + off) = *(int64_t *)what;
	else if (!strcmp(type, "UInt64"))
		*(uint64_t *)((char *)ptr + off) = *(uint64_t *)what;
	else if (!strcmp(type, "Float32"))
		*(float *)((char *)ptr + off) = *(float *)what;
	else if (!strcmp(type, "Float64"))
		*(double *)((char *)ptr + off) = *(double *)what;
	else if (!strcmp(type, "Int16"))
		*(signed short *)((char *)ptr + off) = *(signed short *)what;
	else if (!strcmp(type, "UInt16"))
		*(unsigned short *)((char *)ptr + off) = *(unsigned short *)what;
	else if (!strcmp(type, "UInt8"))
		*(unsigned char *)((char *)ptr + off) = *(unsigned char *)what;
	else if (!strcmp(type, "Int8"))
		*(char *)((char *)ptr + off) = *(char *)what;
	else {
		fprintf(stderr, "mutateit: Type (%s) not accepted. Possibly a pointer to something.\n", type);
		return -1;
	}
	return 0;
}
