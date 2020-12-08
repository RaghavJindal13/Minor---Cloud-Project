#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>
#define SIZE 1024
#define PORT 4444

struct user{
    char username[10];
    char password[10];
}*pUser;

//Caesar Cipher Encryption and Decryption Program
void decrypt(char arr[])
{
      int i;
      for(i = 0; i < strlen(arr); i++)
      {
            arr[i] = arr[i] + 10;
      }
}
 
void encrypt(char arr[])
{
      int i;
      for(i = 0; i < strlen(arr); i++)
      {
            arr[i] = arr[i] - 10;
      }
}




int main(){

	int clientSocket, ret;
	struct sockaddr_in serverAddr;
	char buffer[1024];
	char buffer1[1024];
	char buffer2[1024000];
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSocket < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Client Socket is created.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("192.168.136.128");

	ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Connected to Server.\n");
///////////
int flag = 0;
 FILE *fp;
    char uName[10], pwd[10];int i;char c;
    system("clear");
    
    pUser=(struct user *)malloc(sizeof(struct user));
    printf("\n");
    printf("       	 	  ||########################################||\n");
    printf("       	  	  ||         WELCOME TO WE3 CLOUD !         ||\n");
    printf("   		  ||                 ***                    ||\n");
    printf("    	  	  || 1. Login Through An Existing Account   ||\n");
    printf("    	  	  || 2. Create new Account                  ||\n");
    printf("       	 	  ||########################################||\n");
    scanf("%d",& i);
    //system("cls");
    switch(i){
        case 1:
            if ( ( fp=fopen("user.dat", "r+")) == NULL) {
                if ( ( fp=fopen("user.dat", "w+")) == NULL) {
                    printf ("Could not open file\n");
                    exit ( 1);
                }
            }
            printf("\n Username: ");
            scanf("%9s",uName);
            printf(" Password: ");
            scanf("%9s",pwd);
            while ( fread (pUser, sizeof(struct user), 1, fp) == 1) {
            
            printf("\n Encrypted Password --> \t%s\n", pUser->password);
            decrypt(pUser->password);
            printf("\n Decrypted Password --> \t%s\n", pUser->password);
            
                if( strcmp ( pUser->username, uName) == 0) {
                    printf (" [+]Match username\n");
                    if( strcmp ( pUser->password, pwd) == 0) {
                        printf (" [+]Match password\n");
                        //accessUser();
			printf (" [+]Client Connected\n");
			flag = 1 ;
                    }
                }
               else{printf("Login ID or password is incorrect !\n");
               } 
            }
            break;

        case 2:
            do
            {
                if ( ( fp=fopen("user.dat", "a+")) == NULL) {
                    if ( ( fp=fopen("user.dat", "w+")) == NULL) {
                        printf ("Could not open file\n");
                        exit ( 1);
                    }
                }
                printf(" Choose A Username: ");
                scanf("%9s",pUser->username);
                printf(" Choose A Password: ");
                scanf("%9s",pUser->password);
                
      printf("\n Orignal Password:\t%s\n", pUser->password);        
      encrypt(pUser->password);
      printf("\n Encrypted Password:\t%s\n", pUser->password);
      //decrypt(password);
      //printf("\nDecrypted Password:\t%s\n", password);
                
                fwrite (pUser, sizeof(struct user), 1, fp);
                printf("\n[+]Account successfully created \n");
                printf("\n Add another account? (Y/N): \n");
                scanf(" %c",&c);//skip leading whitespace
            }while(c=='Y'||c=='y');
            break;
    }
    free ( pUser);//free allocated memory
    fclose(fp);

/////////
  if(flag == 1){
	while(1){
	int choise;
	int choise2;
	int a,b,c;
	int root1,root2;
	char foldername[10];
		printf("\n       	 	             *Welcome Client*              \n");
		printf("       	 	  ########################################\n");
		printf("       	 	  ||  Enter service you want to avail   ||\n");
		printf("       	 	  ||          |  1 - IaaS  |            ||\n"); 
		printf("       	 	  ||          |  2 - PaaS  |            ||\n");
		printf("       	 	  ||          |  3 - SaaS  |            ||\n");
               printf("       	 	  ######################################## \n");
		scanf("%d", &choise);
		
		write(clientSocket, &choise, sizeof(int));    	//send this to server
		
		if(choise == 1 ){
		printf("\nYou Chosed Infrastructure as a service\n");
			printf("\n------------------------------Infrastructure as a Service-------------------- \n");
			printf("       	 	  ################################################\n");
			printf("       	 	  ||                                             ||\n");
			printf("       	 	  ||            ** Storage Service **            ||\n"); 
			printf("       	 	  ||                                             ||\n");
               	printf("       	 	  ################################################ \n");
               	printf("\n");
               	printf(" [+]A storage will be given to you on the server side \n");
               	printf(" [+]Enter the name of the folder \n");
               	scanf("%s",foldername);
               	printf(" \n [+]Folder successfully Created \n");
               	write(clientSocket, foldername, sizeof(foldername)); 
               	printf(" [+]Add some files to your storage \n");
               	
               	
               	FILE *f1;
   			int words1 = 0;
    			char c1;
    			
			printf(" Enter File Name\n");
			char filename1[20];
			scanf("%s",filename1);
    			write(clientSocket, filename1, sizeof(filename1));  
    			int wait1=0;
    			while(wait1 ==0 )
    		{
    			
     			f1=fopen(filename1,"r");
     			
   			 while((c1=getc(f1))!=EOF)			//Counting No of words in the file
			{	
			fscanf(f1 , "%s" , buffer1);
			if(isspace(c1)||c1=='\t')
			words1++;	
			}
			
			wait1 = 1;
       
      		}
			write(clientSocket, &words1, sizeof(int));
     			rewind(f1);
       
    			char ch1 ;
      			 while(ch1 != EOF)
      			{
		
			fscanf(f1 , "%s" , buffer1);

			write(clientSocket,buffer1,512);
			ch1 = fgetc(f1);
     			 }
			printf(" [+]The file was sent successfully \n");
			
			
			
               	
               	
		return 0;
		}
		if(choise == 2 ){
			printf("\n[+]You Chosed platform as a service\n");
			printf("\n------------------------------Platform as a Service-------------------- \n");
			printf("       	 	  ################################################\n");
			printf("       	 	  ||                                             ||\n");
			printf("       	 	  ||               ** Compiler **                ||\n"); 
			printf("       	 	  ||                                             ||\n");
               	printf("       	 	  ################################################ \n");
               	printf("\n");
               	
               	
               	
               	int fd;
	char fileName[2000],afileName[2000],vfileName[2000],file_buffer[2000],c;
               	int choice = 1;
	
	while(choice!=4)
	{
		printf("ENTER YOUR CHOICE \n 1.Test your Code files \n 2.Exit \n");
		scanf("%d",&choice);
		
		char num=choice;
		write(clientSocket, &choice, sizeof(int));
		
		switch(choice)
		{
			case 1:
				printf("Enter code file name to send : \n");
    				scanf("%s",fileName);
    				FILE *fp;
     				fp=fopen(fileName,"r");

     				if(fp)
     				{
    	 				printf("\n Reading file contents.\n");
     					fseek(fp,0,SEEK_END);
       					size_t file_size=ftell(fp);
       					fseek(fp,0,SEEK_SET);
      					if(fread(file_buffer,file_size,1,fp)<=0)
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
    				printf("FILE CONTENTS TO SEND \n : %s\n",file_buffer);
    				char kuch[10] = "sac";  				
    				
    				write(clientSocket, file_buffer, sizeof(file_buffer));
    				
    	 			printf(" [+]FILE SENT\n");
    				fclose(fp);
    				break;
    				
    			case 2:
    				
				break;
				
			case 3:
				
				break;
		
			case 4:
				close(fd);
				break;
				
		
		
		}
		printf("\n");
		printf("The output of your code is : ");
			char kuch[10];
           // read(sockfd,buffer,255)
    		read(clientSocket,kuch,sizeof(kuch));
    		printf("%s \n",kuch);	
		printf("\n");
		exit(1);
	}
               	
               	
               	
		
		return 0;
		}
		if(choise == 3 ){
			
			printf("\nYou Chosed software as a service\n");
			printf("\n Welcome to our Software as a Service \n");
			printf("       	 	  ################################################\n");
			printf("       	 	  ||       Enter service you want to avail       ||\n");
			printf("       	 	  ||          |  1 - Calculator     |            ||\n"); 
			printf("       	 	  ||          |  2 - File transfer  |            ||\n");
               	printf("       	 	  ################################################ \n");
			scanf("%d", &choise2);
			write(clientSocket, &choise2, sizeof(int));    	//send this to server	
			if(choise2 == 1){
			printf(" [+]Calculator oppened\n");
			printf(" Enter quadratic equation in the format ax^2+bx+c:\n");
			printf(" Enter a: \n");
			scanf("%d", &a);
			write(clientSocket, &a, sizeof(int));    	//send this to server
			printf(" Enter b: \n");
			scanf("%d", &b);
			write(clientSocket, &b, sizeof(int));    	//send this to server
			printf(" Enter c: \n");
			scanf("%d", &c);
			write(clientSocket, &c, sizeof(int));    	//send this to server
			
			read(clientSocket,&root1,255);
			printf(" root1 is : %d \n",root1);
			read(clientSocket,&root2,255);
			printf(" root2 is : %d \n",root2);
			return 0;
			}
			else if(choise2 == 2){
			printf(" [+]Transfer Files software openned\n");
			
			
			FILE *f;
   			int words = 0;
    			char c;
    			
			printf(" Enter File Name\n");
			char filename[20];
			scanf("%s",filename);
    			write(clientSocket, filename, sizeof(filename));  
    			int wait=0;
    			while(wait ==0 )
    		{
    			
     			f=fopen(filename,"r");
     			
   			 while((c=getc(f))!=EOF)			//Counting No of words in the file
			{	
			fscanf(f , "%s" , buffer);
			if(isspace(c)||c=='\t')
			words++;	
			}
			
			wait = 1;
       
      		}
			write(clientSocket, &words, sizeof(int));
     			rewind(f);
       
    			char ch ;
      			 while(ch != EOF)
      			{
		
			fscanf(f , "%s" , buffer);

			write(clientSocket,buffer,512);
			ch = fgetc(f);
     			 }
			printf(" [+]The file was sent successfully \n");
			
			
			return 0;
			}
			return 0;
		}

		

	}
    }
else
{
	printf("\n Dissconnected due to some reason !\n");
	printf(" Open the client program again !\n");
}
	close(clientSocket);
	return 0;
}
