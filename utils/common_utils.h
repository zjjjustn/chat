#pragma once
#include<pthread.h>
#include<stdio.h>

int start_detach_thread(pthread_t *thread, void *start_function, void*arg);
