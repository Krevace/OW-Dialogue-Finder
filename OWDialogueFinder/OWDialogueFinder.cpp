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
bool sign = false;

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
                    while (getline(input, line))
                    {
                        if (line.find(">SIGN") != string::npos && !includeSigns)
                        {
                            sign = true;
                        }
                        if (line.find(hearthianName) != string::npos)
                        {
                            if (!sign) cout << fileName << endl;
                            else sign = false;
                            break;
                        }
                    }
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