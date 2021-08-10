
# include <stdio.h>
//# include <conio.h>
# include <string.h>
# include <ctype.h>
#include<stdlib.h>

struct node
{
        int st;
        struct node *link;
};

struct dfa
{
	char str[100];
	int found;
	int used;
	int first_index_found;
	int state_no;
	int final;
}closure_unique[50];

typedef struct dfa dfa;

void findclosure(int,int);
void insert_trantbl(int ,char, int);
int findalpha(char);
void get_e_closure(int);

static int set[50],nostate,noalpha,s,notransition,c,r,buffer[50];
char alphabet[20];
static int e_closure[50][50]={0};
struct node * transition[50][50]={NULL};
int ret[200];
static int pos=0;
static int sc=0;
char new[100];

int no_dfa=0;
int final_no_of_dfa_states=0;

int dfa_start_state=1;
int state=1;
int final1=0;
int g=1;
char string[10];
int nfa_end_state;
char dfa_final_states[20];
int dfa_final_count=0;
int dfa_transition_table[50][4];
char a[70][5][50];
char dfa_states[50][4][50];
//nfa_end_state=sc;

struct str_e_closure{
	char str_e_closer[100];
	int final;
}e_close[50];
//char str_e_closer_unique[25][20];
typedef struct str_e_closure str_e_closure;

//char dfa[25];
int buffer_transition[50];
int buffer_transition1[50];

void alphabet_initialize()
{
	alphabet[0]='a';
        alphabet[1]='b';
        alphabet[2]='*';
        alphabet[3]='+';
        alphabet[4]='e';
          /* for(i=0;i<noalpha;i++)
        {
                alphabet[i]=getchar();
                getchar();
        }*/
}

void print_closure()
{
	int i,j;
	printf("\n");
    printf("e-closure of states\n");
       for(i=1;i<=nostate;i++)
        {
                c=0;
               for(j=0;j<50;j++)
                {
                        buffer[j]=0;
                        e_closure[i][j]=0;
                }
                findclosure(i,i);
                printf("\ne-closure(q%d): ",i);
                get_e_closure(i);
        }
}

void epsilon_closures(int notransition,int nostate)
{
	int i,j;
	for(i=0,j=0;i<notransition,j<pos;i++,j=j+3)
        {
                //scanf("%d %c%d",&r,&c,&s);
        		r=ret[j];
        		if(ret[j+1]==238)
        		{
        			c='e';
        		}
        		else
        		{
        		c=(char)ret[j+1];
        		}
        		s=ret[j+2];
        		//printf("r:%d c:%c s:%d\n",r,c,s);
                insert_trantbl(r,c,s);
        }

        print_closure();

}


void insertionSort(int arr[], int n) 
{ 
    int i, key, j; 
    for (i = 1; i < n; i++) { 
        key = arr[i]; 
        j = i - 1; 
  
     

        while (j >= 0 && arr[j] > key) { 
            arr[j + 1] = arr[j]; 
            j = j - 1; 
        } 
        arr[j + 1] = key; 
    } 
} 

void print_nfa_transition(char a[70][5][50])
{
	for(int i=1;i<=sc;i++)
	{
		for(int j=0;j<5;j++)
		{
			if(strcmp(a[i][j],"\0")==0)
			{
				strcpy(a[i][j],"0");
			}
			//strcpy(a[i][j],"\0");
			printf(" %s(%d,%c) ",a[i][j],i,alphabet[j]);
		}
		printf("\n");
	}
}
void sort_strings(dfa a[50],int start)
{
	dfa temp,last;
	strcpy(last.str,a[no_dfa].str);
	last.final=a[no_dfa].final;
    last.found=a[no_dfa].found;
    last.used=a[no_dfa].used;
    last.first_index_found=a[no_dfa].first_index_found;
    last.state_no=a[no_dfa].state_no;
	int i,j;
	//printf("start: ",start);
	//printf("before sorted:");
	/*for(int i=1;i<no_dfa;i++)
	{
		printf("%s\n",a[i].str);
	}*/
	int n=no_dfa;
	while(n>=start+2)
	{
		 strcpy(a[n].str,a[n-1].str);
            a[n].final=a[n-1].final;
            a[n].found=a[n-1].found;
            a[n].used=a[n-1].used;
            a[n].first_index_found=a[n-1].first_index_found;
            a[n].state_no=a[n-1].state_no;
            n--;
	}
	 strcpy(a[start+1].str,last.str);
     a[start+1].final=last.final;
     a[start+1].found=last.found;
     a[start+1].used=last.used;
     a[start+1].first_index_found=last.first_index_found;
     a[start+1].state_no=last.state_no;

	/*printf("sorted:");
	for(int i=1;i<no_dfa;i++)
	{
		printf("%s\n",a[i].str);
	}*/
}


