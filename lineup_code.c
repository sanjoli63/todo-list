#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>     //inserting system dates automatically
#include<process.h>
#include<conio.h>
#include <malloc.h>
#include<dir.h>      //acessing directory where program is running
#include<ctype.h>
#include <dirent.h>
#include <pthread.h>     //multi threading for 2 functions execution at same time
#include <unistd.h>
#include <windows.h>
#include <dos.h>
#define SIZE 25
#define MAX_LEN 128
int page_login();       //global declaration for function and variables
void alarm(void);
char uname[10], pwd[10];
FILE *fp1;
char initial_filename[20];
char filename[20];
char filenameqq[20];
void print_image(FILE *fptr);

struct user{          //User structure defined for authentication data
    char username[10];
    char password[10];
}*first;

void SetColor(int ForgC);
typedef struct ToDo todo;
time_t now;


struct ToDo{
 char data[100],am[10],b,c;
 todo *link;
 int count;
 //location, time and date
 char loc[20];
 int dd,mm,yy;
 int hr,min,ss;
}read_file[50];
todo *start=NULL;


int main()
{
        //alarm
        pthread_t thread;
    int err;

    err = pthread_create(&thread, NULL, alarm, NULL);

        //alarm
        //animation
        FILE *a [ 3 ] ;
    int i ;
    char c;
        a[0]=fopen("welcome.txt","r+");
        a[1]=fopen("to.txt","r+");
        a[2]=fopen("lineup_logo.txt","r+");

    for ( i = 0 ; i < 3 ; i++ )
       {
          // system("COLOR 8E");
           while( c != EOF)
            {
                SetColor(10);
                c = fgetc(a[i]); /* read from file*/
                printf("%c",c);  /*  display on screen*/
            }
           sleep(600);
           c="*";
         //  system("COLOR 8E");
       }
       fclose(*a);
       printf("\n\n");

       system("pause");
        //animation

    int accepted_login;
    int choice;

   accepted_login= page_login();
    while(1){

        system("color 8");
        system("cls");
        SetColor(10);
        printf("\n1.See Your ToDo List-Perticular Day");
        printf("\n2.Create Your ToDos\n");
        printf("\n3.Delete Your ToDos");
        printf("\n4.Update Your ToDos\n");
        printf("\n5.See All Your tasks-All Days");
        SetColor(4);
        printf("\n6.Exit");
        SetColor(3);
        printf("\n\nEnter your choice..");
        scanf("%d",&choice);
        switch(choice){
      case 1:
          seeToDo();
        break;
      case 2:
          createToDo();
        break;
      case 3:
          delToDo();
        break;
      case 4:
           createToDo();
        // updateToDo();
         break;
      case 5:
        seeAllToDo();
         break;
      case 6:
          printf("Press enter again for exit\n");
          MessageBox(0,"ARE YOU SURE TO EXIT?","Error!",0);
          MessageBox(0,"ALL YOUR DATA ARE SUCCESSFULLY SAVED!","CONGRATS",0);
        exit(0);
        }
    }
}

