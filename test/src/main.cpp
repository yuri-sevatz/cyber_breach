#include <cstdlib>

#include <cyber/detect.hpp>
#include <cyber/parse.hpp>
#include <cyber/solve.hpp>

template<typename T>
void expect_eq(const T & lhs, const T & rhs) {
    if (!(lhs == rhs)) {
        std::abort();
    }
}

void test_parse() {
    {
        const cv::Mat image = cv::imread("./examples/5x5_1.1.png");
        const detected_type detected = detect(image);
        const parsed_type parsed = parse(image, detected.matrix_length.value(), detected.sequence_lengths.value());
        expect_eq(
            parsed, parsed_type{
                matrix_ref_type(std::vector<unsigned char>({
                    0x55, 0xBD, 0x55, 0x1C, 0xBD,
                    0x1C, 0xBD, 0x55, 0x55, 0x1C,
                    0xBD, 0x1C, 0x55, 0xE9, 0x55,
                    0x55, 0x1C, 0x55, 0x1C, 0x1C,
                    0x55, 0x55, 0xE9, 0xBD, 0x55,
                }).data(), boost::extents[5][5]),
                sequences_type({
                    {0x55, 0x55, 0x1C}
                })
            }
        );
    }

    {
        const cv::Mat image = cv::imread("./examples/5x5_1.2.png");
        const detected_type detected = detect(image);
        const parsed_type parsed = parse(image, detected.matrix_length.value(), detected.sequence_lengths.value());
        expect_eq(
            parsed, parsed_type{
                matrix_ref_type(std::vector<unsigned char>({
                    0xE9, 0xE9, 0x55, 0xBD, 0x55,
                    0x55, 0x55, 0xBD, 0x55, 0x1C,
                    0x55, 0xBD, 0x1C, 0xE9, 0x1C,
                    0x55, 0x1C, 0x55, 0xE9, 0x1C,
                    0x55, 0x55, 0xBD, 0x1C, 0x55,
                }).data(), boost::extents[5][5]),
                sequences_type({
                    {0x55, 0x1C, 0x55, 0x55}
                })
            }
        );
    }

    {
        const cv::Mat image = cv::imread("./examples/5x5_1.3.png");
        const detected_type detected = detect(image);
        const parsed_type parsed = parse(image, detected.matrix_length.value(), detected.sequence_lengths.value());
        expect_eq(
            parsed, parsed_type{
                matrix_ref_type(std::vector<unsigned char>({
                    0xE9, 0x1C, 0xBD, 0xBD, 0x55,
                    0xBD, 0x1C, 0xE9, 0x1C, 0xE9,
                    0xE9, 0x55, 0x1C, 0x1C, 0x55,
                    0x1C, 0xBD, 0x1C, 0x1C, 0x55,
                    0xE9, 0x55, 0x1C, 0x55, 0x55,
                }).data(), boost::extents[5][5]),
                sequences_type({
                    {0x1C, 0x55, 0x1C, 0x1C}
                })
            }
        );
    }

    {
        const cv::Mat image = cv::imread("./examples/5x5_2.1.png");
        const detected_type detected = detect(image);
        const parsed_type parsed = parse(image, detected.matrix_length.value(), detected.sequence_lengths.value());
        expect_eq(
            parsed, parsed_type{
                matrix_ref_type(std::vector<unsigned char>({
                    0xE9, 0x55, 0x55, 0xBD, 0x1C,
                    0x55, 0x55, 0xBD, 0xBD, 0xBD,
                    0xBD, 0xE9, 0xBD, 0xBD, 0xBD,
                    0x1C, 0xBD, 0xBD, 0xBD, 0xBD,
                    0x55, 0x1C, 0x1C, 0x1C, 0x1C,
                }).data(), boost::extents[5][5]),
                sequences_type({
                    {0xBD, 0xE9, 0xBD},
                    {0xE9, 0xBD, 0xBD}
                })
            }
        );
    }

    {
        const cv::Mat image = cv::imread("./examples/5x5_2.2.png");
        const detected_type detected = detect(image);
        const parsed_type parsed = parse(image, detected.matrix_length.value(), detected.sequence_lengths.value());
        expect_eq(
            parsed, parsed_type{
                matrix_ref_type(std::vector<unsigned char>({
                    0x1C, 0x1C, 0x1C, 0x55, 0x1C,
                    0x55, 0x55, 0x55, 0xBD, 0x1C,
                    0x1C, 0x55, 0x55, 0x55, 0x55,
                    0xBD, 0xBD, 0x1c, 0xBD, 0xBD,
                    0xE9, 0x55, 0x1C, 0x1C, 0xE9,
                }).data(), boost::extents[5][5]),
                sequences_type({
                    {0x55, 0x1C, 0x55, 0x55},
                    {0x55, 0xBD, 0xBD}
                })
            }
        );
    }

    {
        const cv::Mat image = cv::imread("./examples/5x5_2.3.png");
        const detected_type detected = detect(image);
        const parsed_type parsed = parse(image, detected.matrix_length.value(), detected.sequence_lengths.value());
        expect_eq(
            parsed, parsed_type{
                matrix_ref_type(std::vector<unsigned char>({
                    0xBD, 0x55, 0x1C, 0x55, 0xBD,
                    0x1C, 0x55, 0xE9, 0xBD, 0xBD,
                    0x1C, 0xBD, 0x1C, 0x1C, 0xE9,
                    0x55, 0x1C, 0x55, 0x55, 0x1C,
                    0x1C, 0xE9, 0x1C, 0x55, 0xBD,
                }).data(), boost::extents[5][5]),
                sequences_type({
                    {0x55, 0x1C, 0x55, 0xBD},
                    {0xBD, 0x1C, 0x55}
                })
            }
        );
    }

    {
        const cv::Mat image = cv::imread("./examples/5x5_2.4.png");
        const detected_type detected = detect(image);
        const parsed_type parsed = parse(image, detected.matrix_length.value(), detected.sequence_lengths.value());
        expect_eq(
            parsed, parsed_type{
                matrix_ref_type(std::vector<unsigned char>({
                    0x1C, 0x55, 0x1C, 0xE9, 0xE9,
                    0xBD, 0x1C, 0x55, 0x1C, 0xBD,
                    0x1C, 0x1C, 0xBD, 0xE9, 0x1C,
                    0xBD, 0x1C, 0xE9, 0x1C, 0xE9,
                    0x1C, 0x1C, 0x55, 0x1C, 0x55,
                }).data(), boost::extents[5][5]),
                sequences_type({
                    {0x1C, 0x55, 0x1C},
                    {0x1C, 0x55, 0xE9}
                })
            }
        );
    }

    {
        const cv::Mat image = cv::imread("./examples/5x5_2.5.png");
        const detected_type detected = detect(image);
        const parsed_type parsed = parse(image, detected.matrix_length.value(), detected.sequence_lengths.value());
        expect_eq(
            parsed, parsed_type{
                matrix_ref_type(std::vector<unsigned char>({
                    0xE9, 0xE9, 0x1C, 0x1C, 0xBD,
                    0xBD, 0xBD, 0xBD, 0x1C, 0x1C,
                    0xE9, 0x55, 0x1C, 0xBD, 0xE9,
                    0x55, 0xE9, 0x1C, 0xBD, 0xBD,
                    0xBD, 0xBD, 0xBD, 0xBD, 0x1C,
                }).data(), boost::extents[5][5]),
                sequences_type({
                    {0xBD, 0x1C, 0xBD},
                    {0xBD, 0xE9, 0xBD},
                })
            }
        );
    }

    {
        const cv::Mat image = cv::imread("./examples/5x5_2.6.png");
        const detected_type detected = detect(image);
        const parsed_type parsed = parse(image, detected.matrix_length.value(), detected.sequence_lengths.value());
        expect_eq(
            parsed, parsed_type{
                matrix_ref_type(std::vector<unsigned char>({
                    0x55, 0x55, 0x1C, 0xBD, 0x1C,
                    0x1C, 0xBD, 0x1C, 0x1C, 0x1C,
                    0x1C, 0x55, 0x1C, 0x55, 0xBD,
                    0xBD, 0x55, 0xE9, 0x1C, 0x55,
                    0x55, 0x55, 0x55, 0xBD, 0x55,
                }).data(), boost::extents[5][5]),
                sequences_type({
                    {0x55, 0x1C, 0x1C},
                    {0x1C, 0x55, 0x55},
                })
            }
        );
    }

    {
        const cv::Mat image = cv::imread("./examples/5x5_2.7.png");
        const detected_type detected = detect(image);
        const parsed_type parsed = parse(image, detected.matrix_length.value(), detected.sequence_lengths.value());
        expect_eq(
            parsed, parsed_type{
                matrix_ref_type(std::vector<unsigned char>({
                    0x1C, 0xBD, 0x1C, 0xBD, 0x1C,
                    0x55, 0x1C, 0x1C, 0xBD, 0xE9,
                    0x55, 0x1C, 0x55, 0x55, 0x55,
                    0x1C, 0xE9, 0x55, 0xBD, 0x1C,
                    0xE9, 0x55, 0x55, 0x1C, 0xBD,
                }).data(), boost::extents[5][5]),
                sequences_type({
                    {0xE9, 0x55, 0x1C},
                    {0x1C, 0x1C, 0xE9}
                })
            }
        );
    }

    {
        const cv::Mat image = cv::imread("./examples/5x5_2.8.png");
        const detected_type detected = detect(image);
        const parsed_type parsed = parse(image, detected.matrix_length.value(), detected.sequence_lengths.value());
        expect_eq(
            parsed, parsed_type{
                matrix_ref_type(std::vector<unsigned char>({
                    0x1C, 0x55, 0x1C, 0xE9, 0x55,
                    0xE9, 0x55, 0x1C, 0x1C, 0x55,
                    0x1C, 0x1C, 0xBD, 0x55, 0x1C,
                    0xBD, 0x1C, 0x55, 0x1C, 0x1C,
                    0xE9, 0x55, 0x1C, 0x55, 0x1C,
                }).data(), boost::extents[5][5]),
                sequences_type({
                    {0x1C, 0x1C, 0xE9, 0x1C},
                    {0x55, 0x1C, 0xE9}
                })
            }
        );
    }

    {
        const cv::Mat image = cv::imread("./examples/5x5_2.9.png");
        const detected_type detected = detect(image);
        const parsed_type parsed = parse(image, detected.matrix_length.value(), detected.sequence_lengths.value());
        expect_eq(
            parsed, parsed_type{
                matrix_ref_type(std::vector<unsigned char>({
                    0x55, 0x1C, 0xE9, 0xE9, 0x1C,
                    0x55, 0x1C, 0xBD, 0x55, 0x55,
                    0x1C, 0x1C, 0x55, 0xE9, 0xBD,
                    0xBD, 0xE9, 0x55, 0x55, 0x1C,
                    0xE9, 0x55, 0x1C, 0x55, 0x1C,
                }).data(), boost::extents[5][5]),
                sequences_type({
                    {},
                    {0xBD, 0x55, 0x1C}
                })
            }
        );
    }

    {
        const cv::Mat image = cv::imread("./examples/5x5_2.10.png");
        const detected_type detected = detect(image);
        const parsed_type parsed = parse(image, detected.matrix_length.value(), detected.sequence_lengths.value());
        expect_eq(
            parsed, parsed_type{
                matrix_ref_type(std::vector<unsigned char>({
                    0x1C, 0x55, 0x55, 0x55, 0x55,
                    0x1C, 0x55, 0xE9, 0x55, 0x55,
                    0x1C, 0xBD, 0xBD, 0xE9, 0xBD,
                    0xE9, 0xE9, 0x55, 0x55, 0x1C,
                    0xE9, 0xBD, 0xBD, 0x55, 0x55,
                }).data(), boost::extents[5][5]),
                sequences_type({
                    {0xE9, 0x55, 0xBD},
                    {0xE9, 0x1C, 0xE9}
                })
            }
        );
    }

    {
        const cv::Mat image = cv::imread("./examples/5x5_2.11.png");
        const detected_type detected = detect(image);
        const parsed_type parsed = parse(image, detected.matrix_length.value(), detected.sequence_lengths.value());
        expect_eq(
            parsed, parsed_type{
                matrix_ref_type(std::vector<unsigned char>({
                    0xBD, 0x55, 0xE9, 0xBD, 0x55,
                    0x1C, 0xE9, 0x55, 0x55, 0xBD,
                    0xE9, 0x55, 0xBD, 0xBD, 0xE9,
                    0x1C, 0xBD, 0x55, 0x55, 0xE9,
                    0x1C, 0x1C, 0x1C, 0xBD, 0x55,
                }).data(), boost::extents[5][5]),
                sequences_type({
                    {0x55, 0xBD, 0xE9},
                    {0x1C, 0x55, 0xBD}
                })
            }
        );
    }

    {
        const cv::Mat image = cv::imread("./examples/5x5_2.12.png");
        const detected_type detected = detect(image);
        const parsed_type parsed = parse(image, detected.matrix_length.value(), detected.sequence_lengths.value());
        expect_eq(
            parsed, parsed_type{
                matrix_ref_type(std::vector<unsigned char>({
                    0xE9, 0x55, 0xBD, 0xE9, 0x55,
                    0x55, 0x55, 0x55, 0x55, 0x55,
                    0x55, 0x55, 0xBD, 0x1C, 0x1C,
                    0xBD, 0xBD, 0x55, 0x1C, 0xBD,
                    0x1C, 0xE9, 0x1C, 0x1C, 0xBD,
                }).data(), boost::extents[5][5]),
                sequences_type({
                    {0x55, 0xE9, 0x1C, 0x55},
                    {0x55, 0x55, 0x55}
                })
            }
        );
    }

    {
        const cv::Mat image = cv::imread("./examples/6x6_3.1.png");
        const detected_type detected = detect(image);
        const parsed_type parsed = parse(image, detected.matrix_length.value(), detected.sequence_lengths.value());
        expect_eq(
            parsed, parsed_type{
                matrix_ref_type(std::vector<unsigned char>({
                    0x1C, 0x55, 0x1C, 0x1C, 0x1C, 0x7A,
                    0x55, 0x55, 0xE9, 0x1C, 0x55, 0x7A,
                    0x1C, 0x1C, 0xBD, 0x7A, 0x1C, 0x1C,
                    0x55, 0x1C, 0x1C, 0x55, 0xE9, 0xE9,
                    0x1C, 0xBD, 0x1C, 0x7A, 0xE9, 0xBD,
                    0x7A, 0xBD, 0xBD, 0x55, 0x1C, 0xBD,
                }).data(), boost::extents[6][6]),
                sequences_type({
                    {},
                    {0x1C, 0xBD, 0x1C},
                    {0xBD, 0x55, 0x1C}
                })
            }
        );
    }

    {
        const cv::Mat image = cv::imread("./examples/6x6_3.2.png");
        const detected_type detected = detect(image);
        const parsed_type parsed = parse(image, detected.matrix_length.value(), detected.sequence_lengths.value());
        expect_eq(
            parsed, parsed_type{
                matrix_ref_type(std::vector<unsigned char>({
                    0xBD, 0x1C, 0xE9, 0x1C, 0x1C, 0x55,
                    0x7A, 0xBD, 0x1C, 0x1C, 0xBD, 0x1C,
                    0x55, 0x55, 0x7A, 0x55, 0x1C, 0x1C,
                    0x1C, 0x55, 0x7A, 0x55, 0x1C, 0x1C,
                    0x55, 0x7A, 0xBD, 0xBD, 0xBD, 0x7A,
                    0x55, 0x1C, 0x1C, 0x1C, 0xE9, 0xE9,
                }).data(), boost::extents[6][6]),
                sequences_type({
                    {0xE9, 0x1C, 0x1C},
                    {0x1C, 0x1C, 0xBD},
                    {0x55, 0x1C, 0x7A}
                })
            }
        );
    }

    {
        const cv::Mat image = cv::imread("./examples/6x6_3.3.png");
        const detected_type detected = detect(image);
        const parsed_type parsed = parse(image, detected.matrix_length.value(), detected.sequence_lengths.value());
        expect_eq(
            parsed, parsed_type{
                matrix_ref_type(std::vector<unsigned char>({
                    0xE9, 0x1C, 0x1C, 0xBD, 0xBD, 0x1C,
                    0x7A, 0x7A, 0x7A, 0x7A, 0x55, 0xBD,
                    0x7A, 0x7A, 0x1C, 0x55, 0xE9, 0x1C,
                    0x55, 0xBD, 0x55, 0x7A, 0x1C, 0x7A,
                    0x7A, 0x55, 0x7A, 0x7A, 0x55, 0x1C,
                    0x55, 0x1C, 0xE9, 0x7A, 0x1C, 0xE9,
                }).data(), boost::extents[6][6]),
                sequences_type({
                    {0x7A, 0x1C, 0xBD},
                    {0x55, 0x7A, 0x7A},
                    {0x7A, 0x7A, 0x7A, 0x55}
                })
            }
        );
    }

    {
        const cv::Mat image = cv::imread("./examples/6x6_3.4.png");
        const detected_type detected = detect(image);
        const parsed_type parsed = parse(image, detected.matrix_length.value(), detected.sequence_lengths.value());
        expect_eq(
            parsed, parsed_type{
                matrix_ref_type(std::vector<unsigned char>({
                    0xE9, 0xE9, 0x7A, 0x55, 0x1C, 0x55,
                    0x55, 0xBD, 0x7A, 0xBD, 0x7A, 0x55,
                    0x55, 0xBD, 0x55, 0x55, 0x1C, 0x55,
                    0x55, 0x1C, 0xBD, 0x7A, 0x7A, 0xE9,
                    0xBD, 0x1C, 0x1C, 0x7A, 0x7A, 0x55,
                    0x55, 0xBD, 0x7A, 0xBD, 0x1C, 0xBD,
                }).data(), boost::extents[6][6]),
                sequences_type({
                    {0xBD, 0xBD, 0x7A},
                    {0x7A, 0xBD, 0xBD},
                    {0x7A, 0x7A, 0x55, 0x55}
                })
            }
        );
    }

    {
        const cv::Mat image = cv::imread("./examples/6x6_3.5.png");
        const detected_type detected = detect(image);
        const parsed_type parsed = parse(image, detected.matrix_length.value(), detected.sequence_lengths.value());
        expect_eq(
            parsed, parsed_type{
                matrix_ref_type(std::vector<unsigned char>({
                    0x7A, 0x7A, 0xE9, 0x1C, 0x55, 0xBD,
                    0xBD, 0xE9, 0x1C, 0x7A, 0x7A, 0xBD,
                    0x7A, 0x1C, 0x1C, 0xBD, 0x55, 0x7A,
                    0xBD, 0x1C, 0x7A, 0x55, 0x7A, 0x7A,
                    0x55, 0x55, 0x55, 0x1C, 0x7A, 0x7A,
                    0x7A, 0x55, 0xE9, 0x7A, 0x1C, 0x1C,
                }).data(), boost::extents[6][6]),
                sequences_type({
                    {0x7A, 0x7A, 0xBD},
                    {0x7A, 0x1C, 0x55},
                    {0xBD, 0x7A, 0xE9}
                })
            }
        );
    }

    {
        const cv::Mat image = cv::imread("./examples/6x6_3.6.png");
        const detected_type detected = detect(image);
        const parsed_type parsed = parse(image, detected.matrix_length.value(), detected.sequence_lengths.value());
        expect_eq(
            parsed, parsed_type{
                matrix_ref_type(std::vector<unsigned char>({
                    0x1C, 0x55, 0x7A, 0xBD, 0x7A, 0xE9,
                    0x55, 0x7A, 0xE9, 0x1C, 0x55, 0x7A,
                    0x1C, 0x7A, 0x55, 0x1C, 0x7A, 0x7A,
                    0x55, 0x55, 0x55, 0xBD, 0xE9, 0x7A,
                    0x1C, 0x7A, 0x1C, 0x1C, 0xBD, 0x1C,
                    0xE9, 0x7A, 0x55, 0x1C, 0xE9, 0xBD,
                }).data(), boost::extents[6][6]),
                sequences_type({
                    {0x7A, 0x1C, 0x1C},
                    {0x7A, 0xE9, 0x7A},
                    {0x7A, 0x55, 0x7A}
                })
            }
        );
    }

    {
        const cv::Mat image = cv::imread("./examples/6x6_3.7.png");
        const detected_type detected = detect(image);
        const parsed_type parsed = parse(image, detected.matrix_length.value(), detected.sequence_lengths.value());
        expect_eq(
            parsed, parsed_type{
                matrix_ref_type(std::vector<unsigned char>({
                    0xBD, 0x1C, 0x1C, 0x55, 0x55, 0x1C,
                    0x1C, 0x7A, 0x55, 0x7A, 0x1C, 0x55,
                    0xBD, 0x7A, 0x1C, 0x7A, 0x55, 0xBD,
                    0x1C, 0xBD, 0xE9, 0x55, 0xE9, 0x55,
                    0x7A, 0x55, 0xE9, 0xE9, 0x1C, 0x55,
                    0x1C, 0x1C, 0x7A, 0xBD, 0xBD, 0xBD,
                }).data(), boost::extents[6][6]),
                sequences_type({
                    {0x1C, 0x55, 0x7A},
                    {0xE9, 0x1C, 0x1C},
                    {0x7A, 0x55, 0xE9}
                })
            }
        );
    }

    {
        const cv::Mat image = cv::imread("./examples/6x6_3.8.png");
        const detected_type detected = detect(image);
        const parsed_type parsed = parse(image, detected.matrix_length.value(), detected.sequence_lengths.value());
        expect_eq(
            parsed, parsed_type{
                matrix_ref_type(std::vector<unsigned char>({
                    0xBD, 0xBD, 0x1C, 0x1C, 0x55, 0x7A,
                    0x1C, 0x55, 0xE9, 0x7A, 0x7A, 0x55,
                    0xBD, 0x1C, 0x1C, 0x7A, 0x1C, 0x55,
                    0x55, 0x55, 0x55, 0x1C, 0xBD, 0xBD,
                    0x55, 0x55, 0xE9, 0x7A, 0x7A, 0xBD,
                    0xBD, 0xBD, 0x55, 0xE9, 0x55, 0x1C,
                }).data(), boost::extents[6][6]),
                sequences_type({
                    {0x55, 0xBD, 0x7A},
                    {0x7A, 0x55, 0xBD},
                    {0xBD, 0x55, 0x1C, 0x55}
                })
            }
        );
    }

    {
        const cv::Mat image = cv::imread("./examples/6x6_3.9.png");
        const detected_type detected = detect(image);
        const parsed_type parsed = parse(image, detected.matrix_length.value(), detected.sequence_lengths.value());
        expect_eq(
            parsed, parsed_type{
                matrix_ref_type(std::vector<unsigned char>({
                    0x1C, 0x1C, 0x7A, 0x7A, 0x55, 0xE9,
                    0x7A, 0xBD, 0x55, 0x7A, 0x1C, 0x55,
                    0x1C, 0xE9, 0x1C, 0x7A, 0x7A, 0x1C,
                    0x7A, 0x1C, 0x55, 0x7A, 0x55, 0x1C,
                    0x55, 0xE9, 0x7A, 0x1C, 0xBD, 0x1C,
                    0x55, 0xE9, 0xE9, 0x7A, 0xBD, 0x7A,
                }).data(), boost::extents[6][6]),
                sequences_type({
                    {0x55, 0x1C},
                    {0x1C, 0x7A},
                    {0xBD, 0x1C, 0x1C}
                })
            }
        );
    }

    {
        const cv::Mat image = cv::imread("./examples/6x6_3.10.png");
        const detected_type detected = detect(image);
        const parsed_type parsed = parse(image, detected.matrix_length.value(), detected.sequence_lengths.value());
        expect_eq(
            parsed, parsed_type{
                matrix_ref_type(std::vector<unsigned char>({
                    0x55, 0xE9, 0x55, 0xE9, 0x55, 0xE9,
                    0xE9, 0x1C, 0x7A, 0x7A, 0x1C, 0x1C,
                    0xE9, 0x55, 0xE9, 0xE9, 0x1C, 0x55,
                    0x55, 0x55, 0x55, 0xBD, 0x55, 0x1C,
                    0x55, 0x1C, 0x1C, 0x55, 0x1C, 0x55,
                    0xBD, 0x1C, 0x7A, 0x7A, 0x7A, 0xE9,
                }).data(), boost::extents[6][6]),
                sequences_type({
                    {0x55, 0xBD, 0xE9},
                    {0x7A, 0xBD, 0x55},
                    {0x55, 0x55, 0x7A}
                })
            }
        );
    }

    {
        const cv::Mat image = cv::imread("./examples/6x6_3.11.png");
        const detected_type detected = detect(image);
        const parsed_type parsed = parse(image, detected.matrix_length.value(), detected.sequence_lengths.value());
        expect_eq(
            parsed, parsed_type{
                matrix_ref_type(std::vector<unsigned char>({
                    0x55, 0xBD, 0x1C, 0x55, 0x55, 0x7A,
                    0x7A, 0xBD, 0x1C, 0xE9, 0x55, 0x1C,
                    0x1C, 0xBD, 0x7A, 0xBD, 0x7A, 0xBD,
                    0xBD, 0x7A, 0x7A, 0x55, 0x1C, 0x7A,
                    0x1C, 0xBD, 0x1C, 0x55, 0x7A, 0xBD,
                    0x7A, 0xBD, 0x1C, 0x7A, 0x7A, 0x55,
                }).data(), boost::extents[6][6]),
                sequences_type({
                    {0xBD, 0x7A, 0x1C},
                    {0x55, 0x7A, 0x7A},
                    {0xBD, 0x55, 0x55}
                })
            }
        );
    }

    {
        const cv::Mat image = cv::imread("./examples/6x6_3.12.png");
        const detected_type detected = detect(image);
        const parsed_type parsed = parse(image, detected.matrix_length.value(), detected.sequence_lengths.value());
        expect_eq(
            parsed, parsed_type{
                matrix_ref_type(std::vector<unsigned char>({
                    0x55, 0x55, 0x1C, 0x1C, 0x1C, 0x7A,
                    0x55, 0x1C, 0x55, 0x7A, 0x7A, 0x1C,
                    0x1C, 0x7A, 0x1C, 0x1C, 0xBD, 0x1C,
                    0x55, 0x55, 0x1C, 0x1C, 0x1C, 0xBD,
                    0x55, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C,
                    0x1C, 0x55, 0x7A, 0x55, 0x7A, 0xBD,
                }).data(), boost::extents[6][6]),
                sequences_type({
                    {0x7A, 0x1C},
                    {0x1C, 0x1C, 0x1C},
                    {0x1C, 0x55, 0x1C}
                })
            }
        );
    }

    {
        const cv::Mat image = cv::imread("./examples/6x6_3.13.png");
        const detected_type detected = detect(image);
        const parsed_type parsed = parse(image, detected.matrix_length.value(), detected.sequence_lengths.value());
        expect_eq(
            parsed, parsed_type{
                matrix_ref_type(std::vector<unsigned char>({
                    0x1C, 0x55, 0x1C, 0x7A, 0x7A, 0x7A,
                    0x1C, 0x1C, 0xE9, 0x1C, 0xBD, 0x1C,
                    0x7A, 0xBD, 0x7A, 0x1C, 0xE9, 0x55,
                    0x55, 0x1C, 0xE9, 0x55, 0x1C, 0x1C,
                    0x1C, 0x1C, 0x1C, 0x55, 0x7A, 0x55,
                    0xBD, 0x55, 0x1C, 0x1C, 0x7A, 0x1C,
                }).data(), boost::extents[6][6]),
                sequences_type({
                    {0x1C, 0xE9, 0x7A},
                    {0x7A, 0x1C, 0x1C},
                    {0x7A, 0xBD, 0x55}
                })
            }
        );
    }

    {
        const cv::Mat image = cv::imread("./examples/6x6_3.14.png");
        const detected_type detected = detect(image);
        const parsed_type parsed = parse(image, detected.matrix_length.value(), detected.sequence_lengths.value());
        expect_eq(
            parsed, parsed_type{
                matrix_ref_type(std::vector<unsigned char>({
                    0x1C, 0xE9, 0x55, 0x55, 0x55, 0x7A,
                    0x55, 0x7A, 0x1C, 0x7A, 0x7A, 0x1C,
                    0x1C, 0x1C, 0xBD, 0xBD, 0x1C, 0x7A,
                    0x1C, 0x1C, 0xE9, 0x1C, 0x1C, 0x1C,
                    0x55, 0x7A, 0xBD, 0xE9, 0x55, 0x1C,
                    0x1C, 0x55, 0x7A, 0x1C, 0x7A, 0x55,
                }).data(), boost::extents[6][6]),
                sequences_type({
                    {0x7A, 0x55},
                    {0x55, 0x1C, 0xBD},
                    {0xBD, 0x1C, 0x55, 0xE9}
                })
            }
        );
    }

    {
        const cv::Mat image = cv::imread("./examples/6x6_3.15.png");
        const detected_type detected = detect(image);
        const parsed_type parsed = parse(image, detected.matrix_length.value(), detected.sequence_lengths.value());
        expect_eq(
            parsed, parsed_type{
                matrix_ref_type(std::vector<unsigned char>({
                    0x1C, 0x1C, 0x55, 0x1C, 0xE9, 0xBD,
                    0xBD, 0xBD, 0xE9, 0x1C, 0xBD, 0x55,
                    0x7A, 0xBD, 0x55, 0x1C, 0xBD, 0x55,
                    0x1C, 0xE9, 0x7A, 0x55, 0xBD, 0xBD,
                    0x7A, 0x7A, 0xE9, 0x1C, 0x7A, 0x55,
                    0x7A, 0xBD, 0xE9, 0x7A, 0x7A, 0x7A,
                }).data(), boost::extents[6][6]),
                sequences_type({
                    {0x55, 0x7A, 0x7A},
                    {0x55, 0xBD, 0x55},
                    {0x7A, 0xE9, 0x1C, 0x7A}
                })
            }
        );
    }

    {
        const cv::Mat image = cv::imread("./examples/6x6_3.16.png");
        const detected_type detected = detect(image);
        const parsed_type parsed = parse(image, detected.matrix_length.value(), detected.sequence_lengths.value());
        expect_eq(
            parsed, parsed_type{
                matrix_ref_type(std::vector<unsigned char>({
                    0x1C, 0x1C, 0x55, 0x55, 0xE9, 0xE9,
                    0xBD, 0x55, 0x1C, 0x1C, 0x55, 0x55,
                    0x1C, 0x55, 0x55, 0xBD, 0x1C, 0x1C,
                    0x7A, 0x1C, 0xBD, 0x1C, 0x1C, 0x1C,
                    0x1C, 0x55, 0x7A, 0x55, 0x1C, 0x55,
                    0x1C, 0xBD, 0x1C, 0x1C, 0xBD, 0xE9,
                }).data(), boost::extents[6][6]),
                sequences_type({
                    {},
                    {0x55, 0x1C, 0x55},
                    {0x1C, 0x1C, 0x55}
                })
            }
        );
    }
}

