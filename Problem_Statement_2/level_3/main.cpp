//TODO

//After game add newlinw
//Dont display stats everytime
//Add budget system
//Allow to choose move


//Libraries
#include<iostream>
#include<utility>
#include<fstream>
#include<unordered_map>
#include<thread>
#include<chrono>
#include"bender.hpp"
#include"duel.hpp"

//Variables from Other Files
extern int gameCount;
extern int turnCount;
extern int critCount;
extern int effCount;
extern int randInt(int start,int end);
//Function Declarations and Global Variables
std::vector<Move> move_data;
template <typename T>
void shuffle(std::vector<T> &players);

template <typename T_>
T_ input(std::string message);

void tournament(std::string name,std::vector<Bender> players);
bool announced=false;
int choice,diff;
void getData();

Move selectedMoves[4];
void grantMoves(std::string element);
Bender assignEnemy(std::string element, int diff);

int main() {
    getData();
    //Note to self:- 0 to 9:Fire, 10 to 19: Earth
    //20 to 29: Water, 30 to 39: Air
    //Introductary Messages
    std::cout<<"***WELCOME TO BENDER MANAGER!!***"<<std::endl;
    std::cout<<"Plan, Plan and Win!"<<std::endl<<std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    std::cout<<"SELECT MODE:"<<std::endl;
    std::cout<<"-Automatic Bender Tournament (Choose 0)"<<std::endl;
    std::cout<<"-Play Against AI (Choose 1)"<<std::endl;
    std::cout<<"-Quit (Any other Number)"<<std::endl<<std::endl;
    choice=input<int>("Enter Your Choice");
    if(choice==0){      //TOURNAMENT MODE

        //Randomly selecting moves for players, need a better method for players more than 4
        Move air_moves[4] = {
            move_data[randInt(30,31)],move_data[randInt(32,33)],move_data[randInt(34,36)],move_data[randInt(37,39)]
        };
        Move water_moves[4] = {
            move_data[randInt(20,21)],move_data[randInt(22,23)],move_data[randInt(24,26)],move_data[randInt(27,29)]
        };
        Move fire_moves[4] = {
            move_data[randInt(0,1)],move_data[randInt(2,3)],move_data[randInt(4,6)],move_data[randInt(7,9)]
        };
        Move earth_moves[4] = {
            move_data[randInt(10,11)],move_data[randInt(12,13)],move_data[randInt(14,16)],move_data[randInt(17,19)]
        };

        Bender player1("Bayu", "Air", 100, 58, 70, 52, air_moves);
        Bender player2("Jal","Water",92,50,80,60,water_moves);
        Bender player3("Dharti", "Earth", 100, 58, 70, 52, earth_moves);
        Bender player4("Aang","Fire",92,50,80,60,fire_moves);
        std::vector<Bender> players={player1,player2,player3,player4};
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        tournament("ELEMENTAL ARENA CHAMPIONSHIP",players);     //Tournament Function handles the Rest
        std::this_thread::sleep_for(std::chrono::milliseconds(10000));

    }else if(choice==1){
        //Making a Custom Bender for The User(User cant use effects(Maybe we should change this))
        std::cout<<"**DIFFICULTY**"<<std::endl;
        std::cout<<"0. Easy"<<std::endl;
        std::cout<<"1. Medium"<<std::endl;
        std::cout<<"2. Hard"<<std::endl;
        diff=input<int>("What do you Choose?");
        std::string name=input<std::string>("Enter player name");
        std::string element=input<std::string>("Enter Element Type(Fire/Water/Air/Earth)");
        if(element!="Fire" && element!="Water" && element!="Air" && element!="Earth"){
            std::cout<<"Element doesn't exist. Defaulting to Fire..."<<std::endl;   //Maybe I can add error handling here
            element="Fire";
        }
        grantMoves(element);
        Bender player(name,element,100, randInt(50,70), randInt(60,80),randInt(52,80),selectedMoves);
        player.displayStats();
        std::cout<<"Finding Enemy..."<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        Bender enemy=assignEnemy(element,diff);
        std::cout<<"Enemy Assigned!--"<<std::endl;
        enemy.displayStats();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout<<"Starting Match.."<<std::endl;
        Duel game(player,enemy);
        std::cout<<"New Match: "<<player.name<<" VS "<<enemy.name<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        game.getTurn();
        game.play();      //Match Starts,Yayy
    }
    return 0;
}

