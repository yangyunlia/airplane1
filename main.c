#include <stdio.h>
#include <string.h>
#include "airplane.h"

void printfAirport(struct airport *p) {
    printf("%d ", p->airportId);
}

int main() {
    struct airport *head = parserAirplaneInfo("E:/cProject/airplane1/data.csv");
    dfs(head, printfAirport);
    printf("\n");
    bfs(head, printfAirport);
}
