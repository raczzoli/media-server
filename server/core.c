#include "core.h"

static void log_print_time(FILE *fp);

/* LOG */
void log_message(const char *format, ...)
{
	log_print_time(stdout);
	fprintf(stdout, " [message] ");
	
	va_list args;
	va_start (args, format);
		vfprintf(stdout, format, args);
	va_end (args);
}

void log_error(const char *format, ...)
{
	log_print_time(stdout);
	fprintf(stdout, " [error] ");
	
	va_list args;
	va_start (args, format);
		vfprintf(stdout, format, args);
	va_end (args);
}

static void log_print_time(FILE *fp)
{
	char output[32];
	FILE *fpdate = popen("date", "r");
	int i 	= 0;
	int ch 	= 0;
	
	if (fpdate != NULL)
	{
		memset(output, 0, 32);
		
		while ((ch = fgetc(fpdate)) != EOF && i<32)
		{
			if (ch == '\n' || ch == '\r')
				break;
			
			output[i] = ch;
			i++;
		}
		
		fprintf(fp, "[%s]", output);
		pclose(fpdate);
	}
}


/* FILE SYSTEM */
int fs_file_exists(const char *path)
{
	FILE *fp = NULL;
	if ((fp = fopen(path, "r")) != NULL)
	{
		fclose(fp);
		return 1;
	}
	
	return 0;
}