#include<iostream>
using namespace std;

class Office{
	int n;
	string office[10];
	int a[10][10];
	
	public:
		
		void input(){
			cout<<"Enter total number of offices: ";
			cin>>n;
			
			cout<<"Enter the name of offices "<<endl;
			for(int i = 0; i < n; i++){
				cin>>office[i];
			}
			
			cout<<"Enter the cost to connect offices"<<endl;
			for(int i = 0; i < n; i++){
				for(int j = i; j < n; j++){
					if(i == j){
						a[i][j] = 0;
						continue;
					}
					
					cout<<"Enter the cost to connect "<<office[i]<<" and "<<office[j]<<endl;
					cin>>a[i][j];
					a[j][i] = a[i][j];
				}
			}
		}
		
		void display(){
			for(int i = 0; i < n; i++){
				for(int j = 0; j < n; j++){
					cout<<a[i][j]<<"\t";
				}
				cout<<endl;
			}
		}
		
		void prims(){
			int minIndex = 0;
			int minCost = 0;
			int cost = 0;
			int visit[n];
			int count = 1;
			
			for(int i = 0; i < n; i++){
				visit[i] = 0;
			}
		
			visit[0] = 1;
			
			while(1){
					
				minCost = 100000;
				
				for(int i = 0; i < n; i++){
					for(int j = 0; j < n; j++){
						if(visit[i] == 1 && visit[j] == 0 && a[i][j] != 0 && a[i][j] < minCost){
							minCost = a[i][j];
							minIndex = j;
						}
					}
				}
				
				visit[minIndex] = 1;
				cost += minCost;
				count++;
				
				if(count == n){
					break;
				}
			}
			
			cout<<"Minimum Cost is:"<<cost<<endl;
			
		}
};

int main(){
	Office o1;
    int choice;
MENU:
    cout<<"\n\nMINIMUM SPANNING TREE";
    cout<<"\n1. Input data";
    cout<<"\n2. Display data";
    cout<<"\n3. Calculate minimum cost";
    cout<<"\n4. Exit";
    cout<<"\nEnter your choice: ";
    cin >> choice;
    switch(choice)
    {
    case 1:
    	o1.input();
    	break;
    case 2:
    	o1.display();
    	break;
    case 3:
    	o1.prims();
    	break;
    case 4:
    	cout<<"Thank you for using this Program!";
    	return 0;
    default:
    	cout<<"\nInvalid choice.Try again!";
    }
    if(choice != 5)
    	goto MENU;
 
	return 0;
}
