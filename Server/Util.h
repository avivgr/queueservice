#ifndef __UTIL_H_
#define __UTIL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef WIN32
#include <unistd.h>  /* getopt */
#endif

#if defined(NDEBUG)
# define ASSERT(exp)
# define CHECK(exp)   do { if (!(exp)) abort(); } while (0)
# define DEBUG_CHECKS (0)
#else
# define ASSERT(exp)  assert(exp)
# define CHECK(exp)   assert(exp)
# define DEBUG_CHECKS (1)
#endif

#define UNREACHABLE() CHECK(!"Unreachable code reached.")

#define CONTAINER_OF(ptr, type, field)                                        \
  ((type *) ((char *) (ptr) - ((char *) &((type *) 0)->field)))

void *xmalloc(size_t size);

extern int verbose;
void pr_info(const char *fmt, ...);
void pr_warn(const char *fmt, ...);
void pr_err(const char *fmt, ...);
static void pr_do(FILE *stream,
	const char *label,
	const char *fmt,
	va_list ap);

#endif
