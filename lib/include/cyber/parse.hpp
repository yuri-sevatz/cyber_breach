#pragma once

#include <cyber/common.hpp>

struct parsed_type {
    matrix_type matrix;
    sequences_type sequences;
};

inline bool operator==(const parsed_type & lhs, const parsed_type & rhs) {
    return lhs.matrix == rhs.matrix && lhs.sequences == rhs.sequences;
}

inline bool operator!=(const parsed_type & lhs, const parsed_type & rhs) {
    return lhs.matrix != rhs.matrix || lhs.sequences != rhs.sequences;
}

parsed_type parse(cv::Mat image, matrix_length_type matrix_length, sequence_lengths_type sequence_lengths);
