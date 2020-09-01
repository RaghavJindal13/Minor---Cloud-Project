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


int IndividualUserLogin(IndividualUser currUser){
  int ret;
  char extension[20];
  strcpy(extension,"IndividualUser/");
  strcat(extension,currUser.temp);
  IndividualUser user;
  int fd = open(extension,O_RDONLY,0744);  
  int locker;
  struct flock lock;
  lock.l_type = F_RDLCK;
  lock.l_whence=SEEK_SET;
  lock.l_start= 0;          
  lock.l_len=sizeof(IndividualUser);              
  lock.l_pid=getpid();

  locker = fcntl(fd,F_SETLKW,&lock);  //lock the selected record
  read(fd,&user,sizeof(IndividualUser));

  if(!strcmp(currUser.pass,user.pass) && !strcmp(user.stat,"active")){
    printf("Entered as IndividualUser.. !!\n");
    ret = 1;
  }
  else
    ret = 0;
  lock.l_type=F_UNLCK; //unlock it.
  fcntl(fd,F_SETLK,&lock);
  close(fd);
  return ret;
}

int JointUserLogin(JointUser currUser){
  int ret;
  char extension[20];
  strcpy(extension,"JointUser/");
  strcat(extension,currUser.temp);
  JointUser user;
  int fd = open(extension,O_RDONLY,0744);
    
  int locker;
  struct flock lock;
  lock.l_type = F_RDLCK;
  lock.l_whence=SEEK_SET;
  lock.l_start= 0;          
  lock.l_len=sizeof(JointUser);              
  lock.l_pid=getpid();

  locker = fcntl(fd,F_SETLKW,&lock);  //lock the selected record
  read(fd,&user,sizeof(JointUser));

  if(!strcmp(currUser.pass,user.pass) && !strcmp(user.stat,"active")){
    printf("Entered as JointUser.. !!\n");
    ret = 1;
  }
  else
    ret = 0;
  lock.l_type=F_UNLCK; //unlock it.
  fcntl(fd,F_SETLK,&lock);
  close(fd);
  return ret;
}

int AdminLogin(Admin currUser){
    int ret;
    char extension[20];
    strcpy(extension,"Admin/");
    strcat(extension,currUser.temp);

    int fd = open(extension,O_RDONLY,0744);
    Admin user;
    int locker;
    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence=SEEK_SET;
    lock.l_start= 0;          
    lock.l_len=sizeof(Admin);              
    lock.l_pid=getpid();
    
    
    locker = fcntl(fd,F_SETLKW,&lock);  //lock the selected record
    read(fd,&user,sizeof(Admin));

    if(strcmp(currUser.pass,user.pass)==0){
      //write(sockfd,"Admin access....COMPLETED !!",sizeof("Admin access....COMPLETED !!"));
      printf("Entered as admin.. !!\n");
      ret = 1;
    }
    else{
      ret = 0;
      //write(sockfd,"Wrong password....TRY AGAIN !!",sizeof("Wrong password....TRY AGAIN !!"));
    }
    lock.l_type=F_UNLCK; //unlock it.
    fcntl(fd,F_SETLK,&lock);
    close(fd);
    return ret; 
}
int CreateIndividualUser(IndividualUser user){
  Store store;
  int result,ret;
  int fd = open("Store", O_RDONLY,0744);

  int locker;
  struct flock lock;            //read lock 
  lock.l_type = F_RDLCK;
  lock.l_whence=SEEK_SET;
  lock.l_start= 0;          
  lock.l_len=sizeof(Store);              
  lock.l_pid=getpid();
  
  locker = fcntl(fd,F_SETLKW,&lock);

  read(fd,&store,sizeof(Store));
  user.user_id = ++store.id_2;
  user.acc_number = 100 + user.user_id;
  sprintf(user.temp,"%d",user.user_id);
  strcpy(user.stat,"active");
  lock.l_type=F_UNLCK; //unlock it.
  fcntl(fd,F_SETLK,&lock);
  close(fd);  
  
  char extension[20];
  strcpy(extension,"IndividualUser/");
  strcat(extension,user.temp);


  fd = open("Store", O_WRONLY,0744);

  lock.l_type = F_WRLCK;
  lock.l_whence=SEEK_SET;
  lock.l_start= 0;          
  lock.l_len=sizeof(Store);              
  lock.l_pid=getpid();

  locker = fcntl(fd,F_SETLKW,&lock); 

  int fd1 = open(extension,O_RDWR | O_CREAT,0744);
  ret = write(fd1,&user,sizeof(IndividualUser));
  close(fd1);
  printf("%d  %d  %d\n",store.id_1,store.id_2,store.id_3);
  write(fd,&store,sizeof(Store));
  if(ret!=0){
    result = 1;
    printf("New IndividualUser created.. !!\n");
  }
  else
    result = 0;
  lock.l_type=F_UNLCK; //unlock it.
  fcntl(fd,F_SETLK,&lock);
  close(fd);


  
  return result;
}