int page_login()
{
    FILE *fp;
    int i;
    char c;
    int flag=0;
    system("color FC");
    first=(struct user *)malloc(sizeof(struct user));

    while(flag==0){
    system("cls");
    SetColor(0);
    printf("1. Login Through An Existing Account\n2. Create New account\n");
    scanf("%d",& i);
    //system("cls");
    SetColor(1);
    switch(i)
    {
        case 1:
            {
                if ( ( fp=fopen("login.dat", "r+")) == NULL)
                {
                    printf ("Could not open file\n");
                    return -1;
                }

            printf("Username: ");
            scanf("%9s",uname);
            printf("Password: ");
            //password hide-start
            int p=0;
    do{
        pwd[p]=getch();
        if(pwd[p]!='\r'){
            printf("*");
        }
        p++;
    }while(pwd[p-1]!='\r');
    pwd[p-1]='\0';
            //password hide-end
            printf("\n");
            while ( fread (first, sizeof(struct user), 1, fp) == 1)
            {
                if( strcmp ( first->username, uname) == 0)
                {
                    //printf ("Found the username\n");
                    if( strcmp ( first->password, pwd) == 0)
                    {

                        flag=1;
                        //now open the account of the user
                    }
                }

            }

            if(flag==0){

                MessageBox(0,"Login Denied!\nEnter Again","Error!",1);

            }
            else{
                 MessageBox(0,"SUCCESSFULLY, LOGGED IN","Hey Geek!",1);
            }

            break;
            }

        case 2:
            {
            do
            {
                if ( ( fp=fopen("login.dat", "a+")) == NULL)
                    {
                        printf ("Could not open file\n");
                        return -1;
                    }
                printf("Choose A Username: ");
                scanf("%9s",first->username);
                printf("Choose A Password: ");
                //password hide
                int p=0;
    do{
       first->password[p]=getch();
        if(first->password[p]!='\r'){
            printf("*");
        }
        p++;
    }while(first->password[p-1]!='\r');
    first->password[p-1]='\0';
                //hide password

                fwrite (first, sizeof(struct user), 1, fp);
                printf("\nAdd another account? (Y/N): ");
                scanf(" %c",&c);
        //create a folder-start
                char *dirname;
                dirname=malloc(SIZE*sizeof(char));
                strcpy(dirname,first->username);
                mkdir(dirname);
        //create a folder-end
            }while(c=='Y'||c=='y');
            break;
            }
             system("pause");

    }

    fclose(fp);
    }
     return flag;
}


void createToDo(){
    char k='y';
    todo *t,*temp;
    time(&now);
   struct tm *local = localtime(&now);

    system("cls");
    system("color 8A");
    SetColor(14);
    while(1){

        if(k=='n'){
            break;
        }
       else{
        if(1){
        t=(todo *)calloc(1,sizeof(todo));
        start=t;
        printf("\nADD it..\n");
        fflush(stdin);
        printf("Provide a desired date (press n to add today's date or y to input manually): ");
        scanf("%c",&t->b);
        if(t->b!='n')
        {
        fflush(stdin);
        printf("Choose a date first e.g. 21/07/2003:\n");
        scanf("%d/%d/%d",&t->dd,&t->mm,&t->yy);
        }
        else
        {
              t->dd=local->tm_mday;
              t->mm=local->tm_mon+1;
              t->yy=local->tm_year+1900;
        }
//date file created-start

        strcpy(initial_filename,uname);
        strcat(initial_filename,"\\");

        sprintf(filename,"%s%d%d%d.dat",initial_filename,t->dd,t->mm,t->yy);
        fp1=fopen(filename, "a+b");

//date file created-end
        printf("\nAdd up your task\n");
        fflush(stdin);
        gets(t->data);
        printf("\nAdd up your Location:\n");
        fflush(stdin);
        gets(t->loc);
        printf("\nWanna add specified time?y/n: \n");
        fflush(stdin);
        scanf("%c",&t->c);
        if (t->c!='n')
    {
        fflush(stdin);
        printf("Enter Time[21:21:21 am]- ");
            scanf("%d:%d:%d %s",&t->hr,&t->min,&t->ss,&t->am);

    }
        else{
        t->hr=0;
        t->min=0;
        t->ss=0;
        strcpy(t->am,"NA");
    }
    t->count=1;
        //writing data into file-start
        start->link=NULL;

        fwrite (t, sizeof(struct ToDo),1, fp1);
        fclose(fp1);
        //writing data into file-end

        }
       else{
        start=NULL;
       temp=(todo*)calloc(1,sizeof(todo));
       printf("\nADD it..\n");
       fflush(stdin);
       printf("Provide a desired date (press n to add today's date or y to input manually): ");
        scanf("%c",&temp->b);
        if(temp->b!='n')
        {
            fflush(stdin);
         printf("Choose a date first e.g. 21/07/2020:\n");
        scanf("%d/%d/%d",&temp->dd,&temp->mm,&temp->yy);

        }
         else
        {
              temp->dd=local->tm_mday;
              temp->mm=local->tm_mon+1;
              temp->yy=local->tm_year+1900;
        }
//date file created-start

        strcpy(initial_filename,uname);
        strcat(initial_filename,"\\");
        sprintf(filename,"%s%d%d%d.dat",initial_filename,temp->dd,temp->mm,temp->yy);
        fp1=fopen(filename, "a+b");

//date file created-end

        printf("Add up your task\n");
       fflush(stdin);
       gets(temp->data);
        printf("\nAdd up your Location:\n");
        fflush(stdin);
        gets(temp->loc);
        printf("\nWanna add specified time?y/n: \n");
        fflush(stdin);
        scanf("%c",&temp->c);
        if (temp->c!='n')
    {
        fflush(stdin);
        printf("Enter Time[1:1:1 am]- ");
            scanf("%d:%d:%d %s",&temp->hr,&temp->min,&temp->ss,&temp->am);

    }
       else{
        temp->hr=00;
        temp->min=00;
        temp->ss=00;
        strcpy(temp->am,"NA");
        }

        temp->link=NULL;
        t->link=temp;
        t=t->link;

        //writing data into file-start
        fwrite (temp, sizeof(struct ToDo),1, fp1);
        fclose(fp1);
        //writing data into file-end
     }
     fixcount();
     printf("\nWant to add?y/n");
        fflush(stdin);
        scanf("%c",&k);
    }

   }

}