void findclosure(int x,int sta)
{
        struct node *temp;
        int i;
        if(buffer[x])
                return;
		e_closure[sta][c++]=x;
        buffer[x]=1;
        if(alphabet[noalpha-1]=='e' && transition[x][noalpha-1]!=NULL)
        {
                temp=transition[x][noalpha-1];
                while(temp!=NULL)
                {
                        findclosure(temp->st,sta);
                        temp=temp->link;
                }
        }
}

void insert_trantbl(int r,char c,int s)
{
        int j;
        struct node *temp;
       // printf("%d %c %d",r,c,s);
       	j=	findalpha(c);
      //  printf("blah");
        if(j==999)
        {
                printf("error\n");
                exit(0);
        }
 		temp=(struct node *)malloc(sizeof(struct node));
        temp->st=s;
        temp->link=transition[r][j];
       //printf("%d",temp->st);
        transition[r][j]=temp;
      // printf("%d",transition[r][j]->st);
}

int findalpha(char c)
{
        int i=0;
       // printf("%d",i);
        for(i=0;i<noalpha;i++)
        	if(alphabet[i]==c)
        	{	//	printf("%d ",i);
                return i;
            }
        return(999);
}
void get_e_closure(int i)
{
        int j;
        printf("{");
        strcpy(e_close[i].str_e_closer,"\0");
       // strcpy(str_e_closer_unique[no_dfa],"\0");
        j=0;
        while(e_closure[i][j]!=0)
        {
        	j++;
        }
       insertionSort(e_closure[i],j);
        for(j=0;e_closure[i][j]!=0;j++)
        {	char s1[5];
        	if(e_closure[i][j]==nfa_end_state)
        	{
        		e_close[i].final=1;
        	}
        	sprintf(s1, "%d",e_closure[i][j]);
        	strcat(e_close[i].str_e_closer,s1);
        	strcat(e_close[i].str_e_closer,",");
			printf("q%d,",e_closure[i][j]);

    	}
    	//strcat(str_e_closer[i],"}");
    	if(i==1)
        	{	no_dfa++;strcpy(closure_unique[1].str,e_close[i].str_e_closer);
        		/*printf("\nunique1%s\n",str_e_closer_unique[1]);
       	
        		printf("no of dfa states",no_dfa);*/
        		closure_unique[1].found=1;
        		closure_unique[1].used=0;
        		closure_unique[1].first_index_found=1;
        		closure_unique[1].final=e_close[1].final;
        	}
        	else{
        	int k=1;
        	int present=0;
        	
        	while(k!=i)
        	{
        		if(strcmp(e_close[k].str_e_closer,e_close[i].str_e_closer)==0)
        		{	present=1;
        			break;
        		}
        		k++;

        	}
        	if(present==0)
        	{
        		 no_dfa++;
        		 strcpy(closure_unique[no_dfa].str,e_close[i].str_e_closer);
        		 closure_unique[no_dfa].final=e_close[i].final;
        		 closure_unique[no_dfa].found=0;
        		 closure_unique[no_dfa].used=0;
        		 //printf("%dstate:",i);
        		closure_unique[no_dfa].first_index_found= i;
        	}
       		}
    	printf("} ");
    	//printf("%d",j);
    	//printf("%s ",e_close[i].str_e_closer);
    	//printf(" final or not :%d ",e_close[i].final);
    	//printf("%s",str_e_closer_unique[i]);
    	//printf("out of function");
}