int CreateJointUser(JointUser user){
  int result,ret;
  Store store;
  int fd = open("Store", O_RDONLY,0744);

  int locker;
  struct flock lock;            //read lock 
  lock.l_type = F_RDLCK;
  lock.l_whence=SEEK_SET;
  lock.l_start= 0;          
  lock.l_len=sizeof(Store);              
  lock.l_pid=getpid();
  
  locker = fcntl(fd,F_SETLKW,&lock);

  read(fd,&store,sizeof(Store));
  user.user_id = ++store.id_3;
  user.acc_number = 100 + user.user_id;
  sprintf(user.temp,"%d",user.user_id);
  strcpy(user.stat,"active");
  lock.l_type=F_UNLCK; //unlock it.
  fcntl(fd,F_SETLK,&lock);
  close(fd);  
  
  char extension[20];
  strcpy(extension,"JointUser/");
  strcat(extension,user.temp);


  fd = open("Store", O_WRONLY,0744);

  lock.l_type = F_WRLCK;
  lock.l_whence=SEEK_SET;
  lock.l_start= 0;          
  lock.l_len=sizeof(Store);              
  lock.l_pid=getpid();

  locker = fcntl(fd,F_SETLKW,&lock); 

  int fd1 = open(extension,O_RDWR | O_CREAT,0744);
  ret = write(fd1,&user,sizeof(JointUser));
  close(fd1);
  printf("%d  %d  %d\n",store.id_1,store.id_2,store.id_3);
  write(fd,&store,sizeof(Store));
  if(ret!=0){
    result = 1;
    printf("New JointUser created.. !!\n");
  }
  else
    result = 0;
  lock.l_type=F_UNLCK; //unlock it.
  fcntl(fd,F_SETLK,&lock);
  close(fd);

  
  return result;
}


int CreateAdmin(Admin user){
  int result,ret;
  Store store;
  int fd = open("Store", O_RDONLY,0744);

  int locker;
  struct flock lock;            //read lock 
  lock.l_type = F_RDLCK;
  lock.l_whence=SEEK_SET;
  lock.l_start= 0;          
  lock.l_len=sizeof(Store);              
  lock.l_pid=getpid();
  
  locker = fcntl(fd,F_SETLKW,&lock);

  read(fd,&store,sizeof(Store));
  user.user_id = ++store.id_1;
  sprintf(user.temp,"%d",user.user_id);
  
  lock.l_type=F_UNLCK; //unlock it.
  fcntl(fd,F_SETLK,&lock);
  close(fd);  
  
  char extension[20];
  strcpy(extension,"Admin/");
  strcat(extension,user.temp);


  fd = open("Store", O_WRONLY,0744);

  lock.l_type = F_WRLCK;
  lock.l_whence=SEEK_SET;
  lock.l_start= 0;          
  lock.l_len=sizeof(Store);              
  lock.l_pid=getpid();

  locker = fcntl(fd,F_SETLKW,&lock); 

  int fd1 = open(extension,O_RDWR | O_CREAT,0744);
  ret = write(fd1,&user,sizeof(Admin));
  close(fd1);
  printf("%d  %d  %d\n",store.id_1,store.id_2,store.id_3);
  write(fd,&store,sizeof(Store));
  if(ret!=0){
    result = 1;
    printf("New Admin created.. !!\n");
  }
  else
    result = 0;
  lock.l_type=F_UNLCK; //unlock it.
  fcntl(fd,F_SETLK,&lock);
  close(fd);

  return result;
}

