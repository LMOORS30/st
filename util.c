/* See LICENSE for license details. */
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

void
die(const char *fmt, ...)
{
	va_list ap;
	int saved_errno;

	saved_errno = errno;

	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);

	if (fmt[0] && fmt[strlen(fmt)-1] == ':')
		fprintf(stderr, " %s", strerror(saved_errno));
	fputc('\n', stderr);

	exit(1);
}

void *
xcalloc(size_t num, size_t size)
{
	void *p;

	if (!(p = calloc(num, size)))
		die("calloc:");

	return p;
}

void *
xmalloc(size_t len)
{
	void *p;

	if (!(p = malloc(len)))
		die("malloc:");

	return p;
}

void *
xrealloc(void *p, size_t len)
{
	if (!(p = realloc(p, len)))
		die("realloc:");

	return p;
}

char *
xstrdup(const char *s)
{
	char *p;

	if (!(p = strdup(s)))
		die("strdup:");

	return p;
}