void initialize_tables()
{

	for(int i=0;i<=sc;i++)
	{
		for(int j=0;j<4;j++)
		{
			//char s[5];
			//sprintf(s, "%d", "\0");
			//strcat(s,"|");
			strcpy(a[i][j],"\0");
			strcpy(dfa_states[i][j],"\0");
		//	printf("%s ",a[i][j]);
		}
		//printf("\n");
	}

	//printf("put of initialization loop/...");
	//printf("\n\n");
	//	int s='b'-97;
	//	printf("%d",s);
	//	printf()
	char s[15],s1[5];
	strcpy(s,"\0");
	for(int i=0;i<pos;i=i+3)
	{	//printf("loop called\n");	
		//char s[5],s1[5];
		strcpy(s,"\0");
		strcpy(s1,"\0");
		//strcpy(s,"\0");
		//printf("initialization done");
		//strcpy(s,",");
		sprintf(s1, "%d", ret[i+2]);
		//printf("%s",s);
		strcat(s,s1);
		strcat(s,",");
		//printf("%s",s);
		//printf("%s\n",s);
		//printf("%s\n",a[ret[i]-''])
		//printf("%d\n",i);
		if(ret[i+1]!=238 && (ret[i+1]==42 || ret[i+1]==43) )
		
		{
		strcat(a[ret[i]][ret[i+1]-40],s);
		}

		else if(ret[i+1]!=238 )
		
		{
		strcat(a[ret[i]][ret[i+1]-97],s);
		}

	}

	//printf("out of adding values to a /...");

	/*for(int i=0;i<=sc;i++)
	{
		for(int j=0;j<2;j++)
		{
			//strcpy(a[i][j],"\0");
			//printf("ans:%s ",a[i][j]);
			strcat(a[i][j],"}");
		}
		printf("\n");
	}*/

	for(int i=0;i<=sc;i++)
	{
		strcpy(a[i][4],e_close[i].str_e_closer);
	}

}

