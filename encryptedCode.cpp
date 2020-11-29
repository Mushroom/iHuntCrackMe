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
    if((input[0] ^ 0x10) != 0x6a) return 1;
    if((input[1] ^ 0x11) != 0x78) return 1;
    if((input[2] ^ 0x12) != 0x62) return 1;
    if((input[3] ^ 0x13) != 0x7f) return 1;
    if((input[4] ^ 0x14) != 0x7d) return 1;
    if((input[5] ^ 0x15) != 0x7b) return 1;
    if((input[6] ^ 0x16) != 0x73) return 1;

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
    int size = &funcAfter - &checkFunc + 228;

    void* encArea = malloc(size);
    memcpy(encArea, &funcAfter - 228, size);

    encryptDecrypt((char*)encArea, size);

    printf("Size: 0x%x", size);

    for(int i = 0; i < size; i++)
    {
        printf("0x%.2x, ", ((char*)encArea)[i]);
    }

    //printf("Returned 0x%x\n", checkFunc("zipline"));
}