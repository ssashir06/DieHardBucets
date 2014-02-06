//
//  main.cpp
//  DieHardBuckets
//
//  Created by Hiroshi Takeda on 2014/02/01.
//
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <string>
#include <boost/filesystem/operations.hpp>
#include "ProblemDot.h"

using namespace std;
using namespace Diehard;

int main(int argc, const char * argv[])
{
    if (argc < 2)
    {
        cout << "usage: " << argv[0] << "CAPACITIES [--prefix FILENAME]" << endl << endl;
        cout << "Specify bucket capacities by CAPACITIES argument, that is split by space character." << endl;
        cout << "CAPACITIES must be integer." << endl;
        return EXIT_FAILURE;
    }
    
    string prefix = "DieHard";
    vector<Volume> backets = vector<Volume>(argc - 1);;
    try
    {
        for (int i = 1; i < argc; i++)
        {
            if (strcmp(argv[i], "--prefix") == 0)
            {
                prefix = argv[i + 1];
                i++;
            }
            else
            {
                backets[i - 1] = stoi(argv[i]);
            }
        }
    }
    catch (const invalid_argument& ex)
    {
        cerr << "Argument is wrong" << ex.what() <<  endl;
        return EXIT_FAILURE;
    }
    
    auto prob = ProblemDot(backets);
    prob.BuildGraph();
    
    Volume backet_max = 0;
    for_each(backets.begin(), backets.end(), [&](Volume v) { backet_max += v; });
    
    cout << "current directory: " << boost::filesystem::current_path() << endl;
    
    for (Volume goal = 1; goal < backet_max; goal++)
    {
        stringstream ss;
        ss << prefix << ".";
        for (size_t i = 0; i < backets.size(); i++)
        {
            ss << backets[i] << ".";
        }
        ss << "goal." << goal << ".dot";
        
        string filename = ss.str();
        
        ofstream ofs;
        ofs.open(filename, ofstream::out | ofstream::trunc);
        
        cout << "Writing file: " << filename << endl;
        prob.Resolve(goal);
        prob.PrintGraph(ofs);
        
        ofs.close();
    }
    
    return EXIT_SUCCESS;
}

