/* Interface to replace gmp-impl.h

Copyright 2004-2016 Free Software Foundation, Inc.
Contributed by the AriC and Caramba projects, INRIA.

This file is part of the GNU MPFR Library.

The GNU MPFR Library is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 3 of the License, or (at your
option) any later version.

The GNU MPFR Library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
License for more details.

You should have received a copy of the GNU Lesser General Public License
along with the GNU MPFR Library; see the file COPYING.LESSER.  If not, see
http://www.gnu.org/licenses/ or write to the Free Software Foundation, Inc.,
51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA. */

#ifndef __GMPFR_GMP_H__
#define __GMPFR_GMP_H__

//ed
//#include "../gmp/gmp_gmp.h"

#ifndef __MPFR_IMPL_H__
# error  "mpfr-impl.h not included"
#endif

#include <limits.h> /* For INT_MAX, ... */
#include <string.h> /* For memcpy, memset and memmove */

#ifdef _MSC_VER
#define GMP_INLINE	__inline	//ed
#else
#define GMP_INLINE	inline	//ed
#endif

//ed
//gmp-impl.h
#if ! defined (__GMP_WITHIN_CONFIGURE)
//#include "../gmp/gmp_config.h"
//#include "../gmp/mpn/generic/mpn_gmp-mparam.h"
//#include "../gmp/gmp_fib_table.h"
//#include "../gmp/gmp_fac_table.h"
//#include "../gmp/gmp_mp_bases.h"
#if WANT_FAT_BINARY
//#include "../gmp/fat.h"
#endif
#endif

/* The following tries to get a good version of alloca.
   See gmp-impl.h for implementation details and original version */
/* FIXME: the autoconf manual gives a different piece of code under the
   documentation of the AC_FUNC_ALLOCA macro. Should we switch to it? */
#ifndef alloca
# if defined ( __GNUC__ )
#  define alloca __builtin_alloca
# elif defined (__DECC)
#  define alloca(x) __ALLOCA(x)
# elif defined (_MSC_VER)
#  include <malloc.h>
#  define alloca _alloca
# elif defined (HAVE_ALLOCA_H)
#  include <alloca.h>
# elif defined (_AIX) || defined (_IBMR2)
#  pragma alloca
# else
void *alloca (size_t);
# endif
#endif

