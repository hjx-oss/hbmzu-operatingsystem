#include "PCB.h"
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <stdlib.h>

PPCB pcb_run         = NULL;
PPCB pcb_finish      = NULL;
PPCB pcb_ready       = NULL;
PPCB pcb_run_tail    = NULL;
PPCB pcb_ready_tail  = NULL;
PPCB pcb_finish_tail = NULL;
//int test = 100;

int PCB_NUM = 0;

int pcb_init(PPCB* pcb, const char* name, int artime, int running) 
{
    if(*pcb == NULL) {
        *pcb = (PPCB)malloc(sizeof(PCB));
        if(*pcb == NULL) return -1;
    }
    memset(*pcb, 0, sizeof(PCB));
    strcpy((*pcb)->name, name);
    (*pcb)->artime = artime;
    (*pcb)->remaining_time = running;
    (*pcb)->running_time = running;
    (*pcb)->start_time = -1;
    (*pcb)->wait_time = 0;
    return 0;
}



int pcb_add(PPCB pcb){
    if(pcb == NULL) {
        printf("file:%s line:%d, pcb is null\n", __FILE__, __LINE__);
        return -1;
    }
    QTAILADD(pcb, pcb_ready, pcb_ready_tail);
    return 0;
}

int pcb_destory() {
    PPCB p;
    for(p=pcb_run; p!= NULL;){
        pcb_run=p->next;
        free(p);
        p=pcb_run;
    }
    for(p=pcb_ready; p!= NULL;){
        pcb_ready=p->next;
        free(p);
        p=pcb_run;
    }
    for(p=pcb_finish; p!= NULL;){
        pcb_finish=p->next;
        free(p);
        p=pcb_run;
    }
    return 0;
}