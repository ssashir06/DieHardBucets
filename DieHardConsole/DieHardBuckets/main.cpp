//
//  main.cpp
//  DieHardBuckets
//
//  Created by Hiroshi Takeda on 2014/02/01.
//
//

#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include "ProblemDot.h"

using namespace std;
using namespace Diehard;

int main(int argc, const char * argv[])
{
    if (argc <= 2)
    {
        cerr << "bad argments" << endl;
        return EXIT_FAILURE;
    }
    
    int goal;
    vector<Volume> backets = vector<Volume>(argc - 2);;
    try
    {
        goal = stoi(argv[1]);
        for (int i = 0; i < argc - 2; i++)
        {
            backets[i] = stoi(argv[i + 2]);
        }
    }
    catch (const invalid_argument& ex)
    {
        cerr << ex.what() <<  endl;
        return EXIT_FAILURE;
    }
    
    auto prob = ProblemDot(backets);
    prob.BuildGraph();
    prob.Resolve(goal);
    prob.PrintGraph();
    prob.Resolve(2);
    prob.PrintGraph();
    
    return EXIT_SUCCESS;
}

