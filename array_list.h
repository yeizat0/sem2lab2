//
// Created by lzluk on 08/03/2025.
//

#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

struct QueueArrayList {
    int *data;
    size_t size;
    size_t capacity;
};

int QueueArrayListPopFront(QueueArrayList *list);

void QueueArrayListPushBack(QueueArrayList *list, int number);

QueueArrayList QueueArrayListNew();

void QueueArrayListDelete(QueueArrayList *list);

QueueArrayList QueueArrayListWithCapacity(size_t capacity);

void QueueArrayListPrint(const QueueArrayList &list);

QueueArrayList QueueArrayListMerge(QueueArrayList left, QueueArrayList right);

void QueueArrayListWriteBinary(QueueArrayList queue, std::string filename);

#endif //ARRAY_LIST_H
