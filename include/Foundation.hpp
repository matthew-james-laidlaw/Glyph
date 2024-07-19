#pragma once

#if defined(_WIN32) || defined(_WIN64)
#define __OS_WINDOWS__
#endif

#if defined(__APPLE__)
#define __OS_APPLE__
#endif

#if defined(__linux__)
#define __OS_LINUX__
#endif

#if defined(__OS_APPLE__) || defined(__OS_LINUX__)
#define __OS_POSIX__
#endif

#include <cstdint>
#include <cstddef>
#include <stdexcept>
#include <string>

using i8 = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

using isize = std::intmax_t;
using usize = std::uintmax_t;

using String = std::string;

using RuntimeError = std::runtime_error;