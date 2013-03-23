#ifndef LCD19264_LCD19264_HPP_
#define LCD19264_LCD19264_HPP_

#include "config.h"

#ifdef USE_CH19264B
#include "ch19264b/ch19264b.hpp"
typedef class Ch19264b Lcd19264;
#endif  // USE_CH19264B

#endif  // LCD19264_LCD19264_HPP_

