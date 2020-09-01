
#include <netdb.h>
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#define SA struct sockaddr
#define MAX 500
#define PORT 8080 

typedef struct Store{
  int id_1;
  int id_2;
  int id_3;
}Store;

typedef struct IndividualUser{
  char name[30];
  char acc_type;
  int user_id;
  int acc_number;
  long long int balance;
  char temp[30];
  char pass[30];
  char stat[20];
}IndividualUser;

typedef struct JointUser{
  char name1[30];
  char name2[30];
  char acc_type;
  int user_id;
  int acc_number;
  long long int balance;
  char temp[30];
  char pass[30];
  char stat[20];
}JointUser;

typedef struct AdminUser{
  char name[30];
  char pass[30];
  int user_id;
  char temp[30];
}Admin;
int c,currID;

void IndividualUserLogin(int sockfd);
void JointUserLogin(int sockfd);
void AdminLogin(int sockfd);
void sublogin(int sockfd);
void CreateAccount(int sockfd);
void deleteAccount(int sockfd);
void deposit(int sockfd);
void withdraw(int sockfd);
void getBalance(int sockfd);
void Password(int sockfd);
void viewDetails(int sockfd);
void getAccount(int sockfd);

void login(int sockfd){
	write(1,"\n\n\t1 : Individual-User Login",sizeof("\n\n\t1 : Individual-User Login"));
	write(1,"\n\n\t2 : Joint-User Login",sizeof("\n\n\t2 : Joint-User Login"));
	write(1,"\n\n\t3 : Admin Login",sizeof("\n\n\t3 : Admin Login"));

	write(1,"\n\n\tChoose an option : ",sizeof("\n\n\tChoose an option : "));
	scanf("%d",&c);
	switch(c){
		case 1 :
			IndividualUserLogin(sockfd);
			break;
		case 2 :
			JointUserLogin(sockfd);
			break;
		case 3 :
			AdminLogin(sockfd);
			break;
		default :
			write(1,"Invalid option!!\n\n",sizeof("Invalid option!!\n\n"));
			login(sockfd);
			break;
	}
}

void sublogin(int sockfd){
	int c1;
	if(c==1 || c==2){
		write(1,"\n\n\t1 : Deposit",sizeof("\n\n\t1 : Deposit"));
		write(1,"\n\n\t2 : Withdraw",sizeof("\n\n\t2 : Withdraw"));
		write(1,"\n\n\t3 : Balance Enquiry",sizeof("\n\n\t3 : Balance Enquiry"));
		write(1,"\n\n\t4 : Password Change",sizeof("\n\n\t4 : Password Change"));
		write(1,"\n\n\t5 : View Details",sizeof("\n\n\t5 : View Details"));
		write(1,"\n\n\t6 : Exit",sizeof("\n\n\t6 : Exit"));
	
		write(1,"\n\n\tChoose an option : ",sizeof("\n\n\tChoose an option : "));
		scanf("%d",&c1);
		
		switch(c1){
		case 1 :
			deposit(sockfd);
			break;
		case 2 :
			withdraw(sockfd);
			break;
		case 3 :
			getBalance(sockfd);
			break;
		case 4 :
			Password(sockfd);
			break;
		case 5 :
			viewDetails(sockfd);
			break;
		case 6 :
			write(sockfd,&c1,sizeof(int));
			write(1,"\n\n\tThank you\n",sizeof("\n\n\tThank you\n"));
			exit(0);
		default :
			write(1,"Invalid option!!\n\n",sizeof("Invalid option!!\n\n"));
			sublogin(sockfd);
			break;
		}
	}
	else if(c==3){
		write(1,"\n\n\t1 : Add Account",sizeof("\n\n\t1 : Add Account"));
		write(1,"\n\n\t2 : Delete Account",sizeof("\n\n\t2 : Delete Account"));
		write(1,"\n\n\t3 : Search Account",sizeof("\n\n\t3 : Search Account"));
		write(1,"\n\n\t4 : Exit",sizeof("\n\n\t4 : Exit"));

		write(1,"\n\n\tChoose an option : ",sizeof("\n\n\tChoose an option : "));
		scanf("%d",&c1);
		
		switch(c1){
		case 1 :
			CreateAccount(sockfd);
			break;
		case 2 :
			deleteAccount(sockfd);
			break;
		case 3 :
			getAccount(sockfd);
			break;
		case 4 :
			write(sockfd,&c1,sizeof(int));
			write(1,"\n\n\tThank you\n",sizeof("\n\n\tThank you\n"));
			exit(0);
		default :
			write(1,"\n\n\tInvalid option!!",sizeof("\n\n\tInvalid option!!"));
			sublogin(sockfd);
			break;
		}
	}
}

