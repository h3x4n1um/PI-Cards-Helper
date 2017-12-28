#include "json.hpp"
#include <fstream>

using namespace std;
using namespace nlohmann;

void _error();
string myNameIsJeff(int cardId);

const unsigned char heroes[1024] = {
    0x12, 0x0D, 0x0A, 0x09, 0x50, 0x72, 0x6F, 0x66, 0x65, 0x73, 0x73, 0x6F, 0x72, 0x10, 0x01,
    0x12, 0x0F, 0x0A, 0x0B, 0x53, 0x63, 0x6F, 0x72, 0x74, 0x63, 0x68, 0x77, 0x6F, 0x6F, 0x64, 0x10, 0x01,
    0x12, 0x0C, 0x0A, 0x08, 0x4E, 0x69, 0x67, 0x68, 0x74, 0x43, 0x61, 0x70, 0x10, 0x01,
    0x12, 0x11, 0x0A, 0x0D, 0x42, 0x65, 0x74, 0x61, 0x43, 0x61, 0x72, 0x72, 0x6F, 0x74, 0x69, 0x6E, 0x61, 0x10, 0x01,
    0x12, 0x0F, 0x0A, 0x0B, 0x42, 0x72, 0x61, 0x69, 0x6E, 0x46, 0x72, 0x65, 0x65, 0x7A, 0x65, 0x10, 0x01,
    0x12, 0x0D, 0x0A, 0x09, 0x49, 0x6D, 0x70, 0x66, 0x69, 0x6E, 0x69, 0x74, 0x79, 0x10, 0x01,
    0x12, 0x08, 0x0A, 0x04, 0x52, 0x6F, 0x73, 0x65, 0x10, 0x01,
    0x12, 0x0E, 0x0A, 0x0A, 0x57, 0x61, 0x6C, 0x6C, 0x4B, 0x6E, 0x69, 0x67, 0x68, 0x74, 0x10, 0x01,
    0x12, 0x12, 0x0A, 0x0E, 0x48, 0x75, 0x67, 0x65, 0x47, 0x69, 0x67, 0x61, 0x6E, 0x74, 0x61, 0x63, 0x75, 0x73, 0x10, 0x01,
    0x12, 0x0B, 0x0A, 0x07, 0x4E, 0x65, 0x70, 0x74, 0x75, 0x6E, 0x61, 0x10, 0x01,
    0x12, 0x09, 0x0A, 0x05, 0x5A, 0x4D, 0x65, 0x63, 0x68, 0x10, 0x01,
    0x12, 0x0E, 0x0A, 0x0A, 0x47, 0x61, 0x72, 0x67, 0x61, 0x6E, 0x74, 0x75, 0x61, 0x72, 0x10, 0x01,
    0x12, 0x0A, 0x0A, 0x06, 0x43, 0x69, 0x74, 0x72, 0x6F, 0x6E, 0x10, 0x01,
    0x12, 0x0B, 0x0A, 0x07, 0x43, 0x68, 0x6F, 0x6D, 0x70, 0x65, 0x72, 0x10, 0x01,
    0x12, 0x0A, 0x0A, 0x06, 0x43, 0x79, 0x62, 0x6F, 0x72, 0x67, 0x10, 0x01,
    0x12, 0x09, 0x0A, 0x05, 0x44, 0x69, 0x73, 0x63, 0x6F, 0x10, 0x01,
    0x12, 0x12, 0x0A, 0x0E, 0x47, 0x72, 0x61, 0x73, 0x73, 0x5F, 0x4B, 0x6E, 0x75, 0x63, 0x6B, 0x6C, 0x65, 0x73, 0x10, 0x01,
    0x12, 0x0A, 0x0A, 0x06, 0x53, 0x70, 0x75, 0x64, 0x6F, 0x77, 0x10, 0x01,
    0x12, 0x0D, 0x0A, 0x09, 0x43, 0x70, 0x74, 0x42, 0x72, 0x61, 0x69, 0x6E, 0x7A, 0x10, 0x01,
    0x12, 0x0D, 0x0A, 0x09, 0x50, 0x65, 0x6E, 0x65, 0x6C, 0x6F, 0x70, 0x65, 0x61, 0x10, 0x01,
    0x12, 0x0D, 0x0A, 0x09, 0x53, 0x75, 0x6E, 0x66, 0x6C, 0x6F, 0x77, 0x65, 0x72, 0x10, 0x01,
    0x12, 0x09, 0x0A, 0x05, 0x57, 0x69, 0x74, 0x63, 0x68, 0x10, 0x01
};

const vector <string> unhandle = {
    "",
    "null",
    "Board",
    "Token",
    "Superpower",
    "Hero",
    "Cheats",
    "Blank",
    "cheats"
};

json js;
ifstream input;
ofstream output;
string result, chooseSet;
vector <string> handle, listSet;

