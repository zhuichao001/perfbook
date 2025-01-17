/*
 * rcu_nest.h: user-level implementation of RCU permitting nesting.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
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
 * Copyright (c) 2008 Paul E. McKenney, IBM Corporation.
 */

#include "rcu_pointer.h"

DEFINE_SPINLOCK(rcu_gp_lock);
#define RCU_GP_CTR_SHIFT 7
#define RCU_GP_CTR_BOTTOM_BIT (1 << RCU_GP_CTR_SHIFT)
#define RCU_GP_CTR_NEST_MASK (RCU_GP_CTR_BOTTOM_BIT - 1)
long rcu_gp_ctr = 0;	/* increment by RCU_GP_CTR_BOTTOM_BIT each gp. */
DEFINE_PER_THREAD(long, rcu_reader_gp);

static inline int rcu_gp_ongoing(int cpu)
{
	return per_thread(rcu_reader_gp, cpu) & RCU_GP_CTR_NEST_MASK;
}

static void rcu_init(void)
{
	int i;

	init_per_thread(rcu_reader_gp, 0);
}

static void rcu_read_lock(void)
{
	long tmp;
	long *rrgp;

	/*
	 * If this is the outermost RCU read-side critical section,
	 * copy the global grace-period counter.  In either case,
	 * increment the nesting count held in the low-order bits.
	 */

	rrgp = &__get_thread_var(rcu_reader_gp);
retry:
	tmp = *rrgp;
	if ((tmp & RCU_GP_CTR_NEST_MASK) == 0)
		tmp = rcu_gp_ctr;
	tmp++;
	*rrgp = tmp;
	smp_mb();
	if (((tmp & RCU_GP_CTR_NEST_MASK) == 1) &&
	    ((rcu_gp_ctr - tmp) > (RCU_GP_CTR_NEST_MASK << 8)) != 0) {
		(*rrgp)--;
		goto retry;
	}
}

static void rcu_read_unlock(void)
{
	long tmp;

	/*
	 * Decrement the nesting counter held in the low-order bits,
	 * which had better not initially be zero.
	 */

	smp_mb();
#ifdef DEBUG_EXTREME
	BUG_ON((__get_thread_var(rcu_reader_gp) & RCU_GP_CTR_NEST_MASK) != 0);
#endif /* #ifdef DEBUG_EXTREME */
	__get_thread_var(rcu_reader_gp)--;
}

extern void synchronize_rcu(void);
