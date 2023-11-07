## elKernel

An x86 toy kernel implementation written in EPL.

### Before build
  - Need WSL(Windows Subsystem with Linux) environment
  - gas >= `v2.31.1 x86_64-linux-gnu (WSL)`
  - gld >= `v2.31.1 x86_64-linux-gnu (WSL)`
  - objcopy >= `v2.31.1 x86_64-linux-gnu (WSL)`
  - 易語言 >= `v5.5`
  - Visual Studio 2017 or greater

### Build Steps
#### Compile E code in the IDE
  2. Open `source/elkernel.e` in the IDE
  3. Compile the code via 'Statically Compile(靜態編譯)'
  4. Compiler fails with a Win32 COFF file, Do not delete it.

#### Bootable Floppy
  1. Open `build/elKernel.sln` in the Visual Studio
  2. Set `floppy.mk` as startup project
  3. Build (Ctrl+Shift+B)

### How To Debug
  > Use QEMU to debug the kernel
  ```batch
    @echo off
    set PATH=%PATH%;YOUR_QEMU_INSTALLATION
    qemu-system-i386 -gdb tcp::23333 -fda ./elkernel.img
  ```
  Execute the batch file, then attach to the QEMU instance.<br/>
