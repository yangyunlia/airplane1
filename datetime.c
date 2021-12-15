//
// Created by 11130 on 2021/12/14.
//

#include "datetime.h"

#include<string.h>
#include<stdlib.h>
#include "datetime.h"


//参数是日期字符串，日期只有年月日
datetime* parseDate(char *date) {
    datetime* d = malloc(sizeof(datetime));
    d->hour = 0;
    d->minute = 0;
    char *s = strtok(date, "/");
    d->day = atoi(s);
    s = strtok(NULL, "/");
    d->month = atoi(s);
    s = strtok(NULL, "/");
    d->year = atoi(s);
    return d;
}

//参数是日期时间字符串，日期时间只有年月日小时分组
datetime* parseDateTime(char date[]) {
    char *dateStr = strtok(date," ");
    char *timeStr = strtok(NULL, " ");
    datetime* dT = parseDate(dateStr);
    char *s = strtok(timeStr, ":");
    dT->hour = atoi(s);
    s = strtok(NULL, "/");
    dT->minute = atoi(s);
    return dT;
}

datetime* dec(datetime *a, datetime *b) {
    datetime *t = malloc(sizeof(datetime));
    t->hour = a->hour-b->hour;
    t->minute = a->minute - b->minute;
    t->year = a->year - b->year;

}


int compareDateTime(datetime* t0, datetime* t1){
    if(t0->year > t1->year) {
        return 1;
    } else if(t0->year < t1->year) {
        return -1;
    }

    if(t0->month > t1->month) {
        return 1;
    } else if(t0->month < t1->month) {
        return -1;
    }

    if(t0->day > t1->day) {
        return 1;
    } else if(t0->day < t1->day) {
        return -1;
    }

    if(t0->hour > t1->hour) {
        return 1;
    } else if(t0->hour < t1->hour) {
        return -1;
    }

    if(t0->minute > t1->minute) {
        return 1;
    } else if(t0->minute < t1->minute) {
        return -1;
    }
    return 0;
}

