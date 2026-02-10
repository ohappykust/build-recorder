/*
Copyright (C) 2024
SPDX-License-Identifier: LGPL-2.1-or-later
*/

#ifndef PID_HASH_H
#define PID_HASH_H

#include <sys/types.h>

#define PID_HASH_SIZE 256

typedef struct pid_hash_entry {
    pid_t pid;
    int pinfo_idx;
    struct pid_hash_entry *next;
} PID_HASH_ENTRY;

typedef struct {
    PID_HASH_ENTRY *buckets[PID_HASH_SIZE];
} PID_HASH_TABLE;

void pid_hash_init(PID_HASH_TABLE *ht);
void pid_hash_insert(PID_HASH_TABLE *ht, pid_t pid, int pinfo_idx);
int pid_hash_find(PID_HASH_TABLE *ht, pid_t pid);
void pid_hash_remove(PID_HASH_TABLE *ht, pid_t pid);
void pid_hash_free(PID_HASH_TABLE *ht);

#endif /* PID_HASH_H */