int deleteIndividualUser(int id){
  char idch[3];
  int ret=0,result;
  sprintf(idch,"%d",id);
  char extension[20];
  strcpy(extension,"IndividualUser/");
  strcat(extension,idch);
  int fd = open(extension,O_RDWR,0744);
  if(fd == -1){
    result = 0;
    return result;
  }
  int locker;
  struct flock lock;            //writelock 
  lock.l_type = F_WRLCK;
  lock.l_whence=SEEK_SET;
  lock.l_start= 0;          
  lock.l_len=sizeof(IndividualUser);              
  lock.l_pid=getpid();
  IndividualUser user;
  locker = fcntl(fd,F_SETLKW,&lock);
  read(fd,&user,sizeof(IndividualUser));

  if(strcmp(user.stat,"active")==0){  
    strcpy(user.stat,"disconnect");
    //currUser.balance=0;
    
    lseek(fd,(-1)*sizeof(IndividualUser),SEEK_CUR); 
    ret=write(fd,&user,sizeof(IndividualUser));
    
  }
  lock.l_type=F_UNLCK;
  fcntl(fd,F_SETLK,&lock);
  close(fd);
  return result;
  if(ret!=0){
      result=1;
      //printf("IndividualUser ID : %d deleted!!",id);
    }  
    else
      result=0;
  
}

int deleteJointUser(int id){
  char idch[3];
  int ret=0,result;
  sprintf(idch,"%d",id);
  char extension[20];
  strcpy(extension,"JointUser/");
  strcat(extension,idch);
  int fd = open(extension,O_RDWR,0744);
  if(fd == -1){
    result = 0;
    return result;
  }
  int locker;
  struct flock lock;            //writelock 
  lock.l_type = F_WRLCK;
  lock.l_whence=SEEK_SET;
  lock.l_start= 0;          
  lock.l_len=sizeof(JointUser);              
  lock.l_pid=getpid();
  JointUser user;
  locker = fcntl(fd,F_SETLKW,&lock);
  read(fd,&user,sizeof(JointUser));

  if(strcmp(user.stat,"active")==0){  
    strcpy(user.stat,"disconnect");
    //currUser.balance=0;
    
    lseek(fd,(-1)*sizeof(JointUser),SEEK_CUR); 
    ret=write(fd,&user,sizeof(JointUser));
   
  }
  lock.l_type=F_UNLCK;
  fcntl(fd,F_SETLK,&lock);
  close(fd);
  if(ret!=0){
      result=1;
      //printf("JointUser ID : %d deleted!!",id);
    }  
    else
      result=0;
  
  return result;

}
int deposit(int id,long long int dep){
  char idch[3];
  char extension[20];
  int result;
  sprintf(idch,"%d",id);
  strcpy(extension,"IndividualUser/");
  strcat(extension,idch);
  int fd = open(extension,O_RDWR,0744);
  int locker;
  struct flock lock;            //write lock 
  lock.l_type = F_WRLCK;
  lock.l_whence=SEEK_SET;
  lock.l_start= 0;          
  lock.l_len=sizeof(IndividualUser);              
  lock.l_pid=getpid();
  
  locker = fcntl(fd,F_SETLKW,&lock);

  IndividualUser user;
  read(fd,&user,sizeof(IndividualUser));
  if(strcmp(user.stat,"active") == 0){
    user.balance += dep;
    lseek(fd,sizeof(IndividualUser)*(-1),SEEK_CUR);
    write(fd,&user,sizeof(IndividualUser));
    result = 1; 
    //printf("Money deposited!!"); 
  }
  else{
    result = 0;
  }
  lock.l_type=F_UNLCK;
  fcntl(fd,F_SETLK,&lock);
  close(fd);
  return result;
}
int deposit_1(int id,long long int dep){
  char idch[3];
  char extension[20];
  int result;
  sprintf(idch,"%d",id);
  strcpy(extension,"JointUser/");
  strcat(extension,idch);
  int fd = open(extension,O_RDWR,0744);
  int locker;
  struct flock lock;            //write lock 
  lock.l_type = F_WRLCK;
  lock.l_whence=SEEK_SET;
  lock.l_start= 0;          
  lock.l_len=sizeof(JointUser);              
  lock.l_pid=getpid();
  
  locker = fcntl(fd,F_SETLKW,&lock);

  JointUser user;
  read(fd,&user,sizeof(JointUser));
  if(strcmp(user.stat,"active") == 0){
    user.balance += dep;
    lseek(fd,sizeof(JointUser)*(-1),SEEK_CUR);
    write(fd,&user,sizeof(JointUser));
    result = 1; 
    //printf("Money deposited!!"); 
  }
  else{
    result = 0;
  }
  lock.l_type=F_UNLCK;
  fcntl(fd,F_SETLK,&lock);
  close(fd);
  return result;  
}

