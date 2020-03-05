.code16

.intel_syntax noprefix
.equ BOOTSTART, 0x07c0
.equ KRNLNBOOT, 0x07e0

.text
  .global _entry
  xchg bx, bx

# 將扇區内容加載到内存
  _entry:
  xchg bx, bx

  # mov ax, 0x7c00
  # mov ds, ax

# 設置顯示器 (80x25 16色文本)
#  mov ah, 0x00
#  mov al, 0x03
#  int 0x10

# 設置光標位置 (x=0, y=0)
#  mov ah, 0x02
#  mov dx, 0x00
#  int 0x10

# 試著打印字符串!
print:
  xchg bx, bx

  lea ax, _msg_load
  call _func_print_str2
  jmp print


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



# 保存的字串
_msg_load: .asciz "[ OK ] Loading elKernel...\r\n\0"


# 填充空白區域對齊扇區
.org 0x1FE

# 可引導扇區標識符
_flag:
  .word 0xAA55
