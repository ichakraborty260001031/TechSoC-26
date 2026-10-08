#include<iostream>
#include<string>
#include<vector>
#include"bender.hpp"
int round(float n);

Bender::Bender(std::string n,std::string e,int hp_,int atk_,int def_,int spd,Move m[]){
    name=n;
    element=e;
    hp=hp_;
    atk=atk_;     
    def=def_;
    speed=spd;
    for(int i=0;i<4;i++){
        moves[i]=m[i];      //Could I improve this?
    }
}
void Bender::displayStats(){
    std::cout<<name<<" ("<<element<<") - HP: "<<hp<<"/100, Attack: "<<atk;
    std::cout<<", Defense: "<<def<<", Speed: "<<speed<<std::endl;
    std::cout<<"Moves: ";
    for(Move m:moves){
        std::cout<<m.name<<" ("<<m.power<<"),";
    }
    std::cout<<std::endl<<std::endl;
}
void Bender::attack(Bender &enemy,int index){
    int damage = round((atk * moves[index].power) / enemy.def);     //calculate damage
    if(!enemy.isFainted()){
        enemy.hp-=damage;              //decrease damage if not fainted
        if(enemy.hp<0){
            enemy.hp=0;
        }
    }

//Format:- Kael used Ember Slash! 
//Mira took 52 damage!

    std::cout<<name<<" used "<<moves[index].name<<"!"<<std::endl;
    std::cout<<enemy.name<<" took "<<damage<<" damage!"<<std::endl<<std::endl;
}
bool Bender::isFainted(){
    return (hp<=0);
}

int round(float n){
    return (n-int(n)<0.5) ?  int(n) :  int(n)+1;        //First time using ternary operator ^_^
}