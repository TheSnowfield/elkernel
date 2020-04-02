# elKernel

#### 計劃用屑語言做一個垃圾内核跑一個貪吃蛇 (草
#### 也算是作爲一個課題 學習如何製作一個OS

---

## 🤔 構建先決條件
  - 需要WSL環境
  - GCC >= `v8.3.0 (WSL)`
  - GAS >= `v2.31.1 (WSL)`
  - 易語言 >= `v5.5`

## 🐴 構建項目及環境
### Boot Stripper 部分
  1. 進入 `source/krnln.boot.stripper`
  2. 使用易語言IDE打開 `stripper.e`
  3. 使用靜態編譯方式 編譯易代碼到本目錄 
  4. 編譯成功名爲 `stripper.exe` 請勿刪除該文件

### Core Main 部分
  1. 進入 `source/krnln.core.main`
  2. 使用易語言IDE打開 `krnln.core.main.e` 
  3. 使用靜態編譯方式 編譯易代碼 
  4. 編譯將會失敗並殘留一個Win32 COFF文件 請勿刪除該文件

### Bootable Floppy 部分
  1. 使用 `Visual Studio 2019` 打開解決方案文件
  2. 直接構建

## 😩 調試環境
  > 這裏只例舉 qEmu 版本
  ```batch
    @echo off
    set PATH=%PATH%;YOUR_QEMU_INSTALLATION
    qemu-system-i386 -gdb tcp::23333 -fda ./elkernel.img
  ```
  執行批處理文件 啓動GDB 附加即可。<br>
  有關GDB調試方面不再贅述。
