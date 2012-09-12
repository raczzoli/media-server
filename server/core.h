#ifndef CORE_H_
#define CORE_H_

#include <stdio.h>
#include <stdarg.h>

/* log */
void log_message(const char *format, ...);
void log_error(const char *format, ...);

/* file system */
int fs_file_exists(const char *path);

#endif /* CORE_H_ */
