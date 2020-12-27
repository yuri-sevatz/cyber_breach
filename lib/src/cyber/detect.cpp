#include <cyber/detect.hpp>
#include <cyber/layout.hpp>

std::optional<sequence_lengths_type> detect_sequences(cv::Mat borders_hsv, cv::Mat white_hsv, matrix_length_type matrix_length, buffer_length_type buffer_length) {
    // The position of the matrix right border
    const int matrix_border_right = matrix_margin_bottomright.width + matrix_border_topcenter.x + matrix_length * matrix_cell_size.width / 2;

    // The position of the sequences left border
    const int sequences_border_left = matrix_border_right + sequences_border_matrix_left_offset;

    // Sanity check the sequences' left border
    if (borders_hsv.at<uchar>(cv::Point(sequences_border_left, sequences_border_top + 1))) {

        // Matrix inner top midpoint
        const cv::Point sequences_search_begin(cv::Point(sequences_border_left + 1, sequences_border_top + 1));

        // Image edge along same vertical as matrix inner top midpoint
        const cv::Point sequences_search_end(sequences_search_begin.x, borders_hsv.size().height);

        // If the image meets the minimum width
        if (sequences_search_begin.y < sequences_search_end.y) {

            // Iterate over each point along the sequences search path
            for(cv::LineIterator sequences_iterator(borders_hsv, sequences_search_begin, sequences_search_end);
                sequences_iterator.pos() != sequences_search_end; ++sequences_iterator) {

                // The bottom border of the sequences
                const int sequences_border_bottom = sequences_iterator.pos().y;

                // The height of the sequences
                const int sequences_height = sequences_border_bottom - sequences_border_top;

                // If the frame edge was found, with a position greater than the frame minimum (latter places lower bound on unlikely false positives)
                if (borders_hsv.at<uchar>(sequences_iterator.pos()) && sequences_height > sequences_margin_size.height) {

                    // Acquire the sequences length from the sequences height
                    const std::size_t sequences_length = (
                        (sequences_height - sequences_margin_size.height) /
                        (sequence_cell_size.height + sequence_cell_padding.height)
                    );

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

                    sequence_lengths_type sequence_lengths(sequences_length);

                    // For each potential cell in the row
                    for (std::size_t row = 0; row < sequences_length; ++row) {
                        for (std::size_t col = 0; col < buffer_length; ++col) {
                            const cv::Rect cell_rect(
                                sequence_cell_begin.x + col * sequence_cell_step.width,
                                sequence_cell_begin.y + row * sequence_cell_step.height,
                                sequence_cell_size.width,
                                sequence_cell_size.height
                            );
                            if (cv::countNonZero(white_hsv(cell_rect))) {
                                ++sequence_lengths[row];
                            } else {
                                continue;
                            }
                        }
                    }

                    return sequence_lengths;
                }
            }
        }
    }

    return std::nullopt;
}

std::optional<buffer_length_type> detect_buffer(cv::Mat borders_hsv, matrix_length_type matrix_length) {
    // The position of the matrix right border
    const int matrix_border_right = matrix_margin_bottomright.width + matrix_border_topcenter.x + matrix_length * matrix_cell_size.width / 2;

    // The position of the buffer left border
    const int buffer_border_left = matrix_border_right + buffer_border_matrix_left_offset;

    // Sanity check the buffer's left border
    if (borders_hsv.at<uchar>(cv::Point(buffer_border_left, buffer_border_top + 1))) {

        // Matrix inner top midpoint
        const cv::Point buffer_search_begin(cv::Point(buffer_border_left + 1, buffer_border_top + 1));

        // Image edge along same vertical as matrix inner top midpoint
        const cv::Point buffer_search_end(borders_hsv.size().width, buffer_search_begin.y);

        // If the image meets the minimum width
        if (buffer_search_begin.x < buffer_search_end.x) {

            // Iterate over each point along the buffer search path
            for(cv::LineIterator buffer_iterator(borders_hsv, buffer_search_begin, buffer_search_end); buffer_iterator.pos() != buffer_search_end; ++buffer_iterator) {

                // The right border of the buffer
                const int buffer_border_right = buffer_iterator.pos().x;

                // The width of the buffer
                const int buffer_width = buffer_border_right - buffer_border_left;

                // If the frame edge was found, with a position greater than the frame minimum (latter places lower bound on unlikely false positives)
                if (borders_hsv.at<uchar>(buffer_iterator.pos()) && buffer_width >= buffer_width_min) {

                    // Acquire the buffer length from the buffer width
                    return (
                        (buffer_width - buffer_width_min) /
                        (buffer_cell_size.width + buffer_cell_padding.width)
                    );
                }
            }
        }
    }
    return std::nullopt;
}



std::optional<matrix_length_type> detect_matrix(cv::Mat borders_hsv) {
    // Location of a 0-sized matrix bottom right corner
    static const int matrix_border_right_min = matrix_border_topcenter.x + matrix_margin_bottomright.width;

    // Matrix inner top midpoint
    static const cv::Point matrix_search_begin(
        matrix_border_topcenter.x,
        matrix_border_topcenter.y + 2
    );

    // Image edge along same vertical as matrix inner top midpoint
    static const cv::Point matrix_search_end(borders_hsv.size().width, matrix_search_begin.y);

    // If the image meets the minimum width
    if (matrix_search_end.x > matrix_search_begin.x) {

        // Iterate over each point along the matrix search path
        for (cv::LineIterator matrix_iterator(borders_hsv, matrix_search_begin, matrix_search_end); matrix_iterator.pos() != matrix_search_end; ++matrix_iterator) {

            // The right border of the matrix
            const int matrix_border_right = matrix_iterator.pos().x;

            // If the frame edge was found, with a position greater than the frame minimum (latter places lower bound on unlikely false positives)
            if (borders_hsv.at<uchar>(matrix_iterator.pos()) && matrix_border_right >= matrix_border_right_min) {

                // Acquire the matrix length from the position of the right border of the matrix
                return (
                    (matrix_border_right - matrix_border_right_min) /
                    (matrix_cell_size.width / 2)
                );
            }
        }
    }
    return std::nullopt;
}

detected_type detect(const cv::Mat & image) {
    detected_type detected;

    // Convert the image to HSV
    cv::Mat image_hsv;
    cvtColor(image, image_hsv, cv::COLOR_BGR2HSV);

    // "Vomit-yellow" Hue, with a minimum saturation, and a minimum lightness
    // (The S and V are left wide enough so that the matrix + buffer + sequence borders still show
    cv::Mat borders_hsv;
    cv::inRange(image_hsv, cv::Scalar(35,150,100), cv::Scalar(37,255,255), borders_hsv);

    // Detect matrix length
    detected.matrix_length = detect_matrix(borders_hsv).value();

    // If we could detect the matrix_length
    if (detected.matrix_length) {

        // Detect the buffer length
        detected.buffer_length = detect_buffer(
            borders_hsv, *detected.matrix_length
        );

        // If we could detect the buffer_length
        if (detected.buffer_length) {

            // Any Hue, with "White" saturation, and relatively mid-to-high lightness
            cv::Mat white_hsv;
            cv::inRange(image_hsv, cv::Scalar(0,0,100), cv::Scalar(255,20,255), white_hsv);

            detected.sequence_lengths = detect_sequences(
                borders_hsv, white_hsv, *detected.matrix_length, *detected.buffer_length
            );
        }
    }

    return detected;
}
