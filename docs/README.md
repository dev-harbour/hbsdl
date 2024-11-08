# Simple DirectMedia Layer for Harbour

## Installing on Windows

- MSYS2

Before installing the packages, make sure you're running the MinGW 64-bit shell.

   ```
   pacman -S mingw-w64-x86_64-gcc
   pacman -S mingw-w64-x86_64-SDL2
   pacman -S mingw-w64-x86_64-SDL2_ttf
   git clone https://github.com/dev-harbour/hbsdl.git
   ```
- To build the static library, execute:

   ```
   hbmk2 hbsdl.hbp
   ```

- To build and run samples and test code, navigate to the tests directory and execute:

   ```
   cd tests
   hbmk2 window.prg
   ```
## Installing on Linux

- Debian

   ```
   sudo apt update
   sudo apt install libsdl2-dev libsdl2-ttf-dev
   git clone https://github.com/dev-harbour/hbsdl.git
   ```
- To build the static library, execute:

   ```
   hbmk2 hbsdl.hbp
   ```

- To build and run samples and test code, navigate to the examples directory and execute:

   ```
   cd tests
   hbmk2 window.prg
   ```
---
