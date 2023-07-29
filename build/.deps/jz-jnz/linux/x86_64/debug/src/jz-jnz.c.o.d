{
    files = {
        "src/jz-jnz.c"
    },
    values = {
        "/usr/bin/gcc",
        {
            "-m64",
            "-O0",
            "-no-pie",
            "-g"
        }
    },
    depfiles_gcc = "jz-jnz.o: src/jz-jnz.c\
"
}