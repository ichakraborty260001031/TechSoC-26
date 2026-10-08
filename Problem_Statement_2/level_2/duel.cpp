#include<iostream>
#include<string>
#include<vector>
#include<random>
#include"duel.hpp"
extern int critCount;
extern int eff;
int randInt(int start,int end);
Duel::Duel(Bender &p1,Bender &p2):player1(p1),player2(p2){
    player1Turn=true;
    turns=0;
}

void Duel::getTurn(){
    std::cout<<std::endl<<"=== DUEL BEGINS! ==="<<std::endl;
    std::cout<<player1.name<<" ("<<player1.element<<", HP: "<<player1.hp<<"/"<<player1.hpM;
    std::cout<<") VS "<<player2.name<<" ("<<player2.element<<", HP: "<<player2.hp<<"/"<<player2.hpM<<")"<<std::endl<<std::endl;
    if(player1.speed>=player2.speed){
        player1Turn=true;
        std::cout<<player1.name<<" goes first! (Speed: "<<player1.speed<<" vs "<<player2.speed<<")"<<std::endl<<std::endl;
    }else{
        player1Turn=false;
        std::cout<<player2.name<<" goes first! (Speed: "<<player2.speed<<" vs "<<player1.speed<<")"<<std::endl;
    }
    
}
void Duel::play(){
    player1.calcPower(player2);
    player2.calcPower(player1);
    while(!player1.isFainted() && !player2.isFainted()){
        turns++;
        if(player1Turn){
            std::cout<<"Turn "<<turns<<":";
            player1.attack(player2,randInt(0,3));
            player2.displayStats();
            std::cout<<std::endl;
            player1Turn=false;
        }else{
            std::cout<<"Turn "<<turns<<":";
            player2.attack(player1,randInt(0,3));
            player1.displayStats();
            std::cout<<std::endl;
            player1Turn=true;
        }
        
    }
    gameOver();
}
void Duel::gameOver(){
    std::string winner;
    if(player1.isFainted()){
        std::cout<<player1.name<<" fainted!"<<std::endl;
        std::cout<<"## "<<player2.name<<" wins the duel!"<<std::endl;
        winner=player2.name;
    }else{
        std::cout<<player2.name<<" fainted!"<<std::endl;
        std::cout<<"## "<<player1.name<<" wins the duel!"<<std::endl;
        winner=player1.name;
    }
    std::cout<<"Duel Summary: "<<std::endl;
    std::cout<<"- Winner: "<<winner<<std::endl;
    std::cout<<"- Turns: "<<turns<<std::endl;
    std::cout<<"- Critical Hits: "<<critCount<<std::endl;
    std::cout<<"- Super Effective Hits: "<<eff<<std::endl;
}
int randInt(int start,int end){
    static std::random_device rd;      //Learnt a new random implementation along the way!
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(start, end);
    return distrib(gen);
}