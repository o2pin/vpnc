/* borrowed from isakmpd-20030718 (-; */

/*	$OpenBSD: dh.c,v 1.8 2003/06/03 14:28:16 ho Exp $	*/
/*	$EOM: dh.c,v 1.5 1999/04/17 23:20:22 niklas Exp $	*/

/*
 * Copyright (c) 1998 Niels Provos.  All rights reserved.
 * Copyright (c) 1999 Niklas Hallqvist.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * This code was written under funding by Ericsson Radio Systems.
 */

#include "math_group.h"
#include "dh.h"

/*
 * Returns the length of our exchange value.
 */

int dh_getlen(struct group *group)
{
	return group->getlen(group);
}

/*
 * Creates the exchange value we are offering to the other party.
 * Each time this function is called a new value is created, that
 * means the application has to save the exchange value itself,
 * dh_create_exchange should only be called once.
 */
int dh_create_exchange(struct group *group, unsigned char *buf)
{
	if (group->setrandom(group, group->c))
		return -1;
	if (group->operation(group, group->a, group->gen, group->c))
		return -1;
	group->getraw(group, group->a, buf);
	printf("Creates the exchange value we are offering to the other party.\n");
	// hex_dump("Creates the exchange value we are offering to the other party", group, sizeof(buf), NULL);
	return 0;
}

/*
 * Creates the Diffie-Hellman shared secret in 'secret', where 'exchange'
 * is the exchange value offered by the other party. No length verification
 * is done for the value, the application has to do that.
 */
int dh_create_shared(struct group *group, unsigned char *secret, unsigned char *exchange)
{
	if (group->setraw(group, group->b, exchange, group->getlen(group)))
		return -1;
	if (group->operation(group, group->a, group->b, group->c))
		return -1;
	group->getraw(group, group->a, secret);
	return 0;
}
