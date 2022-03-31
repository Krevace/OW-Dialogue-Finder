#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>

using namespace std;

ifstream input;
string line;
string path = PROJECTDIR;
string nomaiName;
string hearthianName;
bool includeSigns = false;
bool sign;

int main() {
    path += "Dialogue";

    while (true) {
        cout << "Character Name?" << endl;
        cin >> hearthianName;
        for (auto& hearthianName : hearthianName) hearthianName = tolower(hearthianName);
        hearthianName[0] = toupper(hearthianName[0]);

        nomaiName = hearthianName;
        for (auto& nomaiName : nomaiName) nomaiName = toupper(nomaiName);
        nomaiName.append(":");

        cout << endl << hearthianName << " appears in: " << endl << endl;

        for (const auto& file : filesystem::directory_iterator(path)) {
            input.open(file);
            if (input.is_open())
            {
                string fileName = file.path().stem().string();
                if (fileName.find(hearthianName) != string::npos)
                {
                    if (!includeSigns) {
                        while (getline(input, line))
                        {
                            if (line.find(">SIGN") != string::npos)
                            {
                                sign = true;
                                break;
                            }
                        }
                    }
                    if (!sign) cout << fileName << endl;
                    else sign = false;
                }
                else
                {
                    while (getline(input, line))
                    {
                        if (line.find(nomaiName) != string::npos)
                        {
                            cout << fileName << endl;
                            break;
                        }
                    }
                }
                input.close();
            }
        }
        cout << endl;
    }
}