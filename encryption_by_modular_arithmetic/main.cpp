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
}

