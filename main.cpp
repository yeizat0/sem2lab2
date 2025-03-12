#include <iostream>
#include <fstream>
#include <cstring>
#include <filesystem>
#include <vector>
#include "array_list.h"
#include "linked_list.h"
#include "main.h"


bool Condition1(const int element, const int n) {
    if (element <= n) {
        return true;
    }
    return false;
}

bool Condition2(const int element, const int n) {
    if ((element * element) * 2 < n) {
        return true;
    }
    return false;
}


void UseLinkedList() {
    QueueLinkedList queue = {};
    const std::string filename = "../numbers1.txt";
    std::ifstream ifs_numbers(filename);
    if (!ifs_numbers.is_open()) {
        std::cout << "Could not open file: " << filename << std::endl;
        return;
    }

    std::string number_str;
    while (std::getline(ifs_numbers, number_str, ' ')) {
        int number = std::stoi(number_str);
        QueueLinkedListPush(&queue, number);
    }

    const std::string filename2 = "../numbers2.txt";
    std::ifstream ifs_numbers2(filename2);
    if (!ifs_numbers2.is_open()) {
        std::cout << "Could not open file: " << filename2 << std::endl;
        return;
    }

    QueueLinkedList queue2 = {};
    std::string number_str2;
    while (std::getline(ifs_numbers2, number_str2, ' ')) {
        int number = std::stoi(number_str2);
        QueueLinkedListPush(&queue2, number);
    }
    QueueLinkedList merged_list = QueueLinkedListMerge(queue2, queue, Condition1, 100);
    std::cout << "Linked list\n";

    ListPrint(merged_list.list);

    QueueLinkedListWriteBinary(merged_list, "../numbers");
    QueueLinkedList new_list = {};
    QueueReadBinary(nullptr,&new_list, "../numbers.ll");
    std::cout << "Linked list From Binary\n";
    ListPrint(new_list.list);

}

void UseArrayList() {
    QueueArrayList queue = QueueArrayListNew();
    const std::string filename = "../numbers1.txt";
    std::ifstream ifs_numbers(filename);
    if (!ifs_numbers.is_open()) {
        std::cout << "Could not open file: " << filename << std::endl;
        return;
    }

    std::string number_str;
    while (std::getline(ifs_numbers, number_str, ' ')) {
        int number = std::stoi(number_str);
        QueueArrayListPushBack(&queue, number);
    }


    const std::string filename2 = "../numbers2.txt";
    std::ifstream ifs_numbers2(filename2);
    if (!ifs_numbers2.is_open()) {
        std::cout << "Could not open file: " << filename2 << std::endl;
        return;
    }

    QueueArrayList queue2 = QueueArrayListNew();
    std::string number_str2;
    while (std::getline(ifs_numbers2, number_str2, ' ')) {
        int number = std::stoi(number_str2);
        QueueArrayListPushBack(&queue2, number);
    }
    QueueArrayList merged_list = QueueArrayListMerge(queue2, queue, Condition2, 100);
    std::cout << "Array list \n";

    QueueArrayListPrint(merged_list);

    QueueArrayListWriteBinary(merged_list, "../numbers");
    QueueArrayList new_list = {};
    QueueReadBinary(&new_list, nullptr, "../numbers.arr");
    std::cout << "Array from binary \n";
    QueueArrayListPrint(new_list);
}

void QueueWriteBinary(const QueueArrayList &queue, const std::string& filename) {
    std::ofstream fs(filename, std::ios::out | std::ios::binary);
    if (!fs.is_open()) {
        std::cout << "Could not open file: " << filename << std::endl;
        std::exit(EXIT_FAILURE);
    }
    fs.write(reinterpret_cast<char *>(queue.data), queue.size * 4);
}

bool QueueReadBinary(QueueArrayList *array_list, QueueLinkedList *linked_list, const std::string& filename) {
    std::filesystem::path file_path = filename;
    if (file_path.extension() == ".arr" && array_list != nullptr) {
        std::ifstream fs(filename, std::ios::in | std::ios::binary);
        if (!fs.is_open()) {
            std::cout << "Could not open file: " << filename << std::endl;
            std::exit(EXIT_FAILURE);
        }
        std::ifstream file(filename, std::ios::in | std::ios::binary | std::ios::ate);
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);

        std::vector<char> buffer(size);
        file.read(buffer.data(), size);
        *array_list = QueueArrayListWithCapacity(size / 4);
        std::memcpy(array_list->data, buffer.data(), buffer.size());
        array_list->size = size / 4;
        return true;
    }
    if (file_path.extension() == ".ll" && linked_list != nullptr) {
        std::ifstream fs(filename, std::ios::in | std::ios::binary);
        if (!fs.is_open()) {
            std::cout << "Could not open file: " << filename << std::endl;
            std::exit(EXIT_FAILURE);
        }

        std::ifstream file(filename, std::ios::in | std::ios::binary | std::ios::ate);
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);

        std::vector<char> buffer(size);
        file.read(buffer.data(), size);
        QueueArrayList temp_array_list = QueueArrayListWithCapacity(size / 4);
        std::memcpy(temp_array_list.data, buffer.data(), buffer.size());
        temp_array_list.size = size / 4;

        for (size_t i = 0; i < temp_array_list.size; i++) {
            QueueLinkedListPush(linked_list, temp_array_list.data[i]);
        }
    }
    return false;
}

int main() {
    UseArrayList();
    UseLinkedList();
    return 0;
}
