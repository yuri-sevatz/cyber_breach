#pragma once

#include <cstddef>
#include <iomanip>
#include <ostream>
#include <vector>

#include <boost/io/ios_state.hpp>
#include <boost/multi_array.hpp>

using byte_type = unsigned char;

using matrix_type = boost::multi_array<byte_type, 2>;
using matrix_ref_type = boost::const_multi_array_ref<byte_type, 2>;
using matrix_length_type = std::size_t;

using sequence_type = std::vector<byte_type>;
using sequences_type = std::vector<sequence_type>;
using sequence_length_type = std::size_t;
using sequence_lengths_type = std::vector<sequence_length_type>;

using buffer_length_type = std::size_t;

inline std::ostream & operator<<(std::ostream & os, const sequences_type & sequences) {
    os << "{\n";
    for (std::size_t r = 0; r < sequences.size(); ++r) {
        os << "    {";
        for (std::size_t c = 0; c < sequences[r].size(); ++c) {
            os << "0x";
            boost::io::ios_base_all_saver _(os);
            os << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (int) sequences[r][c];
            if (c + 1 != sequences[r].size()) {
                os << ", ";
            }
        }
        if (r + 1 != sequences.size()) {
            os << "},\n";
        } else {
            os << "}\n";
        }
    }
    os << '}';
    return os;
}

inline std::ostream & operator<<(std::ostream & os, const matrix_type & matrix) {
    os << "{\n";
    for (std::size_t r = 0; r < matrix.shape()[0]; ++r) {
        os << "    ";
        for (std::size_t c = 0; c < matrix.shape()[1]; ++c) {
            os << "0x";
            boost::io::ios_base_all_saver _(os);
            os << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (int) matrix[r][c];
            if (c + 1 != matrix.shape()[1]) {
                os << ", ";
            } else {
                os << ',';
            }
        }
        os << '\n';
    }
    os << '}';
    return os;
}



