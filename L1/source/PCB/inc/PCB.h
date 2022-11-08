#ifndef MY_PCB
#define MY_PCB

#define QTAILADD(pcb, queue, queue_tail)\
if(queue_tail == NULL){                \
    pcb->next = NULL, queue = pcb, queue_tail = pcb;     \
}else{                                 \
    pcb->next = NULL, queue_tail->next = pcb, queue_tail = pcb;\
}

#define QHEADPOP(pcb, queue, queue_tail){ \
    queue=queue->next;       \
    if(queue==NULL) queue_tail=NULL; \
}

#define QANYPOP(pcb, prePcb, queue, queue_tail) \
if(pcb==queue) QHEADPOP(pcb, queue, queue_tail) \
else { \
    prePcb->next=pcb->next; \
    if(queue_tail==pcb) queue_tail=prePcb; \
}

#define QHEADADD(pcb, queue, queue_tail) { \
    if(queue == NULL) pcb->next =NULL, queue=pcb, queue_tail=pcb; \
    else pcb->next = queue, queue=pcb; \
}

extern int PCB_NUM;

enum {
    P_ROUNDROBIN,
    P_HRRF,
    P_FCFS
};

enum {
    P_RUNNING = 100,
    P_READY,
    P_FINISH
}; 

typedef struct PCB{
    char name[32]; // 进程名
    int artime; //到达时间
    int remaining_time; //剩余执行时间
    int running_time; // 总执行时间
    int start_time; // 开始执行时间
    int finish_time; // 完成时间
    int wait_time; // 等待时间
    int status; // 进程状态
    struct PCB* next; //队列指针
}PCB, *PPCB;

extern PPCB pcb_run;
extern PPCB pcb_ready;
extern PPCB pcb_finish;
extern PPCB pcb_run_tail;
extern PPCB pcb_ready_tail;
extern PPCB pcb_finish_tail;
extern int test;

extern int pcb_init(PPCB* pcb, const char* name, int artime, int running);

extern int pcb_add(PPCB pcb);

extern int pcb_destory();

#endif