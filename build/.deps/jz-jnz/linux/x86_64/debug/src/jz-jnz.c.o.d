{
    values = {
        "/usr/bin/gcc",
        {
            "-m64",
            "-g",
            "-O0"
        }
    },
    files = {
        "src/jz-jnz.c"
    },
    depfiles_gcc = "jz-jnz.o: src/jz-jnz.c\
"
}