void getAccount(int sockfd){
	int c1 = 3,type;
	int id;
	write(sockfd,&c1,sizeof(int));

	printf("\n\n\tEnter the type of account!!");
	printf("\n\n\t1 : Individual Account");
	printf("\n\n\t2 : Joint Account\n\n\t");
	
	scanf("%d",&type);
	write(sockfd,&type,sizeof(int));

	printf("\n\n\tEnter the user-ID : ");
	scanf("%d",&id);
	write(sockfd,&id,sizeof(int));

	if(type==1){
		IndividualUser user1;
		read(sockfd,&user1,sizeof(IndividualUser));
		write(1,"\n\n\tUser ID : ",sizeof("\n\n\tUser ID : "));
		printf("%d\n",user1.user_id);
		write(1,"\n\n\tName : ",sizeof("\n\n\tName : "));
		printf("%s\n",user1.name);
		write(1,"\n\n\tAccount Number : ",sizeof("\n\n\tAccount Number : "));
		printf("%d\n",user1.acc_number);
		write(1,"\n\n\tAvailable Balance : Rs",sizeof("\n\n\tAvailable Balance : Rs"));
		printf("%lld\n",user1.balance);
		write(1,"\n\n\tStatus : ",sizeof("\n\n\tStatus : "));
		printf("%s\n",user1.stat);
		sleep(5);
	}
	if(type == 2){
		JointUser user2;
		read(sockfd,&user2,sizeof(JointUser));
		write(1,"\n\n\tUser ID : ",sizeof("\n\n\tUser ID : "));
		printf("%d\n",user2.user_id);
		write(1,"\n\n\tName 1 : ",sizeof("\n\n\tName 1 : "));
		printf("%s\n",user2.name1);
		write(1,"\n\n\tName 2 : ",sizeof("\n\n\tName 2 : "));
		printf("%s\n",user2.name2);
		write(1,"\n\n\tAccount Number : ",sizeof("\n\n\tAccount Number : "));
		printf("%d\n",user2.acc_number);
		write(1,"\n\n\tAvailable Balance : Rs",sizeof("\n\n\tAvailable Balance : Rs"));
		printf("%lld\n",user2.balance);
		write(1,"\n\n\tStatus : ",sizeof("\n\n\tStatus : "));
		printf("%s\n",user2.stat);
		sleep(5);
	}
	sublogin(sockfd);
	return;
}

void IndividualUserLogin(int sockfd){
	int result;
	IndividualUser user;
	printf("\n\n\tEnter IndividualUser ID : ");
	scanf("%d", &user.user_id);
	printf("\n\n\tEnter IndividualUser password : ");
	scanf("%s", user.pass );
	sprintf(user.temp, "%d", user.user_id);
	currID = user.user_id;
	//to server
	write(sockfd,&c,sizeof(int));
    
	write(sockfd,&user,sizeof(IndividualUser));
	//from server
	read(sockfd,&result,sizeof(result));
	if(result == 0){
		write(1,"\n\n\tInvalid login!!",sizeof("\n\n\tInvalid login!!"));
		login(sockfd);
	}
	else{
		write(1,"\n\n\tSuccesfully logged in!!",sizeof("\n\n\tSuccesfully logged in!!\n\n"));
	}
	return;
}

void JointUserLogin(int sockfd){
	int result;
	JointUser user;
	printf("\n\n\tEnter JointUser ID : ");
	scanf("%d", &user.user_id);
	printf("\n\n\tEnter JointUser password : ");
	scanf("%s", user.pass );
	sprintf(user.temp, "%d", user.user_id);
	currID = user.user_id;
	//to server
	write(sockfd,&c,sizeof(int));
    
	write(sockfd,&user,sizeof(JointUser));
	//from server
	read(sockfd,&result,sizeof(result));
	if(result == 0){
		write(1,"\n\n\tInvalid login!!",sizeof("\n\n\tInvalid login!!"));
		login(sockfd);
	}
	else{
		write(1,"\n\n\tSuccesfully logged in!!",sizeof("\n\n\tSuccesfully logged in!!\n\n"));
	}
	return;

}
void AdminLogin(int sockfd){
	int result;
	Admin user;
	printf("\n\n\tEnter Admin ID : ");
	scanf("%d", &user.user_id);
	printf("\n\n\tEnter Admin password : ");
	scanf("%s", user.pass );
	sprintf(user.temp, "%d", user.user_id);
	currID = user.user_id;
	//to server
	write(sockfd,&c,sizeof(int));
	write(sockfd,&user,sizeof(Admin));
	//from server
	read(sockfd,&result,sizeof(result));
	if(result == 0){
		write(1,"\n\n\tInvalid login!!",sizeof("\n\n\tInvalid login!!"));
		login(sockfd);
	}
	else{
		write(1,"\n\n\tSuccesfully logged in!!",sizeof("\n\n\tSuccesfully logged in!!\n\n"));
	}
	return;

}


