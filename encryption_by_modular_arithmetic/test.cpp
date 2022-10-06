#include <vector>
#include <fstream>
#include <set>

#include "main.cpp"

namespace testing_functions {
	void test_of_pow() {
		// Arrange
		const size_t number_of_tests = 7;
		const std::vector <uint64_t> bases =
				{7ull, 2553ull, 97654653453ull, 1241444124467ull,
				 324235414123ull, 9684565244244423413ull, 18446744073709551615ull};
		const std::vector <uint64_t> exponents =
				{143564634255735ull, 124234556778ull, 1243125543787557661ull,
				 18446744073709551615ull, 97654653456ull, 0ull, 127ull};
		const std::vector <uint64_t> correct_answers =
				{5113014404102018679ull, 8801943770991138801ull, 2990623661040471869ull,
				 13009999415330032635ull, 3028747218708579521ull, 1ull, 18446744073709551615ull};
		std::vector <uint64_t> answers;
		// Act
		for (size_t i = 0; i < number_of_tests; ++i)
			answers.push_back(auxiliary_functions::pow(bases[i], exponents[i]));
		// Assert
		assert(answers == correct_answers);
	}

	void test_of_inv() {
		// Arrange
		const long number_of_tests = 7;
		const std::vector<uint64_t> values =
				{5ull, 2341ull, 74352411143447ull, 1241444124467ull,
				 9684565244244423413ull, 23424223132347ull, 18446744073709551615ull};
		std::vector<uint64_t> inv_values;
		// Act
		for (uint64_t value: values)
			inv_values.push_back(auxiliary_functions::inv(value));
		// Assert
		for (size_t i = 0; i < number_of_tests; ++i)
			assert(values[i]*inv_values[i] == 1);
	}

	uint64_t make_buf(const std::string &str) {//str.size() <= 8
		uint64_t buf = 0;
		size_t i = 0;
		for(char c: str) {
			buf <<= 8;
			buf += static_cast<uint8_t>(c);
			++i;
		}
		buf <<= 8 * (8 - i);
		return buf;
	}

	void test_of_print_as_characters() {
		using namespace std;
		const char *file_name = "temp.txt";
		const vector<string> correct_answer = {"abcdefsd"s, "qwertyui"s, "()a^@f&%"s};
		vector<string> answer;

		for(const string &str: correct_answer) {//std.size() == 8
			// Arrange
			uint64_t buf = make_buf(str);
			size_t n = str.size();
			std::fstream file(file_name, std::ios::binary | std::ios::out | std::ios::trunc);
			//Act
			auxiliary_functions::print_as_characters(file, buf);
			file.close();
			// Assert
			file = std::fstream(file_name, std::ios::binary | std::ios::in);
			answer.emplace_back();
			std::getline(file, answer.back());
			file.close();
		}
		remove(file_name);

		assert(answer == correct_answer);
	}

	void test_of_random_key() {
		std::set<uint64_t> answers;
		const int num_keys = 100000;
		const int acceptable_match = 1;
		// Arrange
		// Act
		for(long i = 0; i < num_keys; ++i)
			answers.insert(auxiliary_functions::random_key());
		// Assert
		assert(answers.size() >= num_keys - acceptable_match);
	}

	bool files_are_equal(const char *file1_name, const char  *file2_name) {
		std::ifstream file1(file1_name, std::ios::binary);
		std::ifstream file2(file2_name, std::ios::binary);

		char c1, c2;
		file1.get(c1);
		file2.get(c2);
		while(!(file1.eof() || file2.eof())) {
			if (c1 != c2) break;
			file1.get(c1);
			file2.get(c2);
		}

		bool res = file1.eof() && file2.eof();

		file1.close();
		file2.close();

		return res;
	}

	void test_of_encryption_and_decryption() {
		// Arrange
		const char *test_file_name = "test";
		std::ofstream test_file(test_file_name);
		test_file << "Hello world! абра-\nкадабра";
		test_file.close();
		const char *encrypted_file_name = "encrypted_file";
		const char *decrypted_file_name = "decrypted_file";
		// Act
		encrypt(test_file_name, encrypted_file_name);
		decrypt(encrypted_file_name, decrypted_file_name);
		// Assert
		assert(files_are_equal(test_file_name, decrypted_file_name));
		remove(test_file_name);
		remove(encrypted_file_name);
		remove(decrypted_file_name);
	}
}
