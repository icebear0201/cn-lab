#include <stdio.h>

int main() {
    int n, w;
    int base = 0, expected = 0;
    int lost = 0, round = 1;

    printf("SLIDING WINDOW PROTOCOL\n");

    printf("Enter total number of frames: ");
    if (scanf("%d", &n) != 1) return 1;

    printf("Enter window size: ");
    if (scanf("%d", &w) != 1) return 1;

    if (n < 1 || n > 100 || w < 1 || w > n) {
        printf("Invalid frame count or window size.\n");
        return 1;
    }

    while (base < n) {
        int end = base + w - 1;

        if (end >= n)
            end = n - 1;

        printf("\nRound %d\n", round++);
        printf("Sender Window: %d to %d\n", base, end);

        for (int i = base; i <= end; i++) {
            printf("\nSending Frame %d\n", i);

            // Simulate loss of Frame 2 once
            if (i == 2 && !lost) {
                printf("Frame 2 LOST!\n");
                lost = 1;
                continue;
            }

            if (i == expected) {
                printf("Frame %d received successfully\n", i);
                printf("ACK %d received\n", i);
                expected++;
            } else {
                printf("Frame %d discarded (out of order)\n", i);
                printf("Duplicate ACK %d\n", expected - 1);
            }
        }

        base = expected;

        if (base < n && base <= end) {
            printf("\nTIMEOUT OCCURRED!\n");
            printf("Retransmitting from Frame %d\n", base);
        } else if (base < n) {
            printf("\nWindow slides to Frame %d\n", base);
        }
    }


    return 0;
}
