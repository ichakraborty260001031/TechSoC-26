#include<iostream>
#include<string>
#include<vector>
#include<random>
#include<thread>
#include<chrono>
#include"duel.hpp"
int randInt(int start,int end);
int gameCount=0;
int turnCount=0;
int critCount=0;
int effCount=0;
extern int choice;
extern int diff;
Duel::Duel(Bender &p1,Bender &p2):player1(p1),player2(p2){
    player1Turn=true;
    turns=0;
}

void Duel::getTurn(){
    std::cout<<std::endl<<"=== DUEL BEGINS! ==="<<std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout<<player1.name<<" ("<<player1.element<<", HP: "<<player1.hp<<"/"<<player1.hpM;
    std::cout<<") VS "<<player2.name<<" ("<<player2.element<<", HP: "<<player2.hp<<"/"<<player2.hpM<<")"<<std::endl<<std::endl;
    player1.manageStatus();
    player2.manageStatus();
    if(player1.speed>=player2.speed){
        player1Turn=true;
        std::cout<<player1.name<<" goes first! (Speed: "<<player1.speed<<" vs "<<player2.speed<<")"<<std::endl<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    }else{
        player1Turn=false;
        std::cout<<player2.name<<" goes first! (Speed: "<<player2.speed<<" vs "<<player1.speed<<")"<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    }
    
}
Bender Duel::play(){
    gameCount++;
    while(!player1.isFainted() && !player2.isFainted()){
        turnCount++;
        turns++;
        player1.manageStatus();
        player2.manageStatus();
        if(player1Turn){
            std::cout<<"Turn "<<turns<<":";
            player1.attack(player2,randInt(0,3));
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            player2.displayHp();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            std::cout<<std::endl;
            player1Turn=false;
        }else{
            std::cout<<"Turn "<<turns<<":";
            //AI MODE
            if(choice==1 && diff!=0){
                if(diff==1 && randInt(1,2)==1){
                    player2.attack(player1, randInt(0, 3));
                }else{
                int healer=-1;
                int maxHeal=0;
                int finisher=-1;
                int maxPow=0;
                for(int i=0;i<4;i++){
                    if(player2.moves[i].healAmount>maxHeal){
                        maxHeal=player2.moves[i].healAmount;
                        healer=i;
                    }
                }
                for(int i=0;i<4;i++){
                    if(player2.moves[i].power>maxPow){
                        maxPow=player2.moves[i].power;
                        finisher=i;
                    }
                }
                if(player2.hp<30 && healer!=-1){
                    player2.attack(player1,healer);
                }else if(player1.hp<50 && finisher!=-1){
                    player2.attack(player1,finisher);
                }else if(player1.hp>60 || player2.hp<60){
                    std::vector<int> effMoves;
                    for(int i=0;i<4;i++) {
                        if(player2.moves[i].effect != "none"){
                            effMoves.push_back(i);
                        }
                    }
                    if(effMoves.size()!=0){
                        int index = effMoves[randInt(0,effMoves.size()-1)];
                        player2.attack(player1,index);
                    }else{
                        player2.attack(player1, randInt(0, 3));
                    }
                }else{
                    std::vector<int> nilMoves;
                    for(int i=0;i<4;i++) {
                        if(player2.moves[i].effect == "none"){
                            nilMoves.push_back(i);
                        }
                    }
                    if(nilMoves.size()!=0){
                        int index = nilMoves[randInt(0,nilMoves.size()-1)];
                        player2.attack(player1,index);
                    }else{
                        player2.attack(player1, randInt(0, 3));
                    }
                }
            }
            }else{
                player2.attack(player1,randInt(0,3));
            }
            player1.displayHp();
            std::cout<<std::endl;
            player1Turn=true;
        }
        
    }
    Bender winner=gameOver();
    return winner;
}
Bender Duel::gameOver(){
    if(player1.isFainted()){
        std::cout<<player1.name<<" fainted!"<<std::endl;
        std::cout<<"## "<<player2.name<<" wins the duel!"<<std::endl;
        Bender winner=player2;
        return winner;
    }else{
        std::cout<<player2.name<<" fainted!"<<std::endl;
        std::cout<<"## "<<player1.name<<" wins the duel!"<<std::endl;
        Bender winner=player1;
        return winner;
    }
}
int randInt(int start,int end){
    static std::random_device rd;      //Learnt a new random implementation along the way!
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(start, end);
    return distrib(gen);
}

