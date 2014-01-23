// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#define NOMINMAX
#include "targetver.h"

#include <stdio.h>
#include <tchar.h>


#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

#include <atlbase.h>
#include <atlstr.h>

// TODO: reference additional headers your program requires here
#pragma warning (error : 4706) // assignment within condition expression
#pragma warning (disable: 4996)
typedef unsigned int uint;