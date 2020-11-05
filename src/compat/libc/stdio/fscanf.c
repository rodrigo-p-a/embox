/**
 * @file
 *
 * @date Nov 3, 2020
 * @author Anton Bondarev
 */

#include <stdio.h>

#include <fs/file_operation.h>

FILE *__fscanf_file;
extern int stdio_scan(const char **in, const char *fmt, va_list args);
int fscanf(FILE *stream, const char *format, ...) {
	va_list args;
	int rv;

	__fscanf_file = stream;

	va_start(args, format);
	rv = stdio_scan((const char **)1, format, args);
	va_end(args);

	return rv;
}
