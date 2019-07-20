
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct events
{
    char cid[20];
    char name[20];
    int ts;
    struct events *next;
}events;

typedef struct uevents
{
    char ename[20];
    struct uevents *next;
}uniqueevents;

events *header=NULL;
events *ptr,*temp;
uniqueevents *header1=NULL;
int noue;
void substring(char s[], char sub[], int p, int l) {
   int c = 0;

   while (c < l) {
      sub[c] = s[p+c-1];
      c++;
   }
   sub[c] = '\0';
}
void insert(char caseid[],char ename[],int time )
{
	/*int data_value;

	printf("\nEnter data of the node: ");
	scanf("%d", &data_value);
	*/
	temp = (struct events *) malloc(sizeof(struct events));

	//Traverse to the end of the linked list.
	if(header==NULL)
        {header=temp;
        strcpy(temp->cid,caseid);
	    strcpy(temp->name,ename);
	    temp->ts= time;
	    temp->next=NULL;
        }

    else
    {

	ptr = header;
	while(ptr->next != NULL)
	{
		ptr = ptr->next;
	}

	strcpy(temp->cid,caseid);
	strcpy(temp->name,ename);
	temp->ts= time;
	temp->next = NULL;
	ptr->next = temp;
    }
}
int dateconv(char *time)
{
    int date1=0;
	int i=0,len;
        while(time[i]!='\0')
	{
	 date1=(date1*10)+(time[i]-48);
	 i++;
	}
    return date1;
}
void store()
{
  FILE *f1;
  char filename[50];
  int c;
  printf("Input filename");
  scanf("%s",filename);

      FILE *fstream = fopen(filename,"r");
      struct events *t1;
    t1 =(struct events *)malloc(sizeof(struct events));
    int i=0,ts,l=1;
    char data[100],caseid[20],cname[20];
    int time;
    for(i=0;i<=68;i++)
    {
        fscanf(fstream, "%s",data );
        char *token;
       /* get the first token */
       token = strtok(data,",");
       while( token != NULL )
       {

          if(l==1)
          {

          char *cid=token;
          strcpy(caseid,cid);
              //printf("\n %s",caseid);
          }else if(l==2)
           {
             char *tim=token;
              //printf("\t%s",tim);
              time=dateconv(tim);

          }else
          {


              char *cn=token;
          strcpy(cname,cn);
              //printf("\t %s",cn);
          }

          token = strtok(NULL,",");
          l++;
          l=l%3+1;
       }



     insert(caseid,cname,time);

     //uniqueEevent();
     //countMat(ue,noue);
}
  //printf("%s",header->name);
}
void main()
{
    store();
    struct events *t1;
    t1 =(struct events *)malloc(sizeof(struct events));
    int i=0,ts,l=1;
    char data[100];
    FILE *fstream = fopen("file.csv","r");
    for(i;i<=68;i++)
    {
        fscanf(fstream, "%s",data );
        char *token;
        char trs[20];
       /* get the first token */
       token = strtok(data,",");
       while( token != NULL )
       {
          strcpy(trs,token);
          if(l==1)
          {
           // printf("\n %s",trs);
          }
          else if(l==2)
           {
               // printf("\t %d",atoi(trs));
          }
          else
          {
             // printf("\t %s",trs);
              checkl(trs);
          }

          token = strtok(NULL,",");
          l++;
          l=l%3+1;
       }
    }

    printf("Unique Events");
    //printf(" %d",header->ts);
     print();
     calculate();
}
void checkl(char str[])
{
    if(header1==NULL)
    {
        header1=(uniqueevents*)malloc(sizeof(uniqueevents));
        strcpy(header1->ename,str);
        header1->next=NULL;
    }
    else
    {
        uniqueevents *ptr1;
        ptr1=header1;
        int l=0;
        while(ptr1->next!=NULL)
        {
            if(strcmp(ptr1->ename,str)==0)
                return 0;
            ptr1=ptr1->next;
        }
        uniqueevents *ptr2;
        ptr2=(uniqueevents*)malloc(sizeof(uniqueevents));
        strcpy(ptr2->ename,str);
        ptr2->next=NULL;
        ptr1->next=ptr2;
    }
}
void print()
{
        uniqueevents *ptr1;
        ptr1=header1;
        while(ptr1->next->next!=NULL)
        {

            printf("\n %s",ptr1->ename);
            ptr1=ptr1->next;
        }
}
char* ue[10];
void calculate()
{

    uniqueevents *temp1= header1;
    int i,c=0,j;
    while(temp1!=NULL)
	{
	c++;
	temp1=temp1->next;
	}
	temp1=header1;
	//char* ue[10];
	for(i=0;i<c;i++)
	{
	    ue[i]=malloc(sizeof(temp1->ename));
	    strcpy(ue[i],temp1->ename);
        temp1=temp1->next;
	}
    noue=c;
    startevent(c);
}
void startevent(int c)
{
    int i,min[c];
    //printf("%s",ue[0]);
    for(i=0;i<c;i++)
        min[i]=100;
    //printf("%d",min[0]);
    for(i=0;i<c;i++)
    {
        temp=header;
       // printf("iiit");
        while(temp!=NULL)
        {
          //  printf("iiit");
         // printf(" %s %s\n",ue[i],temp->name);
            if(strcmp(temp->name,ue[i])==0)
            {
                //printf("iiit");
                if(min[i]>temp->ts)
                {
                    min[i]=temp->ts;
                    //printf("iiit");
                }
            }
            temp=temp->next;
        }
    }
    temp=header->next;
    int minv=100;
  for(i=0;i<c;i++)
  {
     if(minv>min[i])
        minv=min[i];
  }
  printf("\n\nStarting events\n");
  for(i=0;i<c;i++)
  {
     if(minv==min[i])
        printf("%s\n",ue[i]);
  }
  endevent(c);
}

