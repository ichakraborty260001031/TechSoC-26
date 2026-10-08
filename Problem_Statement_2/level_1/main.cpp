#include<iostream>
#include"bender.hpp"
//Moves data(Might try making a spreadsheet for this)
//------Move Data, like the Names and Powers are AI generated--------
Move move_data[40]={
    {"Ember Strike", 40},
    {"Flame Jab", 50},
    {"Fire Breath", 65},
    {"Searing Kick", 75},
    {"Blazing Blitz", 85},
    {"Fireball", 90},
    {"Inferno Blast", 100},
    {"Heatwave", 110},
    {"Volcano Eruption", 125},
    {"Supernova", 135},
    {"Pebble Throw", 35},
    {"Rock Smash", 50},
    {"Mud Slap", 55},
    {"Boulder Toss", 70},
    {"Stone Spike", 80},
    {"Seismic Slam", 90},
    {"Earth Pillar", 100},
    {"Fissure Strike", 110},
    {"Rockslide Avalanche", 120},
    {"Tectonic Shatter", 130},
    {"Water Whip", 40},
    {"Aqua Jet", 50},
    {"Bubble Beam", 65},
    {"Torrent Slash", 75},
    {"Tidal Surge", 85},
    {"Ice Blade", 90},
    {"Frostbite", 95},
    {"Hydro Pump", 110},
    {"Tsunami Blast", 120},
    {"Ocean Wrath", 130},
    {"Gust Slash", 35},
    {"Wind Cutter", 50},
    {"Gale Force", 60},
    {"Air Blade", 70},
    {"Vacuum Strike", 80},
    {"Vortex Blast", 90},
    {"Cyclone Burst", 100},
    {"Tempest Slash", 110},
    {"Hurricane Strike", 120},
    {"Tornado Shatter", 130}
};
int main() {
    //Note to self:- 0 to 9:Fire, 10 to 19: Earth
    //20 to 29: Water, 30 to 39: Air
    Move water_moves[4] = {
        move_data[22],move_data[26],move_data[28],move_data[21]
    };
    Move fire_moves[4] = {
        move_data[2],move_data[1],move_data[0],move_data[5]
    };

    Bender player1("Drowner", "Water", 100, 58, 38, 88, water_moves);
    Bender player2("Aang","Fire",92,50,45,60,fire_moves);
    player1.displayStats();
    player2.displayStats();

    player1.attack(player2,0);
    player2.displayStats();

    std::cout<<"Mira fainted: ";
    player2.isFainted() ? std::cout<<"True" : std::cout<<"False";

    return 0;
}