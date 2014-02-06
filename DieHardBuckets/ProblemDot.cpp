//
//  ProblemDot.cpp
//  DieHardBucketsConsole
//
//  Created by Hiroshi Takeda on 2014/02/06.
//  Copyright (c) 2014年 Hiroshi Takeda. All rights reserved.
//

#include <sstream>
#include "ProblemDot.h"

using namespace std;

namespace Diehard
{
    ProblemDot::ProblemDot(Volume (&capacities)[], Dimention size)
    :Problem(capacities, size){}
    
    ProblemDot::ProblemDot(const std::vector<Volume>& capacities)
    :Problem(capacities){}
    
    void ProblemDot::PrintGraph() const
    {
        auto name = [](const Node& node)
        {
            stringstream ss;
            ss << '"' << node.GetName() << '"';
            return ss.str();
        };
        
        cout << "digraph G {" << endl;
        
        cout << "graph[label=\"Capacity = (";
        for (size_t i = 0; i < capacities.size(); i++)
        {
            if (i != 0) cout << ",";
            cout << capacities[i];
        }
        cout << ") Goal = " << goal_sum << "\"];" << endl;
        
        cout << "subgraph cluster0 {" << endl;
        cout << "label = \"Start\";" << endl;
        for (auto& node : nodes)
        {
            if (node.GetSum() == 0)
                cout << name(node) << ";" << endl;
        }
        cout << "}" << endl;
        
        cout << "subgraph cluster1 {" << endl;
        cout << "label = \"Goal\";" << endl;
        for (auto& node : nodes)
        {
            if (node.GetSum() == goal_sum)
                cout << name(node) << ";" << endl;
        }
        cout << "}" << endl;
        
        for (auto& node_from : nodes)
        {
            
            for (auto node_to_ptr : node_from.connection)
            {
                if (
                    node_from.cost < node_to_ptr->cost &&
                    node_from.is_used && node_to_ptr->is_used)
                    
                    cout <<
                        name(node_from) << " -> " <<
                        name(*node_to_ptr) << ";" << endl;
            }
        }
        
        cout << "}" << endl;
    }
}