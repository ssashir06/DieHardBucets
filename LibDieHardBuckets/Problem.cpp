//
//  Problem.cpp
//  diehard_buckets
//
//  Created by Hiroshi Takeda on 2014/02/01.
//
//

#include <cmath>
#include <iostream>
#include <sstream>
#include "Problem.h"
#include "Volume.h"

using namespace std;

namespace Diehard
{
#pragma mark Constractor
    
    Problem::Problem(Volume (&capacities)[], Dimention size)
    :capacities(size), goal_sum(0)
    {
        for (Dimention i=0; i<size; i++)
            this->capacities[i] = capacities[i];
    }
    
    Problem::Problem(const std::vector<Volume>& capacities)
    :capacities(capacities), goal_sum(0){}
    
#pragma mark Public functions
    void Problem::BuildGraph()
    {
        CreateNodes();
        Link();
        SetCost();
    }
    
    void Problem::Resolve(Volume goal_sum)
    {
        this->goal_sum = goal_sum;
        Strip();
    }
    
#pragma mark Private functions
    
    void Problem::CreateNodes()
    {
        nodes.clear();
        list<Node> edges;
        auto dimention = capacities.size();
        auto origin = Node(dimention);
        
        edges.push_back(origin);
        nodes.push_back(origin);
        
        for (Dimention d = 0; d < dimention; d++)
        {
            list<Node> nodes_new;
            for (auto& node : nodes)
            {
                nodes_new.push_back(Node(node, d, capacities[d]));
            }
            nodes.insert(nodes.end(), nodes_new.begin(), nodes_new.end());
            
            list<Node> edges_new;
            for (auto& edge : edges)
            {
                for (Volume v = 1; v <= capacities[d]; v++)
                {
                    auto n = Node(edge, d, v);
                    if (v == capacities[d])
                        edges_new.push_back(n);
                    else
                        nodes.push_back(n);
                }
            }
            edges.insert(edges.end(), edges_new.begin(), edges_new.end());
        }
    }
    
    void Problem::Link()
    {
        for (auto& node : nodes)
        {
            auto actions = node.GetActions(capacities);
            node.connection.clear();
            for (auto& action : actions)
            {
                auto node_action = GetNode(action);
                if (node_action != nullptr)
                    node.connection.push_back(node_action);
            }
        }
    }
    
    void Problem::SetCost()
    {
        auto start_node_ptr = GetNode(vector<Volume>(capacities.size(), 0));
        if (!start_node_ptr) return;
        
        auto nodes_route = shared_ptr<list<Node*> >(new list<Node*>());
        nodes_route->push_back(start_node_ptr);
        
        for (auto& node : nodes) node.cost = Node::cost_max;
        start_node_ptr->cost = 0;
        Node::Cost cost = 0;
        
        while (!nodes_route->empty())
        {
            auto nodes_route_next = shared_ptr<list<Node*> >(new list<Node*>());
            
            cost++;
            for (auto node_ptr : *nodes_route)
            {
                for (auto node_next_ptr : node_ptr->connection)
                {
                    if (node_next_ptr->cost > cost)
                    {
                        nodes_route_next->push_back(node_next_ptr);
                        node_next_ptr->cost = cost;
                    }
                }
            }
            
            nodes_route = nodes_route_next;
        }
    }
    
    void Problem::Strip()
    {
        auto nodes_to = shared_ptr<list<Node*> >(new list<Node*>());
        for (auto& node : nodes)
        {
            
            if (node.cost != Node::cost_max && node.GetSum() == goal_sum)
            {
                node.is_used = true;
                node.connection.clear();
                nodes_to->push_back(&node);
            }
            else
            {
                node.is_used = false;
            }
        }
        
        while (!nodes_to->empty())
        {
            auto nodes_to_next = shared_ptr<list<Node*> >(new list<Node*>());
            for (auto node_to_ptr : *nodes_to)
            {
                for (auto& node_from : nodes)
                {
                    if (node_from.cost != node_to_ptr->cost - 1) continue;
                    
                    bool is_connected = false;
                    for (auto node_to_ptr_2 : node_from.connection)
                    {
                        if (node_to_ptr_2 != node_to_ptr) continue;
                        is_connected = true;
                        break;
                    }
                    
                    if (is_connected)
                    {
                        nodes_to_next->push_back(&node_from);
                        node_from.is_used = true;
                    }
                }
            }
            
            nodes_to_next->unique();
            nodes_to = nodes_to_next;
        }
    }
    
    Node* Problem::GetNode(const vector<Volume>& volumes)
    {
        for (auto& node : nodes)
        {
            if (equal(volumes.begin(), volumes.end(), node.volumes.begin()))
                return &node;
        }
        return nullptr;
    }
}