int withdraw(int id,long long int dep){
  char idch[3];
  char extension[20];
  int result;
  sprintf(idch,"%d",id);
  strcpy(extension,"IndividualUser/");
  strcat(extension,idch);
  int fd = open(extension,O_RDWR,0744);
  int locker;
  struct flock lock;            //write lock 
  lock.l_type = F_WRLCK;
  lock.l_whence=SEEK_SET;
  lock.l_start= 0;          
  lock.l_len=sizeof(IndividualUser);              
  lock.l_pid=getpid();
  
  locker = fcntl(fd,F_SETLKW,&lock);

  IndividualUser user;
  read(fd,&user,sizeof(IndividualUser));
  if(strcmp(user.stat,"active") == 0 && (user.balance >= dep)){
    user.balance -= dep;
    lseek(fd,sizeof(IndividualUser)*(-1),SEEK_CUR);
    write(fd,&user,sizeof(IndividualUser));
    result = 1; 
    //printf("Money withdrawn!!"); 
  }
  else{
    result = 0;
  }
  lock.l_type=F_UNLCK;
  fcntl(fd,F_SETLK,&lock);
  close(fd);
  return result;

}

int withdraw_1(int id,long long int dep){
  char idch[3];
  char extension[20];
  int result;
  sprintf(idch,"%d",id);
  strcpy(extension,"JointUser/");
  strcat(extension,idch);
  int fd = open(extension,O_RDWR,0744);
  int locker;
  struct flock lock;            //write lock 
  lock.l_type = F_WRLCK;
  lock.l_whence=SEEK_SET;
  lock.l_start= 0;          
  lock.l_len=sizeof(JointUser);              
  lock.l_pid=getpid();
  
  locker = fcntl(fd,F_SETLKW,&lock);

  JointUser user;
  read(fd,&user,sizeof(JointUser));
  if(strcmp(user.stat,"active")==0 && (user.balance >= dep)){
    user.balance -= dep;
    lseek(fd,sizeof(JointUser)*(-1),SEEK_CUR);
    write(fd,&user,sizeof(JointUser));
    result = 1; 
    //printf("Money withdrawn!!"); 
  }
  else{
    result = 0;
  }
  lock.l_type=F_UNLCK;
  fcntl(fd,F_SETLK,&lock);
  close(fd);
  return result;
}

