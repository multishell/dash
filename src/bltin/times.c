/*
 * Copyright (c) 1999 Herbert Xu <herbert@debian.org>
 * This file contains code for the times builtin.
 * $Id$
 */

#include <sys/times.h>
#include <unistd.h>
#ifdef USE_GLIBC_STDIO
#include <stdio.h>
#else
#include "bltin.h"
#endif

#define main timescmd

int main() {
	struct tms buf;
	long int clk_tck = sysconf(_SC_CLK_TCK);

	times(&buf);
	printf("%dm%fs %dm%fs\n%dm%fs %dm%fs\n",
	       (int) (buf.tms_utime / clk_tck / 60),
	       ((double) buf.tms_utime) / clk_tck,
	       (int) (buf.tms_stime / clk_tck / 60),
	       ((double) buf.tms_stime) / clk_tck,
	       (int) (buf.tms_cutime / clk_tck / 60),
	       ((double) buf.tms_cutime) / clk_tck,
	       (int) (buf.tms_cstime / clk_tck / 60),
	       ((double) buf.tms_cstime) / clk_tck);
	return 0;
}
