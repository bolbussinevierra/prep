//
// helpers
//
#include <iostream>
using namespace std;

void _PrintMatrix(int **m, int n)
{   
    for(int i  =  0; i < n; ++i)
    {
        cout<< "\n";
        for(int j  =  0;  j < n;  ++j)
        {
            printf("%d ",m[i][j]);
            //cout <<  m[i][j];
        }
    }
    cout << "\n-------------------------" << endl;
}

void _FillMatrix(int **m, int n)
{
    for(int i = 0; i < n; ++i)
    {
        m[i] = new int[n];
    }

    int value = 1;
    for(int i  =  0; i < n; ++i)
    {
        for(int j  =  0;  j < n;  ++j)
        {
            m[i][j] = value++;
        }
    }

}
//
// helpers
//



bool IsUniqueChars(char * str)
{
    if (str == NULL) return true;
    int length = strlen(str);
    
    // must contain a duplicated if longer than 256. A single character or
    // empty string is vacuously unique
    if (length > 256) return false;
    if (length <= 1) return true;

    // bit vector for ascii (256 chars max)
    char set[32] = {0}; // 256 / 8

    for (int i = 0; i < length; ++i)
    {
        int bit_group = (str[i] - '\0') / 8;
        int bit_pos = (str[i] - '\0') % 8;

        int set_check = set[bit_group];
        if ((set_check & (1 << bit_pos)) > 0)
        {
            return false;
        }
        set[bit_group] = set_check | (1 << bit_pos);
    }
    return true;
}
//
// 1.6
//
void RotateMatrix90(int ** m, int n)
{
    _PrintMatrix(m, n);
    for (int layer = 0; layer < n/2; ++layer)
    {
        int start = layer;
        int end = n - 1 - layer;
        for (int i = start; i < end; ++i)
        {
            int offset = i - start;
            int top = m[start][i];
            m[start][i] = m[end - offset][start];
            m[end - offset][start] = m[end][end - offset];
            m[end][end - offset] = m[i][end];
            m[i][end] = top;
        }
    }
    _PrintMatrix(m, n);
}
