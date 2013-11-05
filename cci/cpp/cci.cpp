// cci.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "chapter.1.h"

int _tmain(int argc, _TCHAR* argv[])
{
    //1.1
	bool result = is_unique_chars(""); 

    // 1.6
    int** someArray = new int*[5];
    fill_matrix(someArray, 5);
    rotate_matrix_90(someArray, 5);
    return 0;
}

