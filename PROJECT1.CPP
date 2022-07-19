//Hare Krishna

#include<iostream.h>
#include<conio.h>
#include<string.h>
#include<stdio.h>
#include<fstream.h>
#include<iomanip.h>
#include<process.h>
#include<stdlib.h>

int tnoc,tnocl,tnos, tnot=0;//tot no of classes ,subjects and teachers
int cnin[100][10];
int tin[100][5];

void del(int n)
{for(int z=1;z<=n;z++)
  cout<<"\b \b";
}

class indextable
{public:
  int range, nopdtot[10][5], nopwtot[10];//range, no of periods in a day, week
  int imaxd, imaxw;
  int itt[5][9];
  indextable();
  indextable(int a, int b, int c);
  void genta();

};

indextable::indextable()
{range=imaxd=imaxw=0;
 for(int i=0;i<10;i++)
  for(int j=0;j<5;j++)
   nopdtot[i][j]=0;
 for(i=0;i<5;i++)
  for(j=0;j<9;j++)
   itt[i][j]=-1;
 for(i=0;i<10;i++)
  nopwtot[i]=0;
}

indextable::indextable(int a, int b, int c)
{range=a;
 imaxd=b;
 imaxw=c;
 for(int i=0;i<10;i++)
  for(int j=0;j<5;j++)
   nopdtot[i][j]=0;
 for(i=0;i<5;i++)
  for(j=0;j<9;j++)
   itt[i][j]=-1;
 for(i=0;i<10;i++)
  nopwtot[i]=0;
}

void indextable::genta()
{randomize();
int n=1+random(range-1);int success=0;
 for(int i=0;i<5;i++)
 {
  for(int j=0;j<9;j++)
   {success=0;
    while(success==0)
     {if(nopdtot[i][n]<2&&nopwtot[n]<9)
       {itt[i][j]=n;
	nopdtot[i][n]++;
	nopwtot[n]++;
	success=1;
       }
      else
       {if(n==range)
	 n=1;
	else
	 n++;
       }
     }
    }
  }
}
indextable indt(5,2,9);


class subject
{private:
  int scode;            //subject code
  int st[10];           //teachers code
  int nopd,nopw;	//no of periods per day, per week
 public:
  char sname[10];       //subject name
  int snoc;             //no of classes having this subject
  int not;     	        //no of teachers required for this subject
  int noct;		//no of classes per teacher of this subject
  subject();
  void input();         //input subject details
  int getcode()         //get subject code details
  {return scode;
  }
  void opname()         //display name of subject
  {cout<<setw(5)<<sname;
  }
  void calnoct(int wl)   //calculate no. of classes a teacher of this subject can handle
  {noct=wl/nopw;
  }
  void calnot()
  {not=snoc/noct;
   if(snoc%noct!=0)
    not++;
  }
}s[50];


subject::subject()
{strcpy(sname," ");
 scode=-1;
 for(int i=0;i<10;i++)
  st[i]=-1;
 not=0;
 nopd=0;
 nopw=0;
 snoc=0;
}
void subject::input()
{cout<<"Subject name: ";
 gets(sname);
 cout<<"Subject code: ";
 cin>>scode;
/* cout<<"Max no. of periods of this subject per day: ";
 cin>>nopd;
 cout<<"Max no. of periods of this subject per week: ";
 cin>>nopw;
 */
 nopd=2;
 nopw=9;
}

class teacher
{protected:
  char tname[10];            //teacher name
  int tid,ts,tc[10],wl;   //id, sub, classes, work load
 public:
  int tino[5];
  int tcno;               //no. of classes
  int ttt[5][9];	 // teacher time table
  teacher();
  void subi(int sc)     //assign subject code and t id to teacher
  {ts=sc;
   tid=tnot+1;
   }
  int getts()          //get subject code of subject teacher is teaching
  {return ts;
  }
  void ctc(int n)
  {tc[tcno]=n;
  }
  int gettid()
  {return tid;
  }
}t[100],tl[100];

teacher::teacher()
{strcpy(tname," ");
 tid=ts=tcno=wl=0;
 for(int i=0;i<5;i++)
  for(int j=0;j<9;j++)
   ttt[i][j]=-1;
 for(i=0;i<10;i++)
  tc[i]=0;
}

