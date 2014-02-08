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
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cstdlib>
#ifdef DEBUG
#include <boost/filesystem/operations.hpp>
#endif
#include "ProblemDot.h"

using namespace std;
using namespace Diehard;

int main(int argc, const char * argv[])
{
    if (argc < 2)
    {
        cout << "usage: " << argv[0] << " CAPACITIES [--prefix FILENAME]" << endl << endl;
        cout << "Specify bucket capacities by CAPACITIES argument, that is split by space character." << endl;
        cout << "CAPACITIES must be integer." << endl;
        return EXIT_FAILURE;
    }
    
    string prefix = "DieHard";
    vector<Volume> backets = vector<Volume>(argc - 1);;
    size_t backet_size = 0;
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "--prefix") == 0)
        {
            prefix = argv[i + 1];
            i++;
        }
        else
        {
            auto capacity = atoi(argv[i]);
            if (capacity <= 0)
            {
                cerr << "Wrong argument, backet capacity cannot be zero or minus." << endl;
                return EXIT_FAILURE;
            }
            backets[backet_size++] = capacity;
        }
    }
    backets.resize(backet_size);
    
    auto prob = ProblemDot(backets);
    prob.BuildGraph();
    
    Volume backet_max = 0;
    for_each(backets.begin(), backets.end(), [&](Volume v) { backet_max += v; });
    
#ifdef DEBUG
    cout << "current directory: " << boost::filesystem::current_path() << endl;
#endif
    
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

