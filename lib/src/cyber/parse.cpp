#include <algorithm>

#include <boost/algorithm/hex.hpp>

#include <opencv2/text/ocr.hpp>

#include <cyber/parse.hpp>

matrix_type parse_matrix(cv::text::OCRTesseract & ocr, const parse_input & input) {
    matrix_type matrix(boost::extents[input.matrix_length][input.matrix_length]);

    const cv::Size size(64, 64);
    const cv::Point begin(490 - (size.width / 2) * input.matrix_length, 346);

    for (int row = 0; row != input.matrix_length; ++row) {
        for(int col = 0; col != input.matrix_length; ++col) {
            cv::Mat cell = input.image(cv::Rect(begin.x + col * size.width, begin.y + row * size.height, size.width, size.height));

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

sequences_type parse_sequences(cv::text::OCRTesseract & ocr, const parse_input & input) {
    sequences_type sequences(input.sequence_lengths.size());

    const cv::Size size(32, 32);
    const cv::Size padding(10, 39);

    const cv::Point begin(680 + (64 / 2) * input.matrix_length, 341);

    for (int row = 0; row != input.sequence_lengths.size(); ++row) {
        sequences[row].resize(input.sequence_lengths[row]);
        for(int col = 0; col != input.sequence_lengths[row]; ++col) {
            const cv::Rect rect(
                begin.x + col * (size.width + padding.width),
                begin.y + row * (size.height + padding.height),
                size.width,
                size.height
            );
            cv::Mat cell = input.image(rect);

            cv::Mat bitwise_not;
            cv::bitwise_not(cell, bitwise_not);

            std::string output_text;
            ocr.run(bitwise_not, output_text);
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

parse_output parse(const parse_input & input) {
    const auto ocr = cv::text::OCRTesseract::create(NULL, "Latin", "0123456789ABCDEF", cv::text::OEM_DEFAULT, cv::text::PSM_SINGLE_BLOCK);
    return parse_output {
        parse_matrix(*ocr, input),
        parse_sequences(*ocr, input)
    };
}
