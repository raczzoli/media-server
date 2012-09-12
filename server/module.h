#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <dlfcn.h>
#include "mediad.h"
#include "core.h"
#include "util.h"


typedef struct
{
	char *name;
	void *handle;
} module_t;

int module_load();
int module_unload();
int module_reload();
