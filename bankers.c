#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int main() {
    int n, m;

    int allocation[MAX_PROCESSES][MAX_RESOURCES];
    int max[MAX_PROCESSES][MAX_RESOURCES];
    int need[MAX_PROCESSES][MAX_RESOURCES];

    int available[MAX_RESOURCES];
    int work[MAX_RESOURCES];

    int safeSeq[MAX_PROCESSES];
    bool finish[MAX_PROCESSES] = {false};

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    // Read Allocation Matrix
    printf("Enter Allocation Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &allocation[i][j]);

    // Read Maximum Matrix
    printf("Enter Maximum Demand Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    // Read Available Resources
    printf("Enter Available Resources:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &available[i]);

    // Need = Max - Allocation
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - allocation[i][j];

    // Initially Work = Available
    for (int i = 0; i < m; i++)
        work[i] = available[i];

    int count = 0;

    // Find Safe Sequence
    while (count < n) {

        bool found = false;

        // Check each process
        for (int i = 0; i < n; i++) {

            if (!finish[i]) {

                bool canFinish = true;

                // Check if Need <= Work
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canFinish = false;
                        break;
                    }
                }

                // Process can execute
                if (canFinish) {

                    // Release allocated resources
                    for (int k = 0; k < m; k++)
                        work[k] += allocation[i][k];

                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        // No process could execute
        if (!found)
            break;
    }

    // Check whether all processes finished
    bool safe = true;

    for (int i = 0; i < n; i++) {
        if (!finish[i]) {
            safe = false;
            break;
        }
    }

    // Display Result
    if (safe) {
        printf("\nSystem is in Safe State\n");
        printf("Safe Sequence: ");

        for (int i = 0; i < n; i++) {
            printf("P%d", safeSeq[i]);

            if (i != n - 1)
                printf(" -> ");
        }
    }
    else {
        printf("\nSystem is NOT in Safe State\n");
    }

    return 0;
}