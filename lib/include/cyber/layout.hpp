#pragma once

#include <opencv2/opencv.hpp>

// Padded matrix width minimum
static const cv::Point matrix_border_topcenter(489,336);

// Matrix cell size
static const cv::Size matrix_cell_size(64, 64);
static const cv::Size matrix_cell_padding(0, 0); // TODO: Padding -- adding this might improve OCR
static const cv::Size matrix_margin_topleft(125, 10);
static const cv::Size matrix_margin_bottomright(125, 10);

static const cv::Size matrix_margin_size(matrix_margin_topleft + matrix_margin_bottomright);

// Padded buffer width minimum
static const int buffer_width_min = 28;

// Buffer border
static const int buffer_border_top = 177;
static const int buffer_border_matrix_left_offset = 47;

// Matrix cell size
static const cv::Size buffer_cell_size(32, 32);
static const cv::Size buffer_cell_padding(10, 0);
static const cv::Size buffer_cell_margin_topleft(19, 19);
static const cv::Size buffer_cell_margin_bottomright(19, 19);
static const cv::Size buffer_cell_margin_size(buffer_cell_margin_topleft + buffer_cell_margin_bottomright);

// Sequences border
static const int sequences_border_matrix_left_offset = 46;
static const int sequences_border_top = 332;

static const cv::Size sequence_cell_size(32, 68); // NOTE: The height is larger to account for padding reset bug (below)
static const cv::Size sequence_cell_padding(10, 0); // NOTE: The height resets its padding to 0 after moving the mouse
static const cv::Size sequences_margin_topleft(20, 10);
static const cv::Size sequences_margin_bottomright(12, 22);
static const cv::Size sequences_margin_size(sequences_margin_topleft + sequences_margin_bottomright);

