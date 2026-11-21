#include <stdio.h>

#define MAX_TIME 100

int minimum(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int capacity, rate, n, incoming[MAX_TIME];
    int stored = 0, tokens = 0;
    int i, sent, dropped;

    printf("Enter bucket capacity: ");
    if (scanf("%d", &capacity) != 1) return 1;

    printf("Enter output/token rate: ");
    if (scanf("%d", &rate) != 1) return 1;

    printf("Enter number of time units: ");
    if (scanf("%d", &n) != 1) return 1;

    if (capacity <= 0 || capacity > 100000 ||
        rate <= 0 || rate > 100000 ||
        n <= 0 || n > MAX_TIME) {
        printf("Invalid input values.\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        printf("Packets arriving at time %d: ", i + 1);

        if (scanf("%d", &incoming[i]) != 1 ||
            incoming[i] < 0 || incoming[i] > 100000) {
            printf("Invalid packet count.\n");
            return 1;
        }
    }

    // LEAKY BUCKET ALGORITHM
    printf("\n1. LEAKY BUCKET ALGORITHM\n");
    printf("Time  Incoming  Sent  Dropped  In Bucket\n");

    for (i = 0; i < n; i++) {
        stored += incoming[i];
        dropped = 0;

        if (stored > capacity) {
            dropped = stored - capacity;
            stored = capacity;
        }

        sent = minimum(stored, rate);
        stored -= sent;

        printf("%4d  %8d  %4d  %7d  %9d\n",
               i + 1, incoming[i], sent,
               dropped, stored);
    }

    while (stored > 0) {
        sent = minimum(stored, rate);
        stored -= sent;

        printf("Drain %8d  %4d  %7d  %9d\n",
               0, sent, 0, stored);
    }

    // TOKEN BUCKET ALGORITHM
    printf("\n2. TOKEN BUCKET ALGORITHM\n");
    printf("Time  Incoming  Sent  Dropped  Tokens Left\n");

    for (i = 0; i < n; i++) {
        tokens = minimum(capacity, tokens + rate);

        sent = minimum(incoming[i], tokens);
        dropped = incoming[i] - sent;
        tokens -= sent;

        printf("%4d  %8d  %4d  %7d  %11d\n",
               i + 1, incoming[i], sent,
               dropped, tokens);
    }

    return 0;
}
