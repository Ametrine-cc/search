# Search

A simple, recursive file search tool written in C++.
Currently, it only supports searching for linux and other unix-like / unix-based systems, as Windows has not been tested or accounted for as a supported platform.

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

## Installation & Requirements

#### To install search you need the following:
*   `cmake` - A cross-platform build system.
*   `Kamakazi` -  The C++ log library by Ametrine Foundation
*   `gcc` or `clang` - A C++ compiler.
*   `sudo` - A command-line utility for executing commands with administrative privileges.

Install Kamakazi from the [github](https://github.com/Ametrine-cc/Kamakazi)

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

# done!!!
``` 

To install with the install.sh script, run:

1. Clone the repository: 
```bash
git clone https://github.com/Ametrine-cc/search.git
cd search
```

2. Run the installation script

```bash
chmod +x install.sh
./install.sh

# done!!!
``` 

## Uninstallation

To uninstall the binary, run:

```bash
sudo rm -rf /usr/local/bin/search $HOME/.config/search
``` 

# Configuration file

The configuration file is located at `~/.config/search/config.lua`.
To customize search, you can modify this file. Using the following format:

```lua
local use_config = true

local explore_all = true
```

### use_config

If `use_config` is `true`, search will use the configuration file. If `false`, search will use default settings.

### explore_all

If `explore_all` is `true`, search will explore all files in the current directory. If `false`, search will only explore files in the current directory that match the search query.

## Development

This project was built using C++.

## License

This project is licensed under the GPLv3 license. See [LICENSE](LICENSE.md) [License source](https://www.gnu.org/licenses/gpl-3.0.en.html#license-text) for more details.
