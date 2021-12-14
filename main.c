#include <stdio.h>
#include <string.h>
#include "airplane.h"

void printfAirport(struct airport *p) {
    printf("%d ", p->airportId);
}

int main() {
    struct airport *head = parserAirplaneInfo("/Users/yangruiyuan/airplane1/data.csv");
}