#if defined (__cplusplus)
extern "C" {
#endif

//ed
//gmp-impl.h
/* Usage: TMP_DECL;
	  TMP_MARK;
	  ptr = TMP_ALLOC (bytes);
	  TMP_FREE;

   Small allocations should use TMP_SALLOC, big allocations should use
   TMP_BALLOC.  Allocations that might be small or big should use TMP_ALLOC.

   Functions that use just TMP_SALLOC should use TMP_SDECL, TMP_SMARK, and
   TMP_SFREE.

   TMP_DECL just declares a variable, but might be empty and so must be last
   in a list of variables.  TMP_MARK must be done before any TMP_ALLOC.
   TMP_ALLOC(0) is not allowed.  TMP_FREE doesn't need to be done if a
   TMP_MARK was made, but then no TMP_ALLOCs.  */

/* The alignment in bytes, used for TMP_ALLOCed blocks, when alloca or
   __gmp_allocate_func doesn't already determine it.  Currently TMP_ALLOC
   isn't used for "double"s, so that's not in the union.  */
union tmp_align_t {
  mp_limb_t  l;
  char       *p;
};
#define __TMP_ALIGN  sizeof (union tmp_align_t)
/* Return "a" rounded upwards to a multiple of "m", if it isn't already.
   "a" must be an unsigned type.
   This is designed for use with a compile-time constant "m".
   The POW2 case is expected to be usual, and gcc 3.0 and up recognises
   "(-(8*n))%8" or the like is always zero, which means the rounding up in
   the WANT_TMP_NOTREENTRANT version of TMP_ALLOC below will be a noop.  */
#define ROUND_UP_MULTIPLE(a,m)          \
  (POW2_P(m) ? (a) + (-(a))%(m)         \
   : (a)+(m)-1 - (((a)+(m)-1) % (m)))
#if defined (WANT_TMP_ALLOCA) || defined (WANT_TMP_REENTRANT)
struct tmp_reentrant_t {
  struct tmp_reentrant_t  *next;
  size_t		  size;	  /* bytes, including header */
};
__GMP_DECLSPEC void *__gmp_tmp_reentrant_alloc (struct tmp_reentrant_t **, size_t) ATTRIBUTE_MALLOC;
__GMP_DECLSPEC void  __gmp_tmp_reentrant_free (struct tmp_reentrant_t *);
#endif
#if WANT_TMP_ALLOCA
#define TMP_SDECL
#define TMP_DECL		struct tmp_reentrant_t *__tmp_marker
#define TMP_SMARK
#define TMP_MARK		__tmp_marker = 0
#define TMP_SALLOC(n)		alloca(n)
#define TMP_BALLOC(n)		__gmp_tmp_reentrant_alloc (&__tmp_marker, n)
/* The peculiar stack allocation limit here is chosen for efficient asm.  */
#define TMP_ALLOC(n)							\
  (LIKELY ((n) <= 0x7f00) ? TMP_SALLOC(n) : TMP_BALLOC(n))
#define TMP_SFREE
#define TMP_FREE							\
  do {									\
    if (UNLIKELY (__tmp_marker != 0))					\
      __gmp_tmp_reentrant_free (__tmp_marker);				\
  } while (0)
#endif
#if WANT_TMP_REENTRANT
#define TMP_SDECL		TMP_DECL
#define TMP_DECL		struct tmp_reentrant_t *__tmp_marker
#define TMP_SMARK		TMP_MARK
#define TMP_MARK		__tmp_marker = 0
#define TMP_SALLOC(n)		TMP_ALLOC(n)
#define TMP_BALLOC(n)		TMP_ALLOC(n)
#define TMP_ALLOC(n)		__gmp_tmp_reentrant_alloc (&__tmp_marker, n)
#define TMP_SFREE		TMP_FREE
#define TMP_FREE		__gmp_tmp_reentrant_free (__tmp_marker)
#endif
#if WANT_TMP_NOTREENTRANT
struct tmp_marker
{
  struct tmp_stack *which_chunk;
  void *alloc_point;
};
__GMP_DECLSPEC void *__gmp_tmp_alloc (unsigned long) ATTRIBUTE_MALLOC;
__GMP_DECLSPEC void __gmp_tmp_mark (struct tmp_marker *);
__GMP_DECLSPEC void __gmp_tmp_free (struct tmp_marker *);
#define TMP_SDECL		TMP_DECL
#define TMP_DECL		struct tmp_marker __tmp_marker
#define TMP_SMARK		TMP_MARK
#define TMP_MARK		__gmp_tmp_mark (&__tmp_marker)
#define TMP_SALLOC(n)		TMP_ALLOC(n)
#define TMP_BALLOC(n)		TMP_ALLOC(n)
#define TMP_ALLOC(n)							\
  __gmp_tmp_alloc (ROUND_UP_MULTIPLE ((unsigned long) (n), __TMP_ALIGN))
#define TMP_SFREE		TMP_FREE
#define TMP_FREE		__gmp_tmp_free (&__tmp_marker)
#endif
#if WANT_TMP_DEBUG
/* See tal-debug.c for some comments. */
struct tmp_debug_t {
  struct tmp_debug_entry_t  *list;
  const char                *file;
  int                       line;
};
struct tmp_debug_entry_t {
  struct tmp_debug_entry_t  *next;
  void                      *block;
  size_t                    size;
};
__GMP_DECLSPEC void  __gmp_tmp_debug_mark (const char *, int, struct tmp_debug_t **,
					   struct tmp_debug_t *,
					   const char *, const char *);
__GMP_DECLSPEC void *__gmp_tmp_debug_alloc (const char *, int, int,
					    struct tmp_debug_t **, const char *,
					    size_t) ATTRIBUTE_MALLOC;
__GMP_DECLSPEC void  __gmp_tmp_debug_free (const char *, int, int,
					   struct tmp_debug_t **,
					   const char *, const char *);
#define TMP_SDECL TMP_DECL_NAME(__tmp_xmarker, "__tmp_marker")
#define TMP_DECL TMP_DECL_NAME(__tmp_xmarker, "__tmp_marker")
#define TMP_SMARK TMP_MARK_NAME(__tmp_xmarker, "__tmp_marker")
#define TMP_MARK TMP_MARK_NAME(__tmp_xmarker, "__tmp_marker")
#define TMP_SFREE TMP_FREE_NAME(__tmp_xmarker, "__tmp_marker")
#define TMP_FREE TMP_FREE_NAME(__tmp_xmarker, "__tmp_marker")
/* The marker variable is designed to provoke an uninitialized variable
   warning from the compiler if TMP_FREE is used without a TMP_MARK.
   __tmp_marker_inscope does the same for TMP_ALLOC.  Runtime tests pick
   these things up too.  */
#define TMP_DECL_NAME(marker, marker_name)				\
  int marker;								\
  int __tmp_marker_inscope;						\
  const char *__tmp_marker_name = marker_name;				\
  struct tmp_debug_t  __tmp_marker_struct;				\
  /* don't demand NULL, just cast a zero */				\
  struct tmp_debug_t  *__tmp_marker = (struct tmp_debug_t *) 0
#define TMP_MARK_NAME(marker, marker_name)				\
  do {									\
    marker = 1;								\
    __tmp_marker_inscope = 1;						\
    __gmp_tmp_debug_mark  (ASSERT_FILE, ASSERT_LINE,			\
			   &__tmp_marker, &__tmp_marker_struct,		\
			   __tmp_marker_name, marker_name);		\
  } while (0)
#define TMP_SALLOC(n)		TMP_ALLOC(n)
#define TMP_BALLOC(n)		TMP_ALLOC(n)
#define TMP_ALLOC(size)							\
  __gmp_tmp_debug_alloc (ASSERT_FILE, ASSERT_LINE,			\
			 __tmp_marker_inscope,				\
			 &__tmp_marker, __tmp_marker_name, size)
#define TMP_FREE_NAME(marker, marker_name)				\
  do {									\
    __gmp_tmp_debug_free  (ASSERT_FILE, ASSERT_LINE,			\
			   marker, &__tmp_marker,			\
			   __tmp_marker_name, marker_name);		\
  } while (0)
#endif /* WANT_TMP_DEBUG */
/* Allocating various types. */
#define TMP_ALLOC_TYPE(n,type)  ((type *) TMP_ALLOC ((n) * sizeof (type)))
#define TMP_SALLOC_TYPE(n,type) ((type *) TMP_SALLOC ((n) * sizeof (type)))
#define TMP_BALLOC_TYPE(n,type) ((type *) TMP_BALLOC ((n) * sizeof (type)))
#define TMP_ALLOC_LIMBS(n)      TMP_ALLOC_TYPE(n,mp_limb_t)
#define TMP_SALLOC_LIMBS(n)     TMP_SALLOC_TYPE(n,mp_limb_t)
#define TMP_BALLOC_LIMBS(n)     TMP_BALLOC_TYPE(n,mp_limb_t)
#define TMP_ALLOC_MP_PTRS(n)    TMP_ALLOC_TYPE(n,mp_ptr)
#define TMP_SALLOC_MP_PTRS(n)   TMP_SALLOC_TYPE(n,mp_ptr)
#define TMP_BALLOC_MP_PTRS(n)   TMP_BALLOC_TYPE(n,mp_ptr)
/* It's more efficient to allocate one block than many.  This is certainly
   true of the malloc methods, but it can even be true of alloca if that
   involves copying a chunk of stack (various RISCs), or a call to a stack
   bounds check (mingw).  In any case, when debugging keep separate blocks
   so a redzoning malloc debugger can protect each individually.  */
#define TMP_ALLOC_LIMBS_2(xp,xsize, yp,ysize)				\
  do {									\
    if (WANT_TMP_DEBUG)							\
      {									\
	(xp) = TMP_ALLOC_LIMBS (xsize);					\
	(yp) = TMP_ALLOC_LIMBS (ysize);					\
      }									\
    else								\
      {									\
	(xp) = TMP_ALLOC_LIMBS ((xsize) + (ysize));			\
	(yp) = (xp) + (xsize);						\
      }									\
  } while (0)
#define TMP_ALLOC_LIMBS_3(xp,xsize, yp,ysize, zp,zsize)			\
  do {									\
    if (WANT_TMP_DEBUG)							\
      {									\
	(xp) = TMP_ALLOC_LIMBS (xsize);					\
	(yp) = TMP_ALLOC_LIMBS (ysize);					\
	(zp) = TMP_ALLOC_LIMBS (zsize);					\
      }									\
    else								\
      {									\
	(xp) = TMP_ALLOC_LIMBS ((xsize) + (ysize) + (zsize));		\
	(yp) = (xp) + (xsize);						\
	(zp) = (yp) + (ysize);						\
      }									\
  } while (0)
//ed

/* Define GMP_NUMB_BITS
   Can't use sizeof(mp_limb_t) since it should be a preprocessor constant */
#if defined(GMP_NUMB_BITS) /* GMP 4.1.2 or above */
#ifndef GMP_NUMB_BITS
# define GMP_NUMB_BITS  (GMP_NUMB_BITS+GMP_NAIL_BITS)
#endif
#elif defined (__GMP_GMP_NUMB_BITS) /* Older versions 4.x.x */
# define GMP_NUMB_BITS  __GMP_GMP_NUMB_BITS
# define GMP_NUMB_BITS GMP_NUMB_BITS
# ifndef GMP_NAIL_BITS
#  define GMP_NAIL_BITS 0
# endif
#else
# error "Could not detect GMP_NUMB_BITS. Try with gmp internal files."
#endif

//ed
//gmp-impl.h
/* if not provided by gmp-mparam.h */
#ifndef GMP_LIMB_BYTES
#define GMP_LIMB_BYTES  SIZEOF_MP_LIMB_T
#endif
#ifndef GMP_LIMB_BITS
#define GMP_LIMB_BITS  (8 * SIZEOF_MP_LIMB_T)
#endif
//#define BITS_PER_ULONG  (8 * SIZEOF_UNSIGNED_LONG)
#define BITS_PER_ULONG  (8 * BUILD_SIZEOF_UL)
/* gmp_uint_least32_t is an unsigned integer type with at least 32 bits. */
#if HAVE_UINT_LEAST32_T
typedef uint_least32_t      gmp_uint_least32_t;
#else
#if SIZEOF_UNSIGNED_SHORT >= 4
typedef unsigned short      gmp_uint_least32_t;
#else
#if SIZEOF_UNSIGNED >= 4
typedef unsigned            gmp_uint_least32_t;
#else
typedef unsigned long       gmp_uint_least32_t;
#endif
#endif
#endif
//ed

//
//gmp-impl.h
/* pre-inverse types for truncating division and modulo */
typedef struct {mp_limb_t inv32;} gmp_pi1_t;
typedef struct {mp_limb_t inv21, inv32, inv53;} gmp_pi2_t;

//ed
//gmp-impl.h
#if HAVE_ATTRIBUTE_NORETURN
#define ATTRIBUTE_NORETURN  __attribute__ ((noreturn))
#else
#define ATTRIBUTE_NORETURN
#endif
/* "malloc" means a function behaves like malloc in that the pointer it
   returns doesn't alias anything.  */
#if HAVE_ATTRIBUTE_MALLOC
#define ATTRIBUTE_MALLOC  __attribute__ ((malloc))
#else
#define ATTRIBUTE_MALLOC
#endif

//ed
//gmp-impl.h
#define GMP_NUMB_HIGHBIT  (CNST_LIMB(1) << (GMP_NUMB_BITS-1))

/* Define some macros */

#define MP_LIMB_T_MAX (~(mp_limb_t)0)

#define ULONG_HIGHBIT (ULONG_MAX ^ ((unsigned long) ULONG_MAX >> 1))
#define UINT_HIGHBIT  (UINT_MAX ^ ((unsigned) UINT_MAX >> 1))
#define USHRT_HIGHBIT ((unsigned short) (USHRT_MAX ^ ((unsigned short) USHRT_MAX >> 1)))

#define GMP_LIMB_HIGHBIT (MP_LIMB_T_MAX ^ (MP_LIMB_T_MAX >> 1))


#if __GMP_MP_SIZE_T_INT
#define MP_SIZE_T_MAX      INT_MAX
#define MP_SIZE_T_MIN      INT_MIN
#else
#define MP_SIZE_T_MAX      LONG_MAX
#define MP_SIZE_T_MIN      LONG_MIN
#endif

#define LONG_HIGHBIT       LONG_MIN
#define INT_HIGHBIT        INT_MIN
#define SHRT_HIGHBIT       SHRT_MIN

/* MP_LIMB macros */
#define MPN_ZERO(dst, n) memset((dst), 0, (n)*MPFR_BYTES_PER_MP_LIMB)
#define MPN_COPY_DECR(dst,src,n) memmove((dst),(src),(n)*MPFR_BYTES_PER_MP_LIMB)
#define MPN_COPY_INCR(dst,src,n) memmove((dst),(src),(n)*MPFR_BYTES_PER_MP_LIMB)
#define MPN_COPY(dst,src,n) \
  do                                                                  \
    {                                                                 \
      if ((dst) != (src))                                             \
        {                                                             \
          MPFR_ASSERTD ((char *) (dst) >= (char *) (src) +            \
                                     (n) * MPFR_BYTES_PER_MP_LIMB ||  \
                        (char *) (src) >= (char *) (dst) +            \
                                     (n) * MPFR_BYTES_PER_MP_LIMB);   \
          memcpy ((dst), (src), (n) * MPFR_BYTES_PER_MP_LIMB);        \
        }                                                             \
    }                                                                 \
  while (0)

/* MPN macros taken from gmp-impl.h */
#define MPN_NORMALIZE(DST, NLIMBS) \
  do {                                        \
    while (NLIMBS > 0)                        \
      {                                       \
        if ((DST)[(NLIMBS) - 1] != 0)         \
          break;                              \
        NLIMBS--;                             \
      }                                       \
  } while (0)
#define MPN_NORMALIZE_NOT_ZERO(DST, NLIMBS)     \
  do {                                          \
    MPFR_ASSERTD ((NLIMBS) >= 1);               \
    while (1)                                   \
      {                                         \
        if ((DST)[(NLIMBS) - 1] != 0)           \
          break;                                \
        NLIMBS--;                               \
      }                                         \
  } while (0)
#define MPN_OVERLAP_P(xp, xsize, yp, ysize) \
  ((xp) + (xsize) > (yp) && (yp) + (ysize) > (xp))
#define MPN_SAME_OR_INCR2_P(dst, dsize, src, ssize)             \
  ((dst) <= (src) || ! MPN_OVERLAP_P (dst, dsize, src, ssize))
#define MPN_SAME_OR_INCR_P(dst, src, size)      \
  MPN_SAME_OR_INCR2_P(dst, size, src, size)
#define MPN_SAME_OR_DECR2_P(dst, dsize, src, ssize)             \
  ((dst) >= (src) || ! MPN_OVERLAP_P (dst, dsize, src, ssize))
#define MPN_SAME_OR_DECR_P(dst, src, size)      \
  MPN_SAME_OR_DECR2_P(dst, size, src, size)

/* If mul_basecase or mpn_sqr_basecase are not exported, used mpn_mul instead */
//ed
//gmp.h
/*
#ifndef mpn_mul_basecase
# define mpn_mul_basecase(dst,s1,n1,s2,n2) mpn_mul((dst),(s1),(n1),(s2),(n2))
#endif
#ifndef mpn_sqr_basecase
# define mpn_sqr_basecase(dst,src,n) mpn_mul((dst),(src),(n),(src),(n))
#endif
*/


//ed
//gmp-impl.h
#ifndef MUL_TOOM22_THRESHOLD
#define MUL_TOOM22_THRESHOLD             30
#endif
#ifndef MUL_TOOM33_THRESHOLD
#define MUL_TOOM33_THRESHOLD            100
#endif
#ifndef MUL_TOOM44_THRESHOLD
#define MUL_TOOM44_THRESHOLD            300
#endif
#ifndef MUL_TOOM6H_THRESHOLD
#define MUL_TOOM6H_THRESHOLD            350
#endif
#ifndef SQR_TOOM6_THRESHOLD
#define SQR_TOOM6_THRESHOLD MUL_TOOM6H_THRESHOLD
#endif
#ifndef MUL_TOOM8H_THRESHOLD
#define MUL_TOOM8H_THRESHOLD            450
#endif
#ifndef SQR_TOOM8_THRESHOLD
#define SQR_TOOM8_THRESHOLD MUL_TOOM8H_THRESHOLD
#endif
#ifndef MUL_TOOM32_TO_TOOM43_THRESHOLD
#define MUL_TOOM32_TO_TOOM43_THRESHOLD  100
#endif
#ifndef MUL_TOOM32_TO_TOOM53_THRESHOLD
#define MUL_TOOM32_TO_TOOM53_THRESHOLD  110
#endif
#ifndef MUL_TOOM42_TO_TOOM53_THRESHOLD
#define MUL_TOOM42_TO_TOOM53_THRESHOLD  100
#endif
#ifndef MUL_TOOM42_TO_TOOM63_THRESHOLD
#define MUL_TOOM42_TO_TOOM63_THRESHOLD  110
#endif
#ifndef MUL_TOOM43_TO_TOOM54_THRESHOLD
#define MUL_TOOM43_TO_TOOM54_THRESHOLD  150
#endif
/* MUL_TOOM22_THRESHOLD_LIMIT is the maximum for MUL_TOOM22_THRESHOLD.  In a
   normal build MUL_TOOM22_THRESHOLD is a constant and we use that.  In a fat
   binary or tune program build MUL_TOOM22_THRESHOLD is a variable and a
   separate hard limit will have been defined.  Similarly for TOOM3.  */
#ifndef MUL_TOOM22_THRESHOLD_LIMIT
#define MUL_TOOM22_THRESHOLD_LIMIT  MUL_TOOM22_THRESHOLD
#endif
#ifndef MUL_TOOM33_THRESHOLD_LIMIT
#define MUL_TOOM33_THRESHOLD_LIMIT  MUL_TOOM33_THRESHOLD
#endif
#ifndef MULLO_BASECASE_THRESHOLD_LIMIT
#define MULLO_BASECASE_THRESHOLD_LIMIT  MULLO_BASECASE_THRESHOLD
#endif
#ifndef SQRLO_BASECASE_THRESHOLD_LIMIT
#define SQRLO_BASECASE_THRESHOLD_LIMIT  SQRLO_BASECASE_THRESHOLD
#endif
#ifndef SQRLO_DC_THRESHOLD_LIMIT
#define SQRLO_DC_THRESHOLD_LIMIT  SQRLO_DC_THRESHOLD
#endif
/* SQR_BASECASE_THRESHOLD is where mpn_sqr_basecase should take over from
   mpn_mul_basecase.  Default is to use mpn_sqr_basecase from 0.  (Note that we
   certainly always want it if there's a native assembler mpn_sqr_basecase.)

   If it turns out that mpn_toom2_sqr becomes faster than mpn_mul_basecase
   before mpn_sqr_basecase does, then SQR_BASECASE_THRESHOLD is the toom2
   threshold and SQR_TOOM2_THRESHOLD is 0.  This oddity arises more or less
   because SQR_TOOM2_THRESHOLD represents the size up to which mpn_sqr_basecase
   should be used, and that may be never.  */
#ifndef SQR_BASECASE_THRESHOLD
#define SQR_BASECASE_THRESHOLD            0  /* never use mpn_mul_basecase */
#endif
#ifndef SQR_TOOM2_THRESHOLD
#define SQR_TOOM2_THRESHOLD              50
#endif
#ifndef SQR_TOOM3_THRESHOLD
#define SQR_TOOM3_THRESHOLD             120
#endif
#ifndef SQR_TOOM4_THRESHOLD
#define SQR_TOOM4_THRESHOLD             400
#endif
/* See comments above about MUL_TOOM33_THRESHOLD_LIMIT.  */
#ifndef SQR_TOOM3_THRESHOLD_LIMIT
#define SQR_TOOM3_THRESHOLD_LIMIT  SQR_TOOM3_THRESHOLD
#endif
#ifndef MULMID_TOOM42_THRESHOLD
#define MULMID_TOOM42_THRESHOLD     MUL_TOOM22_THRESHOLD
#endif
#ifndef MULLO_BASECASE_THRESHOLD
#define MULLO_BASECASE_THRESHOLD          0  /* never use mpn_mul_basecase */
#endif
#ifndef MULLO_DC_THRESHOLD
#define MULLO_DC_THRESHOLD         (2*MUL_TOOM22_THRESHOLD)
#endif
#ifndef MULLO_MUL_N_THRESHOLD
#define MULLO_MUL_N_THRESHOLD      (2*MUL_FFT_THRESHOLD)
#endif
#ifndef SQRLO_BASECASE_THRESHOLD
#define SQRLO_BASECASE_THRESHOLD          0  /* never use mpn_sqr_basecase */
#endif
#ifndef SQRLO_DC_THRESHOLD
#define SQRLO_DC_THRESHOLD         (MULLO_DC_THRESHOLD)
#endif
#ifndef SQRLO_SQR_THRESHOLD
#define SQRLO_SQR_THRESHOLD        (MULLO_MUL_N_THRESHOLD)
#endif
#ifndef DC_DIV_QR_THRESHOLD
#define DC_DIV_QR_THRESHOLD        (2*MUL_TOOM22_THRESHOLD)
#endif
#ifndef DC_DIVAPPR_Q_THRESHOLD
#define DC_DIVAPPR_Q_THRESHOLD          200
#endif
#ifndef DC_BDIV_QR_THRESHOLD
#define DC_BDIV_QR_THRESHOLD       (2*MUL_TOOM22_THRESHOLD)
#endif
#ifndef DC_BDIV_Q_THRESHOLD
#define DC_BDIV_Q_THRESHOLD             180
#endif
#ifndef DIVEXACT_JEB_THRESHOLD
#define DIVEXACT_JEB_THRESHOLD           25
#endif
#ifndef INV_MULMOD_BNM1_THRESHOLD
#define INV_MULMOD_BNM1_THRESHOLD  (4*MULMOD_BNM1_THRESHOLD)
#endif
#ifndef INV_APPR_THRESHOLD
#define INV_APPR_THRESHOLD         INV_NEWTON_THRESHOLD
#endif
#ifndef INV_NEWTON_THRESHOLD
#define INV_NEWTON_THRESHOLD            200
#endif
#ifndef BINV_NEWTON_THRESHOLD
#define BINV_NEWTON_THRESHOLD           300
#endif
#ifndef MU_DIVAPPR_Q_THRESHOLD
#define MU_DIVAPPR_Q_THRESHOLD         2000
#endif
#ifndef MU_DIV_QR_THRESHOLD
#define MU_DIV_QR_THRESHOLD            2000
#endif
#ifndef MUPI_DIV_QR_THRESHOLD
#define MUPI_DIV_QR_THRESHOLD           200
#endif
#ifndef MU_BDIV_Q_THRESHOLD
#define MU_BDIV_Q_THRESHOLD            2000
#endif
#ifndef MU_BDIV_QR_THRESHOLD
#define MU_BDIV_QR_THRESHOLD           2000
#endif
#ifndef MULMOD_BNM1_THRESHOLD
#define MULMOD_BNM1_THRESHOLD            16
#endif
#ifndef SQRMOD_BNM1_THRESHOLD
#define SQRMOD_BNM1_THRESHOLD            16
#endif
#ifndef MUL_TO_MULMOD_BNM1_FOR_2NXN_THRESHOLD
#define MUL_TO_MULMOD_BNM1_FOR_2NXN_THRESHOLD  (INV_MULMOD_BNM1_THRESHOLD/2)
#endif
#if HAVE_NATIVE_mpn_addmul_2 || HAVE_NATIVE_mpn_redc_2
#ifndef REDC_1_TO_REDC_2_THRESHOLD
#define REDC_1_TO_REDC_2_THRESHOLD       15
#endif
#ifndef REDC_2_TO_REDC_N_THRESHOLD
#define REDC_2_TO_REDC_N_THRESHOLD      100
#endif
#else
#ifndef REDC_1_TO_REDC_N_THRESHOLD
#define REDC_1_TO_REDC_N_THRESHOLD      100
#endif
#endif /* HAVE_NATIVE_mpn_addmul_2 || HAVE_NATIVE_mpn_redc_2 */
/* First k to use for an FFT modF multiply.  A modF FFT is an order
   log(2^k)/log(2^(k-1)) algorithm, so k=3 is merely 1.5 like karatsuba,
   whereas k=4 is 1.33 which is faster than toom3 at 1.485.    */
#define FFT_FIRST_K  4
/* Threshold at which FFT should be used to do a modF NxN -> N multiply. */
#ifndef MUL_FFT_MODF_THRESHOLD
#define MUL_FFT_MODF_THRESHOLD   (MUL_TOOM33_THRESHOLD * 3)
#endif
#ifndef SQR_FFT_MODF_THRESHOLD
#define SQR_FFT_MODF_THRESHOLD   (SQR_TOOM3_THRESHOLD * 3)
#endif
/* Threshold at which FFT should be used to do an NxN -> 2N multiply.  This
   will be a size where FFT is using k=7 or k=8, since an FFT-k used for an
   NxN->2N multiply and not recursing into itself is an order
   log(2^k)/log(2^(k-2)) algorithm, so it'll be at least k=7 at 1.39 which
   is the first better than toom3.  */
#ifndef MUL_FFT_THRESHOLD
#define MUL_FFT_THRESHOLD   (MUL_FFT_MODF_THRESHOLD * 10)
#endif
#ifndef SQR_FFT_THRESHOLD
#define SQR_FFT_THRESHOLD   (SQR_FFT_MODF_THRESHOLD * 10)
#endif
/* Table of thresholds for successive modF FFT "k"s.  The first entry is
   where FFT_FIRST_K+1 should be used, the second FFT_FIRST_K+2,
   etc.  See mpn_fft_best_k(). */
#ifndef MUL_FFT_TABLE
#define MUL_FFT_TABLE							\
  { MUL_TOOM33_THRESHOLD * 4,   /* k=5 */				\
    MUL_TOOM33_THRESHOLD * 8,   /* k=6 */				\
    MUL_TOOM33_THRESHOLD * 16,  /* k=7 */				\
    MUL_TOOM33_THRESHOLD * 32,  /* k=8 */				\
    MUL_TOOM33_THRESHOLD * 96,  /* k=9 */				\
    MUL_TOOM33_THRESHOLD * 288, /* k=10 */				\
    0 }
#endif
#ifndef SQR_FFT_TABLE
#define SQR_FFT_TABLE							\
  { SQR_TOOM3_THRESHOLD * 4,   /* k=5 */				\
    SQR_TOOM3_THRESHOLD * 8,   /* k=6 */				\
    SQR_TOOM3_THRESHOLD * 16,  /* k=7 */				\
    SQR_TOOM3_THRESHOLD * 32,  /* k=8 */				\
    SQR_TOOM3_THRESHOLD * 96,  /* k=9 */				\
    SQR_TOOM3_THRESHOLD * 288, /* k=10 */				\
    0 }
#endif
struct fft_table_nk
{
  gmp_uint_least32_t n:27;
  gmp_uint_least32_t k:5;
};
#ifndef FFT_TABLE_ATTRS
#define FFT_TABLE_ATTRS   static const
#endif
#define MPN_FFT_TABLE_SIZE  16
#ifndef DC_DIV_QR_THRESHOLD
#define DC_DIV_QR_THRESHOLD    (3 * MUL_TOOM22_THRESHOLD)
#endif
#ifndef GET_STR_DC_THRESHOLD
#define GET_STR_DC_THRESHOLD             18
#endif
#ifndef GET_STR_PRECOMPUTE_THRESHOLD
#define GET_STR_PRECOMPUTE_THRESHOLD     35
#endif
#ifndef SET_STR_DC_THRESHOLD
#define SET_STR_DC_THRESHOLD            750
#endif
#ifndef SET_STR_PRECOMPUTE_THRESHOLD
#define SET_STR_PRECOMPUTE_THRESHOLD   2000
#endif
#ifndef FAC_ODD_THRESHOLD
#define FAC_ODD_THRESHOLD    35
#endif
#ifndef FAC_DSC_THRESHOLD
#define FAC_DSC_THRESHOLD   400
#endif
//ed

/* ASSERT */
__MPFR_DECLSPEC void mpfr_assert_fail _MPFR_PROTO((const char *, int,
                                                   const char *));

#define ASSERT_FAIL(expr)  mpfr_assert_fail (__FILE__, __LINE__, #expr)
#define ASSERT(expr)       MPFR_ASSERTD(expr)

/* Access fields of GMP struct */
#define SIZ(x) ((x)->_mp_size)
#define ABSIZ(x) ABS (SIZ (x))
#define PTR(x) ((x)->_mp_d)
#define EXP(x) ((x)->_mp_exp)
#define PREC(x) ((x)->_mp_prec)
#define ALLOC(x) ((x)->_mp_alloc)
#define MPZ_REALLOC(z,n) ((n) > ALLOC(z) ? _mpz_realloc(z,n) : PTR(z))

/* Field access macros.  */
//ed
//gmp-impl.h
//#define SIZ(x) ((x)->_mp_size)
//#define ABSIZ(x) ABS (SIZ (x))
//#define PTR(x) ((x)->_mp_d)
//#define EXP(x) ((x)->_mp_exp)
//#define PREC(x) ((x)->_mp_prec)
//#define ALLOC(x) ((x)->_mp_alloc)
#define NUM(x) mpq_numref(x)
#define DEN(x) mpq_denref(x)

/* Non IEEE float supports -- needs to detect them with proper configure */
#undef  XDEBUG
#define XDEBUG

/* For gmp_longlong.h */
#ifdef HAVE_ATTRIBUTE_MODE
typedef unsigned int UQItype    __attribute__ ((mode (QI)));
typedef          int SItype     __attribute__ ((mode (SI)));
typedef unsigned int USItype    __attribute__ ((mode (SI)));
typedef          int DItype     __attribute__ ((mode (DI)));
typedef unsigned int UDItype    __attribute__ ((mode (DI)));
#else
typedef unsigned char UQItype;
typedef          long SItype;
typedef unsigned long USItype;
#ifdef HAVE_LONG_LONG
typedef long long int DItype;
typedef unsigned long long int UDItype;
#else /* Assume `long' gives us a wide enough type.  Needed for hppa2.0w.  */
typedef long int DItype;
typedef unsigned long int UDItype;
#endif
#endif
typedef mp_limb_t UWtype;
typedef unsigned int UHWtype;
#define W_TYPE_SIZE GMP_NUMB_BITS

/* Remap names of internal mpn functions (for gmp_longlong.h).  */
#undef  __clz_tab
#define __clz_tab               mpfr_clz_tab

/* Use (4.0 * ...) instead of (2.0 * ...) to work around buggy compilers
   that don't convert ulong->double correctly (eg. SunOS 4 native cc).  */
#undef MP_BASE_AS_DOUBLE
#define MP_BASE_AS_DOUBLE (4.0 * ((mp_limb_t) 1 << (GMP_NUMB_BITS - 2)))

/* Structure for conversion between internal binary format and
   strings in base 2..36.  */
struct mpfr_bases_t
{
  /* log(2)/log(conversion_base) */
  double chars_per_bit_exactly;
};
#undef  __mp_bases
#define __mp_bases mpfr_bases
__MPFR_DECLSPEC extern const struct mpfr_bases_t mpfr_bases[257];

/* Standard macros */
#undef ABS
#undef MIN
#undef MAX
#undef numberof
#define ABS(x) ((x) >= 0 ? (x) : -(x))
#define MIN(l,o) ((l) < (o) ? (l) : (o))
#define MAX(h,i) ((h) > (i) ? (h) : (i))
#define numberof(x)  (sizeof (x) / sizeof ((x)[0]))

//ed
//gmp-impl.h
/* From gmp.h, nicer names for internal use. */
//#define CRAY_Pragma(str)               __GMP_CRAY_Pragma(str)
//#define MPN_CMP(result, xp, yp, size)  __GMPN_CMP(result, xp, yp, size)
//#define LIKELY(cond)                   __GMP_LIKELY(cond)
//#define UNLIKELY(cond)                 __GMP_UNLIKELY(cond)

//#define ABS(x) ((x) >= 0 ? (x) : -(x))
#define NEG_CAST(T,x) (- (__GMP_CAST (T, (x) + 1) - 1))
#define ABS_CAST(T,x) ((x) >= 0 ? __GMP_CAST (T, x) : NEG_CAST (T,x))
//#undef MIN
//#define MIN(l,o) ((l) < (o) ? (l) : (o))
//#undef MAX
//#define MAX(h,i) ((h) > (i) ? (h) : (i))
//#define numberof(x)  (sizeof (x) / sizeof ((x)[0]))
//ed

/* Random */
#undef  __gmp_rands_initialized
#undef  __gmp_rands
#define __gmp_rands_initialized mpfr_rands_initialized
#define __gmp_rands             mpfr_rands

__MPFR_DECLSPEC extern char             mpfr_rands_initialized;
__MPFR_DECLSPEC extern gmp_randstate_t  mpfr_rands;

#undef RANDS
#define RANDS                                   \
  ((__gmp_rands_initialized ? 0                 \
    : (__gmp_rands_initialized = 1,             \
       gmp_randinit_default (__gmp_rands), 0)), \
   __gmp_rands)

#undef RANDS_CLEAR
#define RANDS_CLEAR()                   \
  do {                                  \
    if (__gmp_rands_initialized)        \
      {                                 \
        __gmp_rands_initialized = 0;    \
        gmp_randclear (__gmp_rands);    \
      }                                 \
  } while (0)

typedef __gmp_randstate_struct *gmp_randstate_ptr;




//ed
//gmp-impl.h
/* Enhancement: __gmp_allocate_func could have "__attribute__ ((malloc))",
   but current gcc (3.0) doesn't seem to support that.  */

//__GMP_DECLSPEC extern void * (*__gmp_allocate_func) (size_t);
//__GMP_DECLSPEC extern void * (*__gmp_reallocate_func) (void *, size_t, size_t);
//__GMP_DECLSPEC extern void   (*__gmp_free_func) (void *, size_t);

/*
__GMP_DECLSPEC void *__gmp_default_allocate (size_t);
__GMP_DECLSPEC void *__gmp_default_reallocate (void *, size_t, size_t);
__GMP_DECLSPEC void __gmp_default_free (void *, size_t);

#define __GMP_ALLOCATE_FUNC_TYPE(n,type) \
  ((type *) (*__gmp_allocate_func) ((n) * sizeof (type)))
#define __GMP_ALLOCATE_FUNC_LIMBS(n)   __GMP_ALLOCATE_FUNC_TYPE (n, mp_limb_t)

#define __GMP_REALLOCATE_FUNC_TYPE(p, old_size, new_size, type)		\
  ((type *) (*__gmp_reallocate_func)					\
   (p, (old_size) * sizeof (type), (new_size) * sizeof (type)))
#define __GMP_REALLOCATE_FUNC_LIMBS(p, old_size, new_size)		\
  __GMP_REALLOCATE_FUNC_TYPE(p, old_size, new_size, mp_limb_t)

#define __GMP_FREE_FUNC_TYPE(p,n,type) (*__gmp_free_func) (p, (n) * sizeof (type))
#define __GMP_FREE_FUNC_LIMBS(p,n)     __GMP_FREE_FUNC_TYPE (p, n, mp_limb_t)

#define __GMP_REALLOCATE_FUNC_MAYBE(ptr, oldsize, newsize)		\
  do {									\
    if ((oldsize) != (newsize))						\
      (ptr) = (*__gmp_reallocate_func) (ptr, oldsize, newsize);		\
  } while (0)

#define __GMP_REALLOCATE_FUNC_MAYBE_TYPE(ptr, oldsize, newsize, type)	\
  do {									\
    if ((oldsize) != (newsize))						\
      (ptr) = (type *) (*__gmp_reallocate_func)				\
	(ptr, (oldsize) * sizeof (type), (newsize) * sizeof (type));	\
  } while (0)
*/
/* Dummy for non-gcc, code involving it will go dead. */
//#if ! defined (__GNUC__) || __GNUC__ < 2
//#define __builtin_constant_p(x)   0
//#endif
//ed



/* Allocate func are defined in gmp-impl.h */

/* In newer GMP, there aren't anymore __gmp_allocate_func,
   __gmp_reallocate_func & __gmp_free_func in gmp.h
   Just getting the correct value by calling mp_get_memory_functions */
#ifdef mp_get_memory_functions

#undef __gmp_allocate_func
#undef __gmp_reallocate_func
#undef __gmp_free_func
#define MPFR_GET_MEMFUNC                                        \
  ((void) (MPFR_LIKELY (mpfr_allocate_func != 0) ||             \
           (mp_get_memory_functions(&mpfr_allocate_func,        \
                                    &mpfr_reallocate_func,      \
                                    &mpfr_free_func), 1)))
#define __gmp_allocate_func   (MPFR_GET_MEMFUNC, mpfr_allocate_func)
#define __gmp_reallocate_func (MPFR_GET_MEMFUNC, mpfr_reallocate_func)
#define __gmp_free_func       (MPFR_GET_MEMFUNC, mpfr_free_func)
__MPFR_DECLSPEC extern MPFR_THREAD_ATTR void * (*mpfr_allocate_func)   _MPFR_PROTO ((size_t));
__MPFR_DECLSPEC extern MPFR_THREAD_ATTR void * (*mpfr_reallocate_func) _MPFR_PROTO ((void *, size_t, size_t));
__MPFR_DECLSPEC extern MPFR_THREAD_ATTR void   (*mpfr_free_func)       _MPFR_PROTO ((void *, size_t));

#endif

#undef __gmp_default_allocate
#undef __gmp_default_reallocate
#undef __gmp_default_free
#define __gmp_default_allocate   mpfr_default_allocate
#define __gmp_default_reallocate mpfr_default_reallocate
#define __gmp_default_free       mpfr_default_free
__MPFR_DECLSPEC void *__gmp_default_allocate _MPFR_PROTO ((size_t));
__MPFR_DECLSPEC void *__gmp_default_reallocate _MPFR_PROTO ((void *, size_t,
                                                             size_t));
__MPFR_DECLSPEC void __gmp_default_free _MPFR_PROTO ((void *, size_t));


#if defined(WANT_GMP_INTERNALS) && defined(HAVE___GMPN_ROOTREM)
#ifndef __gmpn_rootrem
  __MPFR_DECLSPEC mp_size_t __gmpn_rootrem _MPFR_PROTO ((mp_limb_t*,
                    mp_limb_t*, mp_limb_t*, mp_size_t, mp_limb_t));
#endif
#endif

#if defined(WANT_GMP_INTERNALS) && defined(HAVE___GMPN_SBPI1_DIVAPPR_Q)
#ifndef __gmpn_sbpi1_divappr_q
  __MPFR_DECLSPEC mp_limb_t __gmpn_sbpi1_divappr_q _MPFR_PROTO ((mp_limb_t*,
                mp_limb_t*, mp_size_t, mp_limb_t*, mp_size_t, mp_limb_t));
#endif
#endif

/* Temp memory allocate */

struct tmp_marker
{
  void *ptr;
  size_t size;
  struct tmp_marker *next;
};

__MPFR_DECLSPEC void *mpfr_tmp_allocate _MPFR_PROTO ((struct tmp_marker **,
                                                      size_t));
__MPFR_DECLSPEC void mpfr_tmp_free _MPFR_PROTO ((struct tmp_marker *));

/* Do not define TMP_SALLOC (see the test in mpfr-impl.h)! */
#define TMP_ALLOC(n) (MPFR_LIKELY ((n) < 16384) ?       \
                      alloca (n) : mpfr_tmp_allocate (&tmp_marker, (n)))
