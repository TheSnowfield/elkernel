// 屑語言核心支持庫内部實現
// 沒什麽用的窗口消息循環

__declspec(naked) 
krnl_MMessageLoop() {
  __asm { ret };
}