class lab:public teacher
{public:
 lab();
 int subc;                     //subject code
 int labno;                    //lab no.
 int lno;                      //no. of periods for this lab
 char subname[10];
 int cls[10];
 int clno;
 void input(int n);
}la[50];

lab::lab()
{teacher();
 subc=0;
 labno=0;
 clno=0;
 strcpy(subname," ");
}

void lab::input(int n)
{int check=0;
 labno=n;
 do
 {cout<<"Enter subject name: ";
  gets(subname);
  for(int i=0;i<tnos;i++)
   if(strcmpi(subname,s[i].sname)==0)
   {subc=i+1;
    strcpy(subname,s[i].sname);
    strcpy(subname," lab");
    cout<<subname;
    check++;
   }
  cout<<"Enter no. of periods for this subject: ";
  cin>>lno;
  }while(check==0);
}

class expe:public teacher
{public:
 expe();
 int epno;                     //extra period no.
 int eno;                      //no. of ep
 char epname[10];
 void input(int n);
}ep;

expe::expe()
{epno=0;
 eno=0;
}



class classes
{protected:
  int classno;          //class number as assigned by the program not the actual class name
  int nos;             //no. of subjects
  int csub[10];         //subject code
  int ct[10];           //teacher code
 public:
  int ctt[5][9];       //time table(subjects)
  int cl[5];           //lab no. of lab
  int cln;             //no. of lab periods for this class
  classes();
  void details(int n);  //input class details
  void delab();         //details of lab periods
  void ast();           //assign teachers to class
  void wrcnin();        //write teachers on cnin
  void astt();          //assign time table
  void aslab();         //assign lab periods to class
  void asep();          //assign extra periods like PT, yoga
}c[100];

classes::classes()
{nos=0;
 cln=0;
 for (int i=0;i<10;i++)
  {csub[i]=-1;
   ct[i]=-1;
  }
 for(i=0;i<5;i++)
  for(int j=0;j<9;j++)
   ctt[i][j]=-1;
}
void classes::details(int n)
{int check=0,j=0;
 classno=n;
 cout<<"\nNo. of subjects for this class(excluding lab): ";
 cin>>nos;
 cout<<"Enter subject codes:\n";
 for(int i=0;i<nos;i++)
  {cout<<i+1<<". ";
   do
   {cin>>csub[i];
    for(j=0;j<tnos;j++)
     if(s[j].getcode()==csub[i])
      {cout<<" ";
       s[j].opname();
       check=1;
       s[j].snoc++;
       break;
      }
    if(check==0)
     {cout<<"The subject code you entered is wrong please enter it again";
      getch();
      del(61);
     }
    }while(check!=1);
   cout<<"\n";
  }
}

void classes::ast()
{int l,i,j;
 for(i=0;i<nos;i++)
  for(j=0;j<tnot;j++)
   if(csub[i]==t[j].getts())        //check for teachers available for that sub
    if(t[j].tcno<3)                 //check if teacher can handle***********<3-3 to be changed
     {ct[i]=t[j].gettid();
      t[j].ctc(classno);
      t[j].tcno++;
      break;
      }
}

void classes::wrcnin()
{int i=classno-1;
 for(int j=0;j<nos;j++)
  cnin[i][j]=ct[j];
}

void classes::astt()
{int idx,tidd;
 for(int i=0;i<5;i++)
  for(int j=0;j<9;j++)
   {idx=indt.itt[i][j];
    tidd=cnin[classno-1][idx-1];
    ctt[i][j]=tidd;
    t[tidd-1].ttt[i][j]=classno;
   }
}

void classes::delab()
{int i,j,k;
 char ch;
 cout<<"Does class"<<classno<<" have labs?(y/n)";
 cin>>ch;
 if(ch=='y')
 {cout<<"Enter no. of labs: ";
  cin>>cln;
  cout<<"Enter subject codes for lab subjects(same as the subject): ";
  for(i=0;i<cln;i++)
   {cin>>cl[i];
    for(j=0;j<tnocl;j++)
     if(cl[i]==la[j].subc)
      {la[j].cls[la[j].clno]=classno-1;
       la[j].clno++;
      }
    }
 }
}

