# PI-Cards-Helper
Tool that generate 75% PlayerInventory of Plants vs. Zombies Heroes

## PI stuff
Split into 3 sections:
* Heroes
* Cards
* Currencies
* Unknow (haven't reverse engineer it yet :v)

### General type `xx yy`
Where `xx` is the type of section unique id and `yy` is the number of byte follow it

### Cards (`0xa`)

***0xa `number of bytes` 0x8 `xx` 0x10 `yy`***

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

### Heroes (`0x12`)
Lazy

### Currencies
Lazy