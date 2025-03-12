//
// Created by lzluk on 12/03/2025.
//

#ifndef MAIN_H
#define MAIN_H
#include <string>
#include "linked_list.h"
#include "array_list.h"
void QueueWriteBinary(const QueueArrayList &queue, const std::string& filename);
bool QueueReadBinary(QueueArrayList *array_list, QueueLinkedList *linked_list, const std::string& filename);
#endif //MAIN_H