void convert_to_dfa()
{
	int i=1,j;
	int d=1;
	//for(int i=1;i<=no_dfa;i++)

	if(closure_unique[1].final==1)
	{
		//printf("first state is final \n");
		dfa_final_states[dfa_final_count]=1;
		dfa_final_count++;
	}
	//printf("no_dfa%d",no_dfa);
	//printf("str: %s %d ",closure_unique[1].str,closure_unique[1].final);

	while(i<=no_dfa)
	{	//printf("%d:%d %d\n",i,closure_unique[i].found,closure_unique[i].used);
		if(closure_unique[i].found==1 && closure_unique[i].used==0)//if2
		{	final_no_of_dfa_states++;
			closure_unique[i].state_no=final_no_of_dfa_states;
			closure_unique[i].used=1;
		for(j=0;e_closure[closure_unique[i].first_index_found][j]!=0 ;j++)
		{
			for(int x=0;x<=3;x++)
			{
			if(strcmp(a[e_closure[closure_unique[i].first_index_found][j]][x],"0")!=0)//if1
			{
				//printf("%s   \n",a[e_closure[closure_unique[i].first_index_found][j]][0]);
			//strcat(dfa_states[i][0],a[e_closure[i][j]][0]);
			int k=0;
			while(a[e_closure[closure_unique[i].first_index_found][j]][x][k]!='\0')
			{
				if(a[e_closure[closure_unique[i].first_index_found][j]][x][k]!=',')//if 3
				{	//new starts here
					//char mul[5],mul1[2];   change
					//strcpy(mul,"\0");  change
					//strcat(mul,a[e_closure[closure_unique[i].first_index_found][j]][x][k]);
					//check till it is ,
					/*while(a[e_closure[closure_unique[i].first_index_found][j]][x][k]!=',')
					{
						strcpy(mul1,"\0");
						//strcat(mul,a[e_closure[closure_unique[i].first_index_found][j]][x][k]);
						sprintf(mul1, "%c", a[e_closure[closure_unique[i].first_index_found][j]][x][k]);
						strcat(mul,mul1);
						//printf("mul:%s\n",mul);
						k++;
					}*/// change from while start to here
					//k--;// now it is back at comma
					//changeint state;
					//int state=a[e_closure[closure_unique[i].first_index_found][j]][x][k]-'0';
					//changesscanf(mul, "%d", &state); 
				//	printf("state%d\n", state); 
					//int state=mul-'0'; //new ends here
					//int state=a[e_closure[closure_unique[i].first_index_found][j]][x][k]-'0'; // old statement
					//printf("new state %d  ",state);
					//new
					int state;
					if(a[e_closure[closure_unique[i].first_index_found][j]][x][k+1]!=',')
					{
						int tens=a[e_closure[closure_unique[i].first_index_found][j]][x][k]-'0';
						int ones=a[e_closure[closure_unique[i].first_index_found][j]][x][k+1]-'0';
						state=(10*tens)+ones;
						k++;
					}
					else{state=a[e_closure[closure_unique[i].first_index_found][j]][x][k]-'0';}//new ends
					strcat(dfa_states[final_no_of_dfa_states][x],e_close[state].str_e_closer);
					//printf("dfa state :%s ",dfa_states[final_no_of_dfa_states][x],e_close[state].str_e_closer);

					// store it to an array , do insertion sort , remove repetitions, check with str_e_closer, if not present add a new state e[][] , copy elements to this , add corresponding str_e_closer and closure_unique, no_dfa++;
					
					//int buffer_transition[20];
					/*for(i=0;i<20;i++)
					{
						buffer_transition[i]=0;
					}*/
					int z=0,y=0,final_state_check=0;
					for( y=0;y<50;y++)
					{
						buffer_transition[y]=0;
						buffer_transition1[y]=0;
					}
					y=0;
					//printf("Y:%d ",y);
					while(dfa_states[final_no_of_dfa_states][x][z]!='\0')
					{
						if(dfa_states[final_no_of_dfa_states][x][z]!=',')
						{
							if(dfa_states[final_no_of_dfa_states][x][z+1]!=',')
							{
								int tens=dfa_states[final_no_of_dfa_states][x][z]-'0';
								int ones=dfa_states[final_no_of_dfa_states][x][z+1]-'0';
								buffer_transition[y]=(10*tens)+ones;
								z++;
								y++;
								//printf("buffer_transition 2 digit : %d ", buffer_transition[y]);
							}
						//printf("%c ",dfa_states[final_no_of_dfa_states][x][z]);
							else
							//if(dfa_states[final_no_of_dfa_states][x][z+1]==',')
							{
								buffer_transition[y]=dfa_states[final_no_of_dfa_states][x][z]-'0';
								//printf("buffer_transition 1 digit: %d  ", buffer_transition[y]);
								y++;
								//printf("buffer_transition 1 digit: ", buffer_transition[y]);
							}
							
						//printf("buffer_transition: ", buffer_transition[y]);
						//z++;
						}
						z++;
					}
					//printf("Y: %d",y);
					insertionSort(buffer_transition,y);
					/*for(int q=0;q<y;q++)
					{
						printf("%d ",buffer_transition[q]);
					}*/
					int b=1;
					int ctr=1;
					buffer_transition1[0]=buffer_transition[0];
					while(b<y)
					{
						if(buffer_transition[b]!=buffer_transition[b-1])
						{
							buffer_transition1[ctr]=buffer_transition[b];
							ctr++;
						}
						b++;
					}
					char new_str[30];
					strcpy(new_str,"\0");
					y=ctr;
					for(int e=0;e<y;e++)
					{
						char store[5];
						strcpy(store,"\0");
						sprintf(store, "%d",buffer_transition1[e]);
						if(buffer_transition1[e]==nfa_end_state)
						{
							final_state_check=1;
						}
						strcat(new_str,store);
						strcat(new_str,",");
						//printf(" ans%d ",buffer_transition[e]);
					}
					int flag=0;
					//printf(" \nnew str:%s",new_str);
					for(int g=1;g<=sc;g++)
					{
						if(strcmp(e_close[g].str_e_closer,new_str)==0)
						{	//printf("\nalready present");
							flag=1;
							break;
						}

					//if not present add to e_closure and  e_close[g].str_e_closer
					}

					if(flag==0)
					{	sc++;
						for(int h=0;h<y;h++)
						{
							e_closure[sc][h]=buffer_transition1[h];
						}
						e_closure[sc][y]=0;
						strcpy(e_close[sc].str_e_closer,new_str);
						e_close[sc].final=final_state_check;
						//sort_strings(e_close);
						no_dfa++;
						strcpy(closure_unique[no_dfa].str,e_close[sc].str_e_closer);
        		 		closure_unique[no_dfa].final=e_close[sc].final;
        		 		closure_unique[no_dfa].found=1;
        		 		closure_unique[no_dfa].used=0;
        		 //printf("%dstate:",i);
        				closure_unique[no_dfa].first_index_found= sc;
        				strcpy(dfa_states[final_no_of_dfa_states][x],closure_unique[no_dfa].str);
        			//	printf("what is the value of i %d",i);
        				sort_strings(closure_unique,i);
					}
					//e_closure[no_dfa][y]=0;
					//strcpy(e_close[no_dfa].str_e_closer,new_str);
					/*printf("str_e_closre");
					for(int u=1;u<=no_dfa;u++)
					{
						printf("%s\n",e_close[u].str_e_closer);
					}
					for(int u=0;u<=y;u++)
					{
						printf("%d ",e_closure[no_dfa][u] );

					}*/ // remove later
					/*while(dfa_states[final_no_of_dfa_states][x][z]!='\0')
					{	//printf("reading characters  ");
					/*char mul2[5],mul3[2];
						strcpy(mul2,"\0");
						while(dfa_states[final_no_of_dfa_states][x][z]!=',')
						{
							strcpy(mul3,"\0");
						//strcat(mul,a[e_closure[closure_unique[i].first_index_found][j]][x][k]);
						sprintf(mul3, "%c",dfa_states[final_no_of_dfa_states][x][z]);
						strcat(mul2,mul3);
						//printf("mul:%s\n",mul);
						z++;

						}
						sscanf(mul2,"%d",buffer_transition[y]);
						y++;*/
						/*if(dfa_states[final_no_of_dfa_states][x][z]!=',')
							{ buffer_transition[y]=dfa_states[final_no_of_dfa_states][x][z]-'0';
								y++;
							}
						z++;

					}*/
					//insertionSort(buffer_transition,y);
					/*printf("buffer_transition:\n");
					for(i=0;i<y;i++)
					{
						printf(" ans%d ",buffer_transition[i]);
					}*/

					
					//printf("\ndfa %d ",final_no_of_dfa_states);
					//printf("dfa state :%s ",dfa_states[final_no_of_dfa_states][x],e_close[state].str_e_closer);
					int l=2;
					while(l<=no_dfa)
					{
						if(strcmp(dfa_states[final_no_of_dfa_states][x],closure_unique[l].str)==0)
						{
							//printf("new state added :%s %s %d\n",closure_unique[l].str,dfa_states[final_no_of_dfa_states][0],i);
							closure_unique[l].found=1;
						
						}
						l++;
					}
				}//if 3 gets over
				//while gets over
				k++;
			}//while gets over
			}//if1 over
			//strcat(dfa_states[i][0],a[e_closure[]])
			
			}//for x gets over
		}//for j gets over


			/*if(strcmp(a[e_closure[i][j]][1],"0")!=0)
			{
			//strcat(dfa_states[i][1],a[e_closure[i][j]][1]);
			int k=0;
			while(a[e_closure[i][j]][1][k]!='\0')
			{
				if(a[e_closure[i][j]][1][k]!=',')
				{
					int state=a[e_closure[i][j]][1][k]-'0';
					//printf("%d  ",state);

					strcat(dfa_states[i][1],str_e_closer[state]);
				}
				k++;
			}

			}*/

		/*	if(strcmp(a[e_closure[closure_unique[i].first_index_found][j]][1],"0")!=0)
			{
			//strcat(dfa_states[i][0],a[e_closure[i][j]][0]);
				//printf("%s",a[e_closure[closure_unique[i].first_index_found][j]][1]);
			int k=0;
			while(a[e_closure[closure_unique[i].first_index_found][j]][1][k]!='\0')
			{
				if(a[e_closure[closure_unique[i].first_index_found][j]][1][k]!=',')
				{
					int state=a[e_closure[closure_unique[i].first_index_found][j]][1][k]-'0';
					strcat(dfa_states[final_no_of_dfa_states][1],e_close[state].str_e_closer);
					int l=2;
					while(l<=no_dfa)
					{
						if(strcmp(dfa_states[final_no_of_dfa_states][1],closure_unique[l].str)==0)
						{
							//printf("new state added :%s %s\n",closure_unique[l].str,dfa_states[final_no_of_dfa_states][1]);
							closure_unique[l].found=1;
							
						}
						l++;
					}

				}
				k++;
			}
			//strcat(dfa_states[i][0],a[e_closure[]])
			
			}*/
		
	  }//if2 gets over

	  else if(closure_unique[i].used==1)
	  	continue;
	  else

	  {
	  	closure_unique[i].state_no=0;
	  }

	  i++;
	 // d=i;
	}
}


