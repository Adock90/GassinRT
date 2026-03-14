#include <v8.h>
#include <iostream>

#include <GassinRT/GassinRT.hpp>

void Help(bool helpRequired)
{
	if (helpRequired)
	{
		printf("[GassinRT] Help\n");
	}
	printf("GassinRT:\n"
		"\tAuthor: Adam.Croft (@adock90)\n"
		"\tWritten in: C++, JS\n"
		"GassinRT [<file>] [<options>]:\n"
		"\t[<file>]: File Target\n"
		"\t[<options>] OPTIONAL: just for --h\n"
	      );
	std::exit(1);
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		Help(true);
	}
	for (int i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], "--h") < 1)
		{
			Help(false);
		}
	}

	GassinRT::GassinRTObj GInst;
	GInst.GassinRTInitV8ANDVM(argc, argv);
	GInst.GassinRTCreateJSInstance(argv[1]);
	GInst.GassinRTShutdown();
	return 0;
}
