#include <stdarg.h>
#include "Util.h"

void *xmalloc(size_t size)
{
	void *ptr;

	ptr = malloc(size);
	if (ptr == NULL) {
		pr_err("out of memory, need %lu bytes", (unsigned long)size);
		exit(1);
	}

	return ptr;
}

int verbose = 0;

void pr_info(const char *fmt, ...) 
{
	if (!verbose)
		return;

	va_list ap;
	va_start(ap, fmt);
	pr_do(stdout, "info", fmt, ap);
	va_end(ap);
}

void pr_warn(const char *fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	pr_do(stderr, "warn", fmt, ap);
	va_end(ap);
}

void pr_err(const char *fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	pr_do(stderr, "error", fmt, ap);
	va_end(ap);
}

static void pr_do(FILE *stream,
	const char *label,
	const char *fmt,
	va_list ap) {
	char fmtbuf[1024];
	vsnprintf(fmtbuf, sizeof(fmtbuf), fmt, ap);
	fprintf(stream, "%s:%s: %s\n", "server", label, fmtbuf);
}
