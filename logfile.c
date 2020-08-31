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

int id1=0,id2=0,id3=0;

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
}AdminUser;

void create_1(){
	AdminUser admin;
	char c[10];
	char extension[20];
	strcpy(extension,"Admin/");
	printf("\n\n\tEnter the Admin username :");
	scanf(" %[^\n]",admin.name);
	printf("\n\n\tEnter the Admin password : ");
	scanf(" %[^\n]",admin.pass);
	admin.user_id = ++id1;
	sprintf(admin.temp, "%d",admin.user_id);
	strcat(extension,admin.temp);
	int fd = open(extension,O_RDWR | O_CREAT,0744);
	write(fd,&admin,sizeof(AdminUser));
	close(fd);
	printf("\n\tDo you want to create more Admins(y/n) : ");
	scanf("%s",c);
	if(strcmp(c,"y")==0){
		while(1){
			char ex[20];
			strcpy(ex,"Admin/");
			printf("\n\n\tEnter the Admin username :");
			scanf(" %[^\n]",admin.name);
			printf("\n\n\tEnter the Admin password :");
			scanf(" %[^\n]",admin.pass);
			admin.user_id = ++id1;
			sprintf(admin.temp, "%d",admin.user_id);
			strcat(ex,admin.temp);
			fd = open(ex,O_RDWR | O_CREAT,0744);
			write(fd,&admin,sizeof(AdminUser));
			close(fd);
			printf("\n\tDo you want to create more Admins(y/n) : ");
			scanf("%s",c);
			if(strcmp(c,"n")==0){
				break;
			}
			else
				continue;
		}
	}

}
void create_2(){
	IndividualUser user1;
	char c[10];
	char extension[20];
	strcpy(extension,"IndividualUser/");
	printf("\n\n\tEnter the IndividualUser username :");
	scanf(" %[^\n]",user1.name);
	printf("\n\n\tEnter the IndividualUser password : ");
	scanf(" %[^\n]",user1.pass);
	printf("\n\n\tEnter the IndividualUser account type(S/C) : ");
	scanf(" %c",&user1.acc_type);
	strcpy(user1.stat,"active");
	user1.user_id = ++id2;
	sprintf(user1.temp, "%d",user1.user_id);
	user1.acc_number = 100 + user1.user_id;
	user1.balance = 10000;
	strcat(extension,user1.temp);
	int fd = open(extension,O_RDWR | O_CREAT,0744);
	write(fd,&user1,sizeof(IndividualUser));
	close(fd);
	printf("\n\tDo you want to create more IndividualUser(y/n) : ");
	scanf("%s",c);
	if(strcmp(c,"y")==0){
		while(1){
			char ex[20];
			strcpy(ex,"IndividualUser/");
			printf("\n\n\tEnter the IndividualUser username :");
			scanf(" %[^\n]",user1.name);
			printf("\n\n\tEnter the IndividualUser password :");
			scanf(" %[^\n]",user1.pass);
			printf("\n\n\tEnter the IndividualUser account type(S/C) : ");
			scanf(" %c",&user1.acc_type);
			strcpy(user1.stat,"active");
			user1.user_id = ++id2;
			sprintf(user1.temp, "%d",user1.user_id);
			user1.acc_number = 100 + user1.user_id;
			user1.balance = 10000;
			strcat(ex,user1.temp);
			fd = open(ex,O_RDWR | O_CREAT,0744);
			write(fd,&user1,sizeof(IndividualUser));
			close(fd);
			printf("\n\tDo you want to create more IndividualUser(y/n) : ");
			scanf("%s",c);
			if(strcmp(c,"n")==0){
				break;
			}
			else
				continue;
		}
	}

}
void create_3(){
	JointUser user1;
	char c[10];
	char extension[20];
	strcpy(extension,"JointUser/");
	printf("\n\n\tEnter the JointUser username 1 :");
	scanf(" %[^\n]",user1.name1);
	printf("\n\n\tEnter the JointUser username 2 :");
	scanf(" %[^\n]",user1.name2);
	printf("\n\n\tEnter the JointUser password : ");
	scanf(" %[^\n]",user1.pass);
	printf("\n\n\tEnter the JointUser account type(S/C) : ");
	scanf(" %c",&user1.acc_type);
	strcpy(user1.stat,"active");
	user1.user_id = ++id3;
	sprintf(user1.temp, "%d",user1.user_id);
	user1.acc_number = 100 + user1.user_id;
	user1.balance = 10000;
	strcat(extension,user1.temp);
	int fd = open(extension,O_RDWR | O_CREAT,0744);
	write(fd,&user1,sizeof(JointUser));
	close(fd);
	printf("\n\tDo you want to create more JointUser(y/n) : ");
	scanf("%s",c);
	if(strcmp(c,"y")==0){
		while(1){
			char ex[20];
			strcpy(ex,"JointUser/");
			printf("\n\n\tEnter the JointUser username 1 :");
			scanf(" %[^\n]",user1.name1);
			printf("\n\n\tEnter the JointUser username 2 :");
			scanf(" %[^\n]",user1.name2);
			printf("\n\n\tEnter the JointUser password :");
			scanf(" %[^\n]",user1.pass);
			printf("\n\n\tEnter the JointUser account type(S/C) : ");
			scanf(" %c",&user1.acc_type);
			strcpy(user1.stat,"active");
			user1.user_id = ++id3;
			sprintf(user1.temp, "%d",user1.user_id);
			user1.acc_number = 100 + user1.user_id;
			user1.balance = 10000;
			strcat(ex,user1.temp);
			fd = open(ex,O_RDWR | O_CREAT,0744);
			write(fd,&user1,sizeof(JointUser));
			close(fd);
			printf("\n\tDo you want to create more JointUser(y/n) : ");
			scanf("%s",c);
			if(strcmp(c,"n")==0){
				break;
			}
			else
				continue;
		}
	}

}

void Store_id(){
	Store store;
	store.id_1 = id1;
	store.id_2 = id2;
	store.id_3 = id3;
	int fd = open("Store",O_RDWR | O_CREAT,0744);
	write(fd,&store,sizeof(Store));
}

void main(){
	create_1();
	create_2();
	create_3();
	Store_id();
}

