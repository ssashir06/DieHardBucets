//
//  ProblemTweet.cpp
//  DieHardBucketsTweet
//
//  Created by Hiroshi Takeda on 2014/02/06.
//  Copyright (c) 2014年 Hiroshi Takeda. All rights reserved.
//

#include <vector>
#include <random>
#include <sstream>
#include <algorithm>
#include "ProblemTweet.h"

using namespace std;

namespace Diehard
{
    default_random_engine ProblemTweet::random_engine = default_random_engine(random_device()());
    
    ProblemTweet::ProblemTweet()
    : Problem(*GetRandomCapacities()) {}
    
    shared_ptr<list<string> > ProblemTweet::GetTweets() const
    {
        list<const Node*> nodes_route;
        auto node_goal = GetGoalNodeRandomly();
        if (!node_goal) return nullptr;
        
        auto node_ptr = node_goal;
        while (node_ptr)
        {
            nodes_route.push_front(node_ptr);
            if (node_ptr && node_ptr->GetSum() == 0) break;
            node_ptr = GetFromNodeRandomly(node_ptr);
        }
        
        auto tweets = shared_ptr<list<string> >(new list<string>());
        {
            stringstream ss;
            ss << "Capacities: " << GetName();
            ss << " -> ";
            ss << "Request: " << goal_sum;
            tweets->push_back(ss.str());
        }
        for_each(nodes_route.begin(), nodes_route.end(), [&](const Node* node)
                 {
                     stringstream ss;
                     ss << "Bucket: " << node->GetName();
                     tweets->push_back(ss.str());
                 });
        {
            stringstream ss;
            ss << "Final result: ";
            for (Dimention d = 0; d < capacities.size(); d++)
            {
                if (d != 0) ss << "+";
                ss << node_goal->volumes[d];
            }
            ss << "=" << node_goal->GetSum();
            tweets->push_back(ss.str());
        }
        
        return tweets;
    }
    
#pragma mark Random generator
    
    const Node* ProblemTweet::GetGoalNodeRandomly() const
    {
        list<const Node*> nodes_goal;
        for (auto& node : nodes)
        {
            if (
                node.is_used &&
                node.cost < Node::cost_max &&
                node.GetSum() == goal_sum)
                nodes_goal.push_back(&node);
        }
        
        return GetLowestCostRandomly(nodes_goal);
    }
    
    const Node* ProblemTweet::GetFromNodeRandomly(const Node* node)
    {
        list<const Node*> nodes_from(node->from.begin(), node->from.end());
        return GetLowestCostRandomly(nodes_from);
    }
    
    const Node* ProblemTweet::GetLowestCostRandomly(const std::list<const Node*>& nodes)
    {
        Node::Cost cost_min = Node::cost_max;
        for_each(nodes.begin(), nodes.end(), [&](const Node* node)
                 {
                     if (node->cost < cost_min) cost_min = node->cost;
                 });
        
        vector<const Node*> nodes_lowcost;
        for_each(nodes.begin(), nodes.end(), [&](const Node* node)
                 {
                     if (node->cost == cost_min) nodes_lowcost.push_back(node);
                 });
        
        if (nodes_lowcost.empty())
        {
            return nullptr;
        }
        else
        {
            uniform_int_distribution<size_t> dist_idx(0, nodes_lowcost.size() - 1);
            return nodes_lowcost[dist_idx(random_engine)];
        }
    }
    
    shared_ptr<vector<Volume> > ProblemTweet::GetRandomCapacities()
    {
        uniform_int_distribution<Volume> dist_capacity(2, 200);
        uniform_int_distribution<Dimention> dist_dimention(2, 4);
        auto rand_capacity = bind(dist_capacity, random_engine);
        auto dimention = dist_dimention(random_engine);
        
        shared_ptr<vector<Volume> > capacities(new vector<Volume>(dimention));
        for (Dimention i = 0; i < dimention; i++)
        {
            (*capacities)[i] = rand_capacity();
        }
        
        return capacities;
    }
    
    Volume ProblemTweet::GetRandomGoal()
    {
        Volume sum = 0;
        for_each(capacities.begin(), capacities.end(), [&](Volume v) { sum += v; });
        
        uniform_int_distribution<Volume> dist_goal(1, sum);
        return dist_goal(random_engine);
    }
    
}
