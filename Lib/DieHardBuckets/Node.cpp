//
//  Node.cpp
//  diehard_buckets
//
//  Created by Hiroshi Takeda on 2014/02/01.
//
//

#include <sstream>
#include "Dimention.h"
#include "Node.h"

using namespace std;

namespace Diehard
{
    Node::Node(const vector<Volume>& volumes)
    : volumes(volumes), cost(cost_max), is_used(true)
    {}
    
    Node::Node(Dimention dim, int volume_all)
    : volumes(vector<Volume>(dim, volume_all)), cost(cost_max), is_used(true)
    {}
    
    Node::Node(const Node& node_src)
    : volumes(node_src.volumes), from(node_src.from), to(node_src.to), cost(cost_max), is_used(true)
    {}
    
    Node::Node(const Node& node_src, Dimention dim, Volume v)
    : volumes(node_src.volumes), from(node_src.from), to(node_src.to), cost(cost_max), is_used(true)
    {
        volumes[dim] = v;
    }
    
    list<vector<Volume> > Node::GetActions(const vector<Volume>& capacities) const
    {
        auto dimention = volumes.size();
        auto d_nodes = vector<const Node*>(dimention);
        list<vector<Volume> > result;
        
        for (auto d = 0; d < dimention; d++)
        {
            vector<Volume> v_zero(volumes);
            vector<Volume> v_max(volumes);
            v_zero[d] = 0;
            v_max[d] = capacities[d];
            if (volumes[d] != v_zero[d]) result.push_back(v_zero);
            if (volumes[d] != v_max[d]) result.push_back(v_max);
        }
        
        for (auto d1 = 0; d1 < dimention; d1++)
        {
            for (auto d2 = 0; d2 < dimention; d2++)
            {
                if (d1 == d2) continue;
                
                auto vd1 = volumes[d1] + volumes[d2] - capacities[d2];
                auto vd2 = capacities[d2];
                if (vd1 < 0)
                {
                    vd2 += vd1;
                    vd1 = 0;
                }
                
                if (volumes[d1] != vd1 && volumes[d2] != vd2)
                {
                    vector<Volume> v_swap(volumes);
                    v_swap[d1] = vd1;
                    v_swap[d2] = vd2;
                    result.push_back(v_swap);
                }
            }
        }
        
        return result;
    }
    
    string Node::GetName() const
    {
        stringstream ss;
        ss << "(";
        for (size_t i = 0; i < volumes.size(); i++)
        {
            if (i != 0) ss << ",";
            ss << volumes[i];
        }
        ss << ")";
        return ss.str();
    }
    
    Volume Node::GetSum() const
    {
        Volume sum = 0;
        for (auto v : volumes)
        {
            sum += v;
        }
        return sum;
    }
}