/*void print_unique_closure()
{
	for(int i=1;i<=no_dfa;i++)
{
	if(closure_unique[i].state_no!=0)
	{printf("\nuniquestr:%s found:%d first_index%d  state%d used%d final%d:",closure_unique[i].str,closure_unique[i].found,closure_unique[i].first_index_found,closure_unique[i].state_no,closure_unique[i].used,closure_unique[i].final);
	printf("\n");
}
}*/


void print_dfa_transition()
{
	for(int i=0;i<=final_no_of_dfa_states;i++)
	{
		for(int j=0;j<4;j++)
		{

			int l=1;
			//strcpy(a[i][j],"\0");
		  // printf(" %s(%d,%c) ",dfa_states[i][j],i,alphabet[j]);
			if(strcmp(dfa_states[i][j],"\0")==0)
			{
				strcpy(dfa_states[i][j],"0");

			}
			/*while(l<=no_dfa)
			{
				if(strcmp(closure_unique[l].str,dfa_states[i][j])==0)
				{
					char s[2];
					strcpy(s,"\0");
					sprintf(s,"%d",closure_unique[l].state_no);
					strcpy(dfa_states[i][j],s);
					break;
				}
				l++;
			}*/ //change for while loop

			//new added
			else{
			while(l<=no_dfa)
			{	
				if(strcmp(closure_unique[l].str,dfa_states[i][j])==0)
				{
					char s[2];
					strcpy(s,"\0");
					sprintf(s,"%d",closure_unique[l].state_no);
					//printf(" state check %d ",closure_unique[l].state_no);
					//printf("final state check %d ",closure_unique[l].final);
					if(closure_unique[l].final==1)
					{
						dfa_final_states[dfa_final_count]=closure_unique[l].state_no;
						//printf("%d ",dfa_final_states[dfa_final_count]);
						dfa_final_count++;
						//printf("%d ",dfa_final_count);
						//dfa_final_states[dfa_final_count]
						//dfa_final_count++;
					}
					strcpy(dfa_states[i][j],s);
					break;
				}
				l++;
			}
			}//new added ends
//new added starts
			int stat;
			sscanf(dfa_states[i][j],"%d",&stat);
			dfa_transition_table[i][j]=stat;
			printf(" %d(%d,%c) ",dfa_transition_table[i][j],i,alphabet[j]);
			//new added ends
	//	dfa_transition_table[i][j]=dfa_states[i][j]-'0';
		//	printf(" %s(%d,%c) ",dfa_states[i][j],i,alphabet[j]); //change
		}
		printf("\n");
	}

	/*for(int i=0;i<dfa_final_count;i++)
	{
	printf("%d ",dfa_final_states[i]);
	}*/
	int try=0;
	for(int i=0;i<=no_dfa;i++)
	{
		if(closure_unique[i].state_no!=0 && closure_unique[i].final==1)
		{
			dfa_final_states[try]=closure_unique[i].state_no;
						//printf("%d ",dfa_final_states[dfa_final_count]);
			try++;
		}
	}

	for(int i=0;i<try;i++)
	{
	printf("%d ",dfa_final_states[i]);
	}
	dfa_final_count=try;
}

