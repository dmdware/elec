/* mpq_set_den(dest,den) -- Set the denominator of DEST from DEN.

Copyright 1991, 1994-1996, 2000, 2001, 2012 Free Software Foundation, Inc.

This file is part of the GNU MP Library.

The GNU MP Library is free software; you can redistribute it and/or modify
it under the terms of either:

  * the GNU Lesser General Public License as published by the Free
    Software Foundation; either version 3 of the License, or (at your
    option) any later version.

or

  * the GNU General Public License as published by the Free Software
    Foundation; either version 2 of the License, or (at your option) any
    later version.

or both in parallel, as here.

The GNU MP Library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received copies of the GNU General Public License and the
GNU Lesser General Public License along with the GNU MP Library.  If not,
see https://www.gnu.org/licenses/.  */

#include "../gmp_gmp.h"
#include "../gmp_gmp-impl.h"

void
mpq_set_den (mpq_ptr dest, mpz_srcptr den)
{
  mp_size_t size = SIZ (den);
  mp_size_t abs_size = ABS (size);
  mp_ptr dp;

  dp = MPZ_NEWALLOC (DEN(dest), abs_size);

  SIZ(DEN(dest)) = size;
  MPN_COPY (dp, PTR(den), abs_size);
}
