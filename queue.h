//
// Created by 11130 on 2021/12/14.
//

#ifndef AIRPLANE1_QUEUE_H
#define AIRPLANE1_QUEUE_H
#include "airplane.h"
struct queue {
    struct airport * e;
    struct queue * next;
    struct queue * pre;
};
struct queue * createQueue(); //创建队列
struct airport *deQueue(struct queue *head); //出队
void enQueue(struct queue *head, struct airport *e); //入队
int isEmpty(struct queue *head); //判空
int queueContain(struct  queue *head, struct airport *e); //判断是否包含该元素，包含返回1，不包含0
#endif //AIRPLANE1_QUEUE_H
