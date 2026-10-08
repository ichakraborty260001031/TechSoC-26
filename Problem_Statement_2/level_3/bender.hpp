#include<iostream>
#include<string>
#include<vector>
#pragma once
//Bender class
struct Move{
    std::string name;
    int power;
    std::string effect;
    int healAmount;
};
enum Status{
    none,
    burn,
    frozen,
    buried
};
class Bender{
    public:     
        //Had no idea what should be private, so everything is public
        std::string name;
        std::string element;
        int hp,atk,def,speed;
        int hpM;
        Move moves[4];
        Status status;
        int statusDuration;
        Bender(std::string n,std::string e,int hp_,int atk_,int def_,int spd,Move m[]);
        void displayStats();
        void displayHp();
        void attack(Bender &enemy,int index);
        void applyEffects(Bender &enemy,int index);
        void manageStatus();
        bool isFainted();
        int weak(Bender &p1,Bender &p2);
};
