#include <cyber/mouse.hpp>

#include <Windows.h>

void mouse_move(cv::Point2l p) {
    std::array<INPUT,1> input;
    ZeroMemory(input.data(), sizeof(decltype(input)::value_type) * input.size());

    input[0].type = INPUT_MOUSE;
    input[0].mi.dx = p.x;
    input[0].mi.dy = p.y;
    input[0].mi.dwFlags = MOUSEEVENTF_MOVE;

    SendInput(input.size(), input.data(), sizeof(decltype(input)::value_type));
}

void mouse_press(bool press) {
    std::array<INPUT,1> input;
    ZeroMemory(input.data(), sizeof(decltype(input)::value_type) * input.size());

    input[0].type = INPUT_MOUSE;
    input[0].mi.dwFlags = press ? MOUSEEVENTF_LEFTDOWN : MOUSEEVENTF_LEFTUP;

    SendInput(input.size(), input.data(), sizeof(decltype(input)::value_type));
}