#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<vector>
#include<ctime>
using namespace std;

void printbox(char grid[]);
int checkwinner(char grid[]);
bool getinput(char grid[], char player);
bool checkdraw(char grid[]);
int choice(char grid[]);

int main()
{
	srand(time(0));
	char grid[121],player='X';
	int winner;
	for(int i=0;i<121;i++) grid[i]=' ';
	printbox(grid);
	winner=checkwinner(grid);
	while(winner==0){
		while(getinput(grid,player)) cout<<"Please give right input"<<endl;
		if(player=='O') printbox(grid);
		winner=checkwinner(grid);
		if(winner==1) {
			printbox(grid);
			cout<<"X wins!"<<endl;
			break;
		}
		if(winner==2) {
			cout<<"O wins!"<<endl;
			break;
		}
		if(checkdraw(grid)) {
			cout<<"Draw!"<<endl;
			break;
		}
		if(player=='X') player='O';
		else player='X';
	}
	return 0;
}

void printbox(char grid[])
{
	for(int j=0;j<10;j++){
		for(int i=0;i<10;i++){
			cout<<" "<<grid[11*j+i]<<" |";
		}
		cout<<" "<<grid[11*j+10]<<endl;
		for(int k=0;k<43;k++){
			cout<<"-";
		}
		cout<<endl;
	}
	for(int i=0;i<10;i++){
		cout<<" "<<grid[110+i]<<" |";
	}
	cout<<" "<<grid[120]<<endl;
	cout<<endl;
}

int checkwinner(char grid[])
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

bool getinput(char grid[], char player)
{
	int r,c;
	if(player=='X'){
		do{
			cout<<"Please enter row and column: "<<endl;
			cin>>r>>c;
			if(!(r<12&&r>0&&c<12&&c>0)) return true;
		}while(grid[11*(r-1)+c-1]!=' ');
		grid[11*(r-1)+c-1]=player;
	}
	else grid[choice(grid)]=player;
	return false;
}

bool checkdraw(char grid[])
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

int choice(char grid[])
{
	int x,o,start,countmax=0,maxi=0;
	int score[121];
	vector<int> maxindex;
	for(int i=0;i<121;i++){
		vector<int> scores;
		if(grid[i]!=' ') score[i]=0;
		else{
			start=i;
			while(start%11!=0) start--;
			for(int j=i;j>=i-4&&j>=start;j--){
				x=0;
				o=0;
				for(int k=0;k<5&&j+k<=start+10;k++){
					if(grid[j+k]=='X') x++;
					if(grid[j+k]=='O') o++;
				}
				if(x>0&&o>0){
					x=0;
					o=0;
				}
				scores.push_back(max(x,o));
			}
			start=i;
			while(start>=11) start-=11;
			for(int j=i;j>=i-44&&j>=start;j-=11){
				x=0;
				o=0;
				for(int k=0;k<5&&j+k*11<121;k++){
					if(grid[j+k*11]=='X') x++;
					if(grid[j+k*11]=='O') o++;
				}
				if(x>0&&o>0){
					x=0;
					o=0;
				}
				scores.push_back(max(x,o));
			}
			for(int j=i;j>=i-48&&j>=0;j-=12){
				if(j%11+4==(j+48)%11&&j+48<121){
					x=0;
					o=0;
					for(int k=0;k<5;k++){
						if(grid[j+k*12]=='X') x++;
						if(grid[j+k*12]=='O') o++;
					}
					if(x>0&&o>0){
						x=0;
						o=0;
					}
					scores.push_back(max(x,o));
				}
			}
			for(int j=i;j>=i-40&&j>=0;j-=10){
				if(j%11-4==(j+40)%11&&j+40<121){
					x=0;
					o=0;
					for(int k=0;k<5;k++){
						if(grid[j+k*10]=='X') x++;
						if(grid[j+k*10]=='O') o++;
					}
					if(x>0&&o>0){
						x=0;
						o=0;
					}
					scores.push_back(max(x,o));
				}
			}
		}
		int scoremax=0;
		for(unsigned int p=0;p<scores.size();p++){
			if(scores[p]>scoremax) scoremax=scores[p];
		}
		score[i]=scoremax;
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