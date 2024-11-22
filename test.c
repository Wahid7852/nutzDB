#include <stdio.h>

typedef struct {
    struct Node* next;
    int data;
} __attribute__((packed)) Node;

int main() {
    printf("Size of Node: %zu bytes\n", sizeof(Node));
    return 0;
}
