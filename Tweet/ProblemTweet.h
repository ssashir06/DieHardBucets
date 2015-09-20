//
//  ProblemTweet.h
//  DieHardBucketsTweet
//
//  Created by Hiroshi Takeda on 2014/02/06.
//  Copyright (c) 2014年 Hiroshi Takeda. All rights reserved.
//

#ifndef __DieHardBucketsTweet__ProblemTweet__
#define __DieHardBucketsTweet__ProblemTweet__

#include <memory>
#include <random>
#include <list>
#include <string>
#include <DieHardBuckets/Problem.h>
#include <DieHardBuckets/ProblemDot.h>

namespace Diehard
{
    class ProblemTweet : public ProblemDot
    {
    private:
        static std::default_random_engine random_engine;
        
    public:
        ProblemTweet();
        
    public:
        std::shared_ptr<std::list<std::string> > GetTweets() const;
        static std::shared_ptr<std::vector<Volume> > GetRandomCapacities();
        Volume GetRandomGoal();
        
    private:
        const Node* GetGoalNodeRandomly() const;
        static const Node* GetFromNodeRandomly(const Node* node);
        static const Node* GetLowestCostRandomly(const std::list<const Node*>& nodes);
    };
}

#endif /* defined(__DieHardBucketsTweet__ProblemTweet__) */
