#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <dlfcn.h>
#include "core.h"
#include "util.h"


typedef struct
{
	char *name;
	void *handle;
} module_t;

int module_load(const char *modules_path);
int module_reload(const char *modules_path);
int module_unload();
