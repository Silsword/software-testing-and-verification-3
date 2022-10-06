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
}
