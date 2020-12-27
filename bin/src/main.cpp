#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <optional>
#include <regex>
#include <sstream>
#include <string_view>

#include <boost/lexical_cast.hpp>

#ifdef _WIN32
#include <cyber/capture.hpp>
#endif
#include <cyber/common.hpp>
#include <cyber/detect.hpp>
#include <cyber/parse.hpp>
#include <cyber/solve.hpp>

void help(std::string_view name) {
    std::cerr
    << "Usage: " << name << " [-h] [--load INPUT] [--save OUTPUT]\n"
        << '\n'
        << "Cyberpunk 2077 - Breach Solver\n"
        << "  \n"
        << "optional arguments:\n"
        << "  -h, --help            show this help message and exit\n"
        << "  --load INPUT, -l INPUT\n"
        << "                        input image to load screenshot (default: screenshot)\n"
        << "  --save OUTPUT, -s OUTPUT\n"
        << "                        output dir to save screenshot (default: disabled)\n"
        << "\n"
        << "By default, " << name << " will take screenshots from a running copy of CP2077\n";
    ;
}

int main(int argc, char * argv[]) {
    const std::vector<std::string_view> args(argv, argv + argc);

    std::optional<std::filesystem::path> load;
#ifdef _WIN32
    std::optional<std::filesystem::path> save;
#endif

    auto argi = args.begin() + 1;
    for (; argi != args.end(); ++argi) {
        if (*argi == "--help" || *argi == "-h") {
            help(args.front());
            return EXIT_FAILURE;
        } else if (*argi == "--load" || *argi == "-l") {
            if (++argi != args.end()) {
                load = *argi;
            } else {
                std::cerr << "error: argument --load/-l: expected one argument" << std::endl;
                return EXIT_FAILURE;
            }
#ifdef _WIN32
        } else if (*argi == "--save" || *argi == "-s") {
            if (++argi != args.end()) {
                save = *argi;
            } else {
                std::cerr << "error: argument --save/-s: expected one argument" << std::endl;
                return EXIT_FAILURE;
            }
#endif
        } else {
            std::cerr << "error: unrecognized argument: " << *argi << std::endl;
            return EXIT_FAILURE;
        }
    }

    cv::Mat image;

    if (load) {
        image = cv::imread(load->string());
        if (image.empty()) {
            std::cerr << "error: could not open image from path, aborting" << std::endl;
            return EXIT_FAILURE;
        }
    } else {
#ifdef _WIN32
        image = capture("Cyberpunk 2077 (C) 2020 by CD Projekt RED");
        if (image.empty()) {
            std::cerr << "error: could not capture screenshot, aborting" << std::endl;
            return EXIT_FAILURE;
        } else if (save) {
            const std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::ostringstream os;
            os << std::put_time(std::localtime(&time), "%Y%m%d%H%M%S.png");
            if (!cv::imwrite((*save / os.str()).string(), image)) {
                std::cerr << "error: could not save screenshot, aborting" << std::endl;
                return EXIT_FAILURE;
            }
        }
#else
        std::cerr << "error: screen capture not compiled in, aborting" << std::endl;
        return EXIT_FAILURE;
#endif
    }

    const detected_type detected = detect(image);

    if (!detected.matrix_length) {
        std::cerr << "error: could not detect matrix_length, aborting" << std::endl;
        return EXIT_FAILURE;
    } else {
        std::cout << "matrix_length = " << *detected.matrix_length << std::endl;
    }
    if (!detected.buffer_length) {
        std::cerr << "error: could not detect buffer_length, aborting" << std::endl;
        return EXIT_FAILURE;
    } else {
        std::cout << "buffer_length = " << *detected.buffer_length << std::endl;
    }
    if (!detected.sequence_lengths) {
        std::cerr << "error: could not detect sequence_lengths, aborting" << std::endl;
        return EXIT_FAILURE;
    } else {
        std::cout << "sequence_lengths = [";
        std::copy(detected.sequence_lengths->begin(), detected.sequence_lengths->end(), std::ostream_iterator<sequence_length_type>(std::cout, ","));
        std::cout << ']' << std::endl;
    }

    const parsed_type parsed = parse(image, *detected.matrix_length, *detected.sequence_lengths);

    for (const auto & line : parsed.matrix) {
        for (const auto & item : line) {
            if (!item) {
                std::cerr << "warning: detected a 00 in matrix, proceeding anyway" << std::endl;
                break;
            }
        }
    }

    for (const auto & sequence : parsed.sequences) {
        for (const auto & item : sequence) {
            if (!item) {
                std::cerr << "warning: detected a 00 in sequence, proceeding anyway" << std::endl;
                break;
            }
        }
    }

    solve(parsed.matrix, parsed.sequences, *detected.buffer_length);

    return EXIT_SUCCESS;
}
