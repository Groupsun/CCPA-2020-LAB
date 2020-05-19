#include <cstdio>

// 规定数组bin当中bin[0]为最高位，bin[3]为最低位
char bin[4];

void dec2bin(char num)
{
    for(int i = 0;i < 4;i++)
    {
        bin[3-i] = num % 2;
        num = num / 2;
    }
}

int main()
{
    char in;
    scanf("%d", &in);
    dec2bin(in);
    printf("%d %d %d %d \n", bin[0], bin[1], bin[2], bin[3]);
}

