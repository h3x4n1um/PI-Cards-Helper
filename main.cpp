#include "json.hpp"
#include "PI.h"
#include <iostream>

using namespace std;
using namespace nlohmann;

const vector <string> unhandle = {
    "",
    "Board",
    "Token",
    "Superpower",
    "Hero",
    "Cheats",
    "Blank",
    "cheats"
};

const vector <pair <string, int> > heroes = {
    make_pair("Penelopea", 1),
    make_pair("Sunflower", 1),
    make_pair("NightCap", 1),
    make_pair("Grass_Knuckles", 1),
    make_pair("BetaCarrotina", 1),
    make_pair("Spudow", 1),
    make_pair("Rose", 1),
    make_pair("WallKnight", 1),
    make_pair("Chomper", 1),
    make_pair("Scortchwood", 1),
    make_pair("Citron", 1),
    make_pair("HugeGigantacus", 1),
    make_pair("CptBrainz", 1),
    make_pair("Professor", 1),
    make_pair("Disco", 1),
    make_pair("BrainFreeze", 1),
    make_pair("Cyborg", 1),
    make_pair("Witch", 1),
    make_pair("Impfinity", 1),
    make_pair("Neptuna", 1),
    make_pair("ZMech", 1),
    make_pair("Gargantuar", 1)
};

void _error(){
    cerr << '\n' << R"(Error! "cards.json" (or "cards.txt") not found or not correct format!!!)" << "\n\n";
    system("pause");
}

json js;
ifstream input;
ofstream output, debug;
PI inventory;
vector <pair <int, int> > cards;

int main(){
    puts("PI Cards Helper made by H3x4n1um version 3.0.0");
    puts("Credits: nlohmann for his awesome JSON parser");
    puts("Note: Currently, this tool create the PI with all cards\n");
    printf(R"(Enter "cards.json" (or "cards.txt") file path: )");
    string filePath;
    filePath = R"(C:\Users\boly4\OneDrive\Games\Unity\PvZ Heroes\Beta\cards-CAB-9c7d1d782d8ce65074a2a14aa6e16aad-18366826355415369663.json)";
    //getline(cin, filePath);
    try{
        input.open(filePath);
        input >> js;
        input.close();
        for (int i = filePath.size() - 1; i >= 0; --i){
            if (filePath[i] == 0x5c){
                filePath = filePath.substr(0, i + 1);
                break;
            }
        }
    }
    catch (invalid_argument e){
        _error();
        return 1;
    }
    debug.open(filePath + "PI_Cards_Helper_debug.log");
    try{
        for (auto i : js.get<map <string, json> >()){
            if (i.second.at("set").is_string()){
                string temp = i.second.at("set").get<string>();
                if (find(unhandle.begin(), unhandle.end(), temp) == unhandle.end()){
                    debug << i.first << " " << temp << endl;
                    cards.push_back(make_pair(atoi(i.first.c_str()), 4));
                }
            }
        }
    }
    catch (out_of_range e){
        _error();
        return 1;
    }

    inventory.setHeroes(heroes);
    inventory.setCards(cards);

    output.open(filePath + "PlayerInventoryAllCards", ios::binary);
    inventory.write(output);
    output.close();
    debug.close();
    puts("\nDone!\n");
    system("pause");
    return 0;
}