void test_solve() {
    #if (0)
    const std::size_t length = 3;
    const std::size_t buffer = 5;
    const unsigned char array[length][length] = {
        {0x1C, 0x55, 0xE9},
        {0x1C, 0x55, 0x55},
        {0xE9, 0xBD, 0xE9}
    };
    #else
    const std::size_t length = 5;
    const std::size_t buffer = 8;
    const unsigned char array[length][length] = {
        {0x1C, 0x55, 0xE9, 0x55, 0x1C},
        {0x1C, 0x55, 0x55, 0xBD, 0xE9},
        {0xE9, 0xBD, 0xE9, 0x1C, 0x1C},
        {0x55, 0xBD, 0xBD, 0xE9, 0x55},
        {0x55, 0xE9, 0x1C, 0x55, 0x55}
    };
    #endif
    const sequences_type sequences({
        {0x1C, 0x55},
        {0x1C, 0x1C, 0xE9},
        {0xBD, 0x1C, 0x55, 0x1C}
    });
    solve(
        boost::const_multi_array_ref<unsigned char, 2>((const unsigned char *) array, boost::extents[length][length]),
          sequences,
          buffer
    );
}

int main(int argc, char * argv[]) {

    test_parse();
    test_solve();

    return EXIT_SUCCESS;
}
