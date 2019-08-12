#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>


int main(int argc, char *argv[]){
  char message[2001];
  int server, portNumber;
  struct sockaddr_in servAdd;     // server socket address
  
 if(argc != 3){
    printf("Call model: %s <IP Address> <Port Number>\n", argv[0]);
    exit(0);
  }

  if ((server = socket(AF_INET, SOCK_STREAM, 0)) < 0){
     fprintf(stderr, "Cannot create socket\n");
     exit(1);
  }

  servAdd.sin_family = AF_INET;
  sscanf(argv[2], "%d", &portNumber);
  servAdd.sin_port = htons((uint16_t)portNumber);

  if(inet_pton(AF_INET, argv[1], &servAdd.sin_addr) < 0){
  fprintf(stderr, " inet_pton() has failed\n");
  exit(2);
}

  
 if(connect(server, (struct sockaddr *) &servAdd, sizeof(servAdd))<0){
  fprintf(stderr, "connect() has failed, exiting\n");
  exit(3);
 }

 while(1){
  

  
  fprintf(stderr, "Give a command to server or type quit to exit\n");
  fgets(message, 2000, stdin);
  

  write(server, message, strlen(message)+1);
  
   if(strcmp("quit\n",message)==0)
   {
	    close(server);
    exit(0);
   }
  
  char c;
  char strrr[1024];
  int i=0;
  while(1)
  {
  if (!read(server, &c, 1)){
	   close(server);
    fprintf(stderr, "read() error\n");
    exit(0); 
 }
		strrr[i]=c;
		i++;
		if(c=='\n')
		{
			strrr[i-1]='\0';
			i=0;
		}
   fprintf(stderr, "%c", c);
   if(strcmp("COMPLETED",strrr)==0)
   {
	    fprintf(stderr, "\n");
	   break;
   }
  }
}
}


