#include <cstdlib>
#include <optional>
#include <regex>
#include <string_view>

#include <boost/lexical_cast.hpp>

#ifdef _WIN32
#include <cyber/capture.hpp>
#endif
#include <cyber/common.hpp>
#include <cyber/parse.hpp>
#include <cyber/solve.hpp>

void wip() {
/*
 *   cv::Rect center(begin_x, begin_y, end_x - begin_x, end_y - begin_y);
 *   cv::Mat cropped = image(center);
 *
 *   cv::Mat cropped_hsv;
 *   cvtColor(cropped, cropped_hsv, cv::COLOR_BGR2HSV);
 *
 *   cv::Mat matrix_cursor;
 *   cv::inRange(cropped_hsv, cv::Scalar(105,10,10), cv::Scalar(120,90,90), matrix_cursor);
 *
 *   cv::Mat sequence_cursor;
 *   cv::inRange(cropped_hsv, cv::Scalar(120,0,0), cv::Scalar(125,255,255), sequence_cursor);
 *
 *   cv::Mat installed_mask;
 *   cv::inRange(cropped_hsv, cv::Scalar(60,100,100), cv::Scalar(90,255,255), installed_mask);
 *
 *   cv::Mat cursor_mask;
 *   cv::inRange(cropped_hsv, cv::Scalar(80,100,100), cv::Scalar(100,255,255), cursor_mask);
 *
 *   cv::Mat gray;
 *   cv::cvtColor(cropped, gray, cv::COLOR_BGR2GRAY);
 *
 *   cv::Mat threshold;
 *   cv::threshold(gray, threshold, 100, 255, cv::THRESH_BINARY);
 *
 *   cv::Mat masked;
 *   threshold.copyTo(masked);
 *   masked.setTo(cv::Scalar(0,0,0),installed_mask);
 *   masked.setTo(cv::Scalar(0,0,0),cursor_mask);
 *
 *   cv::Mat blurred;
 *   cv::GaussianBlur(gray, blurred, {5, 5}, 0);
 *
 *   cv::Mat contours;
 *   cv::findContours(blurred, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
 *
 *   cv::Mat edged;
 *   cv::Canny(blurred, edged, 50, 200);
 */
}

void help(std::string_view name) {
    std::cerr
    << "Usage: " << name << " [-h] [--path PATH] [--buffer_length BUFFER_LENGTH] [--matrix_length MATRIX_LENGTH] [--sequence_length SEQUENCE_LENGTHS]\n"
        << '\n'
        << "Cyberpunk 2077 - Breach Solver\n"
        << '\n'
        << "positional arguments:\n"
        << "  \n"
        << "optional arguments:\n"
        << "  -h, --help            show this help message and exit\n"
        << "  --path PATH, -p PATH  input image (default: screen-capture)\n"
        << "\n"
        << "  --buffer_length BUFFER_LENGTH, -b BUFFER_LENGTH\n"
        << "                        buffer length (default: auto-detect)\n"
        << "\n"
        << "  --matrix_length MATRIX_LENGTH, -m MATRIX_LENGTH\n"
        << "                        matrix length (default: auto-detect)\n"
        << "\n"
        << "  --sequence_lengths SEQUENCE_LENGTHS, -s SEQUENCE_LENGTHS\n"
        << "                        sequence lengths (default: auto-detect)\n"
    ;
}

int main(int argc, char * argv[]) {
    const std::vector<std::string_view> args(argv, argv + argc);

    std::optional<std::string> path;
    std::optional<matrix_length_type> matrix_length;
    std::optional<sequence_lengths_type> sequence_lengths;
    std::optional<buffer_length_type> buffer_length;

    auto argi = args.begin() + 1;
    for (; argi != args.end(); ++argi) {
        if (*argi == "--help" || *argi == "-h") {
            help(args.front());
            return EXIT_FAILURE;
        } else if (*argi == "--path" || *argi == "-p") {
            if (++argi != args.end()) {
                path = *argi;
            } else {
                std::cerr << "error: argument --path/-p: expected one argument" << std::endl;
                return EXIT_FAILURE;
            }
        } else if (*argi == "--buffer_length" || *argi == "-b") {
            if (++argi != args.end()) {
                buffer_length = boost::lexical_cast<buffer_length_type>(*argi);
            } else {
                std::cerr << "error: argument --buffer_length/-b: expected one argument" << std::endl;
                return EXIT_FAILURE;
            }
        } else if (*argi == "--matrix_length" || *argi == "-m") {
            if (++argi != args.end()) {
                matrix_length = boost::lexical_cast<matrix_length_type>(*argi);
            } else {
                std::cerr << "error: argument --matrix_length/-m: expected one argument" << std::endl;
                return EXIT_FAILURE;
            }
        } else if (*argi == "--sequence_lengths" || *argi == "-s") {
            if (++argi != args.end()) {
                std::regex regex(",");
                std::regex_token_iterator<std::string_view::iterator> iter(argi->begin(), argi->end(), regex, -1);
                std::regex_token_iterator<std::string_view::iterator> end;
                sequence_lengths = sequence_lengths_type{};
                for (; iter != end; ++iter) {
                    sequence_lengths->push_back(boost::lexical_cast<sequence_length_type>(*iter));
                }
            } else {
                std::cerr << "error: argument --sequence_lengths/-s: expected one argument" << std::endl;
                return EXIT_FAILURE;
            }
        } else {
            std::cerr << "error: unrecognized argument: " << *argi << std::endl;
            return EXIT_FAILURE;
        }
    }

    if (!buffer_length) {
        // TODO: buffer_length autodetect
        std::cerr << "error: buffer_length autodetect is still WIP" << std::endl;
        return EXIT_FAILURE;
    }

    if (!matrix_length) {
        // TODO: matrix_length autodetect
        std::cerr << "error: matrix_length autodetect is still WIP" << std::endl;
        return EXIT_FAILURE;
    }

    if (!sequence_lengths) {
        // TODO: sequence_lengths autodetect
        std::cerr << "error: sequence_lengths autodetect is still WIP" << std::endl;
        return EXIT_FAILURE;
    }

    cv::Mat image;

    if (path) {
        image = cv::imread(*path);
        if (image.empty()) {
            std::cerr << "error: could not open image from path, aborting" << std::endl;
            return EXIT_FAILURE;
        }
    } else {
#ifdef _WIN32
        image = capture("Cyberpunk 2077 (C) 2020 by CD Projekt RED");
        if (image.empty()) {
            std::cerr << "error: could not capture screen-shot, aborting" << std::endl;
            return EXIT_FAILURE;
        }
#else
        std::cerr << "error: screen capture not compiled in, aborting" << std::endl;
        return EXIT_FAILURE;
#endif
    }

    parse_output output = parse(parse_input{image, *matrix_length, *sequence_lengths});

    solve(output.matrix, output.sequences, *buffer_length);

    return EXIT_SUCCESS;
}
