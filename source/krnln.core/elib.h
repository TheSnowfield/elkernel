#ifndef __LIB_INF_H
#define __LIB_INF_H

typedef DATE*	PDATE;

///////////////////////////////////

// 仅用于库命令定义其参数或返回值的数据类型。
#define		_SDT_NULL		  0                                     // 空数据（内部使用，必须为零）

//   1、当用于定义库命令参数时，_SDT_ALL可以匹配所有数据类型（数组类型必须符合要求）。
//   2、由于定义为返回_SDT_ALL数据类型的库命令不允许返回数组或复合数据类型的数据
// 即用户或库自定义数据类型但不包含窗口或菜单组件，所以_SDT_ALL类型的数据只
// 可能为非数组的系统数据类型或窗口组件、菜单数据类型。
#define		_SDT_ALL	   	MAKELONG (MAKEWORD (0, 0), 0x8000)	  // （内部使用）

// 以下是由系统定义的基本数据类型
#define		SDT_BYTE		  MAKELONG (MAKEWORD (1, 1), 0x8000)		// 字节
#define		SDT_SHORT		  MAKELONG (MAKEWORD (1, 2), 0x8000)		// 短整数
#define		SDT_INT			  MAKELONG (MAKEWORD (1, 3), 0x8000)		// 整数
#define		SDT_INT64		  MAKELONG (MAKEWORD (1, 4), 0x8000)		// 长整数
#define		SDT_FLOAT		  MAKELONG (MAKEWORD (1, 5), 0x8000)		// 小数
#define		SDT_DOUBLE	  MAKELONG (MAKEWORD (1, 6), 0x8000)		// 双精度小数
#define		SDT_BOOL		  MAKELONG (MAKEWORD (2, 0),	0x8000)		// 逻辑
#define		SDT_DATE_TIME	MAKELONG (MAKEWORD (3, 0),	0x8000)		// 日期时间
#define		SDT_TEXT		  MAKELONG (MAKEWORD (4, 0),	0x8000)		// 文本
#define		SDT_BIN			  MAKELONG (MAKEWORD (5, 0),	0x8000)		// 字节集
#define		SDT_SUB_PTR		MAKELONG (MAKEWORD (6, 0),	0x8000)		// 子程序指针
#define		SDT_STATMENT	MAKELONG (MAKEWORD (8, 0),	0x8000)

// 用作区分系统类型、用户自定义类型、库定义数据类型
#define	DTM_SYS_DATA_TYPE_MASK		0x80000000
#define	DTM_USER_DATA_TYPE_MASK		0x40000000
#define	DTM_LIB_DATA_TYPE_MASK		0x00000000

// 用作细分用户自定义数据类型
#define	UDTM_USER_DECLARE_MASK		0x00000000	// 用户自定义复合数据类型
#define	UDTM_WIN_DECLARE_MASK		0x10000000	  // 用户自定义窗口类型

// 在数据类型中的数组标志，如果某数据类型值此位置1，则表示为此数据类型的数组。
// 本标志仅用作在运行时为具有AS_RECEIVE_VAR_OR_ARRAY或AS_RECEIVE_ALL_TYPE_DATA
// 标志的库命令参数说明其为是否为数组数据，其他场合均未使用。因此其他地方均
// 可以忽略本标志。
#define	DT_IS_ARY					0x20000000

// 在数据类型中的传址标志，如果某数据类型值此位置1，则表示为此数据类型的变量地址。
// 本标志仅用作在运行时为具有AS_RECEIVE_VAR_OR_OTHER标志的库命令参数说明其为是否为
// 变量地址，其他场合均未使用。因此其他地方均可以忽略本标志。
// 本标志与上标志不能共存。
#define	DT_IS_VAR					0x20000000

typedef DWORD DATA_TYPE;
typedef DATA_TYPE* PDATA_TYPE;

////////////////////////////////////////////////////////////////

typedef struct {
    DWORD m_dwFormID;
    DWORD m_dwUnitID;
} MUNIT, *PMUNIT;

typedef struct {
    DWORD m_dwStatmentSubCodeAdr;
    DWORD m_dwSubEBP;
} STATMENT_CALL_DATA, *PSTATMENT_CALL_DATA;