char* concatenate(char *s)
{
	//char new[100];
	//printf("%s",new);
	//printf("%s",s);
	int i =0,j=0,min=0,max=0;
	while(s[i]!='\0')
	{	//printf("%s\n",new);
		//printf("%s\n",s);
		if((isalpha(s[i])&&s[i+1]!='{') ||(s[i]=='+'&&s[i+1]!='{') ||(s[i]=='*'&&s[i+1]!='{') || (s[i]=='?'&&s[i+1]!='{'))
		{
			if(isalpha(s[i+1]) || s[i+1]=='(' || s[i+1]=='\\'|| s[i+1]=='.')
			{
				new[j]=s[i];
				j++;
				new[j]=' ';
				j++;
			}
			else if(s[i-1]=='\\' && s[i+1]==')')
			{
				new[j]=s[i];
				j++;
				new[j]=' ';
				j++;

			}
			else
			{
				new[j]=s[i];
				j++;
			}
		}
		else if(s[i]==')')
		{
			if(isalpha(s[i]) || s[i+1]=='(' || s[i+1]=='\\' || s[i+1]=='.')
			{
				new[j]=s[i];
				j++;
				new[j]=' ';
				j++;
			}

			else
			{
				new[j]=s[i];
				j++;
			}
		}
		
		else if((isalpha(s[i]) && s[i+1]=='{' ) ||( s[i-1]=='\\' && s[i+1]=='{' ))
		{	
			if(s[i-1]=='\\')
			{
				j--;
			}
			
			if(s[i+2]==',')		// {,a}
			{
				min=0;
				max=s[i+3]-'0';
			}
			else if(s[i+4]=='}')		//{a,}
			{
					min=s[i+2]-'0';
					max=0;
			}
			else if(s[i+3]=='}')		//{a}
			{
				min=(s[i+2])-'0';	
				max=(s[i+2])-'0';	
			}
			else		//{a,b}
			{
				min=s[i+2]-'0';
				max=s[i+4]-'0';
			}
							//if min=0 E , otherwise from min to max range : aa|aaa|... like that if max is 0, min number of time|eg aaa*
			new[j]='(';
			j++;
			printf("%d %d",min,max);
			/*if(min==0)
			{
				new[j]=238;j++;new[j]='|';j++;

			}*/
		/*	if(min<max)
			{		int temp;
				while(max-min>=0)
				{		new[j]='(';
						j++;
						temp=max;
						while(temp>0)
						{
							if(s[i-1]=='\\')
							{
									new[j]='\\';
									j++;
							}
							new[j]=s[i];
							j++;
							new[j]=' ';
							j++;
							temp--;
						}
						j--;
						new[j]=')';
						j++;
						new[j]='|';
						j++;
						
						max--;

				}

				j--;
				if(min==0)
				{
					new[j-1]=238;new[j]=')';j++;
				}
				new[j]=')';
				j++;
				new[j]=' ';
				j++;
			}*/ //changed  if min<max
			//new added beginning
			if(min<max)
			{	int temp;
				int min1=min;
				while(min1-1>0)
				{
					new[j]=s[i];
					j++;
					new[j]=' ';
					j++;
					min1--;
				}
				new[j]='(';
				j++;
				int max1=max;
				while(max-min>=0)
				{		new[j]='(';
						j++;
						temp=max-min+1;
						
						while(temp>0)
						{
							if(s[i-1]=='\\')
							{
									new[j]='\\';
									j++;
							}
							new[j]=s[i];
							j++;
							new[j]=' ';
							j++;
							temp--;
						}
						j--;
						new[j]=')';
						j++;
						new[j]='|';
						j++;
					
						max--;

				}
				j--;
				new[j]=')';
				j++;
				new[j]=')';
				j++;
				new[j]=' ';
				j++;
			}//new added end
			else if(min>max)
			{
				while(min>0)
				{	if(s[i-1]=='\\')
							{
									new[j]='\\';
									j++;
							}
					new[j]=s[i];
					j++;
					new[j]=' ';
					j++;
					min--;
				}
				if(s[i-1]=='\\')
							{
									new[j]='\\';
									j++;
							}
				new[j]=s[i];j++;
				new[j]='*';j++;
				new[j]=')';j++;
				new[j]=' ';
				j++;
			}
			else
			{
				while(min>0)
				{
						new[j]=s[i];
					j++;
					new[j]=' ';
					j++;
					min--;	
				}
				j--;
				new[j]=')';j++;new[j]=' ';
				j++;
			}
			while(s[i]!='}')
				i++;


		}
		
		else if(s[i]=='}'|| s[i]=='.')
		{
				new[j]=s[i];
				j++;
				new[j]=' ';
				j++;
			
		}
		else
		{
			new[j]=s[i];
			j++;	
		}
	

		i++;
	}
	new[j]=s[i];
	//printf("%s",new);
	return new;
	
}

