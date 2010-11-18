#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <getopt.h>
#include <string.h>

void invoke (char* str)
{	int fd = open ("/tmp/makesweavepipe", O_WRONLY);
	size_t length = strlen (str);
	write (fd, str, length);
	close (fd);
}

int main (int argc, char* argv [])
{	const char* const shortopt = "iqf:ct:";
	const struct option longopt [] =
	{	{"init", 0, NULL, 'i'},
		{"quit", 0, NULL, 'q'},
		{"file", 1, NULL, 'f'},
		{"clean", 0, NULL, 'c'},
		{"test", 1, NULL, 't'},
		{NULL, 0, NULL, 0}
	};
	FILE* Rinput;
	FILE* Poutput;
	FILE* statusf;
	char* str = argv [1];
	char cmd [500];
	char cmdj [500];
	int opt = getopt_long (argc, argv, shortopt, longopt, NULL);
	switch (opt)
	{	case 'i':
			//consider --quiet
			Rinput = popen ("R --vanilla", "w");
			fprintf (Rinput, "library (makesweave)\n");
			fprintf (Rinput, "options (error = function () NULL)\n");
			fflush (Rinput);
			while (1)
			{	Poutput = fopen ("/tmp/makesweavepipe", "r");
				fscanf (Poutput, "%s", cmd);
				fclose (Poutput);
				fprintf (Rinput, "%s\n", cmd);
				fflush (Rinput);
			}
		break;

		case 'q':
			invoke ("quit(\"no\")");
		break;

		case 'c':
			invoke ("rm(list=ls())");
		break;

		case 'f':
			sprintf (cmdj, "source(\"%s\")", optarg);
			invoke (cmd);
		break;

		case 't':
			printf ("test:\n%s\n", optarg);
		break;

		case -1:
			statusf = fopen ("/tmp/makesweavestatus", "w");
			fprintf (statusf, ".\n");
			fclose (statusf);
			sprintf (cmdj, "makesweave(\"%s\")", str);
			invoke (cmdj);
		break;
	}
	char status [1];
	status [0] = '.';
	struct timespec t;
	t.tv_sec = 0;
	t.tv_nsec = 50000;
	while (status [0] == '.')
	{	nanosleep (&t, &t);
		statusf = fopen ("/tmp/makesweavestatus", "r");
		fscanf (statusf, "%s", status);
		fclose (statusf);
	}
	if (status [0] == '1') return 1;
	else return 0;
}

