#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "linked_list.h"

#include "array_list.h"
void QueueWriteBinary(QueueArrayList queue, std::string filename);

Node *NodeNew(const int number) {
    return new Node{.number = number, .prev = nullptr, .next = nullptr};
}


void ListInsertAt(LinkedList *list, const int number, const size_t index) {
    if (!list) {
        return;
    }
    Node *node = NodeNew(number);
    if (!list->head || !list->tail) {
        list->head = node;
        list->tail = node;
        list->size++;
        return;
    }
    if (index == 0) {
        list->head->prev = node;
        node->next = list->head;
        list->head = node;
        list->size++;
        return;
    }
    if (index >= list->size) {
        list->tail->next = node;
        node->prev = list->tail;
        list->tail = node;
        list->size++;
        return;
    }

    Node *curr = ListGetAt(*list, index);
    node->next = curr;
    node->prev = curr->prev;
    curr->prev->next = node;
    curr->prev = node;
    list->size++;
}

void ListInsertBefore(LinkedList *list, const int number, Node *curr) {
    if (!list || !curr) {
        return;
    }
    Node *node = NodeNew(number);
    if (!list->head || !list->tail) {
        std::exit(EXIT_FAILURE);
        // return;
    }
    if (curr == list->head) {
        list->head->prev = node;
        node->next = list->head;
        list->head = node;
        list->size++;
        return;
    }
    if (curr == list->tail) {
        list->tail->next = node;
        node->prev = list->tail;
        list->tail = node;
        list->size++;
        return;
    }

    node->next = curr;
    node->prev = curr->prev;
    curr->prev->next = node;
    curr->prev = node;
    list->size++;
}

void ListPushBack(LinkedList *list, const int number) {
    ListInsertAt(list, number, list->size);
}

void ListPushFront(LinkedList *list, const int number) {
    ListInsertAt(list, number, 0);
}

void ListDeleteAt(LinkedList *list, const size_t index) {
    if (!list) {
        return;
    }
    if (!list->head || !list->tail || list->size == 0) {
        return;
    }
    if (list->size == 1) {
        delete list->head;
        list->head = nullptr;
        list->tail = nullptr;
        list->size = 0;
        return;
    }
    if (index == 0) {
        list->head = list->head->next;
        delete list->head->prev;
        list->head->prev = nullptr;
        list->size--;
        return;
    }
    if (index >= list->size) {
        list->tail = list->tail->prev;
        delete list->tail->next;
        list->tail->next = nullptr;
        list->size--;
        return;
    }
    Node *curr = ListGetAt(*list, index);
    Node *prev = curr->prev;
    Node *next = curr->next;
    delete curr;
    prev->next = next;
    next->prev = prev;
    list->size--;
}

void ListPopFront(LinkedList *list) {
    ListDeleteAt(list, 0);
}

void ListPopBack(LinkedList *list) {
    ListDeleteAt(list, list->size);
}

void ListPrint(const LinkedList &list) {
    for (const Node *current = list.head; current; current = current->next) {
        std::cout << current->number << " ";
    }
    std::cout << std::endl;
}


Node *ListGetAt(const LinkedList &list, const size_t index) {
    if (index >= list.size) {
        return nullptr;
    }
    Node *current = list.head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    return current;
}

void ListWriteFile(const LinkedList &list, const std::string &filename) {
    std::ofstream numbers(filename);
    for (const Node *current = list.head; current; current = current->next) {
    }
}

LinkedList ListReadFile(const std::string &filename) {
    LinkedList list = {};
    std::ifstream numbers(filename);
    if (!numbers.is_open()) {
        std::cout << "Could not open file: " << filename << std::endl;
        return list;
    }
    std::string name;
    while (std::getline(numbers, name)) {
        int number = {};

        ListPushBack(&list, number);
    }
    return list;
}


LinkedList ListRead() {
    std::cout << "Enter name of file:" << std::endl;
    std::string filename;
    std::cin >> filename;
    return ListReadFile(filename);
}

void QueueLinkedListPush(QueueLinkedList *queue, int number) {
    ListPushBack(&queue->list, number);
}


void QueueLinkedListPop(QueueLinkedList *queue) {
    ListPopFront(&queue->list);
}

int QueueLinkedListPeekEnd(const QueueLinkedList &queue) {
    if (!queue.list.head) {
        std::exit(EXIT_FAILURE);
    }
    return queue.list.tail->number;
}

int QueueLinkedListPeekFront(const QueueLinkedList &queue) {
    if (!queue.list.head) {
        std::exit(EXIT_FAILURE);
    }
    return queue.list.head->number;
}

LinkedList LinkedListMerge(LinkedList left, LinkedList right) {
    LinkedList list = {};
    const Node *left_current = left.head;
    const Node *right_current = right.head;
    for (; left_current; left_current = left_current->next) {
        while (right_current) {
            if (left_current->number < right_current->number) {
                break;
            }
            ListPushBack(&list, right_current->number);
            right_current = right_current->next;
        }
        ListPushBack(&list, left_current->number);
    }
    if (!left_current) {
        while (right_current) {
            ListPushBack(&list, right_current->number);
            right_current = right_current->next;
        }
    }

    return list;
}

QueueLinkedList QueueLinkedListMerge(QueueLinkedList left_queue, QueueLinkedList right_queue,
                                     bool (*filter)(int element, int n), int n) {
    LinkedList left_list = {};
    for (const Node *current = left_queue.list.head; current != nullptr; current = current->next) {
        if (filter(current->number, n)) {
            continue;
        }
        ListPushBack(&left_list, current->number);
    }
    LinkedList right_list = {};
    for (const Node *current = right_queue.list.head; current != nullptr; current = current->next) {
        if (filter(current->number, n)) {
            continue;
        }
        ListPushBack(&right_list, current->number);
    }
    const LinkedList result = LinkedListMerge(left_list, right_list);
    return {.list = result};
}

void QueueLinkedListWriteBinary(QueueLinkedList queue_list, std::string filename) {
    filename += ".ll";
    QueueArrayList queue_array = QueueArrayListWithCapacity(queue_list.list.size);
    for (const Node *current = queue_list.list.head; current; current = current->next) {
        QueueArrayListPushBack(&queue_array, current->number);
    }
    QueueWriteBinary(queue_array, filename);
}
