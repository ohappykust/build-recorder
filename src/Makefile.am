# Copyright (C) 2023 Alexios Zavras
# Copyright (C) 2023 Fotios Valasiadis
# SPDX-License-Identifier: LGPL-2.1-or-later

bin_PROGRAMS = $(top_builddir)/build-recorder

__top_builddir__build_recorder_SOURCES = \
	hash.c \
	main.c \
	pid_hash.c \
	record.c \
	schema.c \
	tracer.c \
	$(EMPTY)

noinst_HEADERS = hash.h pid_hash.h record.h types.h

EXTRA_DIST = schema.c

SCHEMA = ../doc/build-recorder-schema.ttl

pkgdatadir = $(datadir)/build-recorder
pkgdata_DATA = $(SCHEMA)

if HAVE_XXD
schema.c: $(SCHEMA)
	sed '/^#/d' $^ | $(XXD) -i -n schema > $@
endif
