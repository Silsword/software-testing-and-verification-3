#include <fstream>
#include <string>

namespace auxiliary_functions {
	uint64_t pow(uint64_t b, uint64_t e) {//b^e по модулю 2^64
		uint64_t res = (e & 1) ? b : 1;
		e >>= 1;
		while(e) {
			b *= b;
			if(e & 1) res *= b;
			e >>= 1;
		}
		return res;
	}

	uint64_t inv(uint64_t a) {// (1 / a) по модулю 2^64, а - нечетное
		return pow(a, 9223372036854775807ull);
	}

	void print_as_characters(std::ostream &out, uint64_t buf) {
		for(int i = 7; 0 <= i; --i)
			out << static_cast<uint8_t>((buf >> (i * 8)) % 256);
	}

	uint64_t random_key() {//возвращает нечетное число, каждый байт которого не равен нулю
		//генерация
		uint64_t res = rand();
		res <<= 32;
		res += rand();
		//проверка
		bool b = res & 1;
		for(int i = 15; i >= 0; --i)
			b = b && (res >> i);

		if (!b) res = random_key();
		return res;
	}
}

void generate_key_to_file (const char *key_file_name) {
	std::ofstream out(key_file_name, std::ios::trunc);
	uint64_t shift = auxiliary_functions::random_key();
	uint64_t multiplier = auxiliary_functions::random_key();
	out << shift << ' ' << multiplier;
}

void encrypt(const char *input_file_name, const char *key_file_name) {
	using namespace std;
	ifstream key_file(key_file_name);
	uint64_t shift, multiplier;
	key_file >> shift >> multiplier;
	key_file.close();

	ifstream in(input_file_name, ios::binary);
	string output_file_name = input_file_name + ".enc"s;
	ofstream out(output_file_name, ios::binary);

	uint64_t buf = 0;
	int i = 0;
	char c;
	while(in.get(c)) {
		buf <<= 8;
		buf += static_cast<uint8_t>(c);
		++i;
		if(i == 8) {
			auxiliary_functions::print_as_characters(out, (buf + shift) * multiplier);
			buf = 0;
			i = 0;
		}
	}
	if (i != 0) {
		buf <<= 8 * (8 - i);
		auxiliary_functions::print_as_characters(out, (buf + shift) * multiplier);
	}
	in.close();
	out.close();
}

extern "C" void encrypt(const char *input_file_name) {//ключ по умолчанию
	using namespace std;
	const char *key_file_name = ".default_key";
	ofstream key_file(key_file_name, ios::trunc);
	const uint64_t shift = 567342345623ull;
	const uint64_t multiplier = 1234353354349ull;
	key_file << shift << ' ' << multiplier;
	key_file.close();

	encrypt(input_file_name, key_file_name);
	remove(key_file_name);
}

extern "C" void decrypt(const char *input_file_name, const char *key_file_name) {
	using namespace std;
	ifstream key_file(key_file_name);
	uint64_t shift, multiplier;
	key_file >> shift >> multiplier;
	key_file.close();
	multiplier = auxiliary_functions::inv(multiplier);


	ifstream in(input_file_name, ios::binary);
	string output_file_name = input_file_name + ".dec"s;
	ofstream out(output_file_name, ios::binary);

	uint64_t buf = 0;
	int i = 0;
	char c;
	while(in.get(c)) {
		buf <<= 8;
		buf += static_cast<uint8_t>(c);
		++i;
		if(i == 8) {
			auxiliary_functions::print_as_characters(out, buf * multiplier - shift);
			buf = 0;
			i = 0;
		}
	}
	if (i != 0) {
		buf <<= 8 * (8 - i);
		auxiliary_functions::print_as_characters(out, buf * multiplier - shift);
	}
	in.close();
	out.close();
}

void decrypt(const char *input_file_name) {//ключ по умолчанию
	using namespace std;
	const char *key_file_name = ".default_key";
	ofstream key_file(key_file_name, ios::trunc);
	const uint64_t shift = 567342345623ull;
	const uint64_t multiplier = 1234353354349ull;
	key_file << shift << ' ' << multiplier;
	key_file.close();

	decrypt(input_file_name, key_file_name);
	remove(key_file_name);
}
