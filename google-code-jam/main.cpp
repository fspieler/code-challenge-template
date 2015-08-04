#include <iostream>
#include <string>
#include <cstdio>
#include <vector> 
#include <algorithm> 


using namespace std;

string run_test_case()
{

    // FEED ME CODE
    
    return "";
}

int main(int argc, char* argv[])
{

    int num_test_cases;
    int start;
    cerr << argc << endl;
    if(argc == 3)
    {
        num_test_cases = atoi(argv[1]);
        start = atoi(argv[2]);
    }
    else
    {
        cin >> num_test_cases;
        start = 1;
    }

    for (int test_case = start; test_case < start+num_test_cases; test_case++)
    {
        cout << "Case #" << test_case << ": " << run_test_case() << endl;
    }

    return 0;
}
