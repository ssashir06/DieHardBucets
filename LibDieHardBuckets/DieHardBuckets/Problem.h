//
//  Problem.h
//  diehard_buckets
//
//  Created by Hiroshi Takeda on 2014/02/01.
//
//

#ifndef diehard_buckets_Problem_h
#define diehard_buckets_Problem_h

#include <vector>
#include <list>
#include "Volume.h"
#include "Node.h"

namespace Diehard
{
    class Problem
    {
    protected:
        std::vector<Volume> capacities;
        std::list<Node> nodes;
        Volume goal_sum;
        
    public:
        Problem(Volume (&capacities)[], Dimention size);
        Problem(const std::vector<Volume>& capacities);
        
        void BuildGraph();
        void Resolve(Volume goal_sum);
        
        std::string GetName() const;
        
    private:
        void CreateNodes();
        void Link();
        void SetCost();
        void Strip();
        Node* GetNode(const std::vector<Volume>& volumes);
    };
}


#endif