//#define TMP_DECL(m) struct tmp_marker *tmp_marker
//#define TMP_MARK(m) (tmp_marker = 0)
//#define TMP_FREE(m) mpfr_tmp_free (tmp_marker)
//ed
#define TMP_DECL struct tmp_marker *tmp_marker
#define TMP_MARK (tmp_marker = 0)
#define TMP_FREE mpfr_tmp_free (tmp_marker)
#define TMP_SDECL	//ed //gmp-impl.h
#define TMP_SMARK	//ed //gmp-impl.h
#define TMP_SFREE	//ed //gmp-impl.h

/* invert_limb macro, copied from GMP 5.0.2, file gmp-impl.h.
   It returns invxl = floor((B^2-1)/xl)-B, where B=2^BITS_PER_LIMB,
   assuming the most significant bit of xl is set. */
#undef invert_limb
#define invert_limb(invxl,xl)                             \
  do {                                                    \
    mp_limb_t dummy;                                      \
    MPFR_ASSERTD ((xl) != 0);                             \
    udiv_qrnnd (invxl, dummy, ~(xl), ~(mp_limb_t)0, xl);  \
  } while (0)

typedef struct {mp_limb_t inv32;} mpfr_pi1_t; /* We changed gmp_pi1_t into
                                                 mpfr_pi1_t to avoid using
                                                 GMP's namespace. */