long long int getBalance(int id){
  long long int result;
  char idch[3];
  char extension[20];
  sprintf(idch,"%d",id);
  strcpy(extension,"IndividualUser/");
  strcat(extension,idch);
  int fd = open(extension,O_RDONLY,0744);
  int locker;
  struct flock lock;            //read lock 
  lock.l_type = F_RDLCK;
  lock.l_whence=SEEK_SET;
  lock.l_start= 0;          
  lock.l_len=sizeof(IndividualUser);              
  lock.l_pid=getpid();
  
  locker = fcntl(fd,F_SETLKW,&lock);

  IndividualUser user;
  read(fd,&user,sizeof(IndividualUser));
  if(strcmp(user.stat,"active") == 0){
    result = user.balance;
  }
  else{
    result = 0;
  }
  lock.l_type=F_UNLCK;
  fcntl(fd,F_SETLK,&lock);
  close(fd);
  return result;
}



long long int getBalance_1(int id){
  long long int result;
  char idch[3];
  char extension[20];
  sprintf(idch,"%d",id);
  strcpy(extension,"JointUser/");
  strcat(extension,idch);
  int fd = open(extension,O_RDONLY,0744);
  int locker;
  struct flock lock;            //read lock 
  lock.l_type = F_RDLCK;
  lock.l_whence=SEEK_SET;
  lock.l_start= 0;          
  lock.l_len=sizeof(JointUser);              
  lock.l_pid=getpid();
  
  locker = fcntl(fd,F_SETLKW,&lock);

  JointUser user;
  read(fd,&user,sizeof(JointUser));
  if(strcmp(user.stat,"active") == 0){
    result = user.balance;
  }
  else{
    result = 0;
  }
  lock.l_type=F_UNLCK;
  fcntl(fd,F_SETLK,&lock);
  close(fd);
  return result;
}

int changePassword(int id,char pass[30]){
  char idch[3];
  char extension[20];
  int result;
  sprintf(idch,"%d",id);
  strcpy(extension,"IndividualUser/");
  strcat(extension,idch);
  int fd = open(extension,O_RDWR,0744);
  int locker;
  struct flock lock;            //write lock 
  lock.l_type = F_WRLCK;
  lock.l_whence=SEEK_SET;
  lock.l_start= 0;          
  lock.l_len=sizeof(IndividualUser);              
  lock.l_pid=getpid();
  
  locker = fcntl(fd,F_SETLKW,&lock);

  IndividualUser user;
  read(fd,&user,sizeof(IndividualUser));
  if(strcmp(user.stat,"active") == 0){
    strcpy(user.pass,pass);
    lseek(fd,sizeof(IndividualUser)*(-1),SEEK_CUR);
    write(fd,&user,sizeof(IndividualUser));
    result = 1; 
    //printf("Money withdrawn!!"); 
  }
  else{
    result = 0;
  }
  lock.l_type=F_UNLCK;
  fcntl(fd,F_SETLK,&lock);
  close(fd);
  return result;

}

int changePassword_1(int id,char pass[30]){
  char idch[3];
  char extension[20];
  int result;
  sprintf(idch,"%d",id);
  strcpy(extension,"JointUser/");
  strcat(extension,idch);
  int fd = open(extension,O_RDWR,0744);
  int locker;
  struct flock lock;            //write lock 
  lock.l_type = F_WRLCK;
  lock.l_whence=SEEK_SET;
  lock.l_start= 0;          
  lock.l_len=sizeof(JointUser);              
  lock.l_pid=getpid();
  
  locker = fcntl(fd,F_SETLKW,&lock);

  JointUser user;
  read(fd,&user,sizeof(JointUser));
  if(strcmp(user.stat,"active")==0 ){
    strcpy(user.pass,pass);
    lseek(fd,sizeof(JointUser)*(-1),SEEK_CUR);
    write(fd,&user,sizeof(JointUser));
    result = 1; 
    //printf("Money withdrawn!!"); 
  }
  else{
    result = 0;
  }
  lock.l_type=F_UNLCK;
  fcntl(fd,F_SETLK,&lock);
  close(fd);
  return result;
}

