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

char buffer2[BUFFER_SIZE];
char tekst[BUFFER_SIZE];

void formatuj(void);
int pot(int, int);
void odfiltruj(void);

int main()
{
    int pipe_fd,res;
    int open_mode = O_RDONLY;


    printf("\n\nProces odbiornika uruchomil sie i dziala w tle\nJedo identyfikator to:\t%d\n", getpid());
    pipe_fd = open(FIFO_NAME, open_mode);
    
    if (pipe_fd != -1) {
        do {
            res = read(pipe_fd, buffer2, BUFFER_SIZE);
        } while (res > 0);
        (void)close(pipe_fd);
    }
    else {
        exit(EXIT_FAILURE);
    }

    printf("Otrzymane dane w odbiorniku to:\n%s\n",buffer2);
	 printf("Program odbiornika nr %d zakonczyl sie z sukcesem\n",getpid());
	 formatuj();
	 
	printf("\nOtrzymany lancuch to:\n%s\n\n",tekst);

	odfiltruj();
	exit(EXIT_SUCCESS);
}

void formatuj(void){
int i, j=0, a=0;	

	for(i=0;i<strlen(buffer2);i++){
			if(i%11==0 || i%11==9);
			else if(i%11==10){ tekst[j]=(char)a;a=0;j++;}
			else	a+=((int)buffer2[i]-48)*pot(2,i%11-1);
		}
}

int pot(int a, int b){
	int i,w=1;
	for(i=0;i<b;i++)
		w*=a;
	return w;
}

void odfiltruj(void){
	int a=0,t,c,i=0,j=0,k,l=0;
	FILE *in;
	char gr[1000],tmp[100];
	in = fopen("grubianstwa.txt","r");
		
	while((c=fgetc(in))!=EOF){
	gr[j]=(char)c;
	j++;
	if(c=='\n')	l++;
	}

	while(l--){
		for(c=0,j=a;gr[j]!='\n';j++,c++)
			tmp[c]=gr[j];
			tmp[c]='\0';

//		printf("%s\t%d\n",tmp,strlen(tmp));
	
		for(i=0;i<strlen(tekst);i++){
			t=0;
			if(tekst[i]==tmp[0]){
				for(k=0;k<strlen(tmp);k++)
			if(tmp[k]==tekst[i+k]) t++;
//		printf("%d\n",t);	

		if(t==strlen(tmp)){
				for(k=1;k<strlen(tmp);k++)
					tekst[i+k]='*';
			}}}
		a=j+1;
	}

	printf("Operacja filtrowania powiodla sie, oto wynik:\n%s\n",tekst);
}
