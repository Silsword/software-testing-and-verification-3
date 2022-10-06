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
	}
}

//key - нечетное положительное число < 2^64
void encrypt(const char *input_file_name, const char *output_file_name, const uint64_t key = 1234353354349ull) {
	std::ifstream in(input_file_name, std::ios::binary);
	std::ofstream out(output_file_name, std::ios::binary);

	uint64_t buf = 0;
	int i = 0;
	char c;
	while(in.get(c)) {
		buf <<= 8;
		buf += static_cast<uint8_t>(c);
		++i;
		if(i == 8) {
			auxiliary_functions::print_as_characters(out, buf * key);
			buf = 0;
			i = 0;
		}
	}
	if (i != 0) {
		buf <<= 8 * (8 - i);
		auxiliary_functions::print_as_characters(out, buf * key);
	}
	in.close();
	out.close();
}

void decrypt(const char *input_file_name, const char *output_file_name, const uint64_t key = 1234353354349ull) {
	encrypt(input_file_name, output_file_name, auxiliary_functions::inv(key));
}