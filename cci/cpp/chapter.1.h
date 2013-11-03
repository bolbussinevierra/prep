bool is_unique_chars(char * str)
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
