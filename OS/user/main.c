#include "Cancer.h"
#include "thread.h"
#include "tick.h"
u32 stk1[512];
u32 stk2[512];
os_status task1(void * arg)
{
    DEBUG_PUTS("task1 starts\n");
    while(1)
    {
        DEBUG_PUTS("task1\n");
        DEBUG_PRINTF("tick:%ld\n",getPrivateTick());
        DelayThread(3000,OPT_DELAY_MS,THREAD_SELF);
    }
}

os_status task2(void * arg)
{
    DEBUG_PUTS("task2 starts\n");
    while(1)
    {
        DEBUG_PUTS("task2\n");
        DelayThread(3000,OPT_DELAY_MS,THREAD_SELF);
    }
}
int raise(int arg)
{
    return 0;
}
int main()
{
    struct ThreadObject tcb1;
    struct ThreadObject tcb2;
    Cancer_Init();
    CreateThraed(&tcb1,9,task1,stk1,512);
    CreateThraed(&tcb2,10,task2,stk2,512);
    Cancer_Start();
    //Hal_Init();
    //while(1);
    return 0;
}
