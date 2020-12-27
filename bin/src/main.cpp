#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <optional>
#include <regex>
#include <sstream>
#include <string_view>
#include <unordered_set>

#include <boost/lexical_cast.hpp>

#ifdef _WIN32
#include <cyber/capture.hpp>
#endif
#include <cyber/common.hpp>
#include <cyber/detect.hpp>
#ifdef _WIN32
#include <cyber/init.hpp>
#endif
#include <cyber/parse.hpp>
#include <cyber/solve.hpp>
#include <cyber/term.hpp>

void help(std::string_view name) {
    std::cout
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

#if _WIN32
    init();
#endif

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
                std::cerr << term::red << "error: " << term::reset << "argument --load/-l: expected one argument" << std::endl;
                return EXIT_FAILURE;
            }
#ifdef _WIN32
        } else if (*argi == "--save" || *argi == "-s") {
            if (++argi != args.end()) {
                save = *argi;
            } else {
                std::cerr << term::red << "error: " << term::reset << "argument --save/-s: expected one argument" << std::endl;
                return EXIT_FAILURE;
            }
#endif
        } else {
            std::cerr << term::red << "error: " << term::reset << "unrecognized argument: " << *argi << std::endl;
            return EXIT_FAILURE;
        }
    }

    cv::Mat image;

    if (load) {
        image = cv::imread(load->string());
        if (image.empty()) {
            std::cerr << term::red << "error: " << term::reset << "could not open image from path, aborting" << std::endl;
            return EXIT_FAILURE;
        }
    } else {
#ifdef _WIN32
        image = capture("Cyberpunk 2077 (C) 2020 by CD Projekt RED");
        if (image.empty()) {
            std::cerr << term::red << "error: " << term::reset << "could not capture screenshot, aborting" << std::endl;
            return EXIT_FAILURE;
        } else if (save) {
            const std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::ostringstream os;
            os << std::put_time(std::localtime(&time), "%Y%m%d%H%M%S.png");
            if (!cv::imwrite((*save / os.str()).string(), image)) {
                std::cerr << term::red << "error: " << term::reset << "could not save screenshot, aborting" << std::endl;
                return EXIT_FAILURE;
            }
        }
#else
        std::cerr << term::red << "error: " << term::reset << "screen capture not compiled in, aborting" << std::endl;
        return EXIT_FAILURE;
#endif
    }

    std::cout << "Detecting..." << std::endl;

    const detected_type detected = detect(image);

    if (!detected.matrix_length) {
        std::cerr << term::red << "error: " << term::reset << "could not detect matrix_length, aborting" << std::endl;
        return EXIT_FAILURE;
    } else {
        std::cout
            << " matrix_length = "
            << term::high_red << *detected.matrix_length << term::reset
            << std::endl
        ;
    }
    if (!detected.buffer_length) {
        std::cerr << term::red << "error: " << term::reset << "could not detect buffer_length, aborting" << std::endl;
        return EXIT_FAILURE;
    } else {
        std::cout
            << " buffer_length = "
            << term::high_yellow << *detected.buffer_length << term::reset
            << std::endl
        ;
    }
    if (!detected.sequence_lengths) {
        std::cerr << term::red << "error: " << term::reset << "could not detect sequence_lengths, aborting" << std::endl;
        return EXIT_FAILURE;
    } else {
        std::cout << " sequence_lengths = [";
        if (!detected.sequence_lengths->empty()) {
            auto sequence = detected.sequence_lengths->begin();
            std::cout << term::high_cyan << *sequence << term::reset;
            while (++sequence != detected.sequence_lengths->end()) {
                std::cout << ',' << term::high_cyan << *sequence << term::reset;
            }
        }
        std::cout << ']' << std::endl;
    }

    const parsed_type parsed = parse(image, *detected.matrix_length, *detected.sequence_lengths);

    solve(parsed.matrix, parsed.sequences, *detected.buffer_length);

    static const std::unordered_set<byte_type> expected = {0x1C, 0x55, 0x7A, 0xBD, 0xE9};

    for (const auto & line : parsed.matrix) {
        for (const auto & item : line) {
            if (expected.find(item) == expected.end()) {
                std::cout
                    << term::red << term::on_yellow << "|===========|" << term::reset << '\n'
                    << term::red << term::on_yellow << "|==WARNING==|" << term::reset
                    << " Detected unexpected values in " << term::high_red << "matrix" << term::reset << ", result may be sub-optimal" << '\n'
                    << term::red << term::on_yellow << "|===========|" << term::reset << '\n'
                ;
                break;
            }
        }
    }
    for (const auto & sequence : parsed.sequences) {
        for (const auto & item : sequence) {
            if (expected.find(item) == expected.end()) {
                std::cout
                    << term::red << term::on_yellow << "|===========|" << term::reset << '\n'
                    << term::red << term::on_yellow << "|==WARNING==|" << term::reset
                    << " Detected unexpected values in " << term::high_cyan << "sequence" << term::reset << ", result may be sub-optimal" << '\n'
                    << term::red << term::on_yellow << "|===========|" << term::reset << '\n'
                ;
                break;
            }
        }
    }

    return EXIT_SUCCESS;
}
