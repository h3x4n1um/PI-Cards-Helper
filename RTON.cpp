#include <cmath>
#include <cstdlib>

//#define log256(x) log2(x) / 8  //<- don't do this pls

auto log256(double x) {
    return log2(x) / 8;
}

//this implementation still has bug when convert 0xbe87f407 to 0xfd03be (correct would be 0x7e81df3b ~ 2 billions), kinda strange even I can't find why it would be 0x7e81df3b???

int hexLength(int q) {
    return static_cast<int>(ceil(log256(q)) ? ceil(log256(q)) : 1);
}
//unused function
/*int RTONnum2int(int q) {
    if (hexLength(q) < 1 && q > 0x7f) return 0xffffffff; //return max when RTON number has 1 byte and > 0x7f
    int lastByte = q % 0x100;
    q /= 0x100;
    while (q > 0) {
        int nearLastByte = q % 0x100;
        q /= 0x100;
        if (lastByte % 2 == 0) nearLastByte &= 0x7f;
        nearLastByte += 0x100 * std::floor((float) lastByte / 2);
        lastByte = nearLastByte;
    }
    return lastByte;
}*/

int int2RTONnum(int q) {
    if (q <= 0x7f) return q;
    int firstByte = q % 0x100;
    q /= 0x100;
    int secondByte = q * 2;
    if (firstByte > 0x7f) ++secondByte;
    else firstByte += 0x80; //reverse & 0x7f
    int newSecondByte = int2RTONnum(secondByte);
    return static_cast<int>(firstByte * pow(0x100, hexLength(q)) + newSecondByte);
}

const char CARD = 0xa;
const char HERO = 0x12;
const char NUMBER = 0x10;

const auto HEROES = {"Penelopea", "Sunflower", "NightCap", "Grass_Knuckles", "BetaCarrotina", "Spudow", "Rose",
                     "WallKnight", "Chomper", "Scortchwood", "Citron", "HugeGigantacus", "CptBrainz", "Professor",
                     "Disco", "BrainFreeze", "Cyborg", "Witch", "Impfinity", "Neptuna", "ZMech", "Gargantuar"};
