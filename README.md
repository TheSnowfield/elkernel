## elKernel

An x86 toy kernel implementation written in EPL.

### Before build
  - x86 gcc
  - cmake
  - python3
  - 易語言 >= `v5.1`

### Build Steps
#### Compile E code in the IDE
  2. Open `source/elkernel.e` in the IDE
  3. Compile the code via 'Statically Compile(靜態編譯)'
  4. Compiler fails with a Win32 COFF file, please do not delete it.

#### Compile the code
  1. cmake -Bbuild && cd build && make

### How To Debug
  > Use QEMU to debug the kernel
  ```batch
    @echo off
    set PATH=%PATH%;YOUR_QEMU_INSTALLATION
    qemu-system-i386 -gdb tcp::23333 -fda ./elkernel-fdd.img
  ```
  Execute the batch file, then attach to the QEMU instance.<br/>
