#include "config.h"

static config_entry_t **config_entries 	= NULL;
static int num_entries					= 0;

int config_load(const char *file_path)
{

	FILE *fp 			= fopen(file_path, "r");
	int num_lines	 	= 0;
	
	char line[CONFIG_MAX_LINE_LENGTH];
	char *name			= NULL;
	char *value			= NULL;
	int name_length		= 0;
	int value_length	= 0;
	
	config_entry_t *entry = NULL;
	
	if (fp == NULL)
	{
		log_error("Error loading config.h! No such file.");
		return -1;
	}

	while (fgets(line, CONFIG_MAX_LINE_LENGTH, fp) != NULL)
	{
		if (line[0] != '#' && line[0] != '\n') //comment or newline
		{
			name 	= strtok(line, "=");
			value 	= strtok(NULL, "=");
			
			if (name != NULL && value != NULL)
			{
				num_entries++;
				config_entries 	= util_alloc(config_entries, num_entries * sizeof(*entry));
				if (config_entries != NULL)
				{
					entry = malloc(sizeof(*entry));
					if (entry != NULL)
					{
						name_length		= strlen(name) + 1;
						value_length	= strlen(value) + 1;
						
						entry->name 	= malloc(name_length);
						entry->value 	= malloc(value_length);
						
						memcpy(entry->name, name, name_length);
						memcpy(entry->value, value, value_length);
						
						config_entries[num_entries-1] = entry;
					}
				}
				else
				{
					log_error("Error allocating memory for new config entry!");
					num_entries--;
					break;
				}
			}
			else
			{
				log_error("%s%d%s\n", "Parse error in config.h at line: ", num_lines, ". Syntax should be name=value.");
				break;
			}
			
			name 	= NULL;
			value 	= NULL;
		}
		num_lines++;
	}
	
	fclose(fp);
	return 0;
}


void *config_get_entry_value(const char *name)
{
	if (config_entries != NULL)
	{
		int i = 0;
		for (i=0;i<num_entries;i++)
		{
			if (config_entries[i] != NULL && config_entries[i]->name != NULL && strcmp(config_entries[i]->name, name) == 0)
			{
				return config_entries[i]->value;
			}
		}
	}
	
	return NULL;
}


int config_free_entries()
{
	if (config_entries != NULL)
	{
		int i = 0;
		for (i=0;i<num_entries;i++)
		{
			if (config_entries[i] != NULL)
			{
				free(config_entries[i]->name);
				free(config_entries[i]->value);
				free(config_entries[i]);
			}
		}
		
		free(config_entries);
		config_entries 	= NULL;
	}
	num_entries	= 0;
	
	return 0;

}