#pragma pack (push, old_value)
#pragma pack (1)
typedef struct {
  union {
    BYTE	      m_byte;                 // SDT_BYTE
    SHORT	      m_short;                // SDT_SHORT
    USHORT      m_ushort;
    INT		      m_int;                  // SDT_INT
    DWORD	      m_uint;                 // (DWORD)SDT_INT
    INT64	      m_int64;                // SDT_INT64
    FLOAT	      m_float;                // SDT_FLOAT
    DOUBLE	    m_double;               // SDT_DOUBLE
    DATE        m_date;                 // SDT_DATE_TIME
    BOOL        m_bool;                 // SDT_BOOL
    char*       m_pText;                // SDT_TEXT，不可能为NULL。
                                        // !!!为了避免修改到常量段(m_pText有可能指向常量段区域)中的数据，
                                        // 只可读取而不可更改其中的内容，下同。
    LPBYTE        m_pBin;               // SDT_BIN，不可能为NULL，!!!只可读取而不可更改其中的内容。
    DWORD         m_dwSubCodeAdr;       // SDT_SUB_PTR，记录子程序代码地址。
    STATMENT_CALL_DATA  m_statment;     // SDT_STATMENT数据类型。
    MUNIT         m_unit;               // 窗口组件、菜单数据类型。
    void*         m_pCompoundData;      // 复合数据类型数据指针，指针所指向数据的格式请见 run.h 。
                                        // 可以直接更改其中的数据成员，但是如果需要必须首先释放该成员。
    void*         m_pAryData;           // 数组数据指针，指针所指向数据的格式请见 run.h 。
                                        // 注意如果为文本或字节集数组，则成员数据指针可能为NULL。
                                        // !!! 只可读取而不可更改其中的内容。

                                        // 为指向变量地址的指针，仅当传入参数到库命令实现函数时才有用。
    BYTE*         m_pByte;              // SDT_BYTE*
    SHORT*        m_pShort;             // SDT_SHORT*
    INT*          m_pInt;               // SDT_INT*
    DWORD*        m_pUInt;              // ((DWORD)SDT_INT)*
    INT64*        m_pInt64;             // SDT_INT64*
    FLOAT*        m_pFloat;             // SDT_FLOAT*
    DOUBLE*       m_pDouble;            // SDT_DOUBLE*
    DATE*         m_pDate;              // SDT_DATE_TIME*
    BOOL*         m_pBool;              // SDT_BOOL*
    char**        m_ppText;             // SDT_TEXT，*m_ppText可能为NULL。
                                        // 注意写入新值之前必须释放前值，即：MFree (*m_ppText)。
                                        // !!!不可直接更改*m_ppText所指向的内容，只能释放原指针后换入新指针。
    LPBYTE*       m_ppBin;              // SDT_BIN，*m_ppBin可能为NULL。
                                        // 注意写入新值之前必须释放前值，即：MFree (*m_ppBin)。
                                        // !!!不可直接更改*m_ppBin所指向的内容，只能释放原指针后换入新指针。
    DWORD*        m_pdwSubCodeAdr;      // SDT_SUB_PTR，子程序代码地址变量。
    PSTATMENT_CALL_DATA m_pStatment;    // SDT_STATMENT数据类型变量。
    PMUNIT        m_pUnit;              // 窗口组件、菜单数据类型变量。
    void**        m_ppCompoundData;     // 复合数据类型变量。
                                        // 可以直接更改其中的数据成员，但是如果需要必须首先释放该成员。
    void**        m_ppAryData;          // 数组数据变量，注意：
                                        // 1、写入新值之前必须释放原值（使用NRS_FREE_VAR通知）。
                                        // 2、变量如果为文本或字节集数组，则成员数据指针可能为NULL。
                                        // !!!不可直接更改*m_ppAryData所指向的内容，只能释放原指针后换入新指针。
  };
                                        // 1、当用作传入参数时，如果该参数具有 AS_RECEIVE_VAR_OR_ARRAY 或
                                        //    AS_RECEIVE_ALL_TYPE_DATA 标志，且为数组数据，则包含数组标志 DT_IS_ARY ，
                                        //    这也是 DT_IS_ARY 标志的唯一使用场合。
                                        // 2、当用作传递参数数据时，如果为空白数据，则为 _SDT_NULL 。
  DATA_TYPE       m_dtDataType;
} MDATA_INF;
typedef MDATA_INF* PMDATA_INF;
#pragma pack (pop, old_value)


#endif
