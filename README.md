# Template for C++ projects using CMake + Conan + VSCode

## Prerequisites

1. Python 3.6 or higher
2. CMake 3.23 or higher
3. Ninja 1.11 or higher
4. LLVM 14: clang, libcxx, sanitizers, clang-format, clang-tidy

## Setup

1. Get Conan 2.0 (currently in beta): `pip3 install conan --pre [--upgrade]`
2. Detect a default profile: `conan profile detect`
3. Configure Conan stuff: `conan install . -pr:h ./conan/linux-clang14 -b missing`.

Optional stuff for `conan install`:
* Pass `-o:h sanitize=Address` (and other sanitizers) to configure sanitizer support.
* Pass `-s:h build_type=Release` for release build

## Build

```
cmake --preset sanitize_none
cmake --preset sanitize_address
cmake --build --preset sanitize_none-debug [--target test]
cmake --build --preset sanitize_none-release [--target test]
cmake --build --preset sanitize_address-release [--target test]
```

In VSCode, you can reload a window and select presets in a status line.
