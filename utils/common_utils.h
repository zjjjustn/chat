#pragma once
#include<pthread.h>
#include<stdio.h>

void start_detach_thread(pthread_t *thread, void *start_function, void*arg);