void endevent(int c)
{
    int i,max[c];
    temp=header;
    for(i=0;i<c;i++)
        max[i]=0;
    for(i=0;i<c;i++)
    {
        temp=header;
        while(temp!=NULL)
        {
            if(strcmp(temp->name,ue[i])==0)
            {
                if(max[i]<temp->ts)
                {
                    max[i]=temp->ts;
                }
            }
            temp=temp->next;
        }
    }
    int maxv=0;
  for(i=0;i<c;i++)
  {
     if(maxv<max[i])
        maxv=max[i];
  }
  printf("\nEnding events\n");
  for(i=0;i<c-2;i++)
  {
     if(maxv==max[i])
        printf("%s\n",ue[i]);
  }
  countMat(c);
}

int succeed(char pe[],char se[])
{
    int c=0;
   temp=header;
   while(temp->next!=NULL)
   {
       ptr=temp->next;
       if(strcmp(temp->name,pe)==0 && strcmp(ptr->name,se)==0)
          {
              if(strcmp(temp->cid,ptr->cid)==0)
               c++;
          }
          temp=temp->next;
   }
   //printf("\n%d",c);
    return c;

}
void countMat(int n)
{
events *temp;
temp=header;
int i,j,fpc[n-2][n-2],p;


for(i=0;i<n-2;i++)
{
for(j=0;j<n-2;j++)
{
if(i==j)
{
    fpc[i][j]=-1;
    continue;
}
else
p=succeed(ue[i],ue[j]);
fpc[i][j]=p;
//priintf("%d",p);
}

//LMmatrix(fpc);
}
//check(fpc);
printf("\n");
for(i=0;i<n-2;i++)
{
for(j=0;j<n-2;j++)
{
printf("%d \t",fpc[i][j]);
}
printf("\n\n");
}
printf("\nfootprint matrix\n\n");
for(i=0;i<n-2;i++)
{
for(j=0;j<n-2;j++)
{
    if(fpc[i][j]==-1)
        printf("#\t");
    else if(fpc[i][j]==0 && fpc[j][i]==0)
        printf("#\t");
    else if(fpc[i][j]!=0 && fpc[j][i]==0)
        printf("->\t");
    else if(fpc[i][j]==0 && fpc[j][i]!=0)
        printf("<-\t");
    else
        printf("||\t");
}
printf("\n\n");
}
}
