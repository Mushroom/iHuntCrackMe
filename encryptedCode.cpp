#include <bits/stdc++.h> 

void encryptDecrypt(char inpString[], int length) 
{ 
    // Define XOR key 
    // Any character value will work 
    char xorKey = 0xFF; 

  
    // perform XOR operation of key 
    // with every caracter in string 
    for (int i = 0; i < length; i++) 
    { 
        inpString[i] = inpString[i] ^ xorKey--;
    } 
}

/*int checkFunc(char input[])
{
    char checkArr[] = { 0x6a, 0x78, 0x62, 0x7f, 0x7d, 0x7b, 0x73 };
    char* checkArrStar = checkArr;
    char xorKey = 0x10;

    for (int i = 0; i < 7; i++)
    {
        if((input[i] ^ xorKey++) != checkArr[i])
        {
            return 1;
        }
    }

    return 0;
}*/

int checkFunc(char input[]) //manually unrolled the above so it can be embedded as a payload more easily
{
    char z = 0x6a;
    if((input[0] ^ 0x10) != z) return 1;
    char i = 0x78;
    if((input[1] ^ 0x11) != i) return 1;
    char p = 0x62;
    if((input[2] ^ 0x12) != p) return 1;
    char l = 0x7f;
    if((input[3] ^ 0x13) != l) return 1;
    char i2 = 0x7d;
    if((input[4] ^ 0x14) != i2) return 1;
    char n = 0x7b;
    if((input[5] ^ 0x15) != n) return 1;
    char e = 0x73;
    if((input[6] ^ 0x16) != e) return 1;

    return 0;
}

int funcAfter(char* input) //spam some extra crap into memory
{
    int y = 234;
    y *= 4456;
    y = y << 4;
}

int main(void)
{
    char ghidraBreakingOffsetBytes[] = { 0xe4, 0xff, 0xff, 0xeb, 0x1c, 0x20, 0x9f, 0xe5, 0x1c, 0x10, 0x9f, 0xe5, 0x10, 0x00, 0x9f, 0xe5, 0xd1, 0xfe, 0xff, 0xeb, 0x00, 0x00, 0xa0, 0xe1, 0x04, 0xd0, 0x4b, 0xe2, 0x00, 0x88, 0xbd, 0xe8 };
    char ghidraBreakingOffsetBytes2[] = { 0xe4, 0xff, 0xff, 0xeb, 0x1c, 0x20, 0x9f, 0xe5, 0x1c, 0x10, 0x9f, 0xe5, 0x10, 0x00, 0x9f, 0xe5, 0xd1, 0xfe, 0xff, 0xeb, 0x00, 0x00, 0xa0, 0xe1, 0x04, 0xd0, 0x4b, 0xe2, 0x00, 0x88, 0xbd, 0xe8 };
    int size = &funcAfter - &checkFunc + 368;

    void* encArea = malloc(size + 32);
    memcpy(encArea, ghidraBreakingOffsetBytes, 32);
    memcpy(encArea + 32, &funcAfter - 368, size);

    encryptDecrypt((char*)encArea, size);

    printf("Size: 0x%x", size);

    for(int i = 0; i < size + 32; i++)
    {
        printf("0x%.2x, ", ((char*)encArea)[i]);
    }

    printf("DECRYPTED: \n");

    encryptDecrypt((char*)encArea, size);

    for(int j = 0; j < size + 32; j++)
    {
        printf("0x%.2x, ", ((char*)encArea)[j]);
    }

    //printf("Returned 0x%x\n", checkFunc("zipline"));
}