int main(){
	int card_id;
	printf(R"(PI Cards Helper version 2.1 (made by H3x4n1um)
Credits: nlohmann for his awesome JSON parser
Note: Currently, this tool only creates 75%% of the PI, the remain 25%% is copy-pasted (this step depends on you and your knowledge)

Enter "cards.json" (or "cards.txt") file path: )");
    string file_path, temp;
    getline(cin, file_path);
    try{
        input.open(file_path);
        input >> js;
        input.close();
        for (int i = file_path.size() - 1; i >= 0; i--){
            if (file_path[i] == 0x5c){
                file_path = file_path.substr(0, i + 1);
                break;
            }
        }
    }
    catch (invalid_argument e){
        _error();
        return 1;
    }
    try{
        puts("");
        puts(R"(List of available "set":)");
        for (auto i : js.get<map <string, json> >()){
            temp = i.second.at("set").dump();
            if (find(listSet.begin(), listSet.end(), temp) == listSet.end()){
                cout << "   " << temp << endl;
                listSet.push_back(temp);
            }
        }
        printf(R"([CASE SENSITIVE] Choose what you want to include (look at "set"), default will select all except
    ""
    "null"
    "Board"
    "Token"
    "Superpower"
    "Hero"
    "Cheats"
    "Blank"
    "cheats"
if you want default just type "default" or ENTER: )");
        getline(cin, chooseSet);
        chooseSet += " ";
        while (chooseSet.find(" ") != string::npos){
            handle.push_back(chooseSet.substr(0, chooseSet.find(" ")));
            chooseSet.erase(0, chooseSet.find(" ") + 1);
        }
        for (auto i : js.get<map <string, json> >()){
            temp = i.second.at("set").dump();
            if (temp[0] == '"' && temp[temp.size() - 1] == '"'){
                temp.erase(temp.begin());
                temp.erase(temp.end() - 1);
            }
            if (((handle.size() == 1 && handle[0] == "default") || handle.size() == 0)&&(find(unhandle.begin(), unhandle.end(), temp) == unhandle.end())){
                card_id = atoi(i.first.c_str());
                /*if (card_id <= 0x7f){
                    result = result + (char) 0x0a + (char) 0x04 + (char) 0x08 + (char) card_id;
                }
                else{
                    result = result + (char) 0x0a + (char) 0x05 + (char) 0x08;
                    second_byte = floor((float) card_id / 0x100) * 2;
                    first_byte = card_id - (second_byte / 2) * 0x100;
                    if (first_byte > 0x7f) second_byte = second_byte + 1;
                    else first_byte = first_byte + 0x80;
                    result = result + (char) first_byte + (char) second_byte;
                }
                result = result + (char) 0x10 + (char) 0x04;*/
                result = result + myNameIsJeff(card_id);
            } else if (find(handle.begin(), handle.end(), temp) != handle.end()){
                    card_id = atoi(i.first.c_str());
                    /*if (card_id <= 0x7f){
                        result = result + (char) 0x0a + (char) 0x04 + (char) 0x08 + (char) card_id;
                    }
                    else{
                        result = result + (char) 0x0a + (char) 0x05 + (char) 0x08;
                        second_byte = floor((float) card_id / 0x100) * 2;
                        first_byte = card_id - (second_byte / 2) * 0x100;
                        if (first_byte > 0x7f) second_byte = second_byte + 1;
                        else first_byte = first_byte + 0x80;
                        result = result + (char) first_byte + (char) second_byte;
                    }
                    result = result + (char) 0x10 + (char) 0x04;*/
                    result = result + myNameIsJeff(card_id);
            }
        }
    }
    catch (out_of_range e){
        _error();
        return 1;
    }
    output.open(file_path + "PlayerInventory_75%", ios::binary);
    output.write((char *)&result[0], result.size());
    output.write((char *)&heroes[0], 0x13f);
    output.close();
    puts("\nDone! Please check PlayerInventory_75%\n");
    system("pause");
    return 0;
}

void _error(){
    cerr << '\n' << R"(Error! "cards.json"/"cards.txt") not found / not in a correct format!!!)" << "\n\n";
    system("pause");
}

//prototype of Jeff. Jeff is my only son. No touching & No homo.
string myNameIsJeff(int cardId){
	string rtn;
	int first_byte, second_byte;
	if (cardId <= 0x7f){
        rtn = rtn + (char) 0x0a + (char) 0x04 + (char) 0x08 + (char) cardId;
    } else {
        rtn = rtn + (char) 0x0a + (char) 0x05 + (char) 0x08;
        second_byte = floor((float) cardId / 0x100) * 2;
        first_byte = cardId - (second_byte / 2) * 0x100;
        if (first_byte > 0x7f) second_byte++;
        else first_byte += 0x80;
        rtn = rtn + (char) first_byte + (char) second_byte;
    }
    rtn = rtn + (char) 0x10 + (char) 0x04;
    return rtn;
}