IndividualUser getIndividualUser(int id){
  char idch[3];
  char extension[20];
  int result;
  IndividualUser user;

  sprintf(idch,"%d",id);
  strcpy(extension,"IndividualUser/");
  strcat(extension,idch);
  int fd = open(extension,O_RDONLY,0744);
  int locker;
  struct flock lock;            //read lock 
  lock.l_type = F_RDLCK;
  lock.l_whence=SEEK_SET;
  lock.l_start= 0;          
  lock.l_len=sizeof(IndividualUser);              
  lock.l_pid=getpid();
  
  locker = fcntl(fd,F_SETLKW,&lock);

    
  read(fd,&user,sizeof(IndividualUser));
  lock.l_type=F_UNLCK;
  fcntl(fd,F_SETLK,&lock);
  close(fd);
  return user;

}

JointUser getJointUser(int id){
  char idch[3];
  char extension[20];
  int result;
  JointUser user;
  sprintf(idch,"%d",id);
  strcpy(extension,"JointUser/");
  strcat(extension,idch);
  int fd = open(extension,O_RDONLY,0744);
  int locker;
  struct flock lock;            //write lock 
  lock.l_type = F_RDLCK;
  lock.l_whence=SEEK_SET;
  lock.l_start= 0;          
  lock.l_len=sizeof(JointUser);              
  lock.l_pid=getpid();
  
  locker = fcntl(fd,F_SETLKW,&lock);

    
  read(fd,&user,sizeof(JointUser));
  lock.l_type=F_UNLCK;
  fcntl(fd,F_SETLK,&lock);
  close(fd);
  return user;

}

