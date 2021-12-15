//
// Created by 11130 on 2021/12/14.
//

#include "airplane.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
struct airplaneInfo* parserAirplaneStr(char *s) {
    struct airplaneInfo *info = malloc(sizeof(struct airplaneInfo));
    info->next = NULL;
    char *flightIdStr = strtok(s, ",");
    char *departureDateStr = strtok(NULL,",");
    char *initOrDomeStr = strtok(NULL, ",");
    char *flightNoStr = strtok(NULL, ",");
    char *departureAirportStr = strtok(NULL, ",");
    char *arrivalAirportStr = strtok(NULL, ",");
    char *departureTimeStr = strtok(NULL, ",");
    char *arrivalTimeStr = strtok(NULL, ",");
    char *airplaneIdStr = strtok(NULL, ",");
    char *airplaneModelStr = strtok(NULL, ",");
    char *airFaresStr = strtok(NULL, ",");
    info->flightId = atoi(flightIdStr);
    info->departureDate = parseDate(departureDateStr);
    info->intlOrDome = initOrDomeStr;
    info->flightNo = atoi(flightNoStr);
    info->departureAirport = atoi(departureAirportStr);
    info->arrivalAirport = atoi(arrivalAirportStr);
    info->departureTime = parseDateTime(departureTimeStr);
    info->arrivalTime = parseDateTime(arrivalTimeStr);
    info->airplaneId = atoi(airplaneIdStr);
    info->airplaneModel = atoi(airplaneModelStr);
    info->airFares = atoi(airFaresStr);
    return info;
}
struct airport* parserAirplaneInfo(char *filename) {
    FILE *file = fopen(filename, "r");
    struct airport *head = malloc(sizeof(struct airport));
    head->next = NULL;
    char s[10000];
    fgets(s, 10000, file);
    while (!feof(file)) {
        fgets(s, 10000, file);
        struct airplaneInfo *info = parserAirplaneStr(s);
        struct airport *p;
        p = head->next;
        while (p != NULL) {
            if(p->airportId == info->departureAirport) {
                break;
            }
            p = p->next;
        }

        //如果p为NULL说明这个机场的节点还没有创建
        if(p == NULL) {
            p = malloc(sizeof(struct airport));
            p->traverCount = 0;
            p->airportId = info->departureAirport; //设置机场的编号
            p->head = malloc(sizeof(struct airplaneInfo));//初始化机场信息指针的头节点
            p->head->next = NULL;
            //将p接到head后面
            p->next = head->next;
            head->next = p;
        }
        info->departureAirportNode = p;
        //将机场航班信息接到p.head上
        info->next = p->head->next;
        p->head->next = info;

        //设置info的到达节点指针
        p = head->next;
        while (p != NULL) {
            if(p->airportId == info->arrivalAirport) {
                break;
            }
            p = p->next;
        }

        //如果p为NULL说明这个机场的节点还没有创建
        if(p == NULL) {
            p = malloc(sizeof(struct airport));
            p->traverCount = 0;
            p->airportId = info->arrivalAirport; //设置机场的编号
            p->head = malloc(sizeof(struct airplaneInfo));//初始化机场信息指针的头节点
            p->head->next = NULL;
            //将p接到head后面
            p->next = head->next;
            head->next = p;
        }
        info->arrivalAirportNode = p;
    }
    return head;
}

void dfsImpl(struct airport *node, void (*p)(struct airport *node)) {
    p(node); //node被访问
    int count  = node->traverCount;
    node->traverCount++; //被遍历次数加1
    struct airplaneInfo *info = node->head->next; //边的链表
    while (info != NULL) {
        //等于count证明还没有被遍历，则遍历
        struct airport *arrivalAirport = info->arrivalAirportNode;
        if(arrivalAirport->traverCount == count && compareDateTime(node->arrivalTime, info->departureTime) <= 0) {
            arrivalAirport->arrivalTime = info->arrivalTime;
            dfsImpl(info->arrivalAirportNode, p);
        }
        info = info->next;
    }
}

void dfs(struct airport *head, void (*p)(struct airport *node)) {
    struct airport *n = head->next;
    if(n == NULL) {
        return;
    }
    int count  = n->traverCount;
    while (n != NULL) {
        //等于count证明还没有被遍历
        if(n->traverCount == count) {
            char s[] = {"0/0/0"};
            n->arrivalTime = parseDate(s);
            dfsImpl(n, p);
        }
        n = n->next;
    }
}

