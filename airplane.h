//
// Created by 11130 on 2021/12/14.
//

#ifndef AIRPLANE1_AIRPLANE_H
#define AIRPLANE1_AIRPLANE_H
#include "datetime.h"

//定义机场航班信息，这相当于是一个边，从出发机场到到达机场的一条边，出发机场喝到达机场就是点。
typedef struct airplaneInfo{
    int flightId;
    datetime* departureDate;
    char *intlOrDome;
    int flightNo;
    int departureAirport;
    int arrivalAirport;
    datetime* departureTime;
    datetime* arrivalTime;
    int airplaneId;
    int airplaneModel;
    int airFares;
    struct airport *departureAirportNode; //指向出发机场的airport指针
    struct airport *arrivalAirportNode; //指向出发机场的airport指针
    struct airplaneInfo* next; //信息列表的next指针
};

typedef struct airport {
    int airportId; //机场
    int traverCount; //遍历的时候设置，初始值为0，每遍历一次+1
    datetime *arrivalTime;//到达改机场的时间
    struct airplaneInfo * head;//以该机场为出发机场的所有机场信息组成的链表。
    struct airport *next;//指向下一个机场的指针
};

typedef struct map {
    int *array;
    int n;
};

struct airport* parserAirplaneInfo(char *fileName); //解析文件，生成邻接表
void dfs(struct airport *head, void (*p)(struct airport *node)); //深度优先搜索,p是一个函数指针，用于操作的时候处理node信息
void bfs(struct airport *head, void (*p)(struct airport *node)); //广度优先搜索
struct map * createMap(int n);
int getMapData(struct map *m,int i, int j);
void setMapData(struct map *m,int i, int j, int data);
void printfMap(struct map *m);
struct map * liantong(struct  airport *head);
#endif //AIRPLANE1_AIRPLANE_H
