// C libraries
#include <cstdio>
#include <cstdlib> 
#include <ctime>

// C++ libraries
#include <chrono>
#include <string>

// Custom libraries
#include "httplib.h"
#include "utils.h"

#define BUFFER_SIZE 1024
#define HOST "0.0.0.0"
#define PORT 8080


using namespace httplib;
using namespace std;
using namespace chrono;

int main(void)
{
	Server svr;

	svr.Get(R"(/hash/(\d+))", [&](const Request& req, Response& res) {
		auto start = steady_clock::now(); 

		// Parse the number and compute
		size_t request_number = (size_t)stoi(req.matches[1]);
		size_t number = hash_number(request_number);

		// Generate JSON response string
		char json[BUFFER_SIZE];
		snprintf(json, BUFFER_SIZE, "{\"hash\": %lu}", number);

		// Set the response
        	res.set_content(json, "application/json");

		auto end = steady_clock::now(); 

		// Log request
		fprintf(stderr, "GET 200 /square/%lu - %ld ms\n", request_number, duration_cast<milliseconds>(end - start).count());
	});
	
	svr.set_error_handler([](const auto& req, auto& res) {
		auto fmt = "{\"message\":\"bad request\"}";
		char buf[BUFFER_SIZE];
		
		snprintf(buf, BUFFER_SIZE, fmt, res.status);
		
		res.status = 400;
		res.set_content(buf, "application/json");
	});

	fprintf(stderr, "Server listening at http://%s:%d\n", HOST, PORT);
	svr.listen(HOST, PORT);

	return 0;
}
