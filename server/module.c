#include "module.h"

#define MODULES_PREFIX		"mod_"

static module_t **modules 	= NULL;
static int num_modules		= 0;


int module_load(const char *modules_path)
{
    DIR *dir            	= opendir(modules_path);
    struct dirent *ent  	= NULL;
    void *module_handle		= NULL;
	void (*module_init)() 	= NULL;
	
    if (dir == NULL)
    {
        log_error("%s","Error loading modules!\n");
        return -1;
    }

    char file_path[256];
    while ((ent = readdir(dir)) != NULL)
    {
		module_t *module = NULL;
		
        if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
            continue;
         
        sprintf(file_path, "%s%s/%s%s.so", modules_path, ent->d_name, MODULES_PREFIX, ent->d_name);
     
        if (!fs_file_exists(file_path))
		{
			log_error("%s%s%s","Error loading mod_", ent->d_name, ".so. No such file!\n");
			continue;
		}
		
		module_handle = dlopen(file_path, RTLD_LAZY);
		
		if (module_handle == NULL)
		{
			log_error("%s%s%s","Error loading mod_", ent->d_name, ".so. Invalid module!\n");
			continue;
		}
		
		module_init = dlsym(module_handle, "init");
		
		if (module_init == NULL)
		{
			log_error("%s%s%s","Module mod_", ent->d_name, ".so doesn`t have a init function. Ignoring...!\n");
			dlclose(module_handle);
			continue;
		}
		
		log_message("%s%s\n","Loading module: mod_", ent->d_name);
		
		num_modules++;
		modules = util_alloc(modules, num_modules * sizeof(*module));
		if (modules != NULL)
		{
			module_init();
			
			module = malloc(sizeof(*module));
			if (module != NULL)
			{
				module->name 	= malloc(strlen(ent->d_name) + strlen(MODULES_PREFIX) + 1);
				sprintf(module->name, "%s%s", MODULES_PREFIX, ent->d_name);
				module->handle 	= module_handle;
				
				modules[num_modules-1] = module;
				
				continue;
			}
		}

		log_message("%s%s\n", "Error allocating memory for module mod_", ent->d_name);
		dlclose(module_handle);
		num_modules--;
		
		return -1;
    }
	
	closedir(dir);
	
	return 0;
}


int module_unload()
{
	if (modules != NULL)
	{
		int i = 0;
		for (i=0;i<num_modules;i++)
		{
			if (modules[i] != NULL)
			{
				log_message("Unloading module: %s.\n", modules[i]->name);
				dlclose(modules[i]->handle);
				free(modules[i]->name);
				free(modules[i]);
			}
		}
		
		free(modules);
		modules 	= NULL;
	}
	num_modules	= 0;
	
	return 0;
}

int module_reload(const char *modules_path)
{
	if (module_unload() == 0)
	{
		return module_load(modules_path);
	}
	
	return -1;
}

