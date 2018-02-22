# PI Cards Helper
This tool generates **PlayerInventoryAllCards** in ***Plants vs. Zombies Heroes***

# PlayerInventory stuff
Can be split into the following sections:
* `0xa` (card)
* `0x12` (hero)
* `0x20` (gem)
* `0x28`
* `0x5a`
* `0xbb` (spark)
* `0x60` (lifetime ticket)
* `0x72`

## `xx yy` (general section)
* `xx` is the **section's unique id**
* `yy` is the **number of bytes following it**

## `0xa` (card)
`0xa` **number of bytes** `0x8` **card id** `0x10` **number of copies**
* The latter `0x8` represents **card id**.
* **Card id**:  If the first byte is `0x0`-`0x7f` (`0`-`127` decimal) then it will be just 1-byte and used as is. If the first byte has a 7th bit (`0x80`-`0xff`, `128`-`255` decimal) the parser then reads the second byte and do different things depending on it (little-endian based?)
    * If the second byte is `0x0`, the first byte will be *AND*ed with `0x7f`, which means the 7th bit gets removed.
    * If the second byte is `0x1`, the first byte will be used as is (with 7th bit intact)
    * If the second byte is `0x2`, the first byte will be *AND*ed with `0x7f` and *OR*ed with `0x100` (7th bit removed and 8th bit set)
    * If the second byte is `0x3`, the first byte will be *OR*ed with `0x100` (8th bit set)
    * If the second byte is `0x4`, the first byte will be *AND*ed with `0x7f` and *OR*ed with `0x200` (7th bit removed and 9th bit set)
    * If the second byte is `0x5`, the first byte gets *OR*ed with `0x200` (9th bit set)
    * If the second byte ixs `0x6`, the first byte gets *AND*ed with `0x7f` and *OR*ed with `0x300` (7th bit removed and 10th bit set)
    * If the second byte is `0x7`, the first byte gets *OR*ed with `0x300` (10th bit set)
    *  This pattern repeats ~~until `0xff7f`~~ (`0x20fad` (`135085` in decimal) would be `0xad9f08`). If second byte above `0xff` apply this rule to generate the new second byte and third byte (maybe it limit is fouth byte?). This number system is called **RTON number system** because it from ***PvZ 2*** RTON format
    * Pseudo code:
    ```cpp
    //this implementation still has bug when convert 0xbe87f407 to 0xfd03be (correct would be 0x7e81df3b ~ 2 billions), kinda strange even I can't find why it would be 0x7e81df3b???
    int RTONnum2int(int q){
        if (log256(q) < 1 && q > 0x7f) return 0xffffffff; //return max when RTON number has 1 byte and > 0x7f
        int lastByte = q % 0x100;
        q /= 0x100;
        while(q > 0){
            int nearLastByte = q % 0x100;
            q /= 0x100;
            if (lastByte % 2 == 0) nearLastByte &= 0x7f;
            nearLastByte += 0x100 * floor((float) lastByte / 2);
            lastByte = nearLastByte;
        }
        return lastByte;
    }

    int int2RTONnum(int q){
        if (q <= 0x7f) return q;
        int firstByte = q % 0x100;
        q /= 0x100;
        int secondByte = q * 2;
        if (firstByte > 0x7f) ++secondByte;
        else firstByte += 0x80; //reverse & 0x7f
        int newSecondByte = int2RTONnum(secondByte);
        return firstByte * pow(0x100, ceil(log256(newSecondByte)) ? ceil(log256(newSecondByte)) : 1) + newSecondByte;
    }
    ```
* `0x10` stand for after it is **number of copy**

## `0x12` (hero)
`0x12` **number of bytes** `0xa` **(length of hero's codename)** **(hero's codename)** `0x10` **availablility**
* `0xa` stand for after it is **length of hero's codename** and **hero's codename**
* `0x10` stand for after it is availability (boolean)
    * `0x1` is true which mean player can use that hero
    * `0x0` is false, opposite with `0x1` but the game never use it, instead it doesn't write any info about the hero to **PlayerInventory**
* **Hero codename** cheatsheet

Hero name | Codename | Faction
--- | --- | ---
Green Shadow | Penelopea | Plant
Solar Flare | Sunflower | Plant
Nightcap | NightCap | Plant
Grass Knuckles | Grass_Knuckles | Plant
Beta-Carrotina | BetaCarrotina | Plant
Spudow | Spudow | Plant
Rose | Rose | Plant
Wall-Knight | WallKnight | Plant
Chompzilla | Chomper | Plant
Captain Combustible | Scortchwood | Plant
Citron | Citron | Plant
Huge-Gigantacus | HugeGigantacus | Zombie
Super Brainz | CptBrainz | Zombie
Professor Brainstorm | Professor | Zombie
Electric Boogaloo | Disco | Zombie
Brain Freeze | BrainFreeze | Zombie
Rustbolt | Cyborg | Zombie
Immorticia | Witch | Zombie
Impfinity | Impfinity | Zombie
Neptuna | Neptuna | Zombie
Z-Mech | ZMech | Zombie
The Smash | Gargantuar | Zombie

## `0x20` (gem)
`0x20` **number of gems**
* This uses the **RTON number system**

## `0x28`
???

## `0xbb` (spark)
`0xbb` **number of sparks**
* This uses the **RTON number system**

## `0x5a`
???

## `0x60` (lifetime ticket)
`0x60` **number of lifetime tickets**
* This uses the **RTON number system**

## `0x72`
???

# Credits
* Niels Lohmann for [his awesome JSON parser](https://github.com/nlohmann/json)
