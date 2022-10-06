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

void encrypt(const char *input_file_name, const char *key_file_name) {
}

void encrypt(const char *input_file_name) {//ключ по умолчанию
}

void decrypt(const char *input_file_name, const char *key_file_name) {
}

void decrypt(const char *input_file_name) {//ключ по умолчанию
}