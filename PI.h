#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

int int2RTONnum(int q), RTONnum2int(int q), hexLength(int q);

class PI{
    public:
        int read(){
            return 0;
        }; //will be implement in future lmao
        int write(ofstream &output){
            //Cards
            for (auto i : cards){
                output.write(static_cast<const char *> (&CARD), 1);
                int id = int2RTONnum(i.first);
                int buffer = hexLength(id) + hexLength(i.second) + 2;
                output.write(reinterpret_cast<const char *> (&buffer), hexLength(buffer));
                output.write(reinterpret_cast<const char *> (&id), hexLength(id));
                output.write(static_cast<const char *> (&NUMBER), 1);
                output.write(reinterpret_cast<const char *> (&i.second), hexLength(i.second));
            }
            //Heroes
            for (auto i : heroes){
                output.write(static_cast<const char *> (&HERO), 1);
                int heroesLength = i.first.size();
                int buffer = hexLength(heroesLength) + heroesLength + 3;
                output.write(reinterpret_cast<const char *> (&buffer), hexLength(buffer));
                output.write(static_cast<const char *> (&CARD), 1); //lazy to make another const for 0xa;
                output.write(reinterpret_cast<const char *> (&heroesLength), hexLength(heroesLength));
                output.write(i.first.c_str(), i.first.size());
                output.write(static_cast<const char *> (&NUMBER), 1);
                output.write(reinterpret_cast<const char *> (&i.second), 1);
            }
            return 0;
        };
        int setHeroes(vector <pair <string, int> > heroes_list){
            heroes = heroes_list;
            return 0;
        };
        int setCards(vector <pair <int, int> > cards_list){
            cards = cards_list;
            return 0;
        };
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
        };

    private:
        const char CARD = 0xa;
        const char HERO = 0x12;
        const char NUMBER = 0x10;
        vector <pair <int, int> > cards; //the first will be card id and second is number of copies
        vector <pair <string, int> > heroes; //list of hero codename
        int gems;
        int sparks;
        int tickets;
};
