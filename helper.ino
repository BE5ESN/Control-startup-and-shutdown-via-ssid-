#include "string.h"
char isEndWith(char *raw, char *tgt)
{
    int ii = 0;
    while (raw[ii] != '\0')
    {
        ii++;
        if (ii > 32)
        {
            return -1;
        }
        if (strcmp(&(raw[ii]), tgt) == 0)
        {
            return 0;
        }
    }
    return -1;
}
