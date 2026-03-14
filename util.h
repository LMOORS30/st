/* See LICENSE for license details. */

#define MIN(a, b)		((a) < (b) ? (a) : (b))
#define MAX(a, b)		((a) < (b) ? (b) : (a))
#define LEN(a)			(sizeof(a) / sizeof(a)[0])
#define BETWEEN(x, a, b)	((a) <= (x) && (x) <= (b))

void die(const char *, ...);
void *xcalloc(size_t, size_t);
void *xmalloc(size_t);
void *xrealloc(void *, size_t);
char *xstrdup(const char *);
