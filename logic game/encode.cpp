#include<iostream>
#include<cstdlib>
using namespace std;

int main()
{
	srand(100);
	int user[2];
	int guess[2];
	int truth[2];
	int countblack=0;
	int countwhite=0;
	bool knowledgebase,find0=false,find1=false;
	cout<<"Please give two numbers"<<endl;
	for(int i=0;i<2;i++){
		cin>>user[i];
	}
 	guess[0]=rand()%10;
	guess[1]=rand()%10;
	while(countblack<2){

		for(int i=0;i<2;i++){
			if(guess[i]==user[i]) countblack++;
		}
		for(int i=0;i<2;i++){
			for(int j=0;j<2;j++){
				if(guess[i]==user[j]) countwhite++;
			}
		}
		countwhite-=countblack;

		if(countblack==1) knowledgebase=knowledgebase&&
			((truth[0]==guess[0]&&truth[1]!=guess[1])||(truth[0]!=guess[0]&&truth[1]==guess[1]));

		if(countwhite==1) knowledgebase=knowledgebase&&
			((truth[1]==guess[0]||truth[0]==guess[1])&&!(truth[1]==guess[0]&&truth[0]==guess[1]));

		if(countwhite==2) knowledgebase=knowledgebase&&
			(truth[1]==guess[0]&&truth[0]==guess[1]);
		int k1,k2;
		for(k1=0;k1<10;k1++){
			if(!(knowledgebase&&!(truth[0]==k1))){
				find0=true;
				truth[0]=k1;
				guess[0]=k1;
				break;
			}
		}
		for(k2=0;k2<10;k2++){
			if(!(knowledgebase&&!(truth[1]==k1))){
				find1=true;
				truth[1]=k2;
				guess[1]=k2;
				break;
			} 
		}
		countwhite=0;
		countblack=0;
		if(!find0) guess[0]=rand()%10;
		if(!find1) guess[1]=rand()%10;
	}
	cout<<guess[0]<<" "<<guess[1]<<endl;
	return 0;
}