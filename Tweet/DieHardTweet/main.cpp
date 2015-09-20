//
//  main.cpp
//  DieHardBucketsTweet
//
//  Created by Hiroshi Takeda on 2014/02/06.
//  Copyright (c) 2014年 Hiroshi Takeda. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <list>
#include "../ProblemTweet.h"

using namespace std;
using namespace Diehard;

void writeGraph(const ProblemDot& problem, const string& fileName)
{
    ofstream ofs(fileName.c_str(), ofstream::out);
    problem.PrintGraph(ofs);
    ofs.close();
}

void writeTweets(const list<string>& tweets, const string& fileName)
{
    ofstream ofs(fileName.c_str(), ofstream::out);
    for (auto tweet : tweets)
    {
        ofs << tweet << endl;
    }
    ofs.close();
}

int main(int argc, const char * argv[])
{
    if (argc < 3)
    {
        cerr << "File name must be set: tweets file name and dot file name" << endl;
        return EXIT_FAILURE;
    }
    const string tweetFile(argv[1]);
    const string dotsFile(argv[2]);
    
    int counter = 3;
    while (counter-- != 0)
    {
        auto prob = ProblemTweet();
        prob.BuildGraph();
        prob.Resolve(prob.GetRandomGoal());
        auto tweets = prob.GetTweets();
        
        if (tweets)
        {
            writeTweets(*tweets, tweetFile);
            writeGraph(prob, dotsFile);
            return EXIT_SUCCESS;
        }
    }
    
    cerr << "Generating problem and solving was failed." << endl;
    return EXIT_FAILURE;
}

