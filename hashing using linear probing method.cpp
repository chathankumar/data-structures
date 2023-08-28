#include <stdio.h>

#define SIZE 10

struct HashTable {
    int key;
    int value;
};

void insert(struct HashTable table[], int key, int value) {
    int index = key % SIZE;
    int i = 0;

    while (table[index].key != -1) {
        index = (index + 1) % SIZE;
        i++;

        if (i == SIZE) {
            printf("Hash table is full\n");
            return;
        }
    }

    table[index].key = key;
    table[index].value = value;
}

void display(struct HashTable table[]) {
    for (int i = 0; i < SIZE; i++) {
        if (table[i].key != -1) {
            printf("Key: %d, Value: %d\n", table[i].key, table[i].value);
        }
    }
}

int main() {
    struct HashTable table[SIZE];

    for (int i = 0; i < SIZE; i++) {
        table[i].key = -1;
    }

    insert(table, 5, 10);
    insert(table, 15, 20);
    insert(table, 25, 30);

    display(table);

    return 0;
}
