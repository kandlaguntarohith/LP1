#include <bits/stdc++.h>

using namespace std;

int moves;

class Node {

public:
    int x,y,cost,level;
    Node* parent;
    vector<vector<int>>matrix;

    Node(vector<vector<int>>temp, int x, int y, int newX, int newY, int level, Node* par){

            for(auto i :temp){
                this->matrix.push_back(i);
            }


            int temp_var = this->matrix[x][y];
            this->matrix[x][y] = this->matrix[newX][newY];
            this->matrix[newX][newY] = temp_var;

            this->x = newX;
            this->y = newY;
            this->parent = par;
            this->cost = INT_MAX;
            this->level = level;

    }
};

class Compare {
public:
    bool operator() (Node*p, Node*q)
    {
        return p->cost > q->cost;
    }
};



int calcCost(vector<vector<int>>start, vector<vector<int>>goal){
        int count = 0;
		int n = start[0].size();
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (start[i][j] != 0 && start[i][j] != goal[i][j]) {
					count++;
				}
			}
		}
		return count;
}


bool checkValidCell(int n,int m,int x,int y) {
    return x >=0 && x < n && y>=0 && y <m;
}

void printMatrix(vector<vector<int>>res){
    for(auto i : res){
        for(auto j : i){
            cout<<j<<" ";
        }
        cout<<"\n";
    }
}

void printPath(Node* root) {
    if (root == NULL) {
        return;
    }
    moves++;
    printPath(root->parent);
    if(root->parent != NULL) {
        cout<<"  |\n";
        cout<<"  V\n";
    }
    cout<<"\n";
    printMatrix(root->matrix);
    cout<<"\n";
}


void solvPuzzle(vector<vector<int>>start, vector<vector<int>>goal, int x, int y){


    Node* root = new Node(start,x,y,x,y,0,NULL);

    root->cost = calcCost(start,goal);

    priority_queue <Node*, vector<Node*>, Compare> pq;
    map<Node*,int>s;

    int row[] = {0,1,0,-1};
    int col[] = {1,0,-1,0};

    pq.push(root);

    while(!pq.empty()){

        Node* temp = pq.top();
        pq.pop();

        if(temp->cost == 0){

            printPath(temp);
            cout<<"Number of moves required to reach final matrix: "<<moves-1<<"\n";
            return;
        }

        s[temp]=1;

        for(int i=0;i<4;i++){

            if(checkValidCell(3,3,temp->x + row[i],temp->y+col[i])){
                Node* child = new Node(temp->matrix,temp->x,temp->y,temp->x+row[i],temp->y+col[i],temp->level+1,temp);
                child->cost = calcCost(child->matrix,goal);
                if(s.find(child) == s.end()) {
                    pq.push(child);
                }
            }
        }
    }
}

// intial position of the space/_
vector<int> findInitPos(vector<vector<int>>&mat){

    vector<int>res;

    for(int i=0;i<3;i++){
         for(int j=0;j<3;j++){
           if(mat[i][j] == 0){
                res.push_back(i);
                res.push_back(j);
           }
        }
    }
    return res;
}


// Function to check whether problem is solvable or not
bool isSolvable(vector<vector<int>>&start){

    vector<int>temp;

    for(auto i : start){
        for(auto j : i){
            if(j !=0)
            temp.push_back(j);
        }
    }

    int n = temp.size();
    int count_inv = 0;

    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(temp[i]>temp[j]){
                count_inv++;
            }
        }
    }

    return count_inv%2==0;

}

int main()
{
    // initializing the start and goal matrix
    vector<vector<int>>start(3,vector<int>(3,0));
    vector<vector<int>>goal(3,vector<int>(3,0));

    int a;

    moves=0;

    cout<<"Enter the Start State :"<<endl;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
           cin>>a;
           start[i][j] = a;
        }
    }

    cout<<"Enter the Goal State :"<<endl;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
           cin>>a;
           goal[i][j] = a;
        }
    }

    // check if problem is solvable or not
    if(isSolvable(start)){
        vector<int> res = findInitPos(start);

        cout<<"Solving the Problem..."<<endl;
        solvPuzzle(start,goal,res[0],res[1]);
    }
    else {
        cout<<"The given problem is unsolvable!!"<<endl;
    }

    return 0;
}


/**
	Test Cases

1)	Initial state:
	1 2 3
	_ 4 6
	7 5 8

    or

    1 2 3
    0 4 6
    7 5 8

	Goal state:
	1 2 3
	4 5 6
	7 8 _

    or

    1 2 3
    4 5 6
    7 8 0

2) Initial state:
	8 1 2
	_ 4 3
	7 6 5

    or

    8 1 2    
    0 4 3
    7 6 5

	Goal state:
	1 2 3
	4 5 6
	7 8 _

    or

    1 2 3
    4 5 6                
    7 8 0
 */
