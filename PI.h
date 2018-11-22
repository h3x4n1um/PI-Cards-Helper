#include <utility>

#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

int int2RTONnum(int q), hexLength(int q);
//int RTONnum2int(int q)

class PI{
public:
    /*int read(){
        return 0;
    }; //will be implement in future lmao*/
    //then don't implement it, jesus christ
    void write(const string &path){
        ofstream output;
        output.open(path, ios::binary);
        auto heroes = allHeroes();
        //Cards
        for (auto i : cards){
            output.write(&CARD, 1);
            int id = int2RTONnum(i.first);
            int buffer = hexLength(id) + hexLength(i.second) + 2;
            output.write(reinterpret_cast<const char *> (&buffer), hexLength(buffer));
            output.write(reinterpret_cast<const char *> (&id), hexLength(id));
            output.write(&NUMBER, 1);
            output.write(reinterpret_cast<const char *> (&i.second), hexLength(i.second));
        }
        //Heroes
        for (auto i : heroes){
            output.write(&HERO, 1);
            int heroesLength = static_cast<int>(i.first.size());
            int buffer = hexLength(heroesLength) + heroesLength + 3;
            output.write(reinterpret_cast<const char *> (&buffer), hexLength(buffer));
            output.write(&CARD, 1); //lazy to make another const for 0xa;
            output.write(reinterpret_cast<const char *> (&heroesLength), hexLength(heroesLength));
            output.write(i.first.c_str(), i.first.size());
            output.write(&NUMBER, 1);
            output.write(reinterpret_cast<const char *> (&i.second), 1);
        }

        //test: Expecting ofstream "output" to self-destruct after this line
        // if not, change it back
    };
    /*void setHeroes(vector<pair<string, int>> heroes_list){
        heroes = std::move(heroes_list);
    };*/
    void setCards(vector<pair<int, int>> cards_list) {
        cards = std::move(cards_list);
    };
    vector<pair<string, int>> allHeroes() {
        auto heroes = {"Penelopea", "Sunflower", "NightCap", "Grass_Knuckles", "BetaCarrotina", "Spudow", "Rose",
                       "WallKnight", "Chomper", "Scortchwood", "Citron", "HugeGigantacus", "CptBrainz", "Professor",
                       "Disco", "BrainFreeze", "Cyborg", "Witch", "Impfinity", "Neptuna", "ZMech", "Gargantuar"};
        vector<pair<string, int>> rtn;
        for (auto hero : heroes) {
            rtn.emplace_back(hero, 1);
        }
        return rtn;
    }
    //are you sure these parts are needed?
    /*
    int setGems(int q){
        gems = q;
        return 0;
    };
    int setSparks(int q){
        sparks = q;
        return 0;
    };
    int setTickets(int q){
        tickets = q;
        return 0;
    };*/

private:
    const char CARD = 0xa;
    const char HERO = 0x12;
    const char NUMBER = 0x10;
    vector <pair <int, int> > cards; //the first will be card id and second is number of copies
    //vector <pair <string, int> > heroes; //list of hero codename
    //r u really sure?
    /*
    int gems;
    int sparks;
    int tickets;*/
};
