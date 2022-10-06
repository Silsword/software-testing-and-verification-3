#include <fstream>
#include <vector>

using namespace std;

void key_generation(const char* path){
    srand(time(0));
    string path_file = path + "/key_encal"s;
    std::ofstream out(path_file, std::ios::binary);
    for(int i = 0; i < 9; ++i){
        out << rand() % 128 + 100;
    }
}

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

void encrypt(const char* input_file_name, const char* path_key){
    std::ifstream in(input_file_name, std::ios::binary);
    string output_file_name = input_file_name + ".encal"s;
	std::ofstream out(output_file_name, std::ios::binary);
    vector<int> key = open_key(path_key);
    char c;
    for(int i = 0; in.get(c); ++i){
        out << static_cast<char>((c + key[i]) % 128);
        if(i == 8){
            i = 0;
        }
    }
	in.close();
	out.close();
}

void decrypt(const char* input_file_name, const char* path_key_file){
    vector <int> key = open_key(path_key_file);
    std::ifstream in(input_file_name, std::ios::binary);
    string output_file_name = (input_file_name + ""s).substr((input_file_name + ""s).rfind("."));
	std::ofstream out(output_file_name, std::ios::binary);
    char c;
    for(int i = 0; in.get(c); ++i){
        out << static_cast<char>((128 + c - key[i]) % 128);
        if(i == 8){
            i = 0;
        }
    }
	in.close();
	out.close();

}
