#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpu.h"
#include "PCB.h"

int main() {
    //char PATH[128];
    char* PATH = getenv("L1PATH");
    freopen(strcat(PATH,"/Input"), "r", stdin);
    printf("1. RR\n2. HRRF\n3. P_FCFS\n:");
    int op;
    scanf("%d", &op);
    if(op < 1 || op > 3) return -1;
    scanf("%d", &PCB_NUM);
    printf("PCBNUM:%d\n", PCB_NUM);
    for(int i = 0; i < PCB_NUM; i ++ ) {
        char name[32];
        int ar, run;
        scanf("%s %d %d", name, &ar, &run);
        PPCB pcb = NULL;
        pcb_init(&pcb, name, ar, run);
        pcb_add(pcb);
    }

    for(PPCB p = pcb_run; p != NULL; p=p->next) {
        printf("name: %s, start time: %d , finish time: %d artime:%d runingtime:%d\n", p->name, p->start_time, p->finish_time, p->artime, p->remaining_time);
       
    }
    printf("cpu start \n");
    //printf("op:%d\n", op-1);
    cpu_run(op - 1);
    PPCB p = pcb_finish;
    for(; p!=NULL; p=p->next ) {
        printf("name: %s , start time: %d , finish time: %d turnaoundtime: %d , turnaroundtimewithright : %lf\n", 
                p->name, p->start_time, p->finish_time, p->finish_time-p->artime, (p->finish_time-p->artime)*1.0/p->running_time);

    }
    pcb_destory();
    return 0;
}