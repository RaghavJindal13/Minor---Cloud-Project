#include<stdio.h>
//Raman is a pro in GITHUB

#include<string.h>

void main()

{

char name[25],pwd[25],ver[25];

int i,a,digi=0,up=0,low=0,schar=0;

printf("Enter your Name: ");

fgets(name);

printf("Hello %s, Enter your password:\n",name);

fgets(pwd);

a=strlen(pwd);

if(a<5)

{

printf("Error: Password should contain contain minimum 5 characters ");

}

else if(a>12)

{

printf("Error: Password shouldn't exceed 12 characters ");

}

else

{

for(i=0;pwd[i]!=NULL;i++)

{

if(pwd[i]>='A' && pwd[i]<='Z')

up++;

if(pwd[i]>='a' && pwd[i]<='z')

low++;

if(pwd[i]>='0' && pwd[i]<='9')

digi++;

if(pwd[i]=='@'||pwd[i]=='#'||pwd[i]=='$')

schar++;

}

}

if(up==0)

printf("There must be at least one Uppercase\n");

if(low==0)

printf("There must be at least one Lowercase\n");

if(digi==0)

printf("There must be at least one Digit\n");

if(schar==0)

printf("There must be at least one Special Character\n");

else

{

printf("Confirm your Password\n");

fgets(ver);

if(strcmp(pwd,ver)==0)

printf("Welcome %s, your is Password Verified",name);

else

printf("Password did not match");

}

fgets();

}
