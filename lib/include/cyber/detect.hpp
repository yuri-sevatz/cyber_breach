#pragma once

#include <optional>

#include <opencv2/opencv.hpp>

#include <cyber/common.hpp>

struct detected_type {
    std::optional<matrix_length_type> matrix_length;
    std::optional<buffer_length_type> buffer_length;
    std::optional<sequence_lengths_type> sequence_lengths;
};

detected_type detect(const cv::Mat & image);

