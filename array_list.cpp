//
// Created by lzluk on 08/03/2025.
//

#include <iostream>
#include <fstream>
#include "array_list.h"
#include "main.h"
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

QueueArrayList QueueArrayListMerge(const QueueArrayList &left, const QueueArrayList &right, bool (*filter)(int element, int n),
                                   const int n) {
    QueueArrayList temp_left = QueueArrayListWithCapacity(left.size);
    for (size_t i = 0; i < left.size; i++) {
        if (filter(left.data[i], n)) {
            continue;
        }
        QueueArrayListPushBack(&temp_left, left.data[i]);
    }
    QueueArrayList temp_right = QueueArrayListWithCapacity(right.size);
    for (size_t i = 0; i < right.size; i++) {
        if (filter(right.data[i], n)) {
            continue;
        }
        QueueArrayListPushBack(&temp_right, right.data[i]);
    }

    QueueArrayList list = QueueArrayListWithCapacity(temp_left.size + temp_right.size);
    int k = 0;
    int i = 0;
    for (; i < temp_left.size; i++) {
        for (; k < temp_right.size; k++) {
            if (temp_left.data[i] < temp_right.data[k]) {
                break;
            }
            QueueArrayListPushBack(&list, temp_right.data[k]);
        }
        QueueArrayListPushBack(&list, temp_left.data[i]);
    }
    if (i >= temp_left.size) {
        while (k < temp_right.size) {
            QueueArrayListPushBack(&list, temp_right.data[k]);
            k++;
        }
    }
    QueueArrayListDelete(&temp_left);
    QueueArrayListDelete(&temp_right);
    return list;
}

void QueueArrayListWriteBinary(QueueArrayList queue, std::string filename) {
    filename += ".arr";
    QueueWriteBinary(queue, filename);
}
