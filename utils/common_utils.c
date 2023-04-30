#include"common_utils.h"
int start_detach_thread(pthread_t *thread, void *start_function, void*arg)
{
    pthread_attr_t attr;
    pthread_t thread_t;
    int ret = 0;
    if(thread == NULL)
    {
        thread = &thread_t;
    }
    pthread_attr_init(&attr);

    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

    ret = pthread_create(thread, &attr,(void*(*)(void*))start_function,arg);

    if(ret < 0)
    {
        printf("pthread create error!\n");
        goto err;
    }

    pthread_detach(thread_t);

err:
    pthread_attr_destroy(&attr);

    return 1;
}