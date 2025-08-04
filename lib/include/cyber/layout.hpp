#pragma once

#include <opencv2/opencv.hpp>

static const int scaling = 2;

// Padded matrix width minimum
static const cv::Point matrix_border_topcenter(489 * scaling,336 * scaling);

// Matrix cell size
static const cv::Size matrix_cell_size(64 * scaling, 64 * scaling);
static const cv::Size matrix_cell_padding(0 * scaling, 0 * scaling); // TODO: Padding -- adding this might improve OCR
static const cv::Size matrix_margin_topleft(125 * scaling, 10 * scaling);
static const cv::Size matrix_margin_bottomright(125 * scaling, 10 * scaling);

static const cv::Size matrix_margin_size(matrix_margin_topleft + matrix_margin_bottomright);

// Padded buffer width minimum
static const int buffer_width_min = 28 * scaling;

// Buffer border
static const int buffer_border_top = 177 * scaling;
static const int buffer_border_matrix_left_offset = 47 * scaling;

// Matrix cell size
static const cv::Size buffer_cell_size(32 * scaling, 32 * scaling);
static const cv::Size buffer_cell_padding(10 * scaling, 0 * scaling);
static const cv::Size buffer_cell_margin_topleft(19 * scaling, 19 * scaling);
static const cv::Size buffer_cell_margin_bottomright(19 * scaling, 19 * scaling);

static const cv::Size buffer_cell_margin_size(buffer_cell_margin_topleft + buffer_cell_margin_bottomright);

// Sequences border
static const int sequences_border_matrix_left_offset = 46 * scaling;
static const int sequences_border_top = 332 * scaling;

static const cv::Size sequence_cell_size(32 * scaling, 68 * scaling); // NOTE: The height is larger to account for padding reset bug (below)
static const cv::Size sequence_cell_padding(10 * scaling, 0 * scaling); // NOTE: The height resets its padding to 0 after moving the mouse
static const cv::Size sequences_margin_topleft(20 * scaling, 10 * scaling);
static const cv::Size sequences_margin_bottomright(12 * scaling, 22 * scaling);
static const cv::Size sequences_margin_size(sequences_margin_topleft + sequences_margin_bottomright);

