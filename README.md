# Search

A simple, recursive file search tool written in C++.
Currently, it only supports searching for linux and other unix-like / unix-based systems as Windows has not been tested or accounted for as a supported platform.

## Features

*   Recursively searches directories for specified file names.
*   Supports a `--debug` flag to enable verbose logging.
*   Outputs the full path to any found files.

## Usage

```bash
search <file_or_directory_name> [--debug|--full]
```

### Arguments

*   `<file_or_directory_name>`: The name of the file or directory to search for.
*   `--debug`: Enables debug logging, showing detailed scan progress and potential errors. Currently just adds pretty colors.
*   `--full`: Searches all directories, not just the current one, enters subdirectories it finds along the way.

#### Extra information: If specifying a file must add file extension for specific file types, not adding any extension will search for all files and directories with that name.

## Example

To search for `.cc` files in the current directory and its subdirectories (.cc being a c++ file extention), with debug logging enabled:

```bash
> search .cc --full --debug
search | Found : ./src/main.cc
search | Found : ./src/logs.cc
search | Found : ./build/CMakeFiles/search.dir/src/main.cc.o.d
search | Found : ./build/CMakeFiles/search.dir/src/logs.cc.o.d
search | Found : ./build/CMakeFiles/search.dir/src/logs.cc.o
search | Found : ./build/CMakeFiles/search.dir/src/main.cc.o
...
```

## Installation Uninstallation & Requirements

#### To install search you need the following:
*   `cmake` - A cross-platform build system.
*   `gcc` or `clang` - A C++ compiler.
*   `sudo` - A command-line utility for executing commands with administrative privileges.

To install from source follow these steps:

1. Clone the repository: 
```bash
git clone https://github.com/Ametrine-cc/search.git
cd search
``` 
2. Build the project: 
```bash
cmake -B build && cmake --build build
``` 
3. Install the binary: 
```bash
sudo make --install build
``` 

## Uninstallation

To uninstall the binary, run:
```bash
sudo rm -rf /usr/local/bin/search
``` 

## Development

This project was built using C++.

## License

This project is licensed under the GPLv3 license. See [LICENSE](LICENSE.md) [License source](https://www.gnu.org/licenses/gpl-3.0.en.html#license-text) for more details.
