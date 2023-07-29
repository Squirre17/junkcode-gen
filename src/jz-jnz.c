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

int add_with_junk3(int a, int b){
    int c = 0;
    asm(
        "jb label33;"
        "jnb label33;"
        ".byte 0xe8;"    // call 指令，后面加4bytes的地址偏移，因此导致反汇编器不能正常识别
        "    label33:"
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
/// @brief : 用call到目标地址来跳过中间的垃圾指令
int add_with_junk_call(int a, int b){
    int c = 0;
    asm(
        ".intel_syntax noprefix;"
        ".byte 0xe8, 0x01, 0x00, 0x00, 0x00;"    // call到pop rax那里 修改返回地址 返回正常逻辑
        ".byte 0xff;" // junk
        "pop rax;"
        "add rax, 0x8;"
        "push rax;"
        "ret;"
        ".att_syntax"
    );
    c = a + b;
    return c;
}

int add_with_junk_call_ret_jmp(int a, int b){
    int c = 0;
    asm(
        ".intel_syntax noprefix;"

        "   call label5;"    // call到lable那 返回到jmp out
        "   .byte 0xff;" // junk
        "   jmp out;"
        "label5:;"
        "   add qword ptr[rsp], 1;"
        "   ret;"
        "out:"

        ".att_syntax;"
    );
    c = a + b;
    return c;
}

// not solve yet
// int add_with_junk_inst_overlap(int a, int b){
//     int c = 0;
//     asm(
//         ".intel_syntax noprefix;"

//         "label6:;"
//         "   jmp label6 + 1;"
//         "   .byte 0x3;"

//         ".att_syntax;"
//     );
//     c = a + b;
//     return c;
// }

#include <stdio.h>
int main(int argc, char const *argv[])
{
    printf("%d\n", 
        add(1, 1) + 
        add_with_junk(1, 1) +
        add_with_junk2(1, 1) +
        add_with_junk_xorjz(1, 1) +
        add_with_junk_call(1, 1) + 
        add_with_junk_call_ret_jmp(1, 1)
        // add_with_junk_inst_overlap(1, 1)
    );
    return 0;
}
