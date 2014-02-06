//
//  Node.h
//  diehard_buckets
//
//  Created by Hiroshi Takeda on 2014/02/01.
//
//

#ifndef diehard_buckets_Node_h
#define diehard_buckets_Node_h

#include <vector>
#include <list>
#include <string>
#include <climits>
#include "Dimention.h"
#include "Volume.h"

namespace Diehard
{
    class Node
    {
    public:
        typedef int Cost;
        static const Cost cost_max = INT_MAX;
        
    public:
        std::vector<Volume> volumes;
        std::list<Node*> from, to;
        Cost cost;
        bool is_used;
        
    public:
        Node(const std::vector<Volume>& volumes);
        Node(Dimention dim, int volume_all = 0);
        Node(const Node& node_src);
        Node(const Node& node_src, Dimention dim, Volume v);
        
        std::list<std::vector<Volume> > GetActions(const std::vector<Volume>& capacities) const;
        
        std::string GetName() const;
        
        Volume GetSum() const;
    };
}

#endif
