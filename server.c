#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void child(int);


void serviceClient(char* str) 
{ 
while(1)
{
int n;
char ch;


  
		
		//if(strcmp(str, "exit")==0)      
			//break;
 
    int count=0;
	int commandNo=0;
	char commands[200][100];
	char idn[200];
	int i=0;
	char indentifier=';';
    while(count <= strlen(str)) 
    {		
		if(str[count]==';'|| str[count]=='&' || str[count]=='|')
		{	
			if(str[count]=='&')
			{
				indentifier='&';
			}
			else if(str[count]=='|')
			{
				indentifier='|';
			}
			else{
				indentifier=';';
			}
			if(str[count]=='&' && str[count+1]=='&' )
			{
				
			}
			else if(str[count]=='|' && str[count+1]=='|' )
			{
				
			}
			else{
				commands[commandNo][i]='\0';
				idn[commandNo]=indentifier;			
			    commandNo++;
			 i=0;
			}
		}
		else{
			commands[commandNo][i]=str[count];
			i++;
			
		}
		count++;      
    }
	idn[commandNo]=';';
			

for(i=0;i<=commandNo;i++)
{
      printf("\nCommand: %s\n", commands[i]);
      char *args[10] = {}; 
      args[0] = strtok(commands[i], " ");
      int tokenCounter = 0;
      
      while (args[tokenCounter] != NULL){
        tokenCounter++;
        args[tokenCounter] = strtok(NULL, " ");
      }

      int childpid = fork();

      if (childpid == 0){
        if ((execvp(args[0], args)) < 0){
          printf("Error has been found! Command can not be recognized.\n");
		  exit(-1);
        }
        exit(0);
      }
	  else if (childpid > 0){  	  
        int status;       
        wait(&status);
        if(WIFEXITED(status))
		{
          int exitstat = WEXITSTATUS(status);
		  if(exitstat ==0)
		  {
          //printf("\nChild %d exited !! status is %d\n", childpid, exitstat);
		   if(idn[i]=='|')
			  {
				  i=commandNo+1;
			  }
		  }		  
			else
			{
			 printf("Error with command");
			  if(idn[i]=='&')
			  {
				  i=commandNo+1;
			  }
			}
        }
		else
		{
			printf("signaled by =%d\n",WTERMSIG(status));
		}
      }else{
        printf("Error\n");
        exit(1);
      }
      
    } 
 break;
}	
  
}
int main(int argc, char *argv[]){  
  int sd, client, portNumber;
  struct sockaddr_in servAdd;     // server socket address
  
 if(argc != 2){
    printf("Call model: %s <Port Number>\n", argv[0]);
    exit(0);
  }

  sd = socket(AF_INET, SOCK_STREAM, 0);
  servAdd.sin_family = AF_INET;
  servAdd.sin_addr.s_addr = htonl(INADDR_ANY);
  sscanf(argv[1], "%d", &portNumber);
  servAdd.sin_port = htons((uint16_t)portNumber);
  
  bind(sd, (struct sockaddr *) &servAdd, sizeof(servAdd));
  listen(sd, 5);

  while(1){
    client = accept(sd, NULL, NULL);
    printf("Got a client\n");

    if(!fork())
      child(client);

    close(client);
  }
}
void child(int sd){
	char message[2000];


	while(1){
		fprintf(stderr, "waiting fo client command\n");
		//fgets(message, 254, stdin);
		//write(sd, message, strlen(message)+1);

		if(!read(sd, message, 255)){
			close(sd);
			fprintf(stderr, "Bye, my client is dead, wait for a new one\n");
			exit(0);
		}
		
		.....................................
		fprintf(stderr, "Client send back: (%s)\n", message);
		dup2(sd,1);
		 printf("Running commands\n");
		 int len=strlen(message);
		 message[len-1]='\0';
		 fprintf(stderr, "Running command: (%s)\n", message);
		 
		serviceClient(message);
		printf("\n");
		 printf("COMPLETED\n");
		
	}
}
