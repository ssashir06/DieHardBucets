//
//  ProblemDot.cpp
//  DieHardBucketsConsole
//
//  Created by Hiroshi Takeda on 2014/02/06.
//  Copyright (c) 2014年 Hiroshi Takeda. All rights reserved.
//

#include <sstream>
#include <iostream>
#include "ProblemDot.h"

using namespace std;

namespace Diehard
{
    ProblemDot::ProblemDot(Volume (&capacities)[], Dimention size)
    :Problem(capacities, size) {}
    
    ProblemDot::ProblemDot(const std::vector<Volume>& capacities)
    :Problem(capacities) {}
    
    void ProblemDot::PrintGraph(ostream& os) const
    {
        auto name = [](const Node& node)
        {
            stringstream ss;
            ss << '"' << node.GetName() << '"';
            return ss.str();
        };
        
        os << "digraph G {" << endl;
        
        os << "graph[label=\"Capacity = " << GetName() << " Goal = " << goal_sum << "\"];" << endl;
        
        os << "subgraph cluster0 {" << endl;
        os << "label = \"Start\";" << endl;
        for (auto& node : nodes)
        {
            if (node.GetSum() == 0)
                os << name(node) << ";" << endl;
        }
        os << "}" << endl;
        
        os << "subgraph cluster1 {" << endl;
        os << "label = \"Goal\";" << endl;
        for (auto& node : nodes)
        {
            if (node.GetSum() == goal_sum)
                os << name(node) << ";" << endl;
        }
        os << "}" << endl;
        
        for (auto& node_from : nodes)
        {
            
            for (auto node_to_ptr : node_from.to)
            {
                if (
                    node_from.cost < node_to_ptr->cost &&
                    node_from.is_used && node_to_ptr->is_used)
                    
                    os <<
                        name(node_from) << " -> " <<
                        name(*node_to_ptr) << ";" << endl;
            }
        }
        
        os << "}" << endl;
    }
}