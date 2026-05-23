#include<bits/stdc++.h>
#include<cmath>
#include <cstdlib>
#include <ctime>
using namespace std;
//the node structure
struct node {
    int x,y,val;
    double f,g,h;
    node *parent;
};
//heuristic function using the diagonal distance approach
double heuristic(pair<int,int> p1, pair<int,int> p2) {
    double dx=abs(p1.first-p2.first);
    double dy=abs(p1.second-p2.second);
    return (dx+dy)+(sqrt(2)-2)*min(dx,dy);
}
int main() {
    //initialize the randomizer
    srand(time(0));
    int rows=9,cols=9;//no. of columns and rows
    vector<vector<node>> map(rows,vector<node>(cols)); //the maze
    //initializing the maze
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            map[i][j] = {i, j, rand()%2, 1e3, 1e3, 0, nullptr};
        }
    }
    map[rand()%rows][rand()%cols].val = 1; //making sure that at least one cell will be empty
    pair<int,int> start={rand()%(rows),rand()%(cols)},end={rand()%(rows),rand()%(cols)};//choosing random start and end points
    //making sure that start and end are in empty cells
    while (!map[start.first][start.second].val||!map[end.first][end.second].val) {
        if (!map[start.first][start.second].val) {
            start={rand()%(rows),rand()%(cols)};
        }
        if (!map[end.first][end.second].val) {
            end={rand()%(rows),rand()%(cols)};
        }
    }
    cout<<"("<<start.first<<','<<start.second<<")"<<" ("<<end.first<<","<<end.second<<')'<<"\n";
    //if start and end are in the same cell
    if (start==end) {
        cout<<"start is end";
        return 0;
    }
    //initializing the starting node
    node *current=&map[start.first][start.second];
    current->g=0;
    current->h=heuristic(start,end);
    current->f=current->g+current->h;
    current->parent=nullptr;
    priority_queue<
       pair<double, node*>,              // value type
       vector<pair<double, node*>>,      // container
       greater<pair<double, node*>>      // comparator (min-heap by first)
   > openList;//flipped priority queue to sort according to the lower f value and to make it faster performance wise
    openList.push({current->f,current});//push the first node to the openlist
    vector<node*> closedList;//vector with all the visited nodes
    // directions for 8 neighbors (dx, dy)
    int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int done=0;//flag to check whether there's a solution or no
    while(openList.size()>0) {
        auto [f, curr] = openList.top();//get the smallest f valued node in each iteration
        openList.pop();
        closedList.push_back(curr);//push the node that is to being checked rn
        //identify and check the neighbors
        for(int i=0;i<8;i++) {
            int nx=dx[i]+curr->x,ny=dy[i]+curr->y;//giving nx and ny the coordinates of the neighbor who is going to be checked
            //if neighbor out of map ignore him
            if (nx<0||ny<0||nx>=rows||ny>=cols) {
                continue;
            }
            else {
                //if we reached the endpoint then done and exit
                if (nx==end.first&&ny==end.second) {
                    cout<<"hoorrayyyyyy\n";
                    map[nx][ny].parent = curr;
                    done=1;
                    break;
                }
                if (map[nx][ny].val==1) {// make sure the neighbor is empty not a wall
                    node *temp=&map[nx][ny];//temp is the neighbor node
                    if (find(closedList.begin(), closedList.end(), temp)==closedList.end()) {//check that this neighbor havent been checked before
                        double new_g=curr->g+((curr->x!=temp->x&&curr->y!=temp->y)?sqrt(2):1);//calculate new_g based on the location of the neighbor
                        if (new_g<temp->g){//if new_g is better than the old_g if its the first time to visit the node then the old_g will be 1e3
                            temp->parent=curr;
                            temp->g=new_g;
                            temp->h=heuristic({temp->x,temp->y},end);
                            temp->f=temp->g+temp->h;
                            openList.push({temp->f,temp});
                        }
                    }
                }
            }
        }
        if (done==1) {break;}//stop if done
    }
    if (done) {
        node* temp=&map[end.first][end.second];
        vector<pair<int,int>> path;//vector to store the optimum path
        //iterate over the entire path using the parent of each node
        while (temp != nullptr) {
            temp->val=2;//make the path to have values 2 to know it
            if (temp->x==start.first&&temp->y==start.second) {
                temp->val=3;//make the start has value 3
            }
            if (temp->x==end.first&&temp->y==end.second) {
                temp->val=4;//make the end has value 4
            }
            path.push_back({temp->x, temp->y});
            temp = temp->parent;
        }
        reverse(path.begin(), path.end());//reverse the order to make it in the correct order
        for (auto [x,y]: path) cout << x << " " << y << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (map[i][j].val==1) {
                    cout<<".";
                }
                else if (map[i][j].val==2) {
                    cout<<"*";
                }
                else if (map[i][j].val==0) {
                    cout<<"#";
                }
                else if (map[i][j].val==3) {
                    cout<<"S";
                }
                else if (map[i][j].val==4) {
                    cout<<"E";
                }
                cout<<" ";
            }
            cout<<'\n';
        }
    }
    else {
        cout<<"No path found";
    }

}
