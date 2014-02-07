//
//  ProblemDot.h
//  DieHardBucketsConsole
//
//  Created by Hiroshi Takeda on 2014/02/06.
//  Copyright (c) 2014年 Hiroshi Takeda. All rights reserved.
//

#ifndef __DieHardBucketsConsole__ProblemDot__
#define __DieHardBucketsConsole__ProblemDot__

#include <ostream>
#include <DieHardBuckets/Problem.h>

namespace Diehard
{
    class ProblemDot : public Problem
    {
    public:
        ProblemDot(Volume (&capacities)[], Dimention size);
        ProblemDot(const std::vector<Volume>& capacities);
        
    public:
        void PrintGraph(std::ostream& os = std::cout) const;
    };
}

#endif /* defined(__DieHardBucketsConsole__ProblemDot__) */
