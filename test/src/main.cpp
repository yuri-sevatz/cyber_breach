#include <cstdlib>

#ifdef _WIN32
#include <cyber/init.hpp>
#endif
#include <cyber/detect.hpp>
#include <cyber/parse.hpp>
#include <cyber/solve.hpp>

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
#ifdef _WIN32
    init();
#endif

    test_solve();

    return EXIT_SUCCESS;
}
