// 正常的函数代码
int add(int a, int b){
  int c = 0;
  c = a + b;
  return c;
}
// 添加花指令的函数代码
/*
    1183:       74 03                   je     1188 <label>
    1185:       75 01                   jne    1188 <label>
    1187:       e8                      .byte 0xe8
*/
int add_with_junk(int a, int b){
    int c = 0;
    asm(
        "jz label;"
        "jnz label;"
        ".byte 0xe8;"    // call 指令，后面加4bytes的地址偏移，因此导致反汇编器不能正常识别
        "    label:"
    );
    c = a + b;
    return c;
}

int add_with_junk2(int a, int b){
    int c = 0;
    asm(
        "je label2;"
        "jne label2;"
        ".byte 0xe8;"    // call 指令，后面加4bytes的地址偏移，因此导致反汇编器不能正常识别
        "    label2:"
    );
    c = a + b;
    return c;
}

int add_with_junk_xorjz(int a, int b){
    int c = 0;
    asm(
        ".intel_syntax noprefix;"
        "xor eax, eax;"
        "jz label3;"
        ".byte 0xe8;"    // call 指令
        ".byte 0x0d, 0x00, 0x07, 0x21, 0xff;"
        "    label3:"
        ".att_syntax"
    );
    c = a + b;
    return c;
}

#include <stdio.h>
int main(int argc, char const *argv[])
{
    printf("%d\n", 
        add(1, 2) + 
        add_with_junk(1, 2) +
        add_with_junk2(1, 2) +
        add_with_junk_xorjz(3, 4)
    );
    return 0;
}