void viewDetails(int sockfd){
	int c1=5;
	write(sockfd,&c1,sizeof(int));
	if(c==1){
		IndividualUser user1;
		read(sockfd,&user1,sizeof(IndividualUser));
		write(1,"\n\n\tUser ID : ",sizeof("\n\n\tUser ID : "));
		printf("%d\n",user1.user_id);
		write(1,"\n\n\tName : ",sizeof("\n\n\tName : "));
		printf("%s\n",user1.name);
		write(1,"\n\n\tAccount Number : ",sizeof("\n\n\tAccount Number : "));
		printf("%d\n",user1.acc_number);
		write(1,"\n\n\tAvailable Balance : Rs",sizeof("\n\n\tAvailable Balance : Rs"));
		printf("%lld\n",user1.balance);
		write(1,"\n\n\tStatus : ",sizeof("\n\n\tStatus : "));
		printf("%s\n",user1.stat);
		sleep(5);
	}

	if(c==2){
		JointUser user2;
		read(sockfd,&user2,sizeof(JointUser));
		write(1,"\n\n\tUser ID : ",sizeof("\n\n\tUser ID : "));
		printf("%d\n",user2.user_id);
		write(1,"\n\n\tName 1 : ",sizeof("\n\n\tName 1 : "));
		printf("%s\n",user2.name1);
		write(1,"\n\n\tName 2 : ",sizeof("\n\n\tName 2 : "));
		printf("%s\n",user2.name2);
		write(1,"\n\n\tAccount Number : ",sizeof("\n\n\tAccount Number : "));
		printf("%d\n",user2.acc_number);
		write(1,"\n\n\tAvailable Balance : Rs",sizeof("\n\n\tAvailable Balance : Rs"));
		printf("%lld\n",user2.balance);
		write(1,"\n\n\tStatus : ",sizeof("\n\n\tStatus : "));
		printf("%s\n",user2.stat);
		sleep(5);
	}
	sublogin(sockfd);
	return;
}
void Password(int sockfd){
	int c1=4,result;
	char pass[30];

	write(1,"\n\n\tEnter the new password : ",sizeof("\n\n\tEnter the new password : "));
	scanf("%s",pass);

	write(sockfd,&c1,sizeof(int));
	write(sockfd,pass,sizeof(pass));

	read(sockfd,&result,sizeof(result)); 

	if(result==0){
		write(1,"\n\n\tERROR!!",sizeof("\n\n\tERROR!!"));
	}
	else{
		write(1,"\n\n\tSuccesfully changed your password!!",sizeof("\n\n\tSuccesfully changed your password!!\n\n"));
	}
	sublogin(sockfd);
	return;
}

