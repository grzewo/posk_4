#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_NAME "/tmp/my_fifo"
#define BUFFER_SIZE 1000

int get(void);

char buffer[BUFFER_SIZE];

int main()
{
    int pipe_fd;
    int res;
    int open_mode = O_WRONLY;
    
	buffer[get()]='\0';

	printf("\nTwoja wiadomosc po zakodowaniu to: \n%s\n",buffer);

    printf("Proces nr %d  - nadajnik zaczyna dzialac\n\n", getpid());
//    execl("/home/grzesiek/cw4/ch13/fifo4",0);
	 pipe_fd = open(FIFO_NAME, open_mode);
    


    if (pipe_fd != -1) {
            res = write(pipe_fd, buffer, BUFFER_SIZE);
            if (res == -1) {
                fprintf(stderr, "Write error on pipe\n");
                exit(EXIT_FAILURE);
            }
        (void)close(pipe_fd); 
    }
    else {
        exit(EXIT_FAILURE);        
    }

    printf("Sygnal zostal przeslany i proces nadajnika nr %d zakonczony z sukcesem\n\n", getpid());
    exit(EXIT_SUCCESS);
}

int get(void){	
	short int c,i,j=0;
	printf("Wpisz wiadomosc i zakoncz ja ENTERem\n\n");
	while((c=getchar())!='\n'){
		buffer[j]=49;j++;
		for(i=j;i<j+8;i++,c/=2)
		buffer[i]=(c%2+48);
		j+=8;
		buffer[j]=buffer[j+1]=49; j+=2;
	}
	return j;}
