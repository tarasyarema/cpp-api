// C libraries
#include <cstdio>
#include <cstdlib> 
#include <ctime>

// C++ libraries
#include <chrono>
#include <string>
#include <iostream>

// Custom libraries
#include "picojson.h"
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
    Client cli(HOST, PORT);
    auto elapsed = 0;

    int iterations = 100;
    int errors = 0;

    for (int i = 1; i <= 100; i++)
    {
        char req_uri[BUFFER_SIZE];
        snprintf(req_uri, BUFFER_SIZE, "/hash/%d", i);

		auto start = steady_clock::now(); 
        auto res = cli.Get(req_uri);
		auto end = steady_clock::now(); 

        auto duration = duration_cast<milliseconds>(end - start).count();
        elapsed += duration_cast<milliseconds>(end - start).count();

        if (res) {
            printf("%3d: %d (%ld ms) -> ", i, res->status, duration);

            picojson::value v;
            string err = picojson::parse(v, res->body);

            if (!err.empty()) {
                cerr << "ERROR: " << err << endl;
                continue;
            }

            const picojson::value::object& obj = v.get<picojson::object>();

            for (picojson::value::object::const_iterator j = obj.begin(); j != obj.end(); j++) 
            {
                auto _hash = j->second;
                cout << _hash << " vs " << hash_number(i) << endl;
            }
        }
        else
        {
            errors++;
            printf("%d: ERROR\n", i);
        }
    }

    printf("Errors: %d\n", errors);
    printf("Elapsed time: %ld ms\n", elapsed);

    return 0;
}