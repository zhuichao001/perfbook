/*
 * singleq.h: Simple single-element atomic queue.
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

#ifndef _Q_H_
#define _Q_H_

struct el {
	int data;
};
struct queue {
	struct el *head;
};

void init_q(struct queue *qp);
int q_push(struct el *p, struct queue *q);
struct el *q_pop(struct queue *q);

#endif /* #ifndef _Q_H_ */
