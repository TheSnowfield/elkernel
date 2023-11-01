// 屑語言核心支持庫内部實現
// 讀屬性 不用窗口組件 或許沒什麽用

__declspec(naked)
krnl_MReadProperty() {
  __asm { ret };
}