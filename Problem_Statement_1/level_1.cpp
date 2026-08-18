#include<iostream>
#include<vector>
#include<string>
using namespace std;
class Cell{
    public:
        bool alive;
        Cell(bool f){
            alive=f;
        }
        void display(){
            if(alive){
                cout<<'#';
            }else{
                cout<<'.';
            }
        }

};
int rows;
int cols;
int neighbors(vector<vector<Cell>> &grid,int x,int y){
    int count=0;
    for(int i=x-1;i<x+2;i++){
        for(int j=y-1;j<y+2;j++){
            if(i==x && j==y) continue;
            if(i<0 || j<0 || j>cols-1 || i>rows-1) continue;

            if(grid[i][j].alive==true){
                count++;
            }
        }
    }
    return count;
}
void nextRun(vector<vector<Cell>> &grid){
    vector<vector<Cell>> temp=grid;
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            int num=neighbors(grid,i,j);
            if(num<2 && grid[i][j].alive==true){
                temp[i][j].alive=false;
            }else if(num>3 && grid[i][j].alive==true){
                temp[i][j].alive=false;
            }else if(num==3 && grid[i][j].alive==false){
                temp[i][j].alive=true;
            }
        }
    }
    grid=temp;
}
int getLive(vector<vector<Cell>> &grid){
    int n=0;
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            if(grid[i][j].alive){
                n++;
            }
            
        }
    }
    return n;
}
int main(){
    int times;
    int init_live=0;
    int peak_live=0;
    int now_live=0;
    cin>>rows;
    if(rows<=0) {cout<<"Invalid Value of Row.Rerun.."<<endl; return 0;}
    cin>>cols;
    if(cols<=0) {cout<<"Invalid Value of Column.Rerun.."<<endl; return 0;}
    cin>>times;
    if(times<0) {
    cout<<"Invalid Value of Time. Rerun.."<<endl;
    return 0;
}
    vector<vector<Cell>> grid;
    for(int i=0;i<rows;i++){
        vector<Cell> rowCells;
        string roww;
        cin>>roww;
        if(roww.length()!=cols){
            cout<<"Invalid Input Grid. Rerun.."<<endl;
            return 0;
        }
        for(int j=0;j<cols;j++){
            if(roww[j]=='#'){
                Cell c(true);
                rowCells.push_back(c);
            }else if(roww[j]=='.'){
                Cell c(false);
                rowCells.push_back(c);
            }else{
                cout<<"Invalid Input Grid. Rerun.."<<endl;
                return 0;
            }
            
        }
        grid.push_back(rowCells);
    }
    init_live=getLive(grid);
    peak_live=init_live;
    cout<<"Initial Population: "<<init_live<<endl;
    for(int i=0;i<times;i++){
        nextRun(grid);
        int temp=getLive(grid);
        if(temp>peak_live){
            peak_live=temp;
        }
    }
    now_live=getLive(grid);
    cout<<"Final Population: "<<now_live<<endl;
    cout<<"Peak Population: "<<peak_live<<endl;
    cout<<"Final Grid: "<<endl;
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            grid[i][j].display();
            
        }
        cout<<"\n"; 
    }
   
    return 0;
}