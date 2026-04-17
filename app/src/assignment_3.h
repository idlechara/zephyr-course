#ifndef ASSIGNMENT_3_H
#define ASSIGNMENT_3_H

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <zephyr/kernel.h>

/* Assignment 3 - Heartbeat LED Thread */

/* Thread function for the heartbeat LED */
void heartbeat_thread_fn(void *arg1, void *arg2, void *arg3);

/* External reference to the heartbeat thread */
extern struct k_thread heartbeat_tid;

#ifdef __cplusplus
}
#endif

#endif /* ASSIGNMENT_3_H */