void bfsImpl(struct airport *node, void (*p)(struct airport *node)) {
    struct queue *q = createQueue();
    struct airport *e = node;
    p(e); //访问e
    int count = e->traverCount;
    e->traverCount++;
    enQueue(q, e);
    //队列非空
    while (isEmpty(q) == 0) {
        struct  airport * departureAirport = deQueue(q);
        struct airplaneInfo *info = e->head->next;
        while (info != NULL) {
            struct airport * arrivalPort = info->arrivalAirportNode;
            //如果路径的终点的遍历次数等于count，证明这个中的还没有被遍历
            //并判断出发机场的到达时间是否小于该航班的出发时间，小于才可以搭乘
            if(arrivalPort->traverCount == count && compareDateTime(departureAirport->arrivalTime, info->departureTime) <= 0) {
                p(arrivalPort);
                arrivalPort->arrivalTime = info->arrivalTime;
                arrivalPort->traverCount++;
                enQueue(q, arrivalPort);
            }
            info = info->next;
        }
    }
}

void bfs(struct airport *head, void (*p)(struct airport *node)) {
    struct airport *n = head->next;
    if(n == NULL) {
        return;
    }
    int count  = n->traverCount;
    while (n != NULL) {
        //等于count证明还没有被遍历
        if(n->traverCount == count) {
            char s[] = {"0/0/0"};
            n->arrivalTime = parseDate(s);//初始时间
            bfsImpl(n, p);
        }
        n = n->next;
    }
}

void liantongDfsImpl(struct airport *node, struct queue *q) {
    int count  = node->traverCount;
    node->traverCount++; //被遍历次数加1
    struct airplaneInfo *info = node->head->next; //边的链表
    while (info != NULL) {
        //等于count证明还没有被遍历，则遍历
        struct airport *arrivalAirport = info->arrivalAirportNode;
        if(arrivalAirport->traverCount == count && compareDateTime(node->arrivalTime, info->departureTime) <= 0) {
            arrivalAirport->arrivalTime = info->arrivalTime;
            liantongDfsImpl(info->arrivalAirportNode, q);
        }
        info = info->next;
    }
    enQueue(q, node);
}

void liantongDfs(struct airport *head, struct queue *q) {
    struct airport *n = head->next;
    if(n == NULL) {
        return;
    }
    int count  = n->traverCount;
    while (n != NULL) {
        //等于count证明还没有被遍历
        if(n->traverCount == count) {
            char s[] = {"0/0/0"};
            n->arrivalTime = parseDate(s);
            liantongDfsImpl(n, q);
        }
        n = n->next;
    }
}

struct map * createMap(int n) {
    struct map *m = malloc(sizeof(struct map));
    m->n = n;
    m->array = malloc(sizeof(int) * n * n);
    for(int i = 0; i < n*n; i++) {
        m->array[i] = 0;
    }
    return m;
}

int getMapData(struct map *m,int i, int j) {
    return m->array[i*m->n + j];
}
void setMapData(struct map *m,int i, int j, int data){
    m->array[i*m->n + j] = data;
}

void printfMap(struct map *m) {
    for(int i = 0; i < m->n; i++) {
        for(int j = 0; j < m->n; j++) {
            printf("%d ", getMapData(m, i, j));
        }
        printf("\n");
    }
}

struct map * liantong(struct  airport *head) {
    int i = 0;
    struct airport *p = head->next;
    while (p != NULL) {
        i++;
        p = p->next;
    }
    struct map *m = createMap(i);
    struct queue *q = createQueue();
    liantongDfs(head, q);
    struct queue *qN = createQueue();
    while (!isEmpty(q)) {
        struct airport *qAirport = deQueue(q);
        liantongDfsImpl(qAirport, qN);
        while (!isEmpty(qN)) {
            struct airport *qNAirport = deQueue(qN);
            qNAirport->traverCount--;
            setMapData(m, qAirport->airportId-1, qNAirport->airportId-1, 1);
            setMapData(m, qNAirport->airportId-1, qAirport->airportId-1, 1);
        }
    }
    return m;
}

//狄杰斯特拉算法
struct queue * minTime(struct  airport *head,struct  airport *a, struct airport *b) {
    int i = 0;
    struct airport *p = head->next;
    while (p != NULL) {
        i++;
        p = p->next;
    }
    datetime *
}
