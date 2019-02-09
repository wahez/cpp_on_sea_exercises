# Building and running the examples

## Setup

### Install Google Benchmark

Download Google Benchmark from <https://github.com/google/benchmark> and install it to your system (please see steps below).

### Installation

#### Common

```bash
mkdir bm && cd bm # optional (create directory specifically for benchmark)
git clone https://github.com/google/benchmark.git
git clone https://github.com/google/googletest.git benchmark/googletest
mkdir build && cd build
# cmake -G <generator> [options] ../benchmark (see platform steps)
```

#### Windows

```bash
cmake -G "Visual Studio 15 2017 Win64" -Dgtest_force_shared_crt=ON ..\benchmark\ # for visual studio build files (.sln)
```

#### *nix/macOS

```bash
cmake ../benchmark/ # for make build files
```

#### Common (continued)

```bash
cmake --build . --config Release --target install
```

Note: The install command may require `sudo` on *nix/macOS and administrator privileges on Windows (open cmd as Administrator). Please see miscellaneous for alternatives.

## Exercises

#### Common

```bash
cd <example folder> # e.g. bm_example
mkdir build && cd build
```

#### Windows

```bash
cmake -G "Visual Studio 15 2017 Win64" ..
```

#### *nix/macOS

```bash
cmake ..
```

#### Common

```bash
cmake --build . --config RelWithDebInfo
```

Code for example should now be compiled! 😄

#### Windows

```bash
.\Release\bm_example.exe # run the executable
```

#### *nix/macOS

```bash
./bm_example # run the executable
```

## Miscellaneous

If you wish to install benchmark to a custom folder, you can pass `-DCMAKE_INSTALL_PREFIX="<path>` to the `cmake` command.

e.g. (from benchmark /build folder)
```bash
cmake -DCMAKE_INSTALL_PREFIX="../install" -G "Visual Studio 15 2017 Win64" -Dgtest_force_shared_crt=ON ..\benchmark\
```

Then when building the examples, set `-DCMAKE_PREFIX_PATH` to the path of the installed library to search when running `cmake`.

e.g. (from exercise /build folder)
```bash
cmake -DCMAKE_PREFIX_PATH="..\..\bm\install" -G "Visual Studio 15 2017 Win64" ..
```

It is simpler to just install the library to the system default location if possible though.