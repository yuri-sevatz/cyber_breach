#include <cyber/clicker.hpp>
#include <cyber/mouse.hpp>
#include <cyber/layout.hpp>

#include <Windows.h>

namespace {

void clicker_input(
    matrix_length_type matrix_length,
    const path_type & path
) {
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

    mouse_move(cv::Point(-65535,-65535));
    cv::Point prev(0, 0);

    for (const auto & position : path) {
        const cv::Point next(
            matrix_cell_begin.x + position[1] * matrix_cell_step.width + matrix_cell_step.width / 2,
            matrix_cell_begin.y + position[0] * matrix_cell_step.height + matrix_cell_step.height / 2
        );

        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        mouse_move(next - prev);
        mouse_press(true);
        mouse_press(false);
        prev = next;
    }
}

} // namespace

bool clicker(
    const char * name,
    matrix_length_type matrix_length,
    const path_type & path
) {
    HWND hwnd = FindWindowA(NULL, name);
    if (!hwnd) {
        std::cerr << "FindWindowA returned NULL" << std::endl;
        return false;
    }

    if (!SetForegroundWindow(hwnd)) {
        std::cerr << "SetForegroundWindow returned NULL" << std::endl;
        return false;
    }

    const std::chrono::seconds wait(5);
    const std::chrono::high_resolution_clock::duration poll = std::chrono::milliseconds(100);
    const std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    const std::chrono::high_resolution_clock::time_point finish = start + wait;
    while (GetForegroundWindow() != hwnd) {
        if (finish < std::chrono::high_resolution_clock::now()) {
            std::cerr << "GetForegroundWindow failed after " << wait.count() << " seconds" << std::endl;
            return false;
        } else {
            std::this_thread::sleep_for(poll);
        }
    }

    clicker_input(matrix_length, path);
    return true;
}