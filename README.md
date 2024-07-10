## elkernel - elfOS

An x86 toy OS implementation written in EPL.

Will support the following features in the future:
  - [x] Kernel memory management
  - [x] Interrupt handling
  - [ ] VBE graphics
  - [ ] Standard driver model
  - [ ] File system model
  - [ ] Posix-compatible syscalls

This project is forked from old branch `snake`, see in the branch [snake](https://github.com/TheSnowfield/elkernel/tree/snake).

### Compile the kernel

For nightly build, please refer to the [GitHub Action](https://github.com/TheSnowfield/elkernel/actions) select latest successful build, then download the artifacts.

```bash
$ cmake . -B.build
$ cd .build && make
```

The [el-buildtool](https://github.com/TheSnowfield/el-buildtool/pkgs/container/el-buildtool) docker image will be pulled automatically during the build, then compiling the kernel code without install the EPL environment on your host.

See more details in the el-buildtool [repository](https://github.com/TheSnowfield/el-buildtool).

### How To Debug
  > Use QEMU to debug the kernel
  ```batch
    @echo off
    set PATH=%PATH%;YOUR_QEMU_INSTALLATION
    qemu-system-i386 -gdb tcp::23333 -fda ./elf-fdd.img
  ```
  Execute the batch file, then attach to the QEMU instance.<br/>

### LICENSE
Licensed under the GPL v2 license with ❤️.
