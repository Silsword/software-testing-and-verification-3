#include <cassert>
#include "coder.cpp"

using namespace std;

namespace testing_functions {

    void test_open_key(){
        char *file_name = "test";
        std::ofstream in(file_name, std::ios::binary);
        vector <int> correct_result = {123, 8, 45, 67, 100, 45, 34, 90, 1};
        for(const int& result : correct_result){
            in << result + 100;
        }
        in.close();
        vector <int> result = open_key(file_name);
        for(int i = 0; i < correct_result.size(); ++i){
            assert(correct_result[i] == result[i]);
        }
        remove(file_name);
    }

    void test_encrypt_decrypt(){
        char* file_name = "test";
        char* path_key = "";
        ofstream in(file_name, std::ios::binary);
        const string correct_result = "Hello world!"s;
        in << correct_result;
        in.close();
        char *expansion = ".encal";
        char *decrypt_file_name = file_name + *expansion;
        key_generation(path_key);
        char *expansion_key = "key_encal";
        char *key_file = path_key + *expansion_key;
        encrypt(file_name, key_file);
        decrypt(decrypt_file_name, key_file);
        ifstream out(file_name, std::ios::binary);
        for(int i = 0; i < correct_result.size(); ++i){
            char let;
            out.get(let);
            assert(correct_result[i] == let);
        }
        remove(file_name);
    }
}