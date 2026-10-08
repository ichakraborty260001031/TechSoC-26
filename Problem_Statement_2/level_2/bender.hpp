#include<iostream>
#include<string>
#include<vector>
#pragma once
//Bender class
struct Move{
    std::string name;
    int power;
};

class Bender{
    public:     
        //Had no idea what should be private, so everything is public
        std::string name;
        std::string element;
        int hp,atk,def,speed;
        int hpM;
        Move moves[4];
        Bender(std::string n,std::string e,int hp_,int atk_,int def_,int spd,Move m[]);
        void displayStats();
        void attack(Bender &enemy,int index);
        bool isFainted();
        int weak(Bender &p1,Bender &p2);
        void calcPower(Bender &enemy);
};
