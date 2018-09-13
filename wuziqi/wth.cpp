#include<iostream>
#include<stdio.h> 
#include<string.h>
#include<algorithm>
#include<cstdlib>
#include<vector>
#include<ctime>
using namespace std;
char grid[121];
int n;
void printbox();
int checkwinner();
bool getinput(char player);
bool checkdraw();
int choice();
int main()
{
 srand(time(0));
 char player='X';
 int winner;
 for(int i=0;i<121;i++) grid[i]=' ';
 printbox();
 winner=checkwinner();
 while(winner==0){
  while(getinput(player)) cout<<"Please give right input"<<endl;
  if(player=='O') printbox();
  winner=checkwinner();
  if(winner==1) {
   printbox();
   cout<<"X wins!"<<endl;
   break;
  }
  if(winner==2) {
   cout<<"O wins!"<<endl;
   break;
  }
  if(checkdraw()) {
   cout<<"Draw!"<<endl;
   break;
  }
  if(player=='X') player='O';
  else player='X';
 }
 return 0;
}
void printbox()
{
 int i,j;
 printf("   ");
 for(i=0;i<11;i++)
 printf(" %c ",'a'+i);
 printf("\n");
 for(i=0;i<11;i++)
 {
  printf(" %c|",'A'+i);
  for(j=0;j<11;j++)
  {
   if(grid[i*11+j]=='O')printf(" O|");
   else if(grid[i*11+j]=='X')printf(" X|");
   else printf("  |");
  }
  printf("\n");
 };
}
int checkwinner()
{
 int x,o,start;
 for(int i=0;i<11;i++){
  for(int j=0;j<7;j++){
   x=0;
   o=0;
   for(int k=0;k<5;k++){
    if(grid[11*i+j+k]=='X') x++;
    if(grid[11*i+j+k]=='O') o++;
   }
   if(x==5) return 1;
   if(o==5) return 2;
  }
 }
 for(int i=0;i<11;i++){
  for(int j=0;j<7;j++){
   x=0;
   o=0;
   for(int k=0;k<5;k++){
    if(grid[i+11*(j+k)]=='X') x++;
    if(grid[i+11*(j+k)]=='O') o++;
   }
   if(x==5) return 1;
   if(o==5) return 2;
  }
 }
 for(int i=0;i<121;i++){
  start=i;
  while(start%11!=0) start--;
  if(i+48<121&&i<=start+6){
   x=0;
   o=0;
   for(int k=0;k<5;k++){
    if(grid[i+k*12]=='X') x++;
    if(grid[i+k*12]=='O') o++;
   }
   if(x==5) return 1;
   if(o==5) return 2;
  }
 }
 for(int i=0;i<121;i++){
  start=i;
  while(start%11!=0) start--;
  if(i+40<121&&i>=start+4){
   x=0;
   o=0;
   for(int k=0;k<5;k++){
    if(grid[i+k*10]=='X') x++;
    if(grid[i+k*10]=='O') o++;
   }
   if(x==5) return 1;
   if(o==5) return 2;
  }
 }
 return 0;
}
bool getinput(char player)
{
 int r,c;
 char s,t;
 if(player=='X'){
  do{
   cout<<"Please enter row and column: "<<endl;
   cin>>s>>t;
   r=s-'A'+1;
   c=t-'a'+1;
   if(!(r<12&&r>0&&c<12&&c>0)) return true;
  }while(grid[11*(r-1)+c-1]!=' ');
  grid[11*(r-1)+c-1]=player;
 }
 else grid[choice()]=player;
 return false;
}
bool checkdraw()
{
 int start;
 bool allx,allo;
 for(int i=0;i<11;i++){
  for(int j=0;j<7;j++){
   allx=true;
   allo=true;
   for(int k=0;k<5;k++){
    if(grid[11*i+j+k]=='X') allo=false;
    if(grid[11*i+j+k]=='O') allx=false;
   }
   if(allx||allo) return false;
  }
 }
 for(int i=0;i<11;i++){
  for(int j=0;j<7;j++){
   allx=true;
   allo=true;
   for(int k=0;k<5;k++){
    if(grid[i+11*(j+k)]=='X') allo=false;
    if(grid[i+11*(j+k)]=='O') allx=false;
   }
   if(allx||allo) return false;
  }
 }
 for(int i=0;i<121;i++){
  start=i;
  while(start%11!=0) start--;
  if(i+48<121&&i<=start+6){
   allx=true;
   allo=true;
   for(int k=0;k<5;k++){
    if(grid[i+k*12]=='X') allo=false;
    if(grid[i+k*12]=='O') allx=false;
   }
   if(allx||allo) return false;
  }
 }
 for(int i=0;i<121;i++){
  start=i;
  while(start%11!=0) start--;
  if(i+40<121&&i>=start+4){
   allx=true;
   allo=true;
   for(int k=0;k<5;k++){
    if(grid[i+k*10]=='X') allo=false;
    if(grid[i+k*10]=='O') allx=false;
   }
   if(allx||allo) return false;
  }
 }
 return true;
}
int choice()
{
  int start,row,col,countmax=0,maxi=0;
  int score[121];
  int numx=0,numo=0,empty=0;
  vector<int> maxindex;
  for(int i=0;i<121;i++){
    if(grid[i]!=' ') score[i]=0;
    else{
      score[i]=0;
      start=i;
      while(start%11!=0) start--;
      col=i-start;
      start=i;
      while(start>=11) start-=11;
      row=(i-start)/11;
      for(int j=-1;j<=1;j++){
        for(int k=-1;k<=1;k++){
          if(j!=0||k!=0){
            for(int t=1;t<=4;t++){
              if(row+t*j>=0&&row+t*j<=10&&col+t*k>=0&&col+t*k<=10
                &&grid[(row+t*j)*11+col+t*k]=='X') numx++;
              else if(grid[(row+t*j)*11+col+t*k]==' '){
                empty++;
                break;
              }
              else break;
            }
            for(int t=-1;t>=4;t--){
              if(row+t*j>=0&&row+t*j<=10&&col+t*k>=0&&col+t*k<=10
                &&grid[(row+t*j)*11+col+t*k]=='X') numx++;
              else if(grid[(row+t*j)*11+col+t*k]==' '){
                empty++;
                break;
              }
              else break;
            }
            if(numx==1) score[i]+=1;
            else if(numx==2){
              if(empty==1) score[i]+=5;
              if(empty==2) score[i]+=10;
            }
            else if(numx==3){
              if(empty==1) score[i]+=20;
              else if(empty==2) score[i]+=100;
            }
            else if(numx>=4) score[i]+=1000;
            empty=0;
            for(int t=1;t<=4;t++){
              if(row+t*j>=0&&row+t*j<=10&&col+t*k>=0&&col+t*k<=10
                &&grid[(row+t*j)*11+col+t*k]=='O') numo++;
              else if(grid[(row+t*j)*11+col+t*k]==' '){
                empty++;
                break;
              }
              else break;
            }
            for(int t=-1;t>=4;t--){
              if(row+t*j>=0&&row+t*j<=10&&col+t*k>=0&&col+t*k<=10
                &&grid[(row+t*j)*11+col+t*k]=='O') numo++;
              else if(grid[(row+t*j)*11+col+t*k]==' '){
                empty++;
                break;
              }
              else break;
            }
            if(numo==0) score[i]+=1;
            else if(numo==1) score[i]+=2;
            else if(numo==2){
              if(empty==1) score[i]+=8;
              if(empty==2) score[i]+=30;
            }
            else if(numo==3){
              if(empty==1) score[i]+=50;
              else if(empty==2) score[i]+=200;
            }
            else if(numo>=4) score[i]+=1000;
            numx=0;
            numo=0;
            empty=0;
          }
        }
      }
    }
  }
  for(int i=0;i<121;i++){
    if(score[i]>maxi) maxi=score[i];
  }
  for(int i=0;i<121;i++){
    if(score[i]==maxi){
      countmax++;
      maxindex.push_back(i);
    }
  }
  return maxindex[rand()%countmax];
}