void classes::aslab()
{int i,j,k,l,m,n,count=0;
 int tem[5];
 for(i=0;i<5;i++)
  tem[i]=cnin[classno-1][i];
 for(i=0;i<5;i++)
  {k=tem[i];
   m=0;
   count=0;
   l=t[tem[i]-1].getts();
   for(j=0;j<tnocl;j++)
    if(la[j].subc==l)
     {m=j+1;
      break;
     }
   if(m==0)
    continue;
   m--;
   n=la[m].lno;
   for(j=0;j<9;j++)
    if(c[classno-1].ctt[i][j]==k)
     if(la[m].ttt[i][j]==-1&&j!=8&&j!=9)
      {if(count==n)
	break;
       else
       {
	c[classno-1].ctt[i][j]=(c[classno-1].ctt[i][j]*-1)-1000;
	la[m].ttt[i][j]=classno;
	t[k-1].ttt[i][j]=(t[k-1].ttt[i][j]*-1)-1000;
	count++;
       }
      }
  }
}

void classes::asep()
{int i,j,k,l,n,m,sc,count=0;
 cout<<"Enter no. of extra periods for class"<<classno<<": ";
 cin>>n;
 if(n!=0)
 {cout<<"Enter subject having less no. of periods: ";
  cin>>sc;
 for(i=0;i<tnot;i++)
  if(t[i].getts()==sc)
   m=i;
  m++;
 for(i=0;i<5;i++)
  {for(j=0;j<9;j++)
   {if(count==n)
     break;
    if(ctt[i][j]==m)
     {ctt[i][j]=1000;
      t[m-1].ttt[i][j]=-1;
      count++;
     }
    }
   if(count==n)
    break;
  }}
}

void modify()
{cout<<"Enter no. of subjects per class: ";
 int nos,temp,z,l,k,m,n,i,j,a,f,pq,ab,tea,pos,check=0,tim;
 int count=0;
 int tem[5],temi[5];
 for(l=0;l<5;l++)
  {tem[l]=-1;
   temi[l]=-1;
  }
 cin>>nos;
 for(l=0;l<tnoc;l++)
 {count=0;
  tim=0;
  for(a=0;a<5;a++)
   tem[a]=-1;
  for(k=0;k<nos;k++)
   {tea=cnin[l][k];
    tea--;
    tim=0;
    for(m=l%4;m<=5;m++)
     {tim++;
      if(m==5)
       if(count!=5)
	m=0;
      if(tim>30&&count!=5)
       {ab=0;
	for(i=0;i<5;i++)
	 temi[i]=-1;
	int c=0;
	for(i=0;i<5;i++)
	 {ab=0;
	  for(j=0;j<5;j++)
	   if(tin[tea][j]==i)
	    ab++;
	  if(ab==0)
	   temi[i]=i;
	  }
	 if(tem[m]==-1)
	  {for(i=0;i<5;i++)
	   {if(temi[i]!=-1)       //temi-->array of free indices of teacher unassigned
	     {if(tem[i]!=-1)
	       {ab=tem[i];
		pq=0;
		int z=-1;
		for(int y=0;y<5;y++)
		 {if(tin[ab-1][y]==m)
		   pq++;
		  if(tin[ab-1][y]==-1)
		   z=i;
		  }
		if(pq!=0)
		 continue;
		if(pq==0)
		 {tem[m]=ab;
		  tem[i]=tea+1;
		  tin[ab-1][z]=m;
		  for(int xy=0;xy<5;xy++)
		   {if(tin[ab-1][xy]==i)
		     tin[ab-1][xy]=-1;
		    if(tin[tea][xy]==-1)
		     tin[tea][xy]=i;
		   }
		  c++;
		  count++;
	       } }
	   } }
	  if(c==1)
	   break;
	  }

       }
      if(tim>50)
      {cout<<"Breaking";
       break;
      }
      check=0;
      if(tem[m]==-1)            //check if position is free for the class
      {for(n=0;n<5;n++)
	if(tin[tea][n]==m)
	 {check=10;
	  break;
	  }
       if(check==10)
	continue;
       if(check==0)
	for(i=0;i<5;i++)
	 {if(tin[tea][i]==-1)
	  {tem[m]=tea+1;
	   tin[tea][i]=m;
	   count++;
	   check=20;
	   break;
	  }
	 }
	if(check==20)
	 break;
      }
     }

    }

  for(f=0;f<5;f++)
   cnin[l][f]=tem[f];
 }
}

