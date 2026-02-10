/*
 * Copyright (C) 2022 Alexios Zavras
 * Copyright (C) 2022 Valasiadis Fotios
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */

#ifndef COMPAT_H
#define COMPAT_H

#include "config.h"

/* Handle ARG_MAX - use linux/limits.h if available, otherwise limits.h */
#ifdef HAVE_LINUX_LIMITS_H
#include <linux/limits.h>
#else
#include <limits.h>
#ifndef ARG_MAX
#define ARG_MAX 131072
#endif
#endif

#ifdef HAVE_ERROR_H
#include <error.h>
#else
/* Fallback for systems without error.h (e.g., musl libc) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>

static inline void error(int status, int errnum, const char *format, ...) {
    va_list ap;
    fprintf(stderr, "%s: ", "build-recorder");
    va_start(ap, format);
    vfprintf(stderr, format, ap);
    va_end(ap);
    if (errnum)
        fprintf(stderr, ": %s", strerror(errnum));
    fprintf(stderr, "\n");
    if (status)
        exit(status);
}
#endif

#endif /* COMPAT_H */
