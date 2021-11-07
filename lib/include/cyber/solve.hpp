#pragma once

#include <cyber/common.hpp>

struct solved_type {
    path_type path;
    score_type score;
};

solved_type solve(
    const matrix_type & matrix,
    const sequences_type & sequences,
    buffer_length_type buffer
);