/* invert_pi1 macro, adapted from GMP 5.0.2, file gmp-impl.h.
   It returns dinv = floor((B^3-1)/(d1*B+d0))-B, where B=2^BITS_PER_LIMB,
   assuming the most significant bit of d1 is set. */
#undef invert_pi1
#define invert_pi1(dinv, d1, d0)                                \
  do {                                                          \
    mp_limb_t _v, _p, _t1, _t0, _mask;                          \
    invert_limb (_v, d1);                                       \
    _p = d1 * _v;                                               \
    _p += d0;                                                   \
    if (_p < d0)                                                \
      {                                                         \
        _v--;                                                   \
        _mask = -(_p >= d1);                                    \
        _p -= d1;                                               \
        _v += _mask;                                            \
        _p -= _mask & d1;                                       \
      }                                                         \
    umul_ppmm (_t1, _t0, d0, _v);                               \
    _p += _t1;                                                  \
    if (_p < _t1)                                               \
      {                                                         \
        _v--;                                                   \
        if (MPFR_UNLIKELY (_p >= d1))                           \
          {                                                     \
            if (_p > d1 || _t0 >= d0)                           \
              _v--;                                             \
          }                                                     \
      }                                                         \
    (dinv).inv32 = _v;                                          \
  } while (0)

/* udiv_qr_3by2 macro, adapted from GMP 5.0.2, file gmp-impl.h.
   Compute quotient the quotient and remainder for n / d. Requires d
   >= B^2 / 2 and n < d B. dinv is the inverse

     floor ((B^3 - 1) / (d0 + d1 B)) - B.

   NOTE: Output variables are updated multiple times. Only some inputs
   and outputs may overlap.
*/
#undef udiv_qr_3by2
#define udiv_qr_3by2(q, r1, r0, n2, n1, n0, d1, d0, dinv)               \
  do {                                                                  \
    mp_limb_t _q0, _t1, _t0, _mask;                                     \
    umul_ppmm ((q), _q0, (n2), (dinv));                                 \
    add_ssaaaa ((q), _q0, (q), _q0, (n2), (n1));                        \
                                                                        \
    /* Compute the two most significant limbs of n - q'd */             \
    (r1) = (n1) - (d1) * (q);                                           \
    (r0) = (n0);                                                        \
    sub_ddmmss ((r1), (r0), (r1), (r0), (d1), (d0));                    \
    umul_ppmm (_t1, _t0, (d0), (q));                                    \
    sub_ddmmss ((r1), (r0), (r1), (r0), _t1, _t0);                      \
    (q)++;                                                              \
                                                                        \
    /* Conditionally adjust q and the remainders */                     \
    _mask = - (mp_limb_t) ((r1) >= _q0);                                \
    (q) += _mask;                                                       \
    add_ssaaaa ((r1), (r0), (r1), (r0), _mask & (d1), _mask & (d0));    \
    if (MPFR_UNLIKELY ((r1) >= (d1)))                                   \
      {                                                                 \
        if ((r1) > (d1) || (r0) >= (d0))                                \
          {                                                             \
            (q)++;                                                      \
            sub_ddmmss ((r1), (r0), (r1), (r0), (d1), (d0));            \
          }                                                             \
      }                                                                 \
  } while (0)

