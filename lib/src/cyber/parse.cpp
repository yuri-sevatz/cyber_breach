#ifdef _WIN32
#include <io.h>
#endif

#include <algorithm>
#include <cstdlib>
#include <cstdio>

#include <boost/algorithm/hex.hpp>

#include <opencv2/text/ocr.hpp>

#include <cyber/layout.hpp>
#include <cyber/parse.hpp>

namespace {

matrix_type parse_matrix(cv::text::OCRTesseract & ocr, cv::Mat image, matrix_length_type matrix_length) {
    matrix_type matrix(boost::extents[matrix_length][matrix_length]);

    // The position of the matrix left border
    const cv::Point matrix_cell_begin(
        matrix_border_topcenter.x - (matrix_cell_size.width / 2) * matrix_length + 2,
        matrix_border_topcenter.y + matrix_margin_topleft.height
    );

    // The vector between the first cell and the ith + 1 cell
    const cv::Size matrix_cell_step(
        matrix_cell_size.width + matrix_cell_padding.width,
        matrix_cell_size.height + matrix_cell_padding.height
    );

    for (int row = 0; row != matrix_length; ++row) {
        for(int col = 0; col != matrix_length; ++col) {
            const cv::Rect cell_rect = cv::Rect(
                matrix_cell_begin.x + col * matrix_cell_step.width,
                matrix_cell_begin.y + row * matrix_cell_step.height,
                matrix_cell_size.width,
                matrix_cell_size.height
            );
            const cv::Mat cell = image(cell_rect);

            cv::Mat bitwise_not;
            cv::bitwise_not(cell, bitwise_not);

            std::string output_text;
            ocr.run(bitwise_not, output_text);
            output_text.erase(std::remove_if(output_text.begin(), output_text.end(), [](char x){return std::isspace(x);}), output_text.end());

            if (output_text.size() % 2 == 0) {
                std::string bytes = boost::algorithm::unhex(output_text);
                if (bytes.size() == 1) {
                    matrix[row][col] = static_cast<byte_type>(bytes.front());
                }
            }
        }
    }

    return matrix;
}

sequences_type parse_sequences(cv::text::OCRTesseract & ocr, cv::Mat image, matrix_length_type matrix_length, sequence_lengths_type sequence_lengths) {
    sequences_type sequences(sequence_lengths.size());

    // The position of the matrix right border
    const int matrix_border_right = matrix_margin_bottomright.width + matrix_border_topcenter.x + (matrix_length * matrix_cell_size.width) / 2;

    // The position of the sequences left border
    const int sequences_border_left = matrix_border_right + sequences_border_matrix_left_offset;

    // The coordinate of the first cell
    const cv::Point sequence_cell_begin(
        sequences_border_left + sequences_margin_topleft.width,
        sequences_border_top + sequences_margin_topleft.height
    );

    // The vector between the first cell and the ith + 1 cell
    const cv::Size sequence_cell_step(
        sequence_cell_size.width + sequence_cell_padding.width,
        sequence_cell_size.height + sequence_cell_padding.height
    );

    // For each known cell in the row
    for (int row = 0; row != sequence_lengths.size(); ++row) {
        sequences[row].resize(sequence_lengths[row]);
        for(int col = 0; col != sequence_lengths[row]; ++col) {
            const cv::Rect cell_rect(
                sequence_cell_begin.x + col * sequence_cell_step.width,
                sequence_cell_begin.y + row * sequence_cell_step.height,
                sequence_cell_size.width,
                sequence_cell_size.height
            );
            const cv::Mat cell = image(cell_rect);

            cv::Mat bitwise_not;
            cv::bitwise_not(cell, bitwise_not);

            cv::Mat grayscale;
            cv::cvtColor(bitwise_not, grayscale, cv::COLOR_BGR2GRAY);

            cv::Mat enhance;
            cv::adaptiveThreshold(grayscale, enhance, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 3, 10);

            std::string output_text;
            ocr.run(enhance, output_text);

            output_text.erase(std::remove_if(output_text.begin(), output_text.end(), [](char x){return std::isspace(x);}), output_text.end());

            if (output_text.size() % 2 == 0) {
                std::string bytes = boost::algorithm::unhex(output_text);
                if (bytes.size() == 1) {
                    sequences[row][col] = static_cast<byte_type>(bytes.front());
                }
            }
        }
    }

    return sequences;
}

} // namespace

parsed_type parse(cv::Mat image, matrix_length_type matrix_length, sequence_lengths_type sequence_lengths) {
    const int old = ::dup(2);
    FILE * file;
#ifdef _WIN32
    ::fopen_s(&file, "nul", "w");
#else
    file = ::fopen("/dev/null", "w");
#endif
    ::dup2(::fileno(file), 2);

    auto ocr = cv::text::OCRTesseract::create(NULL, "Latin", "0123456789ABCDEF", cv::text::OEM_DEFAULT, cv::text::PSM_SINGLE_BLOCK);

    const parsed_type result {
        parse_matrix(*ocr, image, matrix_length),
        parse_sequences(*ocr, image, matrix_length, sequence_lengths)
    };

    ocr.reset();

    ::fflush(stderr);
    ::fclose(file);
    ::dup2(old, 2);

    return result;
}
