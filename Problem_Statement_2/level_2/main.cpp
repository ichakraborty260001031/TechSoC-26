#include<iostream>
#include"bender.hpp"
#include"duel.hpp"
//Moves data(Might try making a spreadsheet for this)
//------Move Data, like the Names and Powers are AI generated--------
Move move_data[40]={
    {"Ember Strike", 20},
{"Flame Jab", 25},
{"Fire Breath", 32},
{"Searing Kick", 37},
{"Blazing Blitz", 42},
{"Fireball", 45},
{"Inferno Blast", 50},
{"Heatwave", 55},
{"Volcano Eruption", 62},
{"Supernova", 67},

{"Pebble Throw", 17},
{"Rock Smash", 25},
{"Mud Slap", 27},
{"Boulder Toss", 35},
{"Stone Spike", 40},
{"Seismic Slam", 45},
{"Earth Pillar", 50},
{"Fissure Strike", 55},
{"Rockslide Avalanche", 60},
{"Tectonic Shatter", 65},

{"Water Whip", 20},
{"Aqua Jet", 25},
{"Bubble Beam", 32},
{"Torrent Slash", 37},
{"Tidal Surge", 42},
{"Ice Blade", 45},
{"Frostbite", 47},
{"Hydro Pump", 55},
{"Tsunami Blast", 60},
{"Ocean Wrath", 65},

{"Gust Slash", 17},
{"Wind Cutter", 25},
{"Gale Force", 30},
{"Air Blade", 35},
{"Vacuum Strike", 40},
{"Vortex Blast", 45},
{"Cyclone Burst", 50},
{"Tempest Slash", 55},
{"Hurricane Strike", 60},
{"Tornado Shatter", 65}
};
int main() {
    //Note to self:- 0 to 9:Fire, 10 to 19: Earth
    //20 to 29: Water, 30 to 39: Air
    Move air_moves[4] = {
        move_data[32],move_data[36],move_data[38],move_data[31]
    };
    Move water_moves[4] = {
        move_data[22],move_data[21],move_data[20],move_data[25]
    };

    Bender player1("Bayu", "Air", 100, 58, 70, 52, air_moves);
    Bender player2("Jal","Water",92,50,80,60,water_moves);
    player1.displayStats();
    player2.displayStats();
    Duel game(player1,player2);
    game.getTurn();
    game.play();

    return 0;
}