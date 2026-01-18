use std::ffi::OsStr;
use std::fs;
use std::path::PathBuf;
use std::sync::Mutex;
use termcolor::{Color, ColorChoice, ColorSpec, StandardStream, WriteColor};

static SHOULD_LOG: Mutex<bool> = Mutex::new(false);

fn log(message: &str, type_log: &str) {
    if *SHOULD_LOG.lock().unwrap() {
        let mut stdout = StandardStream::stdout(ColorChoice::Always);
        stdout
            .set_color(ColorSpec::new().set_fg(Some(Color::Red)))
            .unwrap();
        print!("{} : ", type_log);
        stdout
            .set_color(ColorSpec::new().set_fg(Some(Color::Blue)))
            .unwrap();
        println!("{}", message);
        stdout.reset().unwrap();
    }
}

fn search(file_name_to_find: &str, current_scan_dir: &PathBuf) -> bool {
    log(
        &format!("Scanning directory: {}", current_scan_dir.display()),
        "Search",
    );

    let paths = match fs::read_dir(current_scan_dir) {
        Ok(p) => p,
        Err(e) => {
            log(
                &format!(
                    "Error reading directory {}: {}",
                    current_scan_dir.display(),
                    e
                ),
                "Error",
            );
            return false;
        }
    };

    for path_result in paths {
        let entry = match path_result {
            Ok(e) => e,
            Err(e) => {
                log(
                    &format!("Error accessing directory entry: {}", e),
                    "Warning",
                );
                continue;
            }
        };
        let entry_path = entry.path();

        log(&format!("Checking: {}", entry_path.display()), "Search");

        if entry_path.is_file() {
            if let Some(name) = entry_path.file_name() {
                if name == <str as AsRef<OsStr>>::as_ref(file_name_to_find) {
                    log(&format!("Found file: {}", entry_path.display()), "Search");
                    println!("File found at: {}", entry_path.display());
                    return true;
                }
            }
        } else if entry_path.is_dir() {
            log(
                &format!("Entering directory: {}", entry_path.display()),
                "Search",
            );
            if search(file_name_to_find, &entry_path) {
                return true;
            }
        }
    }

    false
}

fn main() {
    let mut search_terms: Vec<String> = Vec::new();

    for arg in std::env::args().skip(1) {
        if arg.starts_with('-') {
            if arg == "--debug" {
                *SHOULD_LOG.lock().unwrap() = true;
                log("Debug mode enabled", "Debug");
            } else {
                log(&format!("Unknown flag: {}", arg), "Warning");
            }
        } else {
            search_terms.push(arg);
        }
    }

    let initial_search_dir = std::env::current_dir().unwrap_or_else(|e| {
        log(&format!("Error getting current directory: {}", e), "Error");
        panic!("Failed to get current directory: {}", e);
    });

    for val in search_terms {
        if !val.contains('-') {
            log(&format!("Attempting to find: '{}'", val), "Search Init");
            if search(&val, &initial_search_dir) {
                log(&format!("Search for '{}' completed: Found", val), "Result");
            } else {
                log(
                    &format!("Search for '{}' completed: Not Found", val),
                    "Result",
                );
            }
        }
    }
}
