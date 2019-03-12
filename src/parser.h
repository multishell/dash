/*-
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
 * Copyright (c) 1997-2005
 *	Herbert Xu <herbert@gondor.apana.org.au>.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Kenneth Almquist.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)parser.h	8.3 (Berkeley) 5/4/95
 */

/* control characters in argument strings */
#define CTL_FIRST '\201'	/* first 'special' character */
#define CTLESC '\201'		/* escape next character */
#define CTLVAR '\202'		/* variable defn */
#define CTLENDVAR '\203'
#define CTLBACKQ '\204'
#define CTLQUOTE 01		/* ored with CTLBACKQ code if in quotes */
/*	CTLBACKQ | CTLQUOTE == '\205' */
#define	CTLARI	'\206'		/* arithmetic expression */
#define	CTLENDARI '\207'
#define	CTLQUOTEMARK '\210'
#define	CTL_LAST '\210'		/* last 'special' character */

/* variable substitution byte (follows CTLVAR) */
#define VSTYPE	0x0f		/* type of variable substitution */
#define VSNUL	0x10		/* colon--treat the empty string as unset */
#define VSQUOTE 0x80		/* inside double quotes--suppress splitting */

/* values of VSTYPE field */
#define VSNORMAL	0x1		/* normal variable:  $var or ${var} */
#define VSMINUS		0x2		/* ${var-text} */
#define VSPLUS		0x3		/* ${var+text} */
#define VSQUESTION	0x4		/* ${var?message} */
#define VSASSIGN	0x5		/* ${var=text} */
#define VSTRIMRIGHT	0x6		/* ${var%pattern} */
#define VSTRIMRIGHTMAX 	0x7		/* ${var%%pattern} */
#define VSTRIMLEFT	0x8		/* ${var#pattern} */
#define VSTRIMLEFTMAX	0x9		/* ${var##pattern} */
#define VSLENGTH	0xa		/* ${#var} */

/* values of checkkwd variable */
#define CHKALIAS	0x1
#define CHKKWD		0x2
#define CHKNL		0x4


/*
 * NEOF is returned by parsecmd when it encounters an end of file.  It
 * must be distinct from NULL, so we use the address of a variable that
 * happens to be handy.
 */
extern int tokpushback;
#define NEOF ((union node *)&tokpushback)
extern int whichprompt;		/* 1 == PS1, 2 == PS2 */
extern int checkkwd;
extern int startlinno;		/* line # where last token started */


union node *parsecmd(int);
void fixredir(union node *, const char *, int);
const char *getprompt(void *);
const char *const *findkwd(const char *);
char *endofname(const char *);
const char *expandstr(const char *);

static inline int
goodname(const char *p)
{
	return !*endofname(p);
}
