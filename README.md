# Search

A simple, recursive file search tool written in Rust.
Currently, it only supports searching for files within the current directory. And is only for linux and other unix-like / unix-based systems.

## Features

*   Recursively searches directories for specified file names.
*   Supports a `--debug` flag to enable verbose logging.
*   Outputs the full path to any found files.

## Usage

```bash
search <file_to_find_1> <file_to_find_2> ... [--debug]
```

### Arguments

*   `<file_to_find_X>`: The name of the file to search for. You can specify multiple file names.
*   `--debug`: Enables debug logging, showing detailed scan progress and potential errors.

## Example

To search for `myfile.txt` and `another.log` in the current directory and its subdirectories, with debug logging enabled:

```bash
search myfile.txt another.log --debug
```

This will output:

```
Debug : Debug mode enabled
Search Init : Attempting to find: 'myfile.txt'
Search : Scanning directory: /home/user/projects/search
Search : Checking: /home/user/projects/search/src
Search : Entering directory: /home/user/projects/search/src
Search : Scanning directory: /home/user/projects/search/src
Search : Checking: /home/user/projects/search/src/main.rs
Search : Checking: /home/user/projects/search/src/lib.rs
Search : Entering directory: /home/user/projects/search/src/some_subdir
... (continues until file is found or all directories are scanned)
Search : Found file: /home/user/projects/search/src/some_subdir/myfile.txt
File found at: /home/user/projects/search/src/some_subdir/myfile.txt
Result : Search for 'myfile.txt' completed: Found
Search Init : Attempting to find: 'another.log'
...
```

## Development

This project was built using Rust and relies on the `termcolor` crate for colored output.

## License

This project is licensed under the GPL-3.0 license. See [LICENSE](https://www.gnu.org/licenses/gpl-3.0.txt) for more details.
