* The cache macros of looptools.h (Aval, Bval, ...) index memory relative to
* the address of the common block ltvars, so they only work if the program
* and the library share one copy of it. This is not a given for a shared
* library.
	program example04
	implicit none

#include "looptools.h"

	memindex b
	ComplexType direct, cached

	call ltini

	direct = B0(1000D0, 50D0, 100D0)
	b = Bget(1000D0, 50D0, 100D0)
	cached = Bval(bb0, b)
	print *, "B0(1000, 50, 100) =", direct
	print *, "Bval(bb0, Bget(1000, 50, 100)) =", cached

	call ltexi

	if( .not. abs(cached - direct) .le. 1D-12*abs(direct) ) then
	  print *, "FAILED: Bval(bb0, Bget) and B0 differ"
	  call exit(1)
	endif
	end
