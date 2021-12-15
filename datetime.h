//
// Created by 11130 on 2021/12/14.
//

#ifndef AIRPLANE1_DATETIME_H
#define AIRPLANE1_DATETIME_H
typedef struct {
    int year;
    int month;
    int day;
    int hour;
    int minute;
}datetime;
datetime* parseDate(char *);
datetime* parseDateTime(char *);
datetime* dec(datetime *a, datetime *b);// 时间a减去时间b
int compareDateTime(datetime* t0, datetime* t1);
#endif //AIRPLANE1_DATETIME_H
