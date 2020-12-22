#pragma once

#include <opencv2/opencv.hpp>

#include <cyber/common.hpp>

struct parse_input {
    cv::Mat image;
    matrix_length_type matrix_length;
    sequence_lengths_type sequence_lengths;
};

struct parse_output {
    matrix_type matrix;
    sequences_type sequences;
};

inline bool operator==(const parse_output & lhs, const parse_output & rhs) {
    return lhs.matrix == rhs.matrix && lhs.sequences == rhs.sequences;
}

inline bool operator!=(const parse_output & lhs, const parse_output & rhs) {
    return lhs.matrix != rhs.matrix || lhs.sequences != rhs.sequences;
}

parse_output parse(const parse_input & input);
