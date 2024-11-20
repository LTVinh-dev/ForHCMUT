#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char* argv[], char* envp[]) {
    int fd;
    const char *message = "Hello from sender!";
    char* buffer=malloc(100*sizeof(char));
    char* msg = malloc(100*sizeof(char));
    char* xyz = malloc(1000*sizeof(char));
    char* dictkey = malloc(100*sizeof(char));
    char* dictval = malloc(100*sizeof(char));


    int i =1;
/*
    while(**envp){
            strncpy(dictkey, *envp, 7);
            //printf("%s\n", dictkey);
            dictkey[7] = 0;
            if(strcmp(dictkey, "MSGFILE") == 0)
                    printf("env MSGFILE");
            // TODO: get the dictvalue to obtain the file
            envp++;
    }
*/
    while ( i < argc){
            printf("%s\n",argv[i]);
          if(strcmp(argv[i], "-w") == 0) {
                  i++;
                  printf("ABC %s\n", argv[i]);
                  strncpy(msg, argv[i], sizeof(*argv[i]));
                  if( strcmp(xyz,"")==0){
                      printf("Error mising filepath\n");
                      return -1;
                  }
                fd = open(xyz, O_WRONLY);
                if(fd==-1){
                        printf("Error file\n");
                        return -1;
                }
                printf("abc %d\n ",sizeof(argv[i]));
                write(fd, argv[i], sizeof(argv[i]));
                close(fd);
          } 
          else if(strcmp(argv[i],"-r") == 0) {
                  printf("read\n");
                 if( strcmp(xyz,"")==0){
                   printf("Error mising filepath\n");
                   return -1;
                 }
                  read(fd,buffer , 100);
                  printf("Received message: %s\n", buffer);
                  close(fd);
                  read(fd,buffer , 100);
                  printf("Received message: %s\n", buffer);
                  close(fd);
          }
          else  if(strcmp(argv[i], "-filepath") == 0) {
                  i++;
                  strcpy(xyz, argv[i]);
                  printf("filepath %s\n", xyz);
          }

         i++;
    }


    return 0;
}