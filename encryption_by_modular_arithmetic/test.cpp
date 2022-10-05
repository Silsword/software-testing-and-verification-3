#include <vector>

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
}
