//
//  main.cpp
//  DieHardBucketsTweet
//
//  Created by Hiroshi Takeda on 2014/02/06.
//  Copyright (c) 2014年 Hiroshi Takeda. All rights reserved.
//

#include <iostream>
#include "ProblemTweet.h"

using namespace std;
using namespace Diehard;

int main(int argc, const char * argv[])
{
    int counter = 3;
    
    while (counter-- != 0)
    {
        auto prob = ProblemTweet();
        prob.BuildGraph();
        prob.Resolve(prob.GetRandomGoal());
        auto tweets = prob.GetTweets();
        
        if (tweets)
        {
            for (auto tweet : *tweets)
                cout << tweet << endl;
            return 0;
        }
    }
    
    return 1;
}

