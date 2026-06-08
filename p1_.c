#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int pid, at, bt, ct, wt, tat;
    struct Node *next;
};

struct Node *head = NULL;

struct Node* createNode(int pid, int at, int bt) {
    struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
    newnode->pid = pid;
    newnode->at = at;
    newnode->bt = bt;
    newnode->ct = newnode->wt = newnode->tat = 0;
    newnode->next = NULL;
    return newnode;
}

void insert(int pid, int at, int bt) {
    struct Node* newnode = createNode(pid, at, bt);
    if (head == NULL) {
        head = newnode;
    } else {
        struct Node* temp = head;
        while (temp->next != NULL) temp = temp->next;
        temp->next = newnode;
    }
}

void bubbleSort() {
    if (head == NULL) return;
    bool swapped;
    struct Node* ptr;
    struct Node* lptr = NULL;

    do {
        swapped = false;
        ptr = head;
        while (ptr->next != lptr) {
            if (ptr->at > ptr->next->at) {
                // Swap pid, at, bt
                int temp_pid = ptr->pid, temp_at = ptr->at, temp_bt = ptr->bt;
                ptr->pid = ptr->next->pid;
                ptr->at = ptr->next->at;
                ptr->bt = ptr->next->bt;
                ptr->next->pid = temp_pid;
                ptr->next->at = temp_at;
                ptr->next->bt = temp_bt;
                swapped = true;
            }
            ptr = ptr->next;
        }
        lptr = ptr;
    } while (swapped);
}

void fcfs() {
    int t = 0;
    struct Node* temp = head;

    while (temp != NULL) {
        if (t < temp->at) t = temp->at;
        temp->wt = t - temp->at;
        temp->ct = t + temp->bt;
        temp->tat = temp->bt + temp->wt;
        t += temp->bt;
        temp = temp->next;
    }

    printf("PID\tAT\tBT\tWT\tTAT\tCT\n");
    struct Node* temp2 = head;
    float awt = 0.0, atat = 0.0; 
    while (temp2 != NULL) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", temp2->pid, temp2->at, temp2->bt,
               temp2->wt, temp2->tat, temp2->ct);
        awt += temp2->wt;
        atat += temp2->tat;
        temp2 = temp2->next;
    }

    printf("Average WT: %.2f\n", awt/n);
    printf("Average TAT: %.2f\n", atat/n);
}

int main() {
    insert(1, 0, 7);
    insert(2, 8, 3);
    insert(3, 3, 4);
    insert(4, 5, 6);
    bubbleSort();
    fcfs();
    return 0;
}