void nfa(int st,int spr,int p,char *s)
{    int i,sp,fs[10],fsc=0;
	sp=spr;pos=p;sc=st;
	char cp; //charprev
	while(*s!='\0')
	{if(isalpha(*s))
	    {
	    	ret[pos++]=sp;
		ret[pos++]=*s;
		ret[pos++]=++sc;
		cp=*s;
	} 
	if(*s =='\\')
	{	
		s++;
		ret[pos++]=sp;
		ret[pos++]=*s;
		ret[pos++]=++sc;
		cp=*s;
		s++;

	}
	if(*s==' ')
		{
		 sp=sc;
		 ret[pos++]=sc;
		 ret[pos++]=238;
		 ret[pos++]=++sc;
		 sp=sc;
		}

	if(*s=='|')
		{
			sp=st;
		 	fs[fsc++]=sc;
		 }
	if(*s=='.')
	{		sp=sc;
		ret[pos++]=sc;
		ret[pos++]=97;
		ret[pos++]=sc+1;
		ret[pos++]=sc;
		ret[pos++]=98;
		ret[pos++]=sc+1;
		ret[pos++]=sc;
		ret[pos++]=42;
		ret[pos++]=sc+1;
		ret[pos++]=sc;
		ret[pos++]=43;
		ret[pos++]=sc+1;
		sc++;
	}
	if(*s=='*')
		{ret[pos++]=sc;
		 ret[pos++]=238;
		 ret[pos++]=sp;
		 ret[pos++]=sp;
		 ret[pos++]=238;
		 ret[pos++]=sc;
		 }

	 if(*s=='+')	//same as aa*
		{/*sp=sc; 
		ret[pos++]=sc;
		ret[pos++]=cp;
		ret[pos++]=++sc;
		ret[pos++]=sc;
		 ret[pos++]=238;
		 ret[pos++]=sp;
		 ret[pos++]=sp;
		 ret[pos++]=238;
		 ret[pos++]=sc;*/
		 ret[pos++]=sc;
		 ret[pos++]=238;
		 ret[pos++]=sp;
		}
	////

	 if(*s=='?')
	 {
	 	ret[pos++]=sp;
		ret[pos++]=238;
		ret[pos++]=sc; 
	 }
	 if (*s=='(')
		{	if(*(s-1)!='|')
			{	char ps[50];
		 		int i=0,flag=1;
		 		s++;
		   		while(flag!=0)
				{	ps[i++]=*s;
			 		if (*s=='(')
						flag++;
			 		if (*s==')')
						flag--;
			 		s++;
			 	}
			 	ps[--i]='\0';
			 	nfa(sc,sp,pos,ps);
			 	s--;
			}
			else
			{
				char ps[50];
		 		int i=0,flag=1;
		 		s++;
		   		while(flag!=0)
				{	ps[i++]=*s;
			 		if (*s=='(')
						flag++;
			 		if (*s==')')
						flag--;
			 		s++;
			 	}
			 	ps[--i]='\0';
			 	nfa(sc,st,pos,ps);
			 	s--;
			}
		}
	 s++;
	}
	sc++;
	  for(i=0;i<fsc;i++)
		 {ret[pos++]=fs[i];
		  ret[pos++]=238;
		  ret[pos++]=sc;
		 }
		  ret[pos++]=sc-1;
		  ret[pos++]=238;
		  ret[pos++]=sc;
}
int check(char x,int intial)
{
	int col;
	if(x=='*' || x=='+')
	{
		col=((int)x-40);
	}
	else
	{	col = ((int)x-97); }
	int row = intial;
	state = dfa_transition_table[row][col];
	return state;
}


