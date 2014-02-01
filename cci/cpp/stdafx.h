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
#include <WinError.h>
#include <windows.h>

// TODO: reference additional headers your program requires here
#pragma warning (error : 4706) // assignment within condition expression
#pragma warning (disable: 4996 4389 4244 4018)

// stl headers
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <vector>
#include <bitset>
#include <stack>
#include <memory>
#include <assert.h>
#include <limits>
#include <unordered_set>
#include <unordered_map>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <deque>
#include <queue>
#include <numeric>
#include <hash_set>
#include <sstream>
#include <list>
#include <tuple>
#include <functional>
using namespace std;

// project level headers
#include "utils.h"
#include "heap.h"
#include "hm.h"
#include "trie.h"


// project level typedefs
typedef unsigned int uint;
#define AS(array) sizeof(array)/sizeof(array[0]) 

