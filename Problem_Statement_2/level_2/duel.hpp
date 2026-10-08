#include<iostream>
#include<string>
#include<vector>
#include"bender.hpp"
#pragma once
class Duel{
    public:
        Bender &player1;
        Bender &player2;
        int turns;
        bool player1Turn;
        Duel(Bender &p1,Bender &p2);
        void getTurn();
        void play();
        void gameOver();
};