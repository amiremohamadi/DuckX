#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

namespace duckx {
typedef unsigned const int formatting_flag;

// text-formatting flags
formatting_flag none = 0;
formatting_flag bold = 1 << 0;
formatting_flag italic = 1 << 1;
formatting_flag underline = 1 << 2;
formatting_flag strikethrough = 1 << 3;
formatting_flag superscript = 1 << 4;
formatting_flag subscript = 1 << 5;
formatting_flag smallcaps = 1 << 6;
formatting_flag shadow = 1 << 7;
} // namespace duckx

#endif