#include<iostream>
#include<string>
#include<vector>
#include"bender.hpp"
int round(float n);
extern int critCount;
extern int effCount;
extern int randInt(int start,int end);

std::string statusName(Status status);
Bender::Bender(std::string n,std::string e,int hp_,int atk_,int def_,int spd,Move m[]){
    name=n;
    element=e;
    hp=hp_;
    atk=atk_;     
    def=def_;
    status=none;
    statusDuration=0;
    speed=spd;
    hpM=hp_;
    for(int i=0;i<4;i++){
        moves[i]=m[i];      
    }
}
void Bender::displayStats(){
    std::cout<<name<<" ("<<element<<") - HP: "<<hp<<"/"<<hpM<<", Attack: "<<atk;
    std::cout<<", Defense: "<<def<<", Speed: "<<speed<<std::endl;

}
void Bender::displayHp(){
    std::cout<<name<<" ("<<element<<") - HP: "<<hp<<"/"<<hpM<<std::endl;
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

void Bender::attack(Bender &enemy,int index){
    if(statusDuration!=0){
        statusDuration--;
    }
    if(status==none || status==burn){
        std::cout<<name<<" used "<<moves[index].name<<"!"<<std::endl;
        float temp = (atk * moves[index].power) / enemy.def;     //calculate primitive damage
        if(weak(*this,enemy)==2){
            std::cout<<"Not very effective... ("<<this->element<<" is weak against "<<enemy.element<<")"<<std::endl;
            temp*=0.5;
        }else if(weak(*this,enemy)==0){
            temp*=2;
            std::cout<<"Super Effective! ("<<this->element<<" is strong against "<<enemy.element<<")"<<std::endl;
            effCount++;
        }
        if(randInt(1,10)==1){
            std::cout<<"CRITICAL HIT!!"<<std::endl;
            critCount++;
            temp*=2;
        }
        applyEffects(enemy,index);
        if(enemy.status==burn){
            temp+=enemy.hpM*0.1;
            std::cout<<enemy.name<<" is Burning! Took 0.1 times extra Damage!"<<std::endl;
        }
        int damage=round(temp);
        if(!enemy.isFainted()){
            enemy.hp-=damage;              //decrease damage if not fainted
            if(enemy.hp<0){
                enemy.hp=0;
            }
        }

        
        std::cout<<enemy.name<<" took "<<damage<<" damage!"<<std::endl;
        
    }else if(status==buried || status==frozen){
        std::cout<<name<<" is "<<statusName(status)<<" and Can't Move!"<<std::endl;
    }
    
}
void Bender::applyEffects(Bender &enemy,int index){
    if(moves[index].effect=="burn"){
        enemy.status=burn;
        enemy.statusDuration=4;
        std::cout<<enemy.name<<" was burned!"<<std::endl;
    }else if(moves[index].effect=="frozen"){
        if(randInt(1,2)==1){        //50% Chance
            enemy.status=frozen;
            enemy.statusDuration=3;
            std::cout<<enemy.name<<" was frozen!"<<std::endl;
        }    
    }else if(moves[index].effect=="buried"){
        enemy.status=buried;
        enemy.statusDuration=randInt(2,4);
        std::cout<<enemy.name<<" was buried!"<<std::endl;
    }

    if(moves[index].healAmount>0){
        int oldHp=hp;
        hp+=moves[index].healAmount;
        if(hp>hpM){
            hp=hpM;
        }
        std::cout<<name<<" recovered "<<hp-oldHp<<" HP!"<<std::endl;
    }
}
void Bender::manageStatus(){
    if(statusDuration==0 && status!=none){
        if(status==frozen){
            std::cout<<name<<" breaks through the cold and strikes!"<<std::endl;
        }else if(status==burn){
            std::cout<<name<<" stopped burning!"<<std::endl;
        }else if(status==buried){
            std::cout<<name<<" breaks free from being buried!"<<std::endl;
        }
        status=none;
    }
}
bool Bender::isFainted(){
    return (hp<=0);
}

int round(float n){
    return (n-int(n)<0.5) ?  int(n) :  int(n)+1;        //First time using ternary operator ^_^
}
std::string statusName(Status status){
    if(status==none){
        return "normal";
    }else if(status==burn){
        return "burning";
    }else if(status==frozen){
        return "frozen";
    }else if(status==buried){
        return "buried";
    }
    return "normal";
}