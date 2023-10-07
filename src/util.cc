#include <util.h>
#include <string.h>

using std::string;

string char_ptr_to_string(char *str)
{
    string s = "";
    int len = strlen(str);

    for(int i=0; i<len; i++)
        s+=str[i];

    return s;
}

int add(int x, int y)
{
    return x+y;
}