void tournament(std::string name,std::vector<Bender> players){
    if(players.size()<2 ||(players.size()&(players.size()-1))!=0){  //Check if players are a valid pow of 2
        std::cout<<"Tournament must have 2^n participants."<<std::endl;
        return;
    }

    int matchCount=1;   //Keeps Track of the Matches per Unit
    if(!announced){
        std::cout<<"==##"<<name<<"##=="<<std::endl;
        std::cout<<"Participants: "<<players.size()<<" Benders"<<std::endl<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        for(Bender p:players){
            p.displayStats();
        }
        std::cout<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout<<"***TOURNAMENT BRACKET***"<<std::endl;
        announced=true; //Again a Wierd Way , but Works
    }
    shuffle(players);   //Shuffles the Players in Random Order
    std::vector<Bender> winners;
    static std::unordered_map<std::string,int> rank_list;
    if(players.size()==16){
        //Unit Display
            std::cout<<"==##ROUND OF 16##=="<<std::endl<<std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        }else if(players.size()==8){
            std::cout<<"==##ROUND OF 8##=="<<std::endl<<std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        }else if(players.size()==4){
            std::cout<<"==##SEMI FINALS!!##=="<<std::endl<<std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        }else if(players.size()==2){
            std::cout<<"==##FINALS!!!##=="<<std::endl<<std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        }
    for(int i=0;i<players.size();i+=2){
        //Tournament Creates new Duels
        Duel game(players[i],players[i+1]); 
        std::cout<<"Match "<<matchCount<<": "<<players[i].name<<" VS "<<players[i+1].name<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        game.getTurn();
        Bender winner=game.play();
        matchCount++;
        winners.push_back(winner);
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
    if(players.size()==4){
        for(Bender p:players){
            rank_list.insert({p.name,3});   //Intialise top 4 to 3
        }
    }
    if(players.size()==2){
        for(Bender p:players){
            rank_list[p.name]=2;    //Update finalists to 2
        }
    }
    if(winners.size()==1){
        rank_list[winners[0].name]=1;
    }
    if(winners.size()>1){
        tournament(name,winners);   //Call Tournament Recursively for Each Pool till You get a winner
    }else{
        //Announce Winner and Stats
        std::cout<<std::endl<<"***"<<winners[0].name<<" WINS THE "<<name<<"!***"<<std::endl<<std::endl;
        std::cout<<"TOURNAMENT SUMMARY: "<<std::endl;
        std::cout<<"- Champion: "<<winners[0].name<<std::endl;
        std::cout<<"-Total Games: "<<gameCount<<std::endl;
        std::cout<<"- Turns: "<<turnCount<<std::endl;
        std::cout<<"- Critical Hits: "<<critCount<<std::endl;
        std::cout<<"- Super Effective Hits: "<<effCount<<std::endl;
        struct Rank{
            int rank;
            std::string name;
        };
        std::vector<Rank> list;
        for(auto&[name,rank]:rank_list){
            list.push_back({rank,name});
        }
        for(int i=1;i<=3;i++){
            for(Rank r:list){
            if(r.rank==i){
                std::cout<<i<<". "<<r.name<<std::endl;
            }
        }
        }
    }
}

//Shuffle function for all datatypes
template <typename T>
void shuffle(std::vector<T> &players){
    for(int i=players.size()-1;i>0;--i){
        int j=randInt(0,i);
        std::swap(players[i],players[j]);
    }
};
//Function to read move information from spreadsheet
void getData(){
    std::ifstream file;
    std::string line="";
    file.open("data.csv");
    std::getline(file,line);
    while(getline(file,line)){
        int location=line.find(',');
        int location2=line.find(',',location+1);
        int location3=line.find(',',location2+1);
        std::string name=line.substr(0,location);
        int pow=std::stoi(line.substr(location+1,location2-location-1));
        std::string effect=line.substr(location2+1,location3-location2-1);
        int heal=std::stoi(line.substr(location3+1));
        move_data.push_back({name,pow,effect,heal});
    }
    file.close();
}
//Custom input function(python inspired)
template <typename T_>
T_ input(std::string message){
    T_ var;
    std::cout<<message<<": ";
    std::cin>>var;
    return var;
}
//Function to grant moves as the user chooses
void grantMoves(std::string element) {
    int off=0;
    if(element=="Fire") {
        off=0;
    }else if(element=="Earth") {
        off=10;
    }else if(element=="Water") {
        off=20;
    }else if(element=="Air") {
        off=30;
    }

    std::cout<<std::endl<<"===Move Selection For " << element << " ===" << std::endl;
    //Tier to classify low power and high power moves
    struct Tier {
        std::string name;
        int start_off;
        int end_off;
    };

    Tier tiers[4] = {{"Lowest Power Move(Choose 1 of 3)", 0, 2},{"Medium-Low Power Move(Choose 1 of 3)", 3, 5},{"Medium-High Power Move(Choose 1 of 2)", 6, 7},{"High Power Move(Choose 1 of 2)", 8, 9}};
    std::cout<<std::endl;
    for (int t=0;t<4;++t) {
        std::cout<<"**Tier " << (t + 1) << ": " << tiers[t].name << "**" << std::endl;
        int option_count = 1;
        int start_idx=off+tiers[t].start_off;
        int end_idx=off+tiers[t].end_off;
        for (int i = start_idx; i <= end_idx; ++i) {
            std::cout<<option_count<<". "<<move_data[i].name<<" (Power: "<<move_data[i].power<<")"<<std::endl;
            option_count++;
        }

        int choice_ = 0;
        while (true) {
            choice_ =input<int>("Select move option number");
            if (choice_>=1 && choice_<=(end_idx-start_idx+1)) {
                break;
            }
            std::cout<<"Invalid choice! Please select a valid option number."<<std::endl;
        }
        int selected_index=start_idx+(choice_-1);
        selectedMoves[t]=move_data[selected_index];
        
    }
}
Bender assignEnemy(std::string element,int diff){
    //THE WORST POSSIBLE PROGRAMMING APPROACH USED(Deadlines -_-)
    Move earth_moves[4]={move_data[randInt(10, 12)],
                        move_data[randInt(13, 15)],
                        move_data[randInt(16, 17)],
                        move_data[randInt(18, 19)]};
            Move fire_moves[4]={move_data[randInt(0, 2)],
                        move_data[randInt(3, 5)],
                        move_data[randInt(6, 7)],
                        move_data[randInt(8, 9)]};
            Move air_moves[4]={move_data[randInt(30, 32)],
                        move_data[randInt(33, 35)],
                        move_data[randInt(36, 37)],
                        move_data[randInt(38, 39)]};
            Move water_moves[4]={move_data[randInt(20, 22)],
                        move_data[randInt(23, 25)],
                        move_data[randInt(26, 27)],
                        move_data[randInt(28, 29)]};
            int moveI=0;
    if(diff==0){
            //No Special Moves
            //Give Neutral or Weaker Enemy
            std::string e_element;
            std::string name;
            int t_num=randInt(1,10);
            if(t_num>8){    //20% chance , give neutral
                if(element=="Fire"){
                    e_element="Earth";
                    name="Rock-bot";
                }else if(element=="Earth"){
                    e_element="Fire";
                    name="Aang-bot";
                }else if(element=="Air"){
                    e_element="Water";
                    name="Drowner";
                }else if(element=="Water"){
                    e_element="Air";
                    name="Blower";
                }
            }else{
                if(element=="Fire"){
                    e_element="Air";
                    name="Blower";
                }else if(element=="Earth"){
                    e_element="Water";
                    name="Drowner";
                }else if(element=="Air"){
                    e_element="Earth";
                    name="Rock-bot";
                }else if(element=="Water"){
                    e_element="Fire";
                    name="Aang-bot";
                }
            }
            if(e_element=="Fire"){
                return Bender(name,e_element,randInt(90,100),randInt(50,65),randInt(60,75),randInt(52,80),fire_moves);       
            }else if(e_element=="Water"){
                return Bender(name,e_element,randInt(90,100),randInt(50,65),randInt(60,75),randInt(52,80),water_moves);       
            }else if(e_element=="Earth"){
                return Bender(name,e_element,randInt(90,100),randInt(50,65),randInt(60,75),randInt(52,80),earth_moves);       
            }else if(e_element=="Air"){
                return Bender(name,e_element,randInt(90,100),randInt(50,65),randInt(60,75),randInt(52,80),air_moves);       
            }
        }else if(diff==1){
            //Low Special Moves Chance
            //30% Weak, 40% Neutral 30% Strong
            std::string e_element;
            std::string name;
            int t_num=randInt(1,10);
            if(t_num<=4){    //40% chance , give neutral
                if(element=="Fire"){
                    e_element="Earth";
                    name="Rock-bot";
                }else if(element=="Earth"){
                    e_element="Fire";
                    name="Aang-bot";
                }else if(element=="Air"){
                    e_element="Water";
                    name="Drowner";
                }else if(element=="Water"){
                    e_element="Air";
                    name="Blower";
                }
            }else if(t_num>=5 && t_num<=7){     //30% chance,give weak
                if(element=="Fire"){
                    e_element="Air";
                    name="Blower";
                }else if(element=="Earth"){
                    e_element="Water";
                    name="Drowner";
                }else if(element=="Air"){
                    e_element="Earth";
                    name="Rock-bot";
                }else if(element=="Water"){
                    e_element="Fire";
                    name="Aang-bot";
                }
            }else{      //Stronger Enemy
                if(element=="Fire"){
                    e_element="Water";
                    name="Drowner";
                }else if(element=="Earth"){
                    e_element="Air";
                    name="Blower";
                }else if(element=="Air"){
                    e_element="Fire";
                    name="Aang-bot";
                }else if(element=="Water"){
                    e_element="Earth";
                    name="Rock-bot";
                }
            }
            if(e_element=="Fire"){
                return Bender(name,e_element,randInt(95,100),randInt(60,70),randInt(62,80),randInt(52,80),fire_moves);       
            }else if(e_element=="Water"){
                return Bender(name,e_element,randInt(95,100),randInt(60,70),randInt(62,80),randInt(52,80),water_moves);       
            }else if(e_element=="Earth"){
                return Bender(name,e_element,randInt(95,100),randInt(60,70),randInt(62,80),randInt(52,80),earth_moves);       
            }else if(e_element=="Air"){
                return Bender(name,e_element,randInt(95,100),randInt(60,70),randInt(62,80),randInt(52,80),air_moves);       
            }
        }
        else if(diff==2){
            //High Special Moves Chance
            //70% Strong 30%Neutral
            std::string e_element;
            std::string name;
            
            Move moves[4];
            int t_num=randInt(1,10);
            //Note to self:- 0 to 9:Fire, 10 to 19: Earth
    //20 to 29: Water, 30 to 39: Air
            if(t_num<=3){    //40% chance , give neutral
                if(element=="Fire"){
                    e_element="Earth";
                    name="Rock-bot";
                    
                }else if(element=="Earth"){
                    e_element="Fire";
                    name="Aang-bot";
                }else if(element=="Air"){
                    e_element="Water";
                    name="Drowner";
                }else if(element=="Water"){
                    e_element="Air";
                    name="Blower";
                }
            }else{      //Stronger Enemy
                if(element=="Fire"){
                    e_element="Water";
                    name="Drowner";
                }else if(element=="Earth"){
                    e_element="Air";
                    name="Blower";
                }else if(element=="Air"){
                    e_element="Fire";
                    name="Aang-bot";
                }else if(element=="Water"){
                    e_element="Earth";
                    name="Rock-bot";
                }
            }
            if(e_element=="Fire"){
                return Bender(name,e_element,randInt(95,100),randInt(60,70),randInt(62,80),randInt(52,80),fire_moves);       
            }else if(e_element=="Water"){
                return Bender(name,e_element,randInt(95,100),randInt(60,70),randInt(62,80),randInt(52,80),water_moves);       
            }else if(e_element=="Earth"){
                return Bender(name,e_element,randInt(95,100),randInt(60,70),randInt(62,80),randInt(52,80),earth_moves);       
            }else if(e_element=="Air"){
                return Bender(name,e_element,randInt(95,100),randInt(60,70),randInt(62,80),randInt(52,80),air_moves);       
            }
        }
}