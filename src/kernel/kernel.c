char toPrint = 'A';
char* str = "Sunt in bss?";
char f(){
    return 'K';
}

void start(){
    char* VIDEO_MEMORY = (char*)(0xb8000 + 2 * 80 * 10);
    char* message = "Pornit kernel din mod protejat, 32 biti";
    for(int i = 0; i < 39; i ++)
        VIDEO_MEMORY[2*i] = message[i];
    toPrint = 'm';
    VIDEO_MEMORY[100] = f();
    VIDEO_MEMORY[102] = toPrint;
    VIDEO_MEMORY[104] = str[3];
}