//ed
//gmp-impl.h
/* Structure for conversion between internal binary format and strings.  */
struct gmp_bases_t
{
  /* Number of digits in the conversion base that always fits in an mp_limb_t.
     For example, for base 10 on a machine where an mp_limb_t has 32 bits this
     is 9, since 10**9 is the largest number that fits into an mp_limb_t.  */
  int chars_per_limb;
  /* log(2)/log(conversion_base) */
  mp_limb_t logb2;
  /* log(conversion_base)/log(2) */
  mp_limb_t log2b;
  /* base**chars_per_limb, i.e. the biggest number that fits a word, built by
     factors of base.  Exception: For 2, 4, 8, etc, big_base is log2(base),
     i.e. the number of bits used to represent each digit in the base.  */
  mp_limb_t big_base;
  /* A GMP_LIMB_BITS bit approximation to 1/big_base, represented as a
     fixed-point number.  Instead of dividing by big_base an application can
     choose to multiply by big_base_inverted.  */
  mp_limb_t big_base_inverted;
};
#define   mp_bases __MPN(bases)
__GMP_DECLSPEC extern const struct gmp_bases_t mp_bases[257];

//ed
//gmp-impl.h
/* Use (4.0 * ...) instead of (2.0 * ...) to work around buggy compilers
   that don't convert ulong->double correctly (eg. SunOS 4 native cc).  */
