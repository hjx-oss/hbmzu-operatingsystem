#include <stdio.h>
#include "cpu.h"
#include "PCB.h"

#define CPU_NUM 1
int time = 0;

inline void checkReady() {
    if(pcb_ready == NULL) return;
    for(PPCB p = pcb_ready, p1 = pcb_ready; p != NULL; p=p->next) {
        if(p->artime == time) {
            QANYPOP(p, p1, pcb_ready, pcb_ready_tail);
            QTAILADD(p, pcb_run, pcb_run_tail);
            //printf("name:%s\n", p->name);
            p=p1->next;
            if(p == NULL) break;
        }
        p1 = p;
    }
}

void execute_FCFS() {
    if(pcb_run != NULL) {
        pcb_run->start_time = pcb_run->start_time == -1 ? time : pcb_run->start_time;
        if(!(-- pcb_run->remaining_time)) {
            PPCB tmp = pcb_run;
            tmp->finish_time = time + 1;
            QHEADPOP(tmp, pcb_run, pcb_run_tail);
            QTAILADD(tmp, pcb_finish, pcb_finish_tail);
        }
    }
}

void execute_ROUNDROBIN()
{
    //printf("time1:%d\n", time);
    if(pcb_run != NULL) {
        pcb_run->start_time = pcb_run->start_time == -1 ? time : pcb_run->start_time;
        if(!(-- pcb_run->remaining_time)) {
            PPCB tmp = pcb_run;
            tmp->finish_time = time + 1;
            QHEADPOP(tmp, pcb_run, pcb_run_tail);
            QTAILADD(tmp, pcb_finish, pcb_finish_tail);
        }
        if(pcb_run == NULL) return;
        PPCB tmp=pcb_run;
        QHEADPOP(tmp, pcb_run, pcb_run_tail);
        QTAILADD(tmp, pcb_run, pcb_run_tail);

    }
    //printf("time2: %d\n", time);
    // for(PPCB p = pcb_run; p != NULL; p = p->next){
    //     printf("name: %s  runingtime:%d\n", p->name, p->remaining_time);
    // }
}

void execute_HRRF() 
{
    //最高相应比优先需要循环一遍pcb_run队列
    PPCB maxResponse = NULL;
    PPCB maxResponsePre = NULL;
    double maxResponseNum = 0;
    // for(PPCB p = pcb_run; p != NULL; p = p->next) {
    //     printf("time:%d  name:%s\n", time, p->name);
    // }
    for(PPCB p = pcb_run, p1 = pcb_run; p != NULL; p = p->next) {
        double execute_time = p->running_time-p->remaining_time;
        
        double Response = 1.0 + (execute_time >= 0? (p->wait_time*1.0/execute_time) : execute_time);
        //printf("time:%d , name:%s , wait_time: %d , response:%f\n", time, p->name, p->wait_time, Response);
        if(Response > maxResponseNum) {
            maxResponseNum = Response;
            maxResponse = p;
            maxResponsePre = p1;
        }
        if(p!=NULL) {
            //printf("111\n");
            p->wait_time ++ ;
        }
        p1 = p;
    }
    if(maxResponse != NULL) {
        QANYPOP(maxResponse, maxResponsePre, pcb_run, pcb_run_tail);
        maxResponse->wait_time = 0;
        QHEADADD(maxResponse, pcb_run, pcb_run_tail);
    }
    if(pcb_run != NULL) {
        pcb_run->start_time = pcb_run->start_time == -1 ? time : pcb_run->start_time;
        if(!(-- pcb_run->remaining_time)) {
            PPCB head = pcb_run;
            head->finish_time = time + 1;
            QHEADPOP(head, pcb_run, pcb_run_tail);
            QTAILADD(head, pcb_finish, pcb_finish_tail);
        }
    }
}

void cpu_run(int mode){
    
    while(pcb_run != NULL || pcb_ready != NULL) {
        checkReady();
        switch(mode) {
            case P_ROUNDROBIN:
                execute_ROUNDROBIN();
            break;
            case P_HRRF:
                execute_HRRF();
            break;
            case P_FCFS:
                execute_FCFS();
            break;
            default:
            printf("file:%s line:%d unknown mode\n", __FILE__, __LINE__);
        }
        time ++;
    }

    
}