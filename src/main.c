
/*
Copyright (C) 2022 Valasiadis Fotios
Copyright (C) 2022 Alexios Zavras
SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "config.h"

#include "compat.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <unistd.h>

#include "record.h"

void run_and_record_fnames(char **av, char **envp);

static void
print_usage(const char *progname)
{
    fprintf(stderr, "Usage: %s [-o outfile] command [args...]\n", progname);
    fprintf(stderr, "\nRecord build process interactions to RDF Turtle format.\n");
    fprintf(stderr, "\nOptions:\n");
    fprintf(stderr, "  -o outfile   Output file (default: build-recorder.out)\n");
    fprintf(stderr, "  --help       Show this help message\n");
    fprintf(stderr, "  --version    Show version information\n");
}

static void
print_version(void)
{
    printf("build-recorder %s\n", PACKAGE_VERSION);
    printf("Copyright (C) 2022-2023 Alexios Zavras, Fotios Valasiadis\n");
    printf("License: LGPL-2.1-or-later\n");
}

int
main(int argc, char **argv, char **envp)
{
    if (argc < 2) {
	print_usage(argv[0]);
	exit(EX_USAGE);
    }

    if (!strcmp(argv[1], "--help") || !strcmp(argv[1], "-h")) {
	print_usage(argv[0]);
	exit(EXIT_SUCCESS);
    }

    if (!strcmp(argv[1], "--version") || !strcmp(argv[1], "-V")) {
	print_version();
	exit(EXIT_SUCCESS);
    }

    char *output_fname = "build-recorder.out";

    if (!strcmp(argv[1], "-o")) {
	if (argc < 4) {
	    fprintf(stderr, "Error: -o requires an output filename and a command\n");
	    print_usage(argv[0]);
	    exit(EX_USAGE);
	}
	output_fname = argv[2];
	argv += 3;
    } else {
	argv += 1;
    }

    if (*argv == NULL) {
	fprintf(stderr, "Error: missing command to record\n");
	print_usage(argv[-1]);
	exit(EX_USAGE);
    }

    record_start(output_fname);
    run_and_record_fnames(argv, envp);
    record_end();

    exit(EXIT_SUCCESS);
}
