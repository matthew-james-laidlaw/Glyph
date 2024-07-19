add_library(libglyph PosixTerminal.cpp WindowsTerminal.cpp)
target_include_directories(libglyph PUBLIC ${PROJECT_SOURCE_DIR}/include)