#define MP_BASE_AS_DOUBLE (4.0 * ((mp_limb_t) 1 << (GMP_NUMB_BITS - 2)))
/* Maximum number of limbs it will take to store any `double'.
   We assume doubles have 53 mantissa bits.  */
#define LIMBS_PER_DOUBLE ((53 + GMP_NUMB_BITS - 2) / GMP_NUMB_BITS + 1)

__GMP_DECLSPEC int __gmp_extract_double (mp_ptr, double);

#define mpn_get_d __gmpn_get_d
__GMP_DECLSPEC double mpn_get_d (mp_srcptr, mp_size_t, mp_size_t, long) __GMP_ATTRIBUTE_PURE;
//ed

//ed
//gmp-impl.h
__GMP_DECLSPEC extern int __gmp_junk;
__GMP_DECLSPEC extern const int __gmp_0;
__GMP_DECLSPEC void __gmp_exception (int) ATTRIBUTE_NORETURN;
__GMP_DECLSPEC void __gmp_divide_by_zero (void) ATTRIBUTE_NORETURN;
__GMP_DECLSPEC void __gmp_sqrt_of_negative (void) ATTRIBUTE_NORETURN;
__GMP_DECLSPEC void __gmp_invalid_operation (void) ATTRIBUTE_NORETURN;
#define GMP_ERROR(code)   __gmp_exception (code)
#define DIVIDE_BY_ZERO    __gmp_divide_by_zero ()
#define SQRT_OF_NEGATIVE  __gmp_sqrt_of_negative ()
#if defined _LONG_LONG_LIMB
#define CNST_LIMB(C) ((mp_limb_t) C##LL)
#else /* not _LONG_LONG_LIMB */
#define CNST_LIMB(C) ((mp_limb_t) C##L)
#endif /* _LONG_LONG_LIMB */

