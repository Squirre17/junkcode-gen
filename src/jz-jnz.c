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

#include <stdio.h>
int main(int argc, char const *argv[])
{
    printf("%d %d\n", add(1, 2), add_with_junk(1, 2));
    return 0;
}
