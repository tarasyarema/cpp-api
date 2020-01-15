// C libraries
#include <cstdio>
#include <cstdlib> 
#include <ctime>

// C++ libraries
#include <chrono>
#include <string>

// Custom libraries
#include "httplib.h"

#define BUFFER_SIZE 1024
#define MOD 0x45d9f3b
#define ITERATIONS 1 // 1e+6

#define HOST "0.0.0.0"
#define PORT 8080

using namespace httplib;
using namespace std;
using namespace chrono;

unsigned int hash_number(unsigned int n) {
	unsigned int x = n;

	for (int i = 0; i < ITERATIONS; i++)
	{
		x = ((x >> 16) ^ x) * MOD;
		x = ((x >> 16) ^ x) * MOD;
		x = (x >> 16) ^ x;
	}

    return x;
}

int main(void)
{
	Server svr;

	svr.Get(R"(/hash/(\d+))", [&](const Request& req, Response& res) {
		auto start = steady_clock::now(); 

		// Parse the number and compute
		unsigned int request_number = (unsigned int)stoi(req.matches[1]);
		unsigned int number = hash_number(request_number);

		// Generate JSON response string
		char json[BUFFER_SIZE];
		snprintf(json, BUFFER_SIZE, "{\"hash\": %u}", number);

		// Set the response
        res.set_content(json, "application/json");

		auto end = steady_clock::now(); 

		// Log request
		fprintf(stderr, "GET 200 /square/%u - %ld ms\n", request_number, duration_cast<milliseconds>(end - start).count());
    });

	fprintf(stderr, "Server listening at http://%s:%d\n", HOST, PORT);
	svr.listen(HOST, PORT);
}
