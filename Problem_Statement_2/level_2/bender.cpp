#include<iostream>
#include<string>
#include<vector>
#include"bender.hpp"
int round(float n);
int critCount=0;
int eff=0;
extern int randInt(int start,int end);
Bender::Bender(std::string n,std::string e,int hp_,int atk_,int def_,int spd,Move m[]){
    name=n;
    element=e;
    hp=hp_;
    atk=atk_;     
    def=def_;
    speed=spd;
    hpM=hp_;
    for(int i=0;i<4;i++){
        moves[i]=m[i];      //Could I improve this?
    }
}
void Bender::displayStats(){
    std::cout<<name<<" ("<<element<<") - HP: "<<hp<<"/"<<hpM<<", Attack: "<<atk;
    std::cout<<", Defense: "<<def<<", Speed: "<<speed<<std::endl;

}
int Bender::weak(Bender &p1,Bender &p2){
    std::vector<std::vector<std::string>> chart={
        {"Water","Fire"},{"Fire","Air"},{"Air","Earth"},{"Earth","Water"}
    };
    
        for(int i=0;i<chart.size();i++){
            if(p1.element==chart[i][0] && p2.element==chart[i][1]){
                return 0;
            }else if(p2.element==chart[i][0] && p1.element==chart[i][1]){
                return 2;
            }
        }
        return 1;
}
void Bender::calcPower(Bender &enemy){
    int w1=weak(*this,enemy);
    if(w1==0){
        this->atk*=2;
    }
    else if(w1==2) this->atk*=0.5;

    
}
void Bender::attack(Bender &enemy,int index){
    std::cout<<name<<" used "<<moves[index].name<<"!"<<std::endl;
    if(weak(*this,enemy)==2){
        std::cout<<"Not very effective... ("<<this->element<<" is weak against "<<enemy.element<<")"<<std::endl;
    }else if(weak(*this,enemy)==0){
        eff++;
        std::cout<<"Super Effective! ("<<this->element<<" is strong against "<<enemy.element<<")"<<std::endl;
    }
    float temp = (atk * moves[index].power) / enemy.def;     //calculate damage
    if(randInt(1,10)==1){
        critCount++;
        std::cout<<"CRITICAL HIT!!"<<std::endl;
        temp*=2;
    }
    int damage=round(temp);
    if(!enemy.isFainted()){
        enemy.hp-=damage;              //decrease damage if not fainted
        if(enemy.hp<0){
            enemy.hp=0;
        }
    }

    
    std::cout<<enemy.name<<" took "<<damage<<" damage!"<<std::endl;
}
bool Bender::isFainted(){
    return (hp<=0);
}

int round(float n){
    return (n-int(n)<0.5) ?  int(n) :  int(n)+1;        //First time using ternary operator ^_^
}