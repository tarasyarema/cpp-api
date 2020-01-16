#define MOD 0x45d9f3b
#define ITERATIONS 1 // 1e+6

#define ull unsigned long long int

inline size_t hash_number(size_t n) {
	size_t x = n;

	for (size_t i = 0; i < ITERATIONS; i++)
	{
		x = ((x >> 8) ^ x) * MOD;
		x = ((x >> 8) ^ x) * MOD;
		x =  (x >> 8) ^ x;
	}

    return x;
}