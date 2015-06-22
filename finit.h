/* Finit - Fast /sbin/init replacement w/ I/O, hook & service plugins
 *
 * Copyright (c) 2008-2010  Claudio Matsuoka <cmatsuoka@gmail.com>
 * Copyright (c) 2008-2015  Joachim Nilsson <troglobit@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef FINIT_H_
#define FINIT_H_

#include "config.h"		/* Generated by configure script */

#include <errno.h>
#include <fcntl.h>
#include <paths.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/* Distribution specific configuration */
#if defined EMBEDDED_SYSTEM
# define SETUP_DEVFS		"/sbin/mdev -s"
# define GETTY			"/sbin/getty -L"
# define GETTY_BUSYBOX		/* Tell tty.c about the getty argument order */
# define BAUDRATE		115200
#else /* Debian/Ubuntu based distributions */
# define SETUP_DEVFS		"/sbin/udevd --daemon"
# define GETTY			"/sbin/getty -8"
# define GETTY_AGETTY		/* Tell tty.c about the getty argument order */
# define BAUDRATE		38400
#endif

/* If the user configures us to not know about any getty use the system
 * defined /bin/sh (or similar) as fallback for TTYs. */
#ifndef FALLBACK_SHELL
# define FALLBACK_SHELL		_PATH_BSHELL
#endif

#define CMD_SIZE                256
#define LINE_SIZE               1024
#define BUF_SIZE                4096

/* We reuse the INIT_CMD_ for the new initctl tool, but telinit only
 * supports changing runlevel and reloading the configuration. */
#define INIT_SOCKET             _PATH_VARRUN "finit.sock"
#define INIT_MAGIC              0x03091969
#define INIT_CMD_RUNLVL         1
#define INIT_CMD_DEBUG          2    /* Toggle Finit debug */
#define INIT_CMD_RELOAD         3    /* Reload *.conf in /etc/finit.d/ */
#define INIT_CMD_START_SVC      4
#define INIT_CMD_STOP_SVC       5
#define INIT_CMD_RELOAD_SVC     6    /* SIGHUP service */
#define INIT_CMD_RESTART_SVC    7    /* STOP + START service */
#define INIT_CMD_QUERY_INETD    8
#define INIT_CMD_NACK           254
#define INIT_CMD_ACK            255

struct init_request {
	int	magic;		/* Magic number			*/
	int	cmd;		/* What kind of request		*/
	int	runlevel;	/* Runlevel to change to	*/
	int	sleeptime;	/* Time between TERM and KILL	*/
	char	data[368];
};

extern int    debug;
extern int    quiet;
extern int    verbose;
extern int    runlevel;
extern int    cfglevel;
extern int    prevlevel;
extern char  *rcsd;
extern char  *sdown;
extern char  *network;
extern char  *hostname;
extern char  *username;
extern char  *runparts;
extern char  *console;
extern char  *__progname;

#endif /* FINIT_H_ */

/**
 * Local Variables:
 *  version-control: t
 *  indent-tabs-mode: t
 *  c-file-style: "linux"
 * End:
 */
