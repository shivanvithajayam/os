#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

// Structure to hold all data for Banker's Algorithm
typedef struct {
    int n; // number of processes
    int m; // number of resources
    int allocation[MAX_PROCESSES][MAX_RESOURCES];
    int max[MAX_PROCESSES][MAX_RESOURCES];
    int need[MAX_PROCESSES][MAX_RESOURCES];
    int available[MAX_RESOURCES];
} BankerSystem;

// Calculate Need matrix
void calculateNeed(BankerSystem *sys) {
    for (int i = 0; i < sys->n; i++)
        for (int j = 0; j < sys->m; j++)
            sys->need[i][j] = sys->max[i][j] - sys->allocation[i][j];
}

// Safety check
bool isSafe(BankerSystem *sys, int safeSeq[]) {
    bool finish[MAX_PROCESSES] = {false};
    int work[MAX_RESOURCES];
    for (int i = 0; i < sys->m; i++)
        work[i] = sys->available[i];

    int count = 0;
    while (count < sys->n) {
        bool found = false;
        for (int i = 0; i < sys->n; i++) {
            if (!finish[i]) {
                bool canFinish = true;
                for (int j = 0; j < sys->m; j++) {
                    if (sys->need[i][j] > work[j]) {
                        canFinish = false;
                        break;
                    }
                }
                if (canFinish) {
                    for (int k = 0; k < sys->m; k++)
                        work[k] += sys->allocation[i][k];
                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) break;
    }

    for (int i = 0; i < sys->n; i++) {
        if (!finish[i]) return false;
    }
    return true;
}

// Handle a new request
bool requestResources(BankerSystem *sys, int process, int request[], int safeSeq[]) {
    // Condition 1: Request <= Need
    for (int j = 0; j < sys->m; j++) {
        if (request[j] > sys->need[process][j]) {
            printf("Error: Process has exceeded its maximum claim.\n");
            return false;
        }
    }

    // Condition 2: Request <= Available
    for (int j = 0; j < sys->m; j++) {
        if (request[j] > sys->available[j]) {
            printf("Resources not available. Process must wait.\n");
            return false;
        }
    }

    // Pretend allocation
    for (int j = 0; j < sys->m; j++) {
        sys->available[j] -= request[j];
        sys->allocation[process][j] += request[j];
        sys->need[process][j] -= request[j];
    }

    // Check safety
    if (isSafe(sys, safeSeq)) {
        printf("Request granted. System remains in safe state.\n");
        printf("Safe sequence after granting request: ");
        for (int i = 0; i < sys->n; i++) {
            printf("P%d", safeSeq[i]);
            if (i != sys->n - 1) printf(" -> ");

        }
        printf("\n");
        return true;
    } else {
        // Rollback
        for (int j = 0; j < sys->m; j++) {
            sys->available[j] += request[j];
            sys->allocation[process][j] -= request[j];
            sys->need[process][j] += request[j];
        }
        printf("Request denied. System would enter unsafe state.\n");
        return false;
    }
}

int main() {
    BankerSystem sys;
    int safeSeq[MAX_PROCESSES];

    printf("Enter number of processes: ");
    scanf("%d", &sys.n);
    printf("Enter number of resources: ");
    scanf("%d", &sys.m);

    printf("Enter Allocation Matrix:\n");
    for (int i = 0; i < sys.n; i++)
        for (int j = 0; j < sys.m; j++)
            scanf("%d", &sys.allocation[i][j]);

    printf("Enter Maximum Demand Matrix:\n");
    for (int i = 0; i < sys.n; i++)
        for (int j = 0; j < sys.m; j++)
            scanf("%d", &sys.max[i][j]);

    printf("Enter Available Resources:\n");
    for (int i = 0; i < sys.m; i++)
        scanf("%d", &sys.available[i]);

    calculateNeed(&sys);

    if (isSafe(&sys, safeSeq)) {
        printf("\nSystem is in a safe state.\nSafe sequence is: ");
        for (int i = 0; i < sys.n; i++) {
            printf("P%d", safeSeq[i]);
            if (i != sys.n - 1) printf(" -> ");
        }
        printf("\n");
    } else {
        printf("\nSystem is NOT in a safe state.\n");
    }

    // Example: handle a new request
    int process;
    int request[MAX_RESOURCES];
    printf("\nEnter process number making request: ");
    scanf("%d", &process);
    printf("Enter request vector:\n");
    for (int j = 0; j < sys.m; j++)
        scanf("%d", &request[j]);

    requestResources(&sys, process, request, safeSeq);

    return 0;
}