int main()
{    int i;
	char inp[100];
	char *new;
	//clrscr();
	printf("enter the regular expression :");
	scanf("%s",inp);
	char *new1=concatenate(inp);
	//char *new1="(a \\* )*";
	printf("\nWith all concatenation : %s\n",new1);
	nfa(1,1,0,new1);
	printf("\nstate    input    state\n");
	for(i=0;i<pos;i=i+3)
		 printf("%d     --%c-->      %d\n",ret[i],ret[i+1],ret[i+2]);
	printf("\n");
	int j,k,m,t,n;
    struct node *temp;
      /*  printf("Enter the number of alphabets?\n");
 scanf("%d",&noalpha);*/
      noalpha=5;
      getchar();
        int sc1=sc;
        alphabet_initialize();
        
       // scanf("%d",&nostate);
        nostate=ret[i-1];
      //  printf("No of states%d\n",nostate);

       /* printf("\nEnter no of transition?\n");
        scanf("%d",&notransition);*/
        notransition=i/3;
        nfa_end_state=sc;
       // printf("No of ret%d\n",ret[i]);
        //printf("No of trans%d\n",notransition);
        epsilon_closures(notransition,nostate);
        initialize_tables();

//	printf("allocatinga/...");
	//int*** A = (int***)malloc(M * sizeof(int**));
//	char a[50][5][20];
//	printf("allocated a/...");
	//int a1[25][3][40]; //94 is for epsilon
//	printf("%d",sc);
//	char dfa_states[20][4][40];
//	printf("allocatined dfa/...");

	printf("\t\tNFA TRANSITION TABLE \n\n");
	print_nfa_transition(a);
	printf("\n\n");
// converting to dfa
	//int transition_state_present =1;
	//printf("%d",no_dfa);
	convert_to_dfa();
	printf("\t\tDFA TRANSITION TABLE \n\n");
	print_dfa_transition();
	printf("\n\nEnter Input String.. ");
    scanf("%s",string);	
    int abb=0;
    while(string[abb]!='\0')
    {
        g=check(string[abb],g);
        printf("%d\n",g);
        abb++;
        
	}
	for(int i=0;i<dfa_final_count;i++)
	{
		if(dfa_final_states[i]==g)
		{
			final1=1;
		}
	}
	if(final1==1)
    printf("\n valid string");
    if(final1==0)
    printf("\n invalid string");
//print_unique_closure();
	
	return 0;
}
