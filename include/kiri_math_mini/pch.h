#include <kiri_math_mini/logging.h>
#include <kiri_math_mini/platform.h>

#ifdef KIRI_MATH_WINDOWS

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#define NOMINMAX
#include <objbase.h>
#endif

#include <kiri_math_mini/private_helpers.h>