void assumptions()
{cout<<"Assumptions and limitations in this program :\n";
 cout<<"1.Classes having different number of subjects and subject-period combination must have different set of teachers.\n";
 cout<<"2.For a particular subject, number of periods per week must be same for all classes.\n";
 cout<<"3.Number of subjects per class must be greater than the number of classes a single teacher can handle.\n";
 cout<<"4.One teacher can handle only one subject.\n";
 cout<<"5.There is only one lab available per subject.\n";
 getch();
}





void gent()
{clrscr();
 int i,j,k,l,wl,o,p,q,w;
 char ch;
 for(i=0;i<100;i++)
  for(j=0;j<5;j++)
   tin[i][j]=-1;
 assumptions();
 clrscr();
 cout<<"Do you want to enter the data or read from file?(e/f)";
 cin>>ch;
 if(ch=='e')
 {cout<<"Enter data:\n";
  cout<<"Enter total no. of subjects: ";
  cin>>tnos;
  for(l=0;l<tnos;l++)                    //input subject details
  {cout<<l+1<<" ";
   s[l].input();
   cout<<"\n";
  }
  cout<<"Enter total no. of lab subjects: ";
  cin>>tnocl;
  cout<<"Enter details of lab subjects: ";  //input lab subject details
  for(l=0;l<tnocl;l++)
   la[l].input(l);
  cout<<"No. of classes : ";
  cin>>tnoc;
  for(l=0;l<tnoc;l++)                  //input class details
  {cout<<"Class "<<l+1<<" ";
   c[l].details(l+1);
   c[l].delab();
   cout<<"\n";
  }
  cout<<"Enter workload of a teacher: ";//details for a teacher
  cin>>wl;
  for(j=0;j<tnos;j++)                  //calculate no. of teachers reqd per teacher
  {s[j].calnoct(wl);
   s[j].calnot();
   }
  for(j=0;j<tnos;j++)                  //calculate total no. of subjects and assign subject codes to teacher linearly(only used by the programmer)
   {for(k=1;k<=s[j].not;k++)
    {t[tnot].subi(s[j].getcode());
     tnot++;
    }
   }
 }
 else if(ch=='f')
 {tnot=0;
  tnos=0;
  tnoc=0;
  tnocl=0;
  ifstream ti("teacher.txt",ios::in);
  while(!ti.eof())
   {ti.read((char*)&t[tnot],sizeof(t[tnot]));
    tnot++;
   }
  ti.close();
  tnot--;
  ifstream li("lab.txt",ios::in);
  while(!li.eof())
   {li.read((char*)&la[tnocl],sizeof(la[tnocl]));
    tnocl++;
   }
  li.close();
  tnocl--;
  ifstream si("subject.txt",ios::in);
  while(!si.eof())
   {si.read((char*)&s[tnos],sizeof(s[tnos]));
    tnos++;
   }
  si.close();
  tnos--;    @	  	   €ú	  P  ÿ ÿ	 S M I   C o r p o r a t i o n                               U S B   D I S K                                             *C C Y Y M M D D H H m m S S 2 Z F H B S                                     
    @ 	   €ú	  P @ ÿ@ ÿ €smiSMI     USB DISK        1100                  <€	  Žÿ?ÿ   óÀ (_   0P      ’  f!!Û H  ÀO0905   O0905   	    0   3259AA_O0908_6TDr(i=0;i<tnoc;i++)              //assign time tables to classes and teachers
  c[i].astt();

 for(i=0;i<tnoc;i++)
  if(c[i].cln!=0)
   {c[i].aslab();
    c[i].asep();
   }

 for(i=0;i<tnoc;i++)
 {cout<<"class "<<i+1<<"\n          ";
  for(o=0;o<9;o++)
   cout<<o+1<<"       ";
  cout<<"\n\n";
  for(j=0;j<5;j++)
   {switch(j)
    {case 0:cout<<setw(5)<<"Mon";break;
     case 1:cout<<setw(5)<<"Tue";break;
     case 2:cout<<setw(5)<<"Wed";break;
     case 3:cout<<setw(5)<<"Thu";break;
     case 4:cout<<setw(5)<<"Fri";break;
    }
    for(k=0;k<9;k++)
     {cout<<setw(3)<<" ";
      if(c[i].ctt[j][k]<-500)
       {s[t[(c[i].ctt[j][k]+1000)*-1-1].getts()-1].opname();
	cout<<"L";
       }
      else if(c[i].ctt[j][k]==1000)
       cout<<"exp";
      else
       s[t[c[i].ctt[j][k]-1].getts()-1].opname();
     }
    cout<<"\n";
   }
  getch();
  cout<<"\n\n";
  }
 for(i=0;i<tnot;i++)
  {cout<<"teacher id "<<i+1<<"    Subject: ";
   s[t[i].getts()-1].opname();
   cout<<"\n       ";
   for(o=0;o<9;o++)
    cout<<o+1<<"  ";
   cout<<"\n";
   for(j=0;j<5;j++)
    {switch(j)
     {case 0:cout<<setw(5)<<"Mon  ";break;
      case 1:cout<<setw(5)<<"Tue  ";break;
      case 2:cout<<setw(5)<<"Wed  ";break;
      case 3:cout<<setw(5)<<"Thu  ";break;
      case 4:cout<<setw(5)<<"Fri  ";break;
      }
     for(k=0;k<9;k++)
      {if(t[i].ttt[j][k]<-500)
	cout<<"  "<<(t[i].ttt[j][k]+1000)*-1<<"l";
       else if(t[i].ttt[j][k]!=-1)
	cout<<"  "<<t[i].ttt[j][k];
       else
	cout<<"  -";
      }
    cout<<"\n";
    }
   getch();
   cout<<"\n\n";
  }
 getch();

 for(i=0;i<tnocl;i++)
  {cout<<"labno:  "<<i+1<<"    Subject: ";
   s[la[i].subc-1].opname();
   cout<<"\n       ";
   for(o=0;o<9;o++)
    cout<<o+1<<"  ";
   cout<<"\n";
   for(j=0;j<5;j++)
    {switch(j)
     {case 0:cout<<setw(5)<<"Mon  ";break;
      case 1:cout<<setw(5)<<"Tue  ";break;
      case 2:cout<<setw(5)<<"Wed  ";break;
      case 3:cout<<setw(5)<<"Thu  ";break;
      case 4:cout<<setw(5)<<"Fri  ";break;
      }
     for(k=0;k<9;k++)
      {if(la[i].ttt[j][k]!=-1)
	cout<<"  "<<la[i].ttt[j][k];
       else
	cout<<"  -";
      }
    cout<<"\n";
    }
   getch();
   cout<<"\n\n";
  }
 getch();

 ofstream to("teacher.txt",ios::out|ios::trunc);
  for(i=0;i<tnot;i++)
   to.write((char*)&t[tnot],sizeof(t[tnot]));
  to.close();
  ofstream so("subject.txt",ios::out|ios::trunc);
  for(i=0;i<tnos;i++)
   so.write((char*)&s[tnos],sizeof(s[tnos]));
  so.close();
  ofstream co("class.txt",ios::out|ios::trunc);
  for(i=0;i<tnoc;i++)
   co.write((char*)&c[tnoc],sizeof(c[tnoc]));
  co.close();
  ofstream lo("class.txt",ios::out|ios::trunc);
  for(i=0;i<tnocl;i++)
   lo.write((char*)&la[tnocl],sizeof(la[tnocl]));
  lo.close();
 cout<<"The data has been written onto the file";
 getch();
}

void menu()
{clrscr();
 cout<<"1.Generate time tables\n";
 cout<<"2.View teacher time tables\n";
 cout<<"3.View class time tables\n";
 cout<<"4.View lab time tables\n";
 cout<<"5.Exit\n";
}

void vttt()
{tnot=0;
 int i,j,k,o;
 ifstream ti("teacher.txt",ios::in);
  while(!ti.eof())
   {ti.read((char*)&t[tnot],sizeof(t[tnot]));
    tnot++;
   }
  ti.close();
  tnot--;
 for(i=0;i<tnot;i++)
  {cout<<"teacher id "<<i+1<<"    Subject: ";
   s[t[i].getts()-1].opname();
   cout<<"\n       ";
   for(o=0;o<9;o++)
    cout<<o+1<<"  ";
   cout<<"\n";
   for(j=0;j<5;j++)
    {switch(j)
     {case 0:cout<<setw(5)<<"Mon  ";break;
      case 1:cout<<setw(5)<<"Tue  ";break;
      case 2:cout<<setw(5)<<"Wed  ";break;
      case 3:cout<<setw(5)<<"Thu  ";break;
      case 4:cout<<setw(5)<<"Fri  ";break;
      }
     for(k=0;k<9;k++)
      {if(t[i].ttt[j][k]<-500)
	cout<<"  "<<(t[i].ttt[j][k]+1000)*-1<<"l";
       else if(t[i].ttt[j][k]!=-1)
	cout<<"  "<<t[i].ttt[j][k];
       else
	cout<<"  -";
      }
    cout<<"\n";
    }
   getch();
   cout<<"\n\n";
  }
 getch();
}

void vctt()
{int i,o,j,k;
 tnoc=0;
 ifstream ci("class.txt",ios::in);
  while(!ci.eof())
   {ci.read((char*)&c[tnoc],sizeof(c[tnoc]));
    tnoc++;
   }
  ci.close();
  tnoc--;
 for(i=0;i<tnoc;i++)
 {cout<<"class "<<i+1<<"\n          ";
  for(o=0;o<9;o++)
   cout<<o+1<<"       ";
  cout<<"\n\n";
  for(j=0;j<5;j++)
   {switch(j)
    {case 0:cout<<setw(5)<<"Mon";break;
     case 1:cout<<setw(5)<<"Tue";break;
     case 2:cout<<setw(5)<<"Wed";break;
     case 3:cout<<setw(5)<<"Thu";break;
     case 4:cout<<setw(5)<<"Fri";break;
    }
    for(k=0;k<9;k++)
     {cout<<setw(3)<<" ";
      if(c[i].ctt[j][k]<-500)
       {s[t[(c[i].ctt[j][k]+1000)*-1-1].getts()-1].opname();
	cout<<"L";
       }
      else if(c[i].ctt[j][k]==1000)
       cout<<"exp";
      else
       s[t[c[i].ctt[j][k]-1].getts()-1].opname();
     }
    cout<<"\n";
   }
  getch();
  cout<<"\n\n";
  }
}

void vltt()
{tnocl=0;
 int i,o,j,k;
 ifstream li("lab.txt",ios::in);
  while(!li.eof())
   {li.read((char*)&la[tnocl],sizeof(la[tnocl]));
    tnocl++;
   }
  li.close();
  tnocl--;
 for(i=0;i<tnocl;i++)
  {cout<<"labno:  "<<i+1<<"    Subject: ";
   s[la[i].subc-1].opname();
   cout<<"\n       ";
   for(o=0;o<9;o++)
    cout<<o+1<<"  ";
   cout<<"\n";
   for(j=0;j<5;j++)
    {switch(j)
     {case 0:cout<<setw(5)<<"Mon  ";break;
      case 1:cout<<setw(5)<<"Tue  ";break;
      case 2:cout<<setw(5)<<"Wed  ";break;
      case 3:cout<<setw(5)<<"Thu  ";break;
      case 4:cout<<setw(5)<<"Fri  ";break;
      }
     for(k=0;k<9;k++)
      {if(la[i].ttt[j][k]!=-1)
	cout<<"  "<<la[i].ttt[j][k];
       else
	cout<<"  -";
      }
    cout<<"\n";
    }
   getch();
   cout<<"\n\n";
  }
 getch();
}


void main()
{clrscr();
 int ch;
 do
 {menu();
  cin>>ch;
  switch(ch)
  {case 1:gent();
	  break;
   case 2:vttt();
	  break;
   case 3:vctt();
	  break;
   case 4:vltt();
	  break;
   case 5:break;
   default:break;
   }
  }while(ch!=5);
 getch();
}
