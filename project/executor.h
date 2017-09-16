//
// Created by michal on 09.09.17.
//

#ifndef PROJECT_EXECUTOR_H
#define PROJECT_EXECUTOR_H

#include <vector>
#include <string>
#include "instruction.h"
#include "memory.h"

class Executor {

public:
    int find_instruction();

    void execute_instruction();

    void find_argument();

    void find_const_value();

    int get_actual_bit();

    void set_actual_bit(int current_bit);

    void reset();

    explicit Executor(std::vector<char> &buffer, std::vector<std::shared_ptr<VMRegister>> &vm_registers, Memory &memory)
            : buffer_ref(buffer),
              vm_registers(vm_registers), memory(memory) {}

private:
    int actual_byte = 0;
    int actual_bit = 0;
    Instruction instruction;
    std::vector<std::string> parameters;
    std::vector<char> &buffer_ref;
    std::vector<std::shared_ptr<VMRegister>> &vm_registers;
    Memory &memory;

    int read_bit();
};


#endif //PROJECT_EXECUTOR_H
