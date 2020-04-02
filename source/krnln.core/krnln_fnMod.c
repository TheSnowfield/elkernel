//  算术运算 - 求余数
//
//  调用格式： 〈双精度小数型〉 求余数 （双精度小数型 被除数，双精度小数型 除数，... ） - 系统核心支持库->算术运算
//  英文名称：mod
//  求出两个数值的商，并返回余数部分，运算符号为“ % ”或“Mod”。本命令为初级命令。命令参数表中最后一个参数可以被重复添加。
//  参数<1>的名称为“被除数”，类型为“双精度小数型（double）”。
//  参数<2>的名称为“除数”，类型为“双精度小数型（double）”。

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
