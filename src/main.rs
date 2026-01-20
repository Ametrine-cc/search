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

// The search function now returns a Vec<PathBuf> of found files, and the caller can handle printing.
// This simplifies the search function's responsibility and avoids modifying a global static in a complex way.
fn search(file_name_to_find: &str, current_scan_dir: &PathBuf) -> Vec<PathBuf> {
    log(
        &format!("Scanning directory: {}", current_scan_dir.display()),
        "Search",
    );

    let mut found_in_this_dir = Vec::new();

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
            return found_in_this_dir; // Return empty vec on error
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
                    found_in_this_dir.push(entry_path.clone());
                }
            }
        } else if entry_path.is_dir() {
            log(
                &format!("Entering directory: {}", entry_path.display()),
                "Search",
            );
            let mut sub_found = search(file_name_to_find, &entry_path);
            found_in_this_dir.append(&mut sub_found);
        }
    }

    found_in_this_dir
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

    let mut all_found_files: Vec<PathBuf> = Vec::new();

    for val in search_terms {
        if !val.contains('-') {
            log(&format!("Attempting to find: '{}'", val), "Search Init");
            let mut found_files = search(&val, &initial_search_dir);
            all_found_files.append(&mut found_files);
        }
    }

    println!("Found files:");
    if all_found_files.is_empty() {
        println!("No files found.");
    } else {
        for file in &all_found_files {
            println!("{}", file.display());
        }
    }
}
