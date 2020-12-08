#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <math.h>
#define SIZE 1024
#define PORT 4444
#define maxlen 70000
#define mlen 100000

int main(){
	system("clear");
	int sockfd, ret;
	 struct sockaddr_in serverAddr;

	int newSocket;
	struct sockaddr_in newAddr;

	socklen_t addr_size;

	char buffer[1024];
	char buffer1[1024];
	char buffer2[1024000];
	pid_t childpid;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Server Socket is created.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = INADDR_ANY;

	ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("[-]Error in binding.\n");
		exit(1);
	}
	printf("[+]Bind to port %d\n", 4444);

	if(listen(sockfd, 10) == 0){
		printf("[+]Listening....\n");
	}else{
		printf("[-]Error in binding.\n");
	}


	while(1){
		newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);
		if(newSocket < 0){
			exit(1);
		}
		printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));

		if((childpid = fork()) == 0){
			close(sockfd);

			while(1){
			int choise;
			int choise2;
			int a,b,c,d;
			int root1,root2;
			char foldername[10];
			read(newSocket, &choise, sizeof(int));
			if(choise == 1){
			printf("Client Selected IaaS \n");
			read(newSocket,foldername,sizeof(foldername));
			printf("%s",foldername);
			
			char folder[50];
			strcpy(folder,"mkdir ");
			strcat(folder , foldername);
			system(folder);
			
			FILE *fp1;
       				  int ch1 = 0;
       				  char filename1[20];
       				  char front1[30]="Recieved_";
       				  read(newSocket,filename1,sizeof(filename1));
       				  strcat(front1,filename1);
          				  fp1 = fopen(front1,"a");            
         				   int words1;
					read(newSocket, &words1, sizeof(int));
           				 //printf("Passed integer is : %d\n" , words);      //Ignore , Line for Testing
         				 while(ch1 != words1)
       	 			  {
        				 read(newSocket , buffer1 , 512); 
	   				 fprintf(fp1 , " %s" , buffer1);   
		 			//printf(" %s %d "  , buffer , ch); //Line for Testing , Ignore
					 ch1++;
	  					 }
     					printf("The file was received successfully\n");
					   printf("The new file created is %s \n",front1);
					
					
			char cd[50];
			strcpy(cd,"mv ");
			strcat(cd , front1);
			strcat(cd," ");
			strcat(cd , foldername);
			system(cd);			
			exit(1);
			}
			else if(choise == 2){
			printf("Client Selected PaaS \n");
			
			
			
  char fileName[100];
  char kuch[100];
  char file_buffer[2000],caufile[maxlen];
  char *vfilep;
  int aufile[700000],vfile[mlen];
  int sd,connfd,len;
	
	
	for(int i=0;i<=100;i++){
	fileName[i]='\0';
}



len=sizeof(newAddr);
  
  int choice=1;
  while(1)
  {
  	char num;

  	 
  	read(newSocket, &num, sizeof(int));
       
	choice = num;

	
	switch(choice)
	{
		case 1:
  			printf("NAME OF TEXT FILE RECEIVED");
			FILE *fp6;			
			
  	 		printf("Contents in the received text file : \n");
  	 		read(newSocket,file_buffer,sizeof(file_buffer));
  	 		printf("%s\n",file_buffer);
  	 		
  			int fsize=strlen(file_buffer);
  			printf("%d",fsize);
			fp6=fopen("code.c","w");
  			if(fp6)
  			{
 				fwrite(file_buffer, fsize, 1, fp6);
  				printf("File received successfully.\n");
  			}
  			else
  			{
	  			printf("Cannot create to output file.\n");
  			}
  			memset(fileName, '\0', sizeof(fileName));
  			fclose(fp6);
  			break;
  		case 2:
  			
     			break;
     		
     		case 3:
     			
     			break;
     			
     		case 4:
  			close(sd);
  			break;   		
	
	}
			printf("\n [+][+][+] YOUR CODE IS UNDER COMPILATION [+][+][+] \n");
			char gcc[50];
			strcpy(gcc,"gcc ");
			strcat(gcc ,"code.c");
			system(gcc);
			char out[50] = "./a.out";
			
			system(out);
			printf("\n FILE COMPILED AND EXECUTED SUCESSFULLY \n");
			break;	
			
  }
	
	
	
	
	
	char file_buffer7[200];
	FILE *fp7;
     				fp7=fopen("output.txt","r");

     				if(fp7)
     				{
    	 				printf("Reading file contents.\n");
     					fseek(fp7,0,SEEK_END);
       					size_t file_size7=ftell(fp7);
       					fseek(fp7,0,SEEK_SET);
      					if(fread(file_buffer7,file_size7,1,fp7)<=0)
         				{
           					printf("Unable to copy file into buffer or empty file.\n");
           					exit(1);
         				}
        			}
        			else
        			{
    					printf("Cannot open file.\n");
    	 				exit(0);
    			 	}
    				printf("FILE CONTENTS TO SEND : %s\n",file_buffer7); 
			write(newSocket,file_buffer7,strlen(file_buffer7));
			exit(1);
			}	
			
			else if(choise == 3){
			printf(" [+]Client Selected SaaS \n");
			read(newSocket, &choise2, sizeof(int));
					if(choise2 == 1){
					printf(" [+]Client want Calculator");
					read(newSocket, &a, sizeof(int));
					read(newSocket, &b, sizeof(int));
					read(newSocket, &c, sizeof(int));
					printf("\n [+]Client entered quadratic eqation \n");
					printf("%d x^2 + %d x + %d \n",a,b,c);
					
					d = b * b - 4 * a * c;
					printf("%d \n",d);
 					if(d>0){
  					root1 = ( -b + sqrt(d)) / (2* a);
   					root2 = ( -b - sqrt(d)) / (2* a);
  					printf("\n Roots of quadratic equation are: %d  %d \n",root1,root2);
 					}
 					send(newSocket, &root1, 10, 0);
 					send(newSocket, &root2, 10, 0);
						
					exit(1);
					}
					else if(choise2 == 2){
					printf("[+]Client wants to Transfer FileS\n");
					
					FILE *fp;
       				  int ch = 0;
       				  char filename[20];
       				  char front[30]="Recieved_";
       				  read(newSocket,filename,sizeof(filename));
       				  strcat(front,filename);
          				  fp = fopen(front,"a");            
         				   int words;
					read(newSocket, &words, sizeof(int));
           				 //printf("Passed integer is : %d\n" , words);      //Ignore , Line for Testing
         				 while(ch != words)
       	 			  {
        				 read(newSocket , buffer , 512); 
	   				 fprintf(fp , " %s" , buffer);   
		 			//printf(" %s %d "  , buffer , ch); //Line for Testing , Ignore
					 ch++;
	  					 }
     					printf("The file was received successfully\n");
					   printf("The new file created is %s \n",front);
					
					
					exit(1);
					}
			exit(1);
			}
			
			
				
			}
		}

	}

	close(newSocket);


	return 0;
}
