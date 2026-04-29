#pragma once
#include <fstream>
#include <cstring>

struct Message {
    char text[20];
};

struct FileHeader {
    int head;
    int tail;
    int maxRecords;
};

inline void writeToQueue(std::fstream& f, const Message& msg) {
    FileHeader header;
    f.seekg(0, std::ios::beg);
    f.read((char*)&header, sizeof(FileHeader));

    f.seekp(sizeof(FileHeader) + (header.tail * sizeof(Message)), std::ios::beg);
    f.write((char*)&msg, sizeof(Message));

    header.tail = (header.tail + 1) % header.maxRecords;
    f.seekp(0, std::ios::beg);
    f.write((char*)&header, sizeof(FileHeader));
}

inline Message readFromQueue(std::fstream& f) {
    FileHeader header;
    f.seekg(0, std::ios::beg);
    f.read((char*)&header, sizeof(FileHeader));

    f.seekg(sizeof(FileHeader) + (header.head * sizeof(Message)), std::ios::beg);
    Message msg;
    f.read((char*)&msg, sizeof(Message));

    header.head = (header.head + 1) % header.maxRecords;
    f.seekp(0, std::ios::beg);
    f.write((char*)&header, sizeof(FileHeader));

    return msg;
}
