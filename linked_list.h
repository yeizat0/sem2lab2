//
// Created by lzluk on 08/03/2025.
//

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

struct Node {
    int number;
    Node *prev;
    Node *next;
};

struct LinkedList {
    Node *head;
    Node *tail;
    size_t size;
};

Node *ListGetAt(const LinkedList &list, size_t index);

void ListPrint(const LinkedList &list);

void ListPopBack(LinkedList *list);

void ListPopFront(LinkedList *list);

void ListDeleteAt(LinkedList *list, size_t index);

void ListPushFront(LinkedList *list, int number);

void ListPushBack(LinkedList *list, int number);

void ListInsertAt(LinkedList *list, int number, size_t index);

void ListWriteFile(const LinkedList &list, const std::string &filename);

LinkedList ListReadFile(const std::string &filename);

void ListDelete(LinkedList *list);

struct QueueLinkedList {
    LinkedList list;
};

void QueueLinkedListPush(QueueLinkedList *queue, int number);

int QueueLinkedListPeekEnd(const QueueLinkedList &queue);

void QueueLinkedListPop(QueueLinkedList *queue);

int QueueLinkedListPeekFront(const QueueLinkedList &queue);

LinkedList LinkedListMerge(LinkedList left, LinkedList right);

QueueLinkedList QueueLinkedListMerge(QueueLinkedList left_queue, QueueLinkedList right_queue,
                                     bool (*filter)(int element, int n), int n);
void QueueLinkedListWriteBinary(QueueLinkedList queue_list, std::string filename);

#endif //LINKED_LIST_H
