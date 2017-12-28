# PI Cards Helper
Tool that generate `75%` **PlayerInventory** in ***Plants vs. Zombies Heroes***

# PlayerInventory stuff
Split into 4 sections:
* Heroes
* Cards
* Currencies
* Unknow (haven't reverse engineer it yet :v)

## General type `xx yy`
Where `xx` is the **section unique id** and `yy` is the **number of byte follow it**

## Cards (`0xa`)
`0xa` **number of byte** `0x8` **card id** `0x10` **number of copy**

`0x8` stand for after it is **card id**.

**Card id**:  If the first byte is `0x0`-`7xf` (`0`-`127` decimal) then it is just 1-byte and used as is. If the first byte has 7th bit (`0x80`-`0xff`, `128`-`255` decimal) the parser reads the second byte and do different things.
* If the second byte is `0x0` the first byte gets *AND*ed with `0x7f`, which means the 7th bit gets removed.
* If the second byte is `0x1` then the first byte is used as is (with 7th bit intact)
* If the second byte is `0x2` then first byte gets *AND*ed with `0x7f` and *OR*ed with `0x100` (7th bit removed and 8th bit set)
* If the second byte is `0x3` then first byte gets *OR*ed with `0x100` (8th bit set)
* If the second byte is `0x4` then first byte gets *AND*ed with `0x7f` and *OR*ed with `0x200` (7th bit removed and 9th bit set)
* If the second byte is `0x5` then first byte gets *OR*ed with `0x200` (9th bit set)
* If the second byte is `0x6` then first byte gets *AND*ed with `0x7f` and *OR*ed with `0x400` (7th bit removed and 10th bit set)
* If the second byte is `0x7` then first byte gets *OR*ed with `0x400` (10th bit set)

This pattern repeats until `0xff 0x7f`.

`0x10` stand for after it is **number of copy**

## Heroes (`0x12`)
`0x12` **number of byte** `0xa` **(length of hero codename)** **(hero codename)** `0x10` **available**

`0xa` stand for after it is **length of hero codename** and **hero codename**

`0x10` stand for after it is availability (`0x1`)

Currently (28/12/2017), ***Plants vs. Zombies Heroes*** has 22 heroes 11 for plant and 11 for zombie they are:

### **Hero name and codename cheatsheet**

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

## Currencies
Lazy

# Credits
* Niels Lohmann for [his awesome JSON parser](https://github.com/nlohmann/json)