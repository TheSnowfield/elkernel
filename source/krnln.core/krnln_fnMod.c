//  数值转换 - 到整数
//
//  调用格式： 〈整数型〉 到整数 （通用型 待转换的文本或数值） - 系统核心支持库->数值转换
//  英文名称：ToInt
//  返回包含于文本内的整数值，文本中是一个适当类型的数值，支持全角书写方式。本命令也可用作将其他类型的数据转换为整数。本命令为初级命令。
//  参数<1>的名称为“待转换的文本或数值”，类型为“通用型（all）”。

#include "stdafx.h"

void __cdecl
krnln_fnMod(PMDATA_INF pRetData, UINT32 uArgCount, PMDATA_INF pArgInf) {

  // 遍歷參數 逐一計算
  INT32 dResult = pArgInf[0].m_double;
  for (int i = 1; i < (int)uArgCount; ++i) {
    (int)dResult %= (int)(&pArgInf[i].m_double);
  }

  // 返回
  pRetData->m_double = (DOUBLE)dResult;
}
