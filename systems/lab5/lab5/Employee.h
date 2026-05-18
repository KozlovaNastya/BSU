#pragma once

struct employee {
    int num;
    char name[10];
    double hours;
};

enum Command {
    CMD_READ = 1,
    CMD_WRITE = 2,
    CMD_SAVE = 3,
    CMD_RELEASE = 4,
    CMD_EXIT = 5
};

struct PipePacket {
    Command cmd;
    int empId;
    employee empData;
    bool success;
};
