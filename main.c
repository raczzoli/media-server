#include "server/core.h"
#include "server/module.h"

int main()
{
	module_load();

	module_unload();
	
	return 0;
}
