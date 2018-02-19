# PI Cards Helper
Tool that generate `75%` **PlayerInventory** in ***Plants vs. Zombies Heroes***

# PlayerInventory stuff
Split into 4 sections:
* `0xa` (card)
* `0x12` (hero)
* `0x20` (gem)
* `0x28`
* `0x5a`
* `0x60` (lifetime tickets)
* `0x72`

## `xx yy` (general section)
* `xx` is the **section unique id**
* `yy` is the **number of byte follow it**

## `0xa` (card)
`0xa` **number of byte** `0x8` **card id** `0x10` **number of copy**
* `0x8` stand for after it is **card id**.
* **Card id**:  If the first byte is `0x0`-`0x7f` (`0`-`127` decimal) then it is just 1-byte and used as is. If the first byte has 7th bit (`0x80`-`0xff`, `128`-`255` decimal) the parser reads the second byte and do different things (little-endian based?).
    * If the second byte is `0x0` the first byte gets *AND*ed with `0x7f`, which means the 7th bit gets removed.
    * If the second byte is `0x1` then the first byte is used as is (with 7th bit intact)
    * If the second byte is `0x2` then first byte gets *AND*ed with `0x7f` and *OR*ed with `0x100` (7th bit removed and 8th bit set)
    * If the second byte is `0x3` then first byte gets *OR*ed with `0x100` (8th bit set)
    * If the second byte is `0x4` then first byte gets *AND*ed with `0x7f` and *OR*ed with `0x200` (7th bit removed and 9th bit set)
    * If the second byte is `0x5` then first byte gets *OR*ed with `0x200` (9th bit set)
    * If the second byte is `0x6` then first byte gets *AND*ed with `0x7f` and *OR*ed with `0x400` (7th bit removed and 10th bit set)
    * If the second byte is `0x7` then first byte gets *OR*ed with `0x400` (10th bit set)
    *  ~~This pattern repeats until `0xff7f`~~ (`135085` would be `0xad9f08`). If second byte above `0xff` apply this rule to generate the new second byte and third byte (maybe it limit is fouth byte?). This number system is called **RTON number system** because it from ***PvZ 2*** RTON format
    * Psuedo code
    ```cpp
    string int2RTONnum(int i){
        string res;
        if (i <= 0x7f) return res = (char) i;
        int secondByte = floor((float) i / 0x100) * 2;
        int firstByte = i - (secondByte / 2) * 0x100;
        if (firstByte > 0x7f) ++secondByte;
        else firstByte = firstByte + 0x80;
        res = res + (char) firstByte;
        if (secondByte > 0xff) return res + int2RTONnum(secondByte);
        return res + (char) secondByte;
    }
    ```
* `0x10` stand for after it is **number of copy**

## `0x12` (hero)
`0x12` **number of byte** `0xa` **(length of hero codename)** **(hero codename)** `0x10` **available**
* `0xa` stand for after it is **length of hero codename** and **hero codename**
* `0x10` stand for after it is availability (boolean)
    * `0x1` is true which mean player can use that hero
    * `0x0` is false opposite with `0x1` but the game never use it, instead of it doesn't write any info about the hero to **PlayerInventory**
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
`0x20` **number of gem**
* **Number of gem** use **RTON number system**

## `0x28`
???

## `0x5a`
???

## `0x60` (lifetime tickets)
`0x60` **number of lifetime tickets**
* **Number of lifetime tickets** use **RTON number system**

## `0x72`
???

# Credits
* Niels Lohmann for [his awesome JSON parser](https://github.com/nlohmann/json)