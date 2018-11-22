#include "json.hpp"
#include "PI.h"
#include <iostream>

using namespace std;
using namespace nlohmann;

int toInt(const char *);
void _error();

//defining file separator
char sep = '/';
#ifdef _WIN32
sep = '\\';
#endif

int main() {
    //this is necessary to catch unexpected exceptions
    //ofstream output, debug;
    //ifstream input;
    string filePath;
    json js;
    PI inventory;
    vector<pair<int, int> > cards;
    const vector<string> unhandle = {
            "",
            "Board",
            "Token",
            "Superpower",
            "Hero",
            "Cheats",
            "Blank",
            "cheats"
    };

    /*const vector<pair<string, int>> heroes = {
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
    };*/
    puts("PI Cards Helper made by H3x4n1um version 3.0.0");
    puts("Credits: nlohmann for his awesome JSON parser");
    puts("Note: Currently, this tool create the PI with all cards\n");
    printf(R"(Enter "cards.json" (or "cards.txt") file path: )");
    getline(cin, filePath);
    try {
        ifstream input;
        input.open(filePath);
        input >> js;
        //input.close();
    }
    catch (invalid_argument& e) {
        _error();
        return 1;
    }
    catch (exception& e) {
        //there are OSes that, if you enter an empty argument, will throw an exception unrelated to invalid_argument
        //fix it
        cerr << "\nOh, so you're just messing around...\n";
        cin.get();
        return 1;
    }
    for (auto i = static_cast<unsigned int>(filePath.size())-1; i >= 0; --i) {
        if (filePath[i] == sep) {
            filePath = filePath.substr(0, i + 1);
            break;
        }
    }
    {
        //RAII - resource Acquisition Is Initialization (test)
        ofstream debug;
        debug.open(filePath + "PI_Cards_Helper_debug.log");
        try {
            for (auto i : js.get<map<string, json> >()) {
                if (i.second.at("set").is_string()) {
                    auto temp = i.second.at("set").get<string>();
                    if (find(unhandle.begin(), unhandle.end(), temp) == unhandle.end()) {
                        debug << i.first << " " << temp << endl;
                        cards.emplace_back(toInt(i.first.c_str()), 4);
                    }
                }
            }
        }
        catch (out_of_range& e) {
            _error();
            return 1;
        }
    }

    //inventory.setHeroes(heroes);
    inventory.setCards(cards);
    inventory.write(filePath + "PlayerInventoryAllCards");
    puts("\nDone!\n");
    cin.get();
    return 0;
}

int toInt(const char * str) {
    char* end;
    long conv = strtol(str, &end, 10);
    if (!*end) {
        return static_cast<int>(conv);
    } else {
        printf("ERROR: Convert string to int failed");
        return 0;
    }
}

void _error() {
    cerr << '\n' << R"(Error! "cards.json" (or "cards.txt") not found or not correct format!!!)" << "\n\n";
    cin.get();
}