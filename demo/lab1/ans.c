#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node {
    int val;
    int password;
    struct node *next;
} circular_linked_list;


/**
 * Read the data from the file and store them in the circular linked list
 */
void ReadFromFile(circular_linked_list **head, int *m, int *n, const char FileName[]) {
    int cnt = 1;
    FILE *file = fopen(FileName, "r");
    assert(file != NULL); // check if the file exists
    fscanf(file, "%d", n);
    circular_linked_list *tail = NULL;
    for (int i = 0; i < *n; i++) {
        int x;
        fscanf(file, "%d", &x);
        circular_linked_list *new_node = \
            (circular_linked_list *) \
            malloc(sizeof(circular_linked_list));
        new_node->password = x;
        new_node->val = cnt++;
        new_node->next = NULL;
        if (*head == NULL) {
            *head = new_node;
            tail = new_node;
            tail->next = *head;
        } else {
            tail->next = new_node;
            tail = new_node;
            tail->next = *head;
        }
    }
    fscanf(file, "%d", m);
    fclose(file);
}

/**
 * Josephus problem
 */
void Josephus_2(circular_linked_list *head, int m, int n) {
    circular_linked_list *cur = head;
    while (cur != cur->next) {
        m = (m-1)%(n--)+1; // a small trick to reduce the time complexity
        if (m == 1) { // special case
            printf("%d ", cur->val);
            circular_linked_list *tmp = cur;
            m = tmp->password;
            cur = cur->next;
            circular_linked_list *tmp2 = cur;
            while (tmp2->next != tmp) {
                tmp2 = tmp2->next;
            }
            tmp2->next = cur;
            free(tmp);
            continue;
        }
        for (int i = 1; i < m-1; i++) {
            cur = cur->next;
        }
        printf("%d ", cur->next->val);
        circular_linked_list *tmp = cur->next;
        cur->next = tmp->next;
        cur = cur->next;
        m = tmp->password;
        free(tmp);
    }
    printf("%d\n", cur->val);
    free(cur);
}

int main() {
    circular_linked_list *head = NULL;
    int m;
    int n;
    ReadFromFile(&head, &m, &n, "./data/testcase.txt");
    Josephus_2(head, m, n);

    return 0;
}