void withdraw(int sockfd){
	int c1=2;
	int result;
	long long int dep;

	printf("\n\n\tEnter the amount you want to withdraw : Rs");
	scanf("%lld",&dep);

	while(dep<=0){
		printf("\n\n\tEnter a valid amount!!");
		printf("\n\n\tEnter the amount you want to withdraw : Rs");
		scanf("%lld",&dep);
	}
	write(sockfd,&c1,sizeof(int));
	write(sockfd,&dep,sizeof(long long int));

	read(sockfd,&result,sizeof(result));

	if(result==0){
		write(1,"\n\n\tError withdrawing your money..LOW BALANCE!!",sizeof("\n\n\tError withdrawing your money..LOW BALANCE!!"));
	}
	else{
		write(1,"\n\n\tSuccesfully withdrawn!!",sizeof("\n\n\tSuccesfully withdrawn!!"));
	}

	sublogin(sockfd);
	return;
}
void deposit(int sockfd){
	int c1=1,result;
	long long int dep;

	printf("\n\n\tEnter the amount you want to deposit : Rs");
	scanf("%lld",&dep);

	while(dep<=0){
		printf("\n\n\tEnter a valid amount!!");
		printf("\n\n\tEnter the amount you want to deposit : Rs");
		scanf("%lld",&dep);
	}
	write(sockfd,&c1,sizeof(int));
	write(sockfd,&dep,sizeof(long long int));

	read(sockfd,&result,sizeof(result));

	if(result==0){
		write(1,"\n\n\tError depositing your money!!",sizeof("\n\n\tError depositing your money!!"));
	}
	else{
		write(1,"\n\n\tSuccesfully deposited!!",sizeof("\n\n\tSuccesfully deposited!!"));
	}

	sublogin(sockfd);
	return;
}
void getBalance(int sockfd){
	long long int bal;
	int c1 =3;
	write(sockfd,&c1,sizeof(int));
	
	read(sockfd,&bal,sizeof(long long int));
	write(1,"\n\n\tBalance : Rs",sizeof("\n\n\tBalance : Rs"));
	printf("%lld\n",bal);
	
	sublogin(sockfd);
	return;
}
void CreateAccount(int sockfd){
	int c1=1;
	int type;
	int result;

	write(sockfd,&c1,sizeof(int));

	printf("\n\n\tEnter the type of account!!");
	printf("\n\n\t1 : Individual Account");
	printf("\n\n\t2 : Joint Account");
	printf("\n\n\t3 : Create new Admin\n\n\t");

	scanf("%d",&type);
	write(sockfd,&type,sizeof(int));

	if(type == 1){
		IndividualUser add1;
		printf("\n\n\tEnter the name of the account holder : ");
		scanf(" %[^\n]",add1.name);
		printf("\n\n\tEnter the password : ");
		scanf("%s",add1.pass);
		printf("\n\n\tEnter the account type(S/C) : ");
		scanf(" %c",&add1.acc_type);
		printf("\n\n\tEnter the initial balance : Rs");
		scanf("%lld",&add1.balance);
		write(sockfd,&add1,sizeof(IndividualUser));
	}

	if(type == 2){
		JointUser add2;
		printf("\n\n\tEnter the name of the account holder 1: ");
		scanf(" %[^\n]",add2.name1);
		printf("\n\n\tEnter the name of the account holder 2: ");
		scanf(" %[^\n]",add2.name2);
		printf("\n\n\tEnter the password : ");
		scanf("%s",add2.pass);
		printf("\n\n\tEnter the account type(S/C) : ");
		scanf(" %c",&add2.acc_type);
		printf("\n\n\tEnter the initial balance : Rs");
		scanf("%lld",&add2.balance);
		write(sockfd,&add2,sizeof(JointUser));
	}
	if(type == 3){
		Admin add3;
		printf("\n\n\tEnter the new admin username : ");
		scanf(" %[^\n]",add3.name);
		printf("\n\n\tEnter the password : ");
		scanf("%s",add3.pass);
		write(sockfd,&add3,sizeof(Admin));
	}

	read(sockfd,&result,sizeof(result)); 

	if(result==0){
		write(1,"\n\n\tError adding the account!!",sizeof("\n\n\tError adding the account!!"));
	}
	else{
		write(1,"\n\n\tSuccesfully created!!",sizeof("\n\n\tSuccesfully created!!"));
	}
	sublogin(sockfd);
	return;
	
}

void deleteAccount(int sockfd){
	int c1=2;
	int type,userID;
	int result;
	write(sockfd,&c1,sizeof(int));

	printf("\n\n\tEnter the type of account!!");
	printf("\n\n\t1 : Individual Account");
	printf("\n\n\t2 : Joint Account\n\n\t");
	//printf("\n\n\t3 : Create new Admin");
	scanf("%d",&type);
	write(sockfd,&type,sizeof(int));

	printf("\n\n\tEnter the user-ID : ");
	scanf("%d",&userID);
	write(sockfd,&userID,sizeof(int));

	read(sockfd,&result,sizeof(result));

	if(result==0){
		write(1,"\n\n\tError deleting the account...TRY AGAIN!!",sizeof("\n\n\tError deleting the account...TRY AGAIN!!"));
	}
	else{
		write(1,"\n\n\tSuccesfully deleted the account!!",sizeof("\n\n\tSuccesfully deleted the account!!"));
	}
	sublogin(sockfd);
	return;

}

//sockaddr_in and sockaddr are same in memory
int main(){
struct sockaddr_in servaddr;
int clientsocket;
clientsocket = socket(AF_INET, SOCK_STREAM, 0);
if(clientsocket ==-1){
	printf("Socket creation failed...\n");
	exit(0);
}
else
	printf("Socket successfully created...\n");
bzero(&servaddr, sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
servaddr.sin_port = htons(PORT);

if (connect(clientsocket, (SA*)&servaddr, sizeof(servaddr)) != 0) { 
        printf("connection with the server failed...\n"); 
        exit(0); 
    } 
    else
        printf("connected to the server..\n"); 
login(clientsocket);
sublogin(clientsocket);
//func(clientsocket);
close(clientsocket);
}
