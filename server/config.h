#include <stdlib.h>
#include "core.h"
#include "util.h"

#define CONFIG_MAX_LINE_LENGTH 	256

typedef struct
{
	char *name;
	char *value;
} config_entry_t;

int config_load(const char *file_path);
void *config_get_entry_value(const char *name);
int config_free_entries();