#include<iostream>
using namespace std;

class node{
   public:

		int data;
		node *left_child, *right_child;
		friend class obst;

		node(int x){
			data = x;
			left_child = NULL;
			right_child = NULL;
		}
};

class obst{

public:
	
	double w[10][10];
	double c[10][10];
	double r[10][10];
	double k;

	node *root;

	obst(){
		root = NULL;
		//n = n;
	}

	void calculate_wt(double[], double[], int);

	node *create_tree(int i,int j){
		node *t = NULL;
		if(i != j){
			k = r[i][j];
			t = new node(k);
			t->left_child = create_tree(i, k-1);
			t->right_child = create_tree(k, j);
//			cout<<"Create tree";
			return t;
		}
		else{
			return NULL;
		}
	}

	void DisplayTable(){
		for(int i = 0;i<=3;i++){
			cout<<"W "<<i<<","<<i<<"= "<<w[i][i]<<" | "<<"C "<<i<<","<<i<<"= "<<c[i][i]<<" | "<<"R "<<i<<","<<i<<"= "<<r[i][i]<<endl;
		}

		cout<<endl<<endl;

		for(int m =1;m<=3;m++){//calcules the cost for Trees with More than 1 Node
			for(int i = 0; i<=3-m;i++){
				int j = i + m;
				cout<<"W "<<i<<","<<j<<"= "<<w[i][j]<<" | "<<"C "<<i<<","<<j<<"= "<<c[i][j]<<" | "<<"R "<<i<<","<<j<<"= "<<r[i][j]<<endl;
			}
		}

	}
	
	void inorder(node *root){
		if(root == NULL){
			return;
		}
		
		inorder(root->left_child);
		cout<<root->data<<" ";
		inorder(root->right_child);
	}

};

void obst::calculate_wt(double p[], double q[] ,int n){
   int k;
   // p is array of Probability of Successful search
   // q is array of unsuccessfull search
   // n is number of identifier
   for(int i = 0;i < n;i++){
      w[i][i] = q[i]; //calculates the cost for
      r[i][i] = 0;    // NULL Tree & Tree with
      c[i][i] = 0;    // One node

      w[i][i+1] = q[i] + q[i+1] + p[i+1];
      r[i][i+1] = i+1;
      c[i][i+1] = w[i][i+1];
   }

   w[n][n] = q[n];
   r[n][n] = 0;
   c[n][n] = 0;

   for(int m = 2; m <= n; m++)//calcules the cost for Trees with More than 1 Node
        for(int i = 0; i <= n - m;i++){
         int min = 999;
         int j = i + m;
         w[i][j] = w[i][j-1] + p[j] + q[j];
         for(int i1 = i+1; i1<=j; i1++){
            int sum1= c[i][i1-1] + c[i1][j];
            if(sum1<min){
               min = sum1;
               k = i1;
            }
         }
         c[i][j] = w[i][j] + c[i][k-1] + c[k][j];
         r[i][j] = k;
        }

      root = create_tree(0, n);

}

int main(){
	obst tree;
	double p[4] = {0, 0.4 ,0.1, 0.2};
	double q[4] = {0.1,0.04,0.09, 0.07};

	tree.calculate_wt(p,q,3);
	tree.DisplayTable();
	tree.inorder(tree.root);

	return 0;
}
