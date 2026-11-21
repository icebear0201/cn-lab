#include <stdio.h>

#define MAX 10
#define INF 9999

int main(void) {
    int n, cost[MAX][MAX];
    int dist[MAX][MAX], nextHop[MAX][MAX];
    int i, j, k, changed;

    printf("DISTANCE VECTOR ROUTING ALGORITHM\n");
    printf("Enter number of routers: ");

    if (scanf("%d", &n) != 1 || n < 2 || n > MAX) {
        printf("Invalid number of routers.\n");
        return 1;
    }

    printf("Enter the cost matrix (9999 for no direct link):\n");

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (scanf("%d", &cost[i][j]) != 1 ||
                cost[i][j] < 0 || cost[i][j] > INF) {
                printf("Invalid cost.\n");
                return 1;
            }

            if (i == j)
                cost[i][j] = 0;

            dist[i][j] = cost[i][j];

            nextHop[i][j] =
                (cost[i][j] == INF) ? -1 : j;
        }
    }

    // Update distance vectors until convergence
    do {
        changed = 0;

        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                for (k = 0; k < n; k++) {
                    if (i == k || cost[i][k] == INF ||
                        dist[k][j] == INF)
                        continue;

                    if (cost[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = cost[i][k] + dist[k][j];
                        nextHop[i][j] = k;
                        changed = 1;
                    }
                }
            }
        }
    } while (changed);

    // Print routing tables
    printf("\nFinal Distance Vector Routing Tables:\n");

    for (i = 0; i < n; i++) {
        printf("\nRouter %d:\n", i);
        printf("Destination\tCost\tNext Hop\n");

        for (j = 0; j < n; j++) {
            if (dist[i][j] == INF)
                printf("%d\t\tINF\t-\n", j);
            else if (i == j)
                printf("%d\t\t%d\tSelf\n", j, dist[i][j]);
            else
                printf("%d\t\t%d\t%d\n",
                       j, dist[i][j], nextHop[i][j]);
        }
    }


    return 0;
}
