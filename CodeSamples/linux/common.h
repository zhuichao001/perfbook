/*
 * common.h: Common Linux kernel-isms.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; but version 2 of the License only due
 * to code included from the Linux kernel.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 * Copyright (c) 2006 Paul E. McKenney, IBM.
 *
 * Much code taken from the Linux kernel.  For such code, the option
 * to redistribute under later versions of GPL might not be available.
 */

#ifndef __always_inline
#define __always_inline inline
#endif

#define BUILD_BUG_ON(condition) ((void)sizeof(char[1 - 2*!!(condition)]))
#define BUILD_BUG_ON_ZERO(e) (sizeof(char[1 - 2 * !!(e)]) - 1)

#ifdef __ASSEMBLY__
#  define stringify_in_c(...)   __VA_ARGS__
#  define ASM_CONST(x)          x
#else
/* This version of stringify will deal with commas... */
#  define __stringify_in_c(...) #__VA_ARGS__
#  define stringify_in_c(...)   __stringify_in_c(__VA_ARGS__) " "
#  define __ASM_CONST(x)        x##UL
#  define ASM_CONST(x)          __ASM_CONST(x)
#endif

