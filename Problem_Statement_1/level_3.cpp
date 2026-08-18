//Libraries

#include<iostream>
#include<vector>
#include<string>
#include <iomanip>
#include<thread>
#include<chrono>
using namespace std;

//An Useless Cell Class

class Cell{
    public:
        bool alive;
        Cell(bool f){
            alive=f;
        }
        //Operator Function used for simple Equality Later
        bool operator==(const Cell& other) const {
            return alive == other.alive;
        }
        //Display Cell on Screen
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
vector<vector<vector<Cell>>> history;   //Didnt Find Anything More Optimised..

// Function to Count Neighbours

int neighbors(vector<vector<Cell>> &grid,int x,int y,string mode){
    int count=0;
    if(mode=="toroidal"){
    for(int i=-1;i<=1;i++){
    for(int j=-1;j<=1;j++){
        if(i==0 && j==0) continue;
        int X = (x+i+rows) % rows;
        int Y = (y+j+cols) % cols;

        if(grid[X][Y].alive){
            count++;
            }
        }
    }
}else {
    for(int i=x-1;i<x+2;i++){
        for(int j=y-1;j<y+2;j++){
            if(i==x && j==y) continue;
            if(i<0 || j<0 || j>cols-1 || i>rows-1) continue;

            if(grid[i][j].alive==true){
                count++;
            }
        }
    }
}
    return count;
}

//Generating Next Frame

void nextRun(vector<vector<Cell>> &grid,string mode){
    vector<vector<Cell>> temp=grid;
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            int num=neighbors(grid,i,j,mode);
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
    history.push_back(grid);
}

//Getting Total Alive 

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

//Classify Function

vector<int> classify(){
   for(int i=0;i<history.size();i++){
    for(int j=i+1;j<history.size();j++){
        if(history[j]==history[i]){
            return {j-i,i,j};
        }
    }
   }
   return {0,-1,-1};
}
//CALCULATING THE BOX AND COM STUFF
vector<double> getMetrics(vector<vector<Cell>> &grid){
    double minI=rows+1;
    double minJ=cols+1;
    double maxI=-1;
    double maxJ=-1;
    double xcom=0;
    double ycom=0;
    if(getLive(grid)==0){
        return {minI,minJ,maxI,maxJ,-1,-1};
    }
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            if(grid[i][j].alive){
                xcom+=i;
                ycom+=j;
                if(minI>i){
                    minI=i;
                }
                if(minJ>j){
                    minJ=j;
                }
                if(maxI<i){
                    maxI=i;
                }
                if(maxJ<j){
                    maxJ=j;
                }
            }
        }
    }
    xcom=xcom/getLive(grid);
    ycom=ycom/getLive(grid);
    return {minI,minJ,maxI,maxJ,xcom,ycom};
}

//Function to Control Animation
void controlAnimation(vector<vector<Cell>> &grid,int times){
    for(int i=0;i<times;i++){
        cout<<"Generation: "<<i<<" ";
        cout<<"Population: "<<getLive(grid)<<endl;
        for(int j=0;j<rows;j++){
            for(int k=0;k<cols;k++){
                grid[j][k].display();
            }
            cout<<endl;
        }
        this_thread::sleep_for(chrono::milliseconds(50));
        system("cls");
        nextRun(grid,"animate");
    }
}
//MAIN
int main(){
    //Variables Initialised
    int dead_at=-1;
    int times;
    int init_live=0;
    int peak_live=0;
    int now_live=0;
    string mode;

    //Inputs with Error Handling..

    cin>>mode;
    if(mode==""){  cout<<"Please Specify Mode.Rerun.."<<endl;return 0;};
    
    cin>>rows;
    if(rows<=0) {cout<<"Invalid Value of Row.Rerun.."<<endl; return 0;}
    cin>>cols;
    if(cols<=0) {cout<<"Invalid Value of Column.Rerun.."<<endl; return 0;}
    if(mode!="classify"){
        cin>>times;
        if(times<0) {
        cout<<"Invalid Value of Time. Rerun.."<<endl;
        return 0;
        }
    }else{
        times=10;
    }
    vector<vector<Cell>> grid;  //The Real Game Interface
    //Initialising The Grid
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
    history.push_back(grid);
    peak_live=init_live;


    //ANIMATING 

    if(mode=="animate"){
        controlAnimation(grid,times);
    }

//Printing Intro Line Based on Command Choice

    if(mode=="toroidal"){
        cout<<"Mode: Toroidal"<<endl;
    }
    if(mode!="classify"){
        for(int i=0;i<times;i++){
            nextRun(grid,mode);
            int temp=getLive(grid);
            if(temp>peak_live){
                peak_live=temp;
        }
    }
}
    if(mode=="classify"){
        for(int i=0;i<times;i++){
            nextRun(grid,mode);
            int temp=getLive(grid);
            if(temp==0){
                dead_at=i+1;
                break;
            }
            if(temp>peak_live){
                peak_live=temp;
        }
    }
        vector<int> data=classify();
        //STILL LIFE
        if(dead_at!=-1){
            cout<<"Classification:Extinct"<<endl;
            cout<<"Extinction Step: "<<dead_at<<endl;
            cout<<"Final Population: 0"<<endl;
        }else if(data[0]==1){
            cout<<"Classification:Still Life"<<endl;
            cout<<"Stable at Step: "<<data[1]<<endl;
            cout<<"Period: 1"<<endl;
            cout<<"Population: "<<getLive(grid)<<endl;
        }else if(data[0]==0){
            cout<<"Classification:Active"<<endl;
            now_live=getLive(grid);
            cout<<"Initial Population: "<<init_live<<endl;
            cout<<"Final Population: "<<now_live<<endl;
            cout<<"Peak Population: "<<peak_live<<endl;
        }else if(data[0]>1){
            cout<<"Classification: Oscillator"<<endl;
            cout<<"Period: "<<data[0]<<endl;
            cout<<"First Repeat Step: "<<data[2]<<"( Matches Step "<<data[1]<<")"<<endl;
            cout<<"Population: "<<getLive(grid)<<endl;
        }
        return 0;
    }
    if(mode=="metrics"){
        vector<double> metData=getMetrics(grid);
        cout<<"Live Cells: "<<getLive(grid)<<endl;
        //Order is minI,minJ,maxI,maxJ,xcom,ycom
        if(metData[2]!=-1){
            cout<<"Bounding Box: "<<(metData[2]-metData[0]+1)<<"x"<<(metData[3]-metData[1]+1);
            cout<<"(Rows: "<<metData[0]<<"-"<<metData[2]<<")";
            cout<<"(Cols: "<<metData[1]<<"-"<<metData[3]<<")"<<endl;
        }else{
            cout<<"Bounding Box: 0x0"<<endl;
        }
        if(metData[4]==-1){
            cout<<"Center of Mass: N/A"<<endl;
        }
        else{
            cout<<"Center of Mass: ("<<fixed<<setprecision(2)<<metData[4]<<" , "<<fixed<<setprecision(2)<<metData[5]<<")"<<endl;
        }
      
    }
    now_live=getLive(grid);
    if(mode!="metrics" && mode!="animate"){
    cout<<"Initial Population: "<<init_live<<endl;
    cout<<"Final Population: "<<now_live<<endl;
    cout<<"Peak Population: "<<peak_live<<endl;
    cout<<"Final Grid: "<<endl;
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            grid[i][j].display();
            
        }
        cout<<"\n"; 
    }
}
    
    return 0;
}