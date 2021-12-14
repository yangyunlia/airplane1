//
// Created by 11130 on 2021/12/14.
//

#include <stdlib.h>
#include "queue.h"

struct queue * createQueue() {
    struct queue * head  = malloc(sizeof(struct queue));
    head->next = head;
    head->pre = head;
    return head;
}
struct airport *deQueue(struct queue *head) {
    struct airport *e = head->next->e;
    struct queue * p = head->next;
    p->next->pre = p->pre;
    p->pre->next = p->next;
    return e;
}
void enQueue(struct queue *head, struct airport *e) {
    struct queue *p = malloc(sizeof(struct queue));
    p->e = e;
    p->next = head;
    p->pre = head->pre;
    head->pre->next = p;
    head->pre = p;
}
int isEmpty(struct queue *head) {
    if(head->next == head) {
        return 1;
    }
    return 0;
}

int queueContain(struct queue *head, struct airport *e) {
    struct queue *p = head->next;
    while (p != head) {
        if(p->e == e) {
            return 1;
        }
    }
    return 0;
}