void Options(int sockfd){
  int msgLength,c1,type,c,accType,currUserID;
  int result;
  while(1){
    read(sockfd,&c,sizeof(c));
    printf("Option : %d\n",c);

    if(c==1){
      IndividualUser currUser1;
      accType=1;
      msgLength=read(sockfd,&currUser1,sizeof(IndividualUser));
      printf("Username : %d\n",currUser1.user_id);
      printf("Password : %s\n",currUser1.pass);
      currUserID=currUser1.user_id;
      result=IndividualUserLogin(currUser1);
      write(sockfd,&result,sizeof(result));
    }
    else if(c==2){
      JointUser currUser2;
      accType=2;
      msgLength=read(sockfd,&currUser2,sizeof(JointUser));
      printf("Username : %d\n",currUser2.user_id);
      printf("Password : %s\n",currUser2.pass);
      currUserID=currUser2.user_id;
      result=JointUserLogin(currUser2);
      write(sockfd,&result,sizeof(result));
    }
    else if(c==3){
      Admin currUser3;
      accType=3;
      msgLength=read(sockfd,&currUser3,sizeof(Admin));
      printf("Username : %d\n",currUser3.user_id);
      printf("Password : %s\n",currUser3.pass);
      currUserID=currUser3.user_id;
      result=AdminLogin(currUser3);
      write(sockfd,&result,sizeof(result));
    }
    else{
      result= 0 ;
      write(sockfd,&result,sizeof(result));
    }
    if(result)  
      break;    
  }
  
  while(1){
    read(sockfd,&c1,sizeof(int));
    if(c==1 || c==2){
      if(c1==1){
        long long int dep;
        read(sockfd,&dep,sizeof(long long int));
        if(accType==1){
          result = deposit(currUserID,dep);
          write(sockfd,&result,sizeof(result));  
        }
        else if(accType==2){
          result = deposit_1(currUserID,dep);
          write(sockfd,&result,sizeof(result));
        }
      }
      else if(c1==2){
        long long int dep;
        read(sockfd,&dep,sizeof(long long int));
        if(accType==1){
          result=withdraw(currUserID,dep);
          write(sockfd,&result,sizeof(result));
        }
        else if(accType==2){
          result=withdraw_1(currUserID,dep);
          write(sockfd,&result,sizeof(result));
        }
      }
      
      else if(c1==3){
        long long int bal;
        if(accType == 1){
          bal=getBalance(currUserID);
          write(sockfd,&bal,sizeof(long long int));  
        }
        else if(accType==2){
         bal=getBalance_1(currUserID);
        write(sockfd,&bal,sizeof(long long int)); 
        } 
      }
      else if(c1==4){
        char pass[30];
        read(sockfd,pass,sizeof(pass));
        if(accType ==1){
          result=changePassword(currUserID,pass);
          write(sockfd,&result,sizeof(result));  
        }
        if(accType ==2){
          result=changePassword_1(currUserID,pass);
          write(sockfd,&result,sizeof(result));  
        }
        
      }
      
      else if(c1==5){
        if(c==1){
          IndividualUser user1=getIndividualUser(currUserID);
          write(sockfd,&user1,sizeof(IndividualUser));
        }
        else if(c==2){
          JointUser user2=getJointUser(currUserID);
          write(sockfd,&user2,sizeof(JointUser));
        }
      }
      else if(c1==6)  
        break;
    }
    else if(c==3){
      read(sockfd,&type,sizeof(int));
      if(c1==1){
        if(type==1){
          IndividualUser newUser1;
          read(sockfd,&newUser1,sizeof(IndividualUser));
          result=CreateIndividualUser(newUser1);
          write(sockfd,&result,sizeof(result));
        }
        else if(type==2){
          JointUser newUser2;
          read(sockfd,&newUser2,sizeof(JointUser));
          result=CreateJointUser(newUser2);
          write(sockfd,&result,sizeof(result));
        }
        else if(type==3){
          Admin newUser3;
          read(sockfd,&newUser3,sizeof(Admin));
          result=CreateAdmin(newUser3);
          write(sockfd,&result,sizeof(result));
        }
      }
      else if(c1==2){
        if(type==1){
          int delUserID1;
          read(sockfd,&delUserID1,sizeof(int));
          result=deleteIndividualUser(delUserID1);
          write(sockfd,&result,sizeof(result));
        }
        else if(type==2){
          int delUserID2;
          read(sockfd,&delUserID2,sizeof(int));
          result=deleteJointUser(delUserID2);
          write(sockfd,&result,sizeof(result));
        }
      }
      else if(c1==3){
        if(type==1){
          IndividualUser u1;
          int user_id1;
          read(sockfd,&user_id1,sizeof(int));
          u1=getIndividualUser(user_id1);
          write(sockfd,&u1,sizeof(IndividualUser));
        }
        else if(type==2){
          JointUser u2;
          int user_id2;
          read(sockfd,&user_id2,sizeof(int));
          u2=getJointUser(user_id2);
          write(sockfd,&u2,sizeof(JointUser));
        }
      }
      else if(c1==4) 
       break;
    }
  }
  close(sockfd);
  write(1,"Ended client session.....\n",sizeof("Ended client session.....\n"));
  return;
}

int main(){

int sockfd;
struct sockaddr_in servaddr;

int newsocket;
struct sockaddr_in newaddr;

//socket creation and verification
sockfd = socket(AF_INET, SOCK_STREAM, 0);
if(sockfd ==-1){
  printf("Socket creation failed...\n");
  exit(0);
}
else
  printf("Socket successfully created...\n");
bzero(&servaddr, sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
servaddr.sin_port = htons(PORT);

//Binding
if ((bind(sockfd, (SA*)&servaddr,sizeof(servaddr))) != 0){
  printf("Socket bind failed...\n");
  exit(0);
}
else
  printf("Socket successfully binded...\n");

// Listening to the client at max 5
if(listen(sockfd,5)!=0){
printf("Listen failed...\n");
exit(0);
}
else
  printf("Server listening...\n");
int len = sizeof(newaddr);
write(1,"Waiting for the client.....\n",sizeof("Waiting for the client.....\n"));


while(1){
    len=sizeof(newaddr);
    newsocket=accept(sockfd,(SA*)&newaddr,&len);
    write(1,"Connected to the client.....\n",sizeof("Connected to the client.....\n"));
    if(!fork()){
      close(sockfd);  
      Options(newsocket);
      exit(0);
    }
    else{
      close(newsocket); 
    }   
  }
return 0;
}
