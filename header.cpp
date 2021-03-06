//
// Created by michal on 09.09.17.
//

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdio.h>
#include "header.h"

const char *magic_number = "ESET-VM2";

Header::Header() {
    magic[0] = '\0';
    code_size = 0;
    data_size = 0;
    initial_data_size = 0;
}

void Header::read_header(std::vector<char> &buffer) {

    std::vector<char> header(buffer.begin(), buffer.begin() + header_length_in_bytes);

    std::vector<char> header_magic_number(header.begin(), header.begin() + magic_number_length);
    verify(header_magic_number);
    for (int i = 0; i < header_magic_number.size(); i++) {
        magic[i] = header_magic_number[i];
    }

    std::vector<char> header_code_size(header.begin() + magic_number_length,
                                       header.begin() + magic_number_length + header_param_length);
    code_size = extract_uint_32_value(header_code_size);

    std::vector<char> header_data_size(header.begin() + magic_number_length + header_param_length,
                                       header.begin() + magic_number_length + 2 * header_param_length);
    data_size = extract_uint_32_value(header_data_size);

    std::vector<char> header_initial_data_size(header.begin() + magic_number_length + 2 * header_param_length,
                                               header.begin() + magic_number_length + 3 * header_param_length);
    initial_data_size = extract_uint_32_value(header_initial_data_size);
}

void Header::verify(std::vector<char> &buffer) {
    char *buffer_char = buffer.data();
    buffer_char[8] = '\0';
    if (strcmp(buffer_char, magic_number) != 0) {
        fprintf(stderr, "You did not provide EVM file.\n");
        exit(1);
    }
}

uint32_t Header::extract_uint_32_value(std::vector<char> &buffer) {
    char *buffer_char = buffer.data();
    buffer_char[4] = '\0';
    uint32_t int_value;
    int_value = (uint32_t) (buffer_char[3] << 24) | (buffer_char[2] << 16) | (buffer_char[1] << 8) | buffer_char[0];
    return int_value;
}

uint32_t Header::get_data_size() {
    return data_size;
}

int Header::get_size_of_file() {
    return sizeof(Header) + initial_data_size + code_size;
}

uint32_t Header::get_initial_data_size() {
    return initial_data_size;
}