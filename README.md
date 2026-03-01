# Search

A simple, recursive file search tool written in Rust.
Currently, it only supports searching for files within the current directory. And is only for linux and other unix-like / unix-based systems.

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

## Development

This project was built using C++.

## License

This project is licensed under the GPL-3.0 license. See [LICENSE](https://www.gnu.org/licenses/gpl-3.0.txt) for more details.
