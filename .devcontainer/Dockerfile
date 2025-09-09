# Use Microsoft C++ development image (includes build-essential, cmake, gdb)
FROM mcr.microsoft.com/vscode/devcontainers/cpp:0-ubuntu-22.04

# Install anything extra you might want (sqlite for optional SQL demo)
RUN apt-get update && apt-get install -y sqlite3 libsqlite3-dev && rm -rf /var/lib/apt/lists/*
