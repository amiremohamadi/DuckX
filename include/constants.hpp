#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

namespace duckx {
typedef unsigned const int formatting_flag;

// text-formatting flags
formatting_flag none = 0;
formatting_flag bold = 1 << 0;
formatting_flag italic = 1 << 1;
formatting_flag underline = 1 << 2;
formatting_flag emphasis = 1 << 3;
formatting_flag strikethrough = 1 << 4;
formatting_flag superscript = 1 << 5;
formatting_flag subscript = 1 << 6;
formatting_flag smallcaps = 1 << 7;
formatting_flag shadow = 1 << 8;
formatting_flag allcaps = 1 << 9;
formatting_flag relief = 1 << 10;
formatting_flag intaglio = 1 << 11;
formatting_flag doublestrikethrough = 1 << 12;
formatting_flag hollow = 1 << 13;
formatting_flag hide = 1 << 14;

typedef enum paragraph_alignment
{
	align_left,
	align_center,
	align_right,
	align_both
};

} // namespace duckx

#endif