//ed
//gmp-impl.h
/* ASSERT() is a private assertion checking scheme, similar to <assert.h>.
   ASSERT() does the check only if WANT_ASSERT is selected, ASSERT_ALWAYS()
   does it always.  Generally assertions are meant for development, but
   might help when looking for a problem later too.  */
#ifdef __LINE__
#define ASSERT_LINE  __LINE__
#else
#define ASSERT_LINE  -1
#endif
#ifdef __FILE__
#define ASSERT_FILE  __FILE__
#else
#define ASSERT_FILE  ""
#endif
__GMP_DECLSPEC void __gmp_assert_header (const char *, int);
__GMP_DECLSPEC void __gmp_assert_fail (const char *, int, const char *) ATTRIBUTE_NORETURN;
//#define ASSERT_FAIL(expr)  __gmp_assert_fail (ASSERT_FILE, ASSERT_LINE, #expr)
#define ASSERT_ALWAYS(expr)						\
  do {									\
    if (UNLIKELY (!(expr)))						\
      ASSERT_FAIL (expr);						\
  } while (0)

/*
#if WANT_ASSERT
#define ASSERT(expr)   ASSERT_ALWAYS (expr)
#else
#define ASSERT(expr)   do {} while (0)
#endif
*/
/* ASSERT_CARRY checks the expression is non-zero, and ASSERT_NOCARRY checks
   that it's zero.  In both cases if assertion checking is disabled the
   expression is still evaluated.  These macros are meant for use with
   routines like mpn_add_n() where the return value represents a carry or
   whatever that should or shouldn't occur in some context.  For example,
   ASSERT_NOCARRY (mpn_add_n (rp, s1p, s2p, size)); */
#if WANT_ASSERT
#define ASSERT_CARRY(expr)     ASSERT_ALWAYS ((expr) != 0)
#define ASSERT_NOCARRY(expr)   ASSERT_ALWAYS ((expr) == 0)
#else
#define ASSERT_CARRY(expr)     (expr)
#define ASSERT_NOCARRY(expr)   (expr)
#endif
/* ASSERT_CODE includes code when assertion checking is wanted.  This is the
   same as writing "#if WANT_ASSERT", but more compact.  */
#if WANT_ASSERT
#define ASSERT_CODE(expr)  expr
#else
#define ASSERT_CODE(expr)
#endif
/* Test that an mpq_t is in fully canonical form.  This can be used as
   protection on routines like mpq_equal which give wrong results on
   non-canonical inputs.  */
#if WANT_ASSERT
#define ASSERT_MPQ_CANONICAL(q)						\
  do {									\
    ASSERT (q->_mp_den._mp_size > 0);					\
    if (q->_mp_num._mp_size == 0)					\
      {									\
	/* zero should be 0/1 */					\
	ASSERT (mpz_cmp_ui (mpq_denref(q), 1L) == 0);			\
      }									\
    else								\
      {									\
	/* no common factors */						\
	mpz_t  __g;							\
	mpz_init (__g);							\
	mpz_gcd (__g, mpq_numref(q), mpq_denref(q));			\
	ASSERT (mpz_cmp_ui (__g, 1) == 0);				\
	mpz_clear (__g);						\
      }									\
  } while (0)
#else
#define ASSERT_MPQ_CANONICAL(q)	 do {} while (0)
#endif
/* Check that the nail parts are zero. */
#define ASSERT_ALWAYS_LIMB(limb)					\
  do {									\
    mp_limb_t  __nail = (limb) & GMP_NAIL_MASK;				\
    ASSERT_ALWAYS (__nail == 0);					\
  } while (0)
#define ASSERT_ALWAYS_MPN(ptr, size)					\
  do {									\
    /* let whole loop go dead when no nails */				\
    if (GMP_NAIL_BITS != 0)						\
      {									\
	mp_size_t  __i;							\
	for (__i = 0; __i < (size); __i++)				\
	  ASSERT_ALWAYS_LIMB ((ptr)[__i]);				\
      }									\
  } while (0)
#if WANT_ASSERT
#define ASSERT_LIMB(limb)       ASSERT_ALWAYS_LIMB (limb)
#define ASSERT_MPN(ptr, size)   ASSERT_ALWAYS_MPN (ptr, size)
#else
#define ASSERT_LIMB(limb)       do {} while (0)
#define ASSERT_MPN(ptr, size)   do {} while (0)
#endif
/* Assert that an mpn region {ptr,size} is zero, or non-zero.
   size==0 is allowed, and in that case {ptr,size} considered to be zero.  */
#if WANT_ASSERT
#define ASSERT_MPN_ZERO_P(ptr,size)					\
  do {									\
    mp_size_t  __i;							\
    ASSERT ((size) >= 0);						\
    for (__i = 0; __i < (size); __i++)					\
      ASSERT ((ptr)[__i] == 0);						\
  } while (0)
#define ASSERT_MPN_NONZERO_P(ptr,size)					\
  do {									\
    mp_size_t  __i;							\
    int	       __nonzero = 0;						\
    ASSERT ((size) >= 0);						\
    for (__i = 0; __i < (size); __i++)					\
      if ((ptr)[__i] != 0)						\
	{								\
	  __nonzero = 1;						\
	  break;							\
	}								\
    ASSERT (__nonzero);							\
  } while (0)
#else
#define ASSERT_MPN_ZERO_P(ptr,size)     do {} while (0)
#define ASSERT_MPN_NONZERO_P(ptr,size)  do {} while (0)
#endif
//ed

#if defined (__cplusplus)
}
#endif

//ed
//gmp-impl.h
/* FIXME: Make these itch functions less conservative.  Also consider making
   them dependent on just 'an', and compute the allocation directly from 'an'
   instead of via n.  */
/* toom22/toom2: Scratch need is 2*(an + k), k is the recursion depth.
   k is ths smallest k such that
     ceil(an/2^k) < MUL_TOOM22_THRESHOLD.
   which implies that
     k = bitsize of floor ((an-1)/(MUL_TOOM22_THRESHOLD-1))
       = 1 + floor (log_2 (floor ((an-1)/(MUL_TOOM22_THRESHOLD-1))))
*/
#define mpn_toom22_mul_itch(an, bn) \
  (2 * ((an) + GMP_NUMB_BITS))
#define mpn_toom2_sqr_itch(an) \
  (2 * ((an) + GMP_NUMB_BITS))
/* toom33/toom3: Scratch need is 5an/2 + 10k, k is the recursion depth.
   We use 3an + C, so that we can use a smaller constant.
 */
#define mpn_toom33_mul_itch(an, bn) \
  (3 * (an) + GMP_NUMB_BITS)
#define mpn_toom3_sqr_itch(an) \
  (3 * (an) + GMP_NUMB_BITS)
/* toom33/toom3: Scratch need is 8an/3 + 13k, k is the recursion depth.
   We use 3an + C, so that we can use a smaller constant.
 */
#define mpn_toom44_mul_itch(an, bn) \
  (3 * (an) + GMP_NUMB_BITS)
#define mpn_toom4_sqr_itch(an) \
  (3 * (an) + GMP_NUMB_BITS)
#define mpn_toom6_sqr_itch(n)						\
  (((n) - SQR_TOOM6_THRESHOLD)*2 +					\
   MAX(SQR_TOOM6_THRESHOLD*2 + GMP_NUMB_BITS*6,				\
       mpn_toom4_sqr_itch(SQR_TOOM6_THRESHOLD)))
#define MUL_TOOM6H_MIN							\
  ((MUL_TOOM6H_THRESHOLD > MUL_TOOM44_THRESHOLD) ?			\
    MUL_TOOM6H_THRESHOLD : MUL_TOOM44_THRESHOLD)
#define mpn_toom6_mul_n_itch(n)						\
  (((n) - MUL_TOOM6H_MIN)*2 +						\
   MAX(MUL_TOOM6H_MIN*2 + GMP_NUMB_BITS*6,				\
       mpn_toom44_mul_itch(MUL_TOOM6H_MIN,MUL_TOOM6H_MIN)))
static GMP_INLINE mp_size_t
mpn_toom6h_mul_itch (mp_size_t an, mp_size_t bn) {
  mp_size_t estimatedN;
  estimatedN = (an + bn) / (size_t) 10 + 1;
  return mpn_toom6_mul_n_itch (estimatedN * 6);
}
#define mpn_toom8_sqr_itch(n)						\
  ((((n)*15)>>3) - ((SQR_TOOM8_THRESHOLD*15)>>3) +			\
   MAX(((SQR_TOOM8_THRESHOLD*15)>>3) + GMP_NUMB_BITS*6,			\
       mpn_toom6_sqr_itch(SQR_TOOM8_THRESHOLD)))
#define MUL_TOOM8H_MIN							\
  ((MUL_TOOM8H_THRESHOLD > MUL_TOOM6H_MIN) ?				\
    MUL_TOOM8H_THRESHOLD : MUL_TOOM6H_MIN)
#define mpn_toom8_mul_n_itch(n)						\
  ((((n)*15)>>3) - ((MUL_TOOM8H_MIN*15)>>3) +				\
   MAX(((MUL_TOOM8H_MIN*15)>>3) + GMP_NUMB_BITS*6,			\
       mpn_toom6_mul_n_itch(MUL_TOOM8H_MIN)))
static GMP_INLINE mp_size_t
mpn_toom8h_mul_itch (mp_size_t an, mp_size_t bn) {
  mp_size_t estimatedN;
  estimatedN = (an + bn) / (size_t) 14 + 1;
  return mpn_toom8_mul_n_itch (estimatedN * 8);
}
static GMP_INLINE mp_size_t
mpn_toom32_mul_itch (mp_size_t an, mp_size_t bn)
{
  mp_size_t n = 1 + (2 * an >= 3 * bn ? (an - 1) / (size_t) 3 : (bn - 1) >> 1);
  mp_size_t itch = 2 * n + 1;
  return itch;
}
static GMP_INLINE mp_size_t
mpn_toom42_mul_itch (mp_size_t an, mp_size_t bn)
{
  mp_size_t n = an >= 2 * bn ? (an + 3) >> 2 : (bn + 1) >> 1;
  return 6 * n + 3;
}
static GMP_INLINE mp_size_t
mpn_toom43_mul_itch (mp_size_t an, mp_size_t bn)
{
  mp_size_t n = 1 + (3 * an >= 4 * bn ? (an - 1) >> 2 : (bn - 1) / (size_t) 3);
  return 6*n + 4;
}
static GMP_INLINE mp_size_t
mpn_toom52_mul_itch (mp_size_t an, mp_size_t bn)
{
  mp_size_t n = 1 + (2 * an >= 5 * bn ? (an - 1) / (size_t) 5 : (bn - 1) >> 1);
  return 6*n + 4;
}
static GMP_INLINE mp_size_t
mpn_toom53_mul_itch (mp_size_t an, mp_size_t bn)
{
  mp_size_t n = 1 + (3 * an >= 5 * bn ? (an - 1) / (size_t) 5 : (bn - 1) / (size_t) 3);
  return 10 * n + 10;
}
static GMP_INLINE mp_size_t
mpn_toom62_mul_itch (mp_size_t an, mp_size_t bn)
{
  mp_size_t n = 1 + (an >= 3 * bn ? (an - 1) / (size_t) 6 : (bn - 1) >> 1);
  return 10 * n + 10;
}
static GMP_INLINE mp_size_t
mpn_toom63_mul_itch (mp_size_t an, mp_size_t bn)
{
  mp_size_t n = 1 + (an >= 2 * bn ? (an - 1) / (size_t) 6 : (bn - 1) / (size_t) 3);
  return 9 * n + 3;
}
static GMP_INLINE mp_size_t
mpn_toom54_mul_itch (mp_size_t an, mp_size_t bn)
{
  mp_size_t n = 1 + (4 * an >= 5 * bn ? (an - 1) / (size_t) 5 : (bn - 1) / (size_t) 4);
  return 9 * n + 3;
}
/* let S(n) = space required for input size n,
   then S(n) = 3 floor(n/2) + 1 + S(floor(n/2)).   */
#define mpn_toom42_mulmid_itch(n) \
  (3 * (n) + GMP_NUMB_BITS)
#if 0
#define mpn_fft_mul mpn_mul_fft_full
#else
#define mpn_fft_mul mpn_nussbaumer_mul
#endif
//ed

#endif /* Gmp internal emulator */
