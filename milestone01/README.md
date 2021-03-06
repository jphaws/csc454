# Milestone 1

## Setup the Development Environment
As discussed in class, OS development requires a specialized build environment. For the first milesonte you need access to this environment. Ensure you are up-to-date on all class readings before continuing. You have a few different options:

- Download and use the .ova image I have already set up with your favorite VMM. The user name and password are both "cpe454".
- Install on your existing Linux installation and/or create your own VM. The steps for this are:
    - Ubuntu 20.04 LTS virtual machine (my preference) or native boot. Make sure the VM has at least 2GB of memory.
    - Qemu virtual machine for testing.
    - nasm for assembly
    - gcc cross-compiler targeting **x86_64-elf**. Follow the directions from the [OSDev Wiki](https://wiki.osdev.org/GCC_Cross-Compiler). 

Whatever you decide to do, make sure you have access to the development environment during our lab time. The computers in lab will not have the correct software installed. 

## Implementation Notes
- Source code versions built:
  - `binutils 2.38`
  - `gcc 11.2.0`
- Build notes
  - `export TARGET=x86_64-elf`
  - Run the top level `configure` with parameters given in the [osdev wiki](https://wiki.osdev.org/GCC_Cross-Compiler). 
  - Build binutils & gcc outside of the source tree.
  - Build gcc/Libgcc without the ["red zone"](https://wiki.osdev.org/Libgcc_without_red_zone).
