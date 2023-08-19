char f(){
    return 'K';
}

void start(){
    char* VIDEO_MEMORY = (char*)(0xb8000 + 80 * 10);
    char* message = "Pornit kernel din mod protejat, 32 biti";
    for(int i = 0; i < 39; i ++)
        VIDEO_MEMORY[2*i] = message[i];
    VIDEO_MEMORY[100] = f();
}