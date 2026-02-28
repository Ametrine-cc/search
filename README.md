# Search

A simple, recursive file search tool written in Rust.
Currently, it only supports searching for files within the current directory. And is only for linux and other unix-like / unix-based systems.

## Features

*   Recursively searches directories for specified file names.
*   Supports a `--debug` flag to enable verbose logging.
*   Outputs the full path to any found files.

## Usage

```bash
search <file_or_directory_name> [--debug]
```

### Arguments

*   `<file_or_directory_name>`: The name of the file or directory to search for.
*   `--debug`: Enables debug logging, showing detailed scan progress and potential errors.

## Example

To search for `git` in the current directory and its subdirectories, with debug logging enabled:

```bash
search git --debug
```

This will output:

```bash
Debug : Debug mode enabled
finding_folder | .git [DIR]
finding_file | README.md
finding_folder | .old [DIR]
finding_folder | src [DIR]
finding_file | CMakeLists.txt
finding_file | .gitignore
finding_folder | build [DIR]
...
```

## Development

This project was built using CPP.

## License

This project is licensed under the GPL-3.0 license. See [LICENSE](https://www.gnu.org/licenses/gpl-3.0.txt) for more details.