void delToDo(){
  system("cls");
  int d,deleted=0;
  int i=0,n=0,dd1,mm1,yy1;
  todo *temp1,*temp,m;
  time(&now);
   char s;
   struct tm *local = localtime(&now);
   temp=start;

  printf("\nEnter the no of the todo you want to remove\n");
  scanf("%d",&d);
    d=d-1;
  printf("Provide a desired date (press n to add today's date or y to input manually): ");
         fflush(stdin);
        scanf("%c",&s);
        if(s!='n')
        {
        fflush(stdin);
        printf("Choose a date first e.g. 21/07/2003:\n");
        scanf("%d/%d/%d",&dd1,&mm1,&yy1);
        }
        else
        {
              dd1=local->tm_mday;
              mm1=local->tm_mon+1;
              yy1=local->tm_year+1900;
        }

        strcpy(initial_filename,uname);
        strcat(initial_filename,"\\");
        sprintf(filename,"%s%d%d%d.dat",initial_filename,dd1,mm1,yy1);

        fp1=fopen(filename, "r+b");
        fseek( fp1, d*sizeof(m), SEEK_SET );
        m.dd=32;
        fwrite(&m, sizeof(struct ToDo),1, fp1);
        fclose(fp1);

        fp1=fopen(filename, "rb");
        fread(read_file, sizeof(struct ToDo),20, fp1);



        MessageBox(0,"TASK SUCCESSFULLY DELETED.","Congrats",0);

       printf("\n\n\n");
            fclose(fp1);
       system("pause");


   }

void fixcount(){
  todo *temp;
  int i=1;
  temp=start;
  while(temp!=NULL){
    temp->count=i;
    i++;
    temp=temp->link;
  }

}

