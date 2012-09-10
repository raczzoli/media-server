#include "core.h"

void log_message(const char *format, ...)
{
	va_list args;
	va_start (args, format);
		vfprintf(stdout, format, args);
	va_end (args);
}

void log_error(const char *format, ...)
{
	va_list args;
	va_start (args, format);
		vfprintf(stdout, format, args);
	va_end (args);
}

