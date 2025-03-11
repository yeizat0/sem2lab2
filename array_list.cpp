//
// Created by lzluk on 08/03/2025.
//

#include <iostream>
#include <fstream>
#include "array_list.h"
void QueueWriteBinary(QueueArrayList queue, std::string filename);
#include <cstring>

QueueArrayList QueueArrayListWithCapacity(size_t capacity) {
    if (capacity == 0) {
        capacity = 4;
    }
    size_t size = 0;
    int *data = new int[capacity * sizeof(int)];
    return {
        .data = data,
        .size = size,
        .capacity = capacity,
    };
}

void QueueArrayListDelete(QueueArrayList *list) {
    delete[] list->data;
    list->data = nullptr;
    list->size = 0;
    list->capacity = 0;
}

QueueArrayList QueueArrayListNew() {
    return QueueArrayListWithCapacity(4);
}

void QueueArrayListPushBack(QueueArrayList *list, const int number) {
    if (list->size < list->capacity) {
        list->data[list->size] = number;
        list->size += 1;
        return;
    }

    size_t new_capacity = list->capacity * 2;
    if (new_capacity == 0) {
        new_capacity = 4;
    }
    int *new_data = new int[new_capacity * sizeof(number)];
    for (int i = 0; i < list->size; i++) {
        new_data[i] = list->data[i];
    }
    delete [] list->data;
    list->data = new_data;
    list->capacity = new_capacity;

    list->data[list->size] = number;
    list->size += 1;
}

int QueueArrayListPopFront(QueueArrayList *list) {
    if (!list || list->size == 0) {
        std::exit(EXIT_FAILURE);
    }
    const int number = list->data[0];
    for (size_t i = 0; i < list->size + 1; i++) {
        list->data[i] = list->data[i + 1];
    }
    list->size -= 1;
    return number;
}

void QueueArrayListPrint(const QueueArrayList &list) {
    for (int i = 0; i < list.size; i++) {
        std::cout << list.data[i] << ' ';
    }
    std::cout << std::endl;
}

QueueArrayList QueueArrayListMerge(QueueArrayList left, QueueArrayList right) {
    QueueArrayList list = QueueArrayListWithCapacity(left.capacity + right.capacity);
    int k = 0;
    int i = 0;
    for (; i < left.size; i++) {
        for (; k < right.size; k++) {
            if (left.data[i] < right.data[k]) {
                break;
            }
            QueueArrayListPushBack(&list, right.data[k]);
        }
        QueueArrayListPushBack(&list, left.data[i]);
    }
    if (i >= left.size) {
        while (k < right.size) {
            QueueArrayListPushBack(&list, right.data[k]);
            k++;
        }
    }

    return list;
}

void QueueArrayListWriteBinary(QueueArrayList queue, std::string filename) {
    filename += ".arr";
    QueueWriteBinary(queue, filename);
}


