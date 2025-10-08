# AGENTS.md

This file provides guidance for AI agents working with the gopher64 codebase.

## Project Overview

Gopher64 is a Nintendo 64 emulator written in Rust. It aims for a good balance of performance and accuracy. It supports features like netplay, save states, and cheats.

## Code Structure

The main application logic is in `src/main.rs`. Other key files and directories include:

- `src/`: Contains the core source code of the emulator.
  - `src/ui/`: Slint-based UI code.
  - `src/device/`: Code for emulating different N64 devices.
  - `src/netplay.rs`: Handles netplay functionality.
  - `src/savestates.rs`: Manages save and load states.
  - `src/cheats.rs`: Implements cheat code support.
- `parallel-rdp/`: The parallel RDP (Reality Display Processor) plugin.
- `data/`: Contains data files used by the emulator.
- `Cargo.toml`: The Rust package manifest, defining dependencies and project metadata.
- `build.rs`: The build script for the project.

## How to build

Follow the instructions in the `README.md` file for building the project. The basic steps are:

1. Install Rust: `https://www.rust-lang.org/tools/install`
2. For Linux, install SDL3 dependencies.
3. Clone the repository recursively: `git clone --recursive https://github.com/gopher64/gopher64.git`
4. Change into the project directory: `cd gopher64`
5. Build in release mode: `cargo build --release`

The final executable will be in `./target/release/gopher64`.

## How to run tests

This project does not currently have an automated test suite. All testing is done manually. When making changes, please test the following:

1.  Launch the emulator with a known-good ROM.
2.  Verify that the game boots and is playable.
3.  Test save states (saving and loading).
4.  If your changes affect netplay, test joining and playing a netplay session.

## Contribution Guidelines

- Before starting substantial work, please open a GitHub issue or contact `loganmc10` on Discord to discuss your proposed changes.
- Ensure your code is formatted with `rustfmt`.
- Keep changes focused on a single feature or bug fix.
- Test your changes thoroughly before submitting a pull request.