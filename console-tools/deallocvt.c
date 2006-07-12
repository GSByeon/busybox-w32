/* vi: set sw=4 ts=4: */
/*
 * Disallocate virtual terminal(s)
 *
 * Copyright (C) 2003 by Tito Ragusa <farmatito@tiscali.it>
 * Copyright (C) 1999-2004 by Erik Andersen <andersen@codepoet.org>
 *
 * Licensed under GPLv2 or later, see file LICENSE in this tarball for details.
 */

/* no options, no getopt */

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include "busybox.h"

/* From <linux/vt.h> */
enum { VT_DISALLOCATE = 0x5608 }; /* free memory associated to vt */

int deallocvt_main(int argc, char *argv[])
{
	/* num = 0 deallocate all unused consoles */
	int num = 0;

	switch (argc) {
		case 2:
			if ((num = bb_xgetlarg(argv[1], 10, 0, INT_MAX)) == 0) {
				bb_error_msg_and_die("0: illegal VT number");
			}
		/* Fallthrough */
		case 1:
			break;
		default:
			bb_show_usage();
	}

	if (-1 == ioctl(get_console_fd(), VT_DISALLOCATE, num)) {
		bb_perror_msg_and_die("VT_DISALLOCATE");
	}
	return EXIT_SUCCESS;
}
