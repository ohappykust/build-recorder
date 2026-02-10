/*
Copyright (C) 2024
SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "config.h"

#include <stdlib.h>
#include <errno.h>
#include "compat.h"

#include "pid_hash.h"

static unsigned int
hash_pid(pid_t pid)
{
    return ((unsigned int)pid) % PID_HASH_SIZE;
}

void
pid_hash_init(PID_HASH_TABLE *ht)
{
    for (int i = 0; i < PID_HASH_SIZE; i++) {
	ht->buckets[i] = NULL;
    }
}

void
pid_hash_insert(PID_HASH_TABLE *ht, pid_t pid, int pinfo_idx)
{
    unsigned int idx = hash_pid(pid);
    PID_HASH_ENTRY *entry = malloc(sizeof(PID_HASH_ENTRY));

    if (entry == NULL) {
	error(EXIT_FAILURE, errno, "allocating pid hash entry");
    }

    entry->pid = pid;
    entry->pinfo_idx = pinfo_idx;
    entry->next = ht->buckets[idx];
    ht->buckets[idx] = entry;
}

int
pid_hash_find(PID_HASH_TABLE *ht, pid_t pid)
{
    unsigned int idx = hash_pid(pid);
    PID_HASH_ENTRY *entry = ht->buckets[idx];

    while (entry != NULL) {
	if (entry->pid == pid) {
	    return entry->pinfo_idx;
	}
	entry = entry->next;
    }

    return -1;
}

void
pid_hash_remove(PID_HASH_TABLE *ht, pid_t pid)
{
    unsigned int idx = hash_pid(pid);
    PID_HASH_ENTRY *entry = ht->buckets[idx];
    PID_HASH_ENTRY *prev = NULL;

    while (entry != NULL) {
	if (entry->pid == pid) {
	    if (prev == NULL) {
		ht->buckets[idx] = entry->next;
	    } else {
		prev->next = entry->next;
	    }
	    free(entry);
	    return;
	}
	prev = entry;
	entry = entry->next;
    }
}

void
pid_hash_free(PID_HASH_TABLE *ht)
{
    for (int i = 0; i < PID_HASH_SIZE; i++) {
	PID_HASH_ENTRY *entry = ht->buckets[i];
	while (entry != NULL) {
	    PID_HASH_ENTRY *next = entry->next;
	    free(entry);
	    entry = next;
	}
	ht->buckets[i] = NULL;
    }
}
