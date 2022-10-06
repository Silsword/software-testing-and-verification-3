#include <fstream>
#include <vector>

using namespace std;

vector <int> open_key(const char* path_key_file){
    std::ifstream in(path_key_file, std::ios::binary);
    vector <int> key;
    for (int i = 0; i < 9; ++i){
        string num = "";
        char c;
        in.get(c);
        num += c;
        in.get(c);
        num += c;
        in.get(c);
        num += c;
        key.push_back(stoi(num) - 100);
    }
    in.close();
    return key;
}
