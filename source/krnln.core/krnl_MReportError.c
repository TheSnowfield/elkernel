// 屑語言核心支持庫内部實現
// 報告錯誤 目前沒什麽用

__declspec(naked)
krnl_MReportError() {
  __asm { ret };
}