void updateToDo(){
  system("cls");
  system("color 8A");
    SetColor(14);
  todo *temp,*t;
  char k;
  while(1){
        printf("\nWant to add?y/n");
        fflush(stdin);
        scanf("%c",&k);
        if(k=='n')
            break;
       printf("\nADD it..\n");
       temp=(todo *)calloc(1,sizeof(todo));
          fflush(stdin);
        printf("you want to add date y/n:");
        scanf("%c",&temp->b);
        if(temp->b!='n')
        {
             fflush(stdin);
        printf("Choose a date first e.g. 21/07/2003\n");
        scanf("%d/%d/%d",&temp->dd,&temp->mm,&temp->yy);

        }

        printf("Add up your task\n");
       fflush(stdin);
       gets(temp->data);
        printf("\nAdd up your Location\n");
        fflush(stdin);
        gets(temp->loc);
         printf("\nWanna add specified time?y/n \n");
        fflush(stdin);
        scanf("%c",&temp->c);
        if (temp->c!='n')
    {
        fflush(stdin);
        printf("Enter Time[1:1:1 am]- ");
            scanf("%d:%d:%d %s",&temp->hr,&temp->min,&temp->ss,&temp->am);

    }

       temp->link=NULL;
       t=start;
      while(t->link!=NULL){
        t=t->link;
      }
      t->link=temp;
      fixcount();
}
printf("\n\n");
system("pause");
}
void seeToDo(){
   system("cls");
   system("color 6E");
   todo *temp;
   time(&now);
   int i=0,n=0,dd1,mm1,yy1;
   char s;
   struct tm *local = localtime(&now);
   temp=start;
         SetColor(0);
         printf("Provide a desired date (press n to add today's date or y to input manually): ");
         fflush(stdin);
        scanf("%c",&s);
        if(s!='n')
        {
        fflush(stdin);
        printf("Choose a date first e.g. 21/07/2003:\n");
        scanf("%d/%d/%d",&dd1,&mm1,&yy1);
        }
        else
        {
              dd1=local->tm_mday;
              mm1=local->tm_mon+1;
              yy1=local->tm_year+1900;
        }

        strcpy(initial_filename,uname);
        strcat(initial_filename,"\\");
        printf("%s",initial_filename);
        sprintf(filename,"%s%d%d%d.dat",initial_filename,dd1,mm1,yy1);
        fp1=fopen(filename, "rb");
        fread(read_file, sizeof(struct ToDo),20, fp1);
         system("cls");
        printf("\tDate\t\tTime\t\t Occassion\tLocation\n");

        printf("\nReading this file ------>>%s\n\n",filename);
        while(i<40){
                    if(dd1==read_file[i].dd && mm1==read_file[i].mm && yy1==read_file[i].yy ){
          printf("%d\t%d/%d/%d\t%d:%d:%d %s\t%s\t\t%s\n",i+1,read_file[i].dd, read_file[i].mm, read_file[i].yy,read_file[i].hr,read_file[i].min,read_file[i].ss,read_file[i].am,read_file[i].data,read_file[i].loc);

          printf("--------------------------------------------------------------------------------\n");

          }
          i++;
       }
       printf("\n\n\n");

       system("pause");
   }
void seeAllToDo(){
   system("cls");
   system("color 6E");
    struct dirent *de;  // Pointer for directory entry

   int i=0,n=2,dd1,mm1,yy1,aske;
   char s;
   struct tm *local = localtime(&now);

    strcpy(initial_filename,uname);

  DIR *dr = opendir(initial_filename);
  SetColor(0);

    if (dr == NULL)  // opendir returns NULL if couldn't open directory
    {
        printf("Could not open current directory" );
        return 0;
    }


    printf("\n\tDate\t\tTime\t\tOccassion\tLocation\n");

    while ((de = readdir(dr)) != NULL)
            {
         strcpy(initial_filename,uname);
        strcat(initial_filename,"\\");

        sprintf(filename,"%s%s",initial_filename,de->d_name);
        fp1=fopen(filename, "rb");
        fread(read_file, sizeof(struct ToDo),20, fp1);
            if(n<=0){
        printf("\nReading this file -------->> %s\n\n",filename);

            }
        while(i<40 && n<=0){

                if((read_file[i].dd+48)==de->d_name[0] || ((read_file[i].dd)/10+48)==de->d_name[0] ){
          printf("%d\t%d/%d/%d\t%d:%d:%d %s\t%s\t\t%s\n",i+1,read_file[i].dd, read_file[i].mm, read_file[i].yy,read_file[i].hr,read_file[i].min,read_file[i].ss,read_file[i].am,read_file[i].data,read_file[i].loc);

          printf("--------------------------------------------------------------------------------\n");

            read_file[i].dd=5;
                }
          i++;

       }
       printf("\n");
       n--;
       i=0;
        fclose(fp1);

            }
          closedir(dr);
       system("pause");
   }
   void print_image(FILE *fptr)
{
    system("cls");

    char read_string[MAX_LEN];
    while(fgets(read_string,sizeof(read_string),fptr) != NULL)
    {SetColor(10);
        printf("%s",read_string);}
      SetColor(3);
    printf("\n\n\n                                                                                  WELCOME TO LINE UP....\n\n\n");
    system("pause");
    fclose(fptr);

    system("cls");
    system("COLOR 3F");

}
void SetColor(int ForgC)
{
     WORD wColor;
     //This handle is needed to get the current background attribute

     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     //csbi is used for wAttributes word

     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          //To mask out all but the background attribute, and to add the color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}
void alarm(void)                        //Alarm function
{
   for(int i=0;i<2;i++){
 Beep(2050, 200);
 Beep(5050, 200);
 Beep(3050, 200);
 Beep(4050, 200);
    }
}
void sleep(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}
