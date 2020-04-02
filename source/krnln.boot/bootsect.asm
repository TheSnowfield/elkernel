.intel_syntax noprefix
.equ BOOTSTART, 0x07c0
.equ KRNLNBOOT, 0x07e0
.extern _krnl_MMain

.code16
.text
  .global _entry
  _entry:

  # 清除寄存器 
  # 不清除會導致在各個仿真器/虛擬機上行爲不同
  mov ax, 0x0000
  mov cx, ax
  mov dx, ax
  mov bx, ax
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  # 重置顯示器
  call _func_reset_screen

  # 打印字串
  lea ax, _msg_load
  call _func_print_str2

  # 加載程序主體部分
  lea ax, _msg_ldisk
  call _func_print_str2
    call _func_disk_read
    cmp ax, 0x0000
    jnz _flag_e
  lea ax, _msg_ok
  call _func_print_str2

  # 加載全局描述符表
  lea ax, _msg_lgdt
  call _func_print_str2
    call _func_load_gdt
    cmp ax, 0x0000
    jnz _flag_e
  lea ax, _msg_ok
  call _func_print_str2

  # 可以進入保護模式啦 萬歲
  lea ax, _msg_entrypm
  call _func_print_str2
    call _func_entry_pmode
    call _func_main
    # 這裏代碼就不會執行啦

  _flag_e:
  lea ax, _msg_failed
  call _func_print_str2

  hlt

  # 打印字符
  #   al = 字符
  _func_print_ch:
    mov ah, 0x0e
    int 0x10
  ret

  # 打印字串
  # 遍歷字串打印法
  #   ax = 字串指針
  _func_print_str:
    mov si, ax      # 參數 字串所在指針
    
    _flag_b:
      mov ax, [si]     # 取出數據
      cmp al, 0x00    # 是否爲\0
      jz _flag_a

      mov ah, 0x0e    # 中斷函數
      int 0x10        # 調用中斷函數
      inc si          # 指針遞增
      jmp _flag_b

    _flag_a:
  ret

  # 打印字串
  # 中斷函數打印法
  #   ax = 字串指針
  _func_print_str2:
    mov si, ax      # 參數 字串所在指針
    
    _flag_d:
      lodsb           # 加載指針
      cmp al, 0x00    # 是否加載成功
      jz _flag_c
      
      mov ah, 0x0e    # 中斷函數
      int 0x10
      jmp _flag_d

    _flag_c:
  ret

  # 重置默認顯示器
  _func_reset_screen:
    mov ax, 0x0003  # 設置顯示器 (80x25 16色文本)
    int 0x10
  ret

  # 將程序加載到内存
  # 返回 ax 加載是否成功
  _func_disk_read:
    mov ax, KRNLNBOOT # 中斷參數 緩衝區
    mov es, ax
    mov ah, 0x02      # 中斷函數
    mov bx, 0x0000    # 中斷參數 緩衝區偏移
    mov al, 0x40      # 中斷參數 讀取扇區數
    mov ch, 0x00      # 中斷參數 柱面號
    mov cl, 0x02      # 中斷參數 扇區號
    mov dh, 0x00      # 中斷參數 磁頭號
    mov dl, 0x00      # 中斷參數 驅動器號

    int 0x13          # 調用中斷
    cmp ah, 0x00      # 是否成功
    jnz _flag_f
    xor ax, ax        # 清空寄存器 返回成功
    
    _flag_f:
  ret

  # 加載全局描述符表
  _func_load_gdt:
    xchg bx,bx
    lgdt ds:[_GDT_HEADER] # 加載GDT
    mov ax, 0x0000
  ret

  # 進入保護模式
  _func_entry_pmode:
    xor eax, eax

    cli               # 關閉中斷
    
    in al, 0x92       # 使用快速 A20 門
    or al, 2          # 啓用 A20 綫
    out 0x92, al

    mov eax, cr0      # 啓用保護
    or al, 1
    mov cr0, eax

  ret

  # 調用上層代碼
  _func_main:
    jmp 0x08:_krnl_MMain  # 超級遠跳轉
                          # 一去不復返 2333
  ret


# 保存的字串
.org 0x150
  _msg_ok:      .asciz " OK!\r\n"
  _msg_failed:  .asciz " FAILED!\r\n"
  _msg_load:    .asciz "== Hello World! ==\r\n"
  _msg_ldisk:   .asciz "Loading elKernel..."
  _msg_lgdt:    .asciz "Loading GDT...     "
  _msg_entrypm: .asciz "Entry into Protected Mode..."

# 全局描述符表
.org 0x1D0
  _GDT_HEADER:
    .2byte _GDT_ENTRIES_END - _GDT_ENTRIES  # GDT Size
    .4byte _GDT_ENTRIES                     # GDT Base

  _GDT_ENTRIES:
    _GDT_NULL:
      .2byte 0x0000   # limit low
      .2byte 0x0000   # base low
      .byte  0x00     # base middle
      .byte  0x00     # access type
      .byte  0x00     # limit high, flags
      .byte  0x00     # base high

    _GDT_CODE32:
      # Base  0x00000000
      # Limit 0x000FFFFF
      # Access 1(Pr) 00(Privl) 1(S) 1(Ex) 0(DC) 1(RW) 1(Ac)
      # Flag   1(Gr) 1(Sz) 0(Null) 0(Null)
      .2byte 0xFFFF   # limit low
      .2byte 0x0000   # base low
      .byte  0x00     # base middle
      .byte  0x9A     # access type
      .byte  0xCF     # limit high, flags
      .byte  0x00     # base high

    _GDT_DATA:
      # Base  0x00000000
      # Limit 0x000FFFFF
      # Access 1(Pr) 00(Privl) 1(S) 0(Ex) 0(DC) 1(RW) 1(Ac)
      # Flag   1(Gr) 1(Sz) 0(Null) 0(Null)
      .2byte 0xFFFF   # limit low
      .2byte 0x0000   # base low
      .byte  0x00     # base middle
      .byte  0x93     # access type
      .byte  0xCF     # limit high, flags
      .byte  0x00     # base high

    _GDT_VIDEO:
  _GDT_ENTRIES_END:

# 可引導扇區標識符
# 填充空白區域對齊扇區
.org 0x1FE
  .2byte 0xAA55
