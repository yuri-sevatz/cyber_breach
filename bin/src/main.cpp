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
#include <cyber/clicker.hpp>
#endif
#include <cyber/common.hpp>
#include <cyber/detect.hpp>
#ifdef _WIN32
#include <cyber/init.hpp>
#endif
#include <cyber/parse.hpp>
#include <cyber/solve.hpp>
#include <cyber/term.hpp>

constexpr const char * const window_name = "Cyberpunk 2077 (C) 2020 by CD Projekt RED";

void help(std::string_view name) {
    std::cout << "Usage: ";

    const std::array<std::ostream &(*)(std::ostream&),7> colors({
        term::bright_red,
        term::bright_green,
        term::bright_yellow,
        term::bright_blue,
        term::bright_magenta,
        term::bright_cyan,
        term::bright_white,
    });
    /*
    auto color = colors.begin();
    for (auto ch : name) {
        if (color == colors.end()) {
            color = colors.begin();
        }
        std::cout << *color++ << ch << term::reset;
    }
    */
    std::cout << term::bright_cyan << term::underline << term::bold << name << term::reset;
    std::cout<< ' '
        << term::magenta << "[-h]" << term::reset << ' '
        << term::red << "[-l INPUT]" << term::reset << ' '
#ifdef _WIN32
        << term::yellow << "[-s OUTPUT]" << term::reset << ' '
        << term::green << "[--no-autoclick]" << term::reset << ' '
#endif
        << "\n\n"
        << term::bright_yellow << term::reverse << term::bold << "Cyberpunk 2077" << term::reset << " - "
        << term::bold << "Breach Protocol Auto-Solver" << term::reset << '\n'
        << '\n'
        << "optional arguments:\n"
        << "  "
        << term::magenta << "-h" << term::reset << ", " << term::magenta << "--help" << term::reset
        << "            "
        << "show this help message and exit" << '\n'
        << "  "
        << term::red << "--load INPUT" << term::reset << ", " << term::red << "-l INPUT" << term::reset << '\n'
        << "                        "
        << "input file to load screenshot" << ' '
        << '(' << "default:" << ' ' << term::underline << "capture" << term::reset << ')' << '\n'
#ifdef _WIN32
        << "  "
        << term::yellow << "--save OUTPUT" << term::reset << ", " << term::yellow << "-s OUTPUT" << term::reset << '\n'
        << "                        "
        << "output directory to save screenshot" << ' '
        << '(' << "default:" << ' ' << term::underline << "disabled" << term::reset << ')' << '\n'
        << "  "
        << term::green << "--no-autoclick" << term::reset << '\n'
        << "                        "
        << "turn off auto-clicking" << ' '
        << '(' << "default:" << ' ' << term::underline << "autoclick" << term::reset << ", iff capture" << ')' << '\n'
#endif
        << '\n'
        << "By default " << name << " will capture and auto-click a running copy of CP2077\n";
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

    bool no_autoclick = false;

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
        } else if (*argi == "--no-autoclick") {
            no_autoclick = true;
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
        image = capture(window_name);
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
            << term::bright_red << *detected.matrix_length << term::reset
            << std::endl
        ;
    }
    if (!detected.buffer_length) {
        std::cerr << term::red << "error: " << term::reset << "could not detect buffer_length, aborting" << std::endl;
        return EXIT_FAILURE;
    } else {
        std::cout
            << " buffer_length = "
            << term::bright_yellow << *detected.buffer_length << term::reset
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
            std::cout << term::bright_cyan << *sequence << term::reset;
            while (++sequence != detected.sequence_lengths->end()) {
                std::cout << ',' << term::bright_cyan << *sequence << term::reset;
            }
        }
        std::cout << ']' << std::endl;
    }

    const parsed_type parsed = parse(image, *detected.matrix_length, *detected.sequence_lengths);

    std::cout
        << "Matrix:\n"
        << term::bright_red
    ;
    for (std::size_t r = 0; r < parsed.matrix.shape()[0]; ++r) {
        for (std::size_t c = 0; c < parsed.matrix.shape()[1]; ++c) {
            boost::io::ios_base_all_saver _(std::cout);
            std::cout << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (int) parsed.matrix[r][c];
            if (c != parsed.matrix.shape()[1] - 1) {
                std::cout << ' ';
            }
        }
        std::cout <<  '\n';
    }
    std::cout << term::reset;

    std::cout
        << "Buffer:\n"
        << term::bright_yellow << *detected.buffer_length << term::reset << '\n';

    std::cout
        << "Sequences:\n"
        << term::bright_cyan
    ;
    for (auto sequence = parsed.sequences.begin(); sequence != parsed.sequences.end(); ++sequence) {
        boost::io::ios_base_all_saver _(std::cout);
        std::cout << std::hex << std::setfill('0') << std::setw(2) << std::uppercase;
        std::copy(sequence->begin(), sequence->end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << '\n';
    }
    std::cout << term::reset;

    const std::unordered_set<byte_type> expected = {0x1C, 0x55, 0x7A, 0xBD, 0xE9};

    bool matrix_good = true;
    for (const auto & line : parsed.matrix) {
        for (const auto & item : line) {
            if (expected.find(item) == expected.end()) {
                matrix_good = false;
                break;
            }
        }
    }

    bool sequence_good = true;
    for (const auto & sequence : parsed.sequences) {
        for (const auto & item : sequence) {
            if (expected.find(item) == expected.end()) {
                sequence_good = false;
                break;
            }
        }
    }

    const solved_type solved = solve(parsed.matrix, parsed.sequences, *detected.buffer_length);

    std::cout
        << "Path:\n"
        << term::bright_magenta
    ;
    for (auto step = solved.path.begin(); step != solved.path.end(); ++step) {
        boost::io::ios_base_all_saver _(std::cout);
        const position_type position{
            static_cast<matrix_type::index>((*step)[0]),
            static_cast<matrix_type::index>((*step)[1])
        };
        std::cout << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (int) parsed.matrix(position);
        if (step + 1 != solved.path.end()) {
            std::cout << ' ';
        }
    }
    std::cout
        << term::reset
        << '\n'
    ;

    std::cout
        << "Solution:\n"
        << term::bright_green
    ;
    for (std::size_t r = 0; r < parsed.matrix.shape()[0]; ++r) {
        for (std::size_t c = 0; c < parsed.matrix.shape()[1]; ++c) {
            const auto step = std::find(solved.path.begin(), solved.path.end(), position_type{static_cast<matrix_type::index>(r),static_cast<matrix_type::index>(c)});
            if (step == solved.path.end()) {
                std::cout << "--";
            } else {
                std::cout << std::setw(2) << std::distance(solved.path.begin(), step);
            }
            if (c != parsed.matrix.shape()[1] - 1) {
                std::cout << ' ';
            }
        }
        std::cout << '\n';
    }
    std::cout << term::reset;

    std::cout
        << "Score:\n"
        << solved.score << '/' << ((1 << parsed.sequences.size()) - 1) << '\n'
    ;

    if (!matrix_good) {
        std::cout
            << term::red << term::on_yellow << "|===========|" << term::reset << '\n'
            << term::red << term::on_yellow << "|==WARNING==|" << term::reset
            << " Detected unexpected values in " << term::bright_red << "matrix" << term::reset << ", result may be sub-optimal" << '\n'
            << term::red << term::on_yellow << "|===========|" << term::reset << '\n'
        ;
    }

    if (!sequence_good) {
        std::cout
            << term::red << term::on_yellow << "|===========|" << term::reset << '\n'
            << term::red << term::on_yellow << "|==WARNING==|" << term::reset
            << " Detected unexpected values in " << term::bright_cyan << "sequence" << term::reset << ", result may be sub-optimal" << '\n'
            << term::red << term::on_yellow << "|===========|" << term::reset << '\n'
        ;
    }

    if (!matrix_good || !sequence_good) {
        return EXIT_FAILURE;
    } else if (load || no_autoclick) {
        return EXIT_SUCCESS;
    }
#ifdef _WIN32
    return clicker(window_name, *detected.matrix_length, solved.path) ? EXIT_SUCCESS : EXIT_FAILURE;
#else
    return EXIT_SUCCESS;
#endif
}
