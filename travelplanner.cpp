#include<iostream>
#include <bits/stdc++.h>
#include <limits.h>
#include <algorithm>  
#include <vector>
#include <unordered_map>
#include <queue>
#include <string>
#include "travelplanner.hpp"
using namespace std;

TravelPlanner* TravelPlanner :: travelPlannerInstance = nullptr;

TravelPlanner ::  TravelPlanner(int numOfLocations, vector<string>places, vector<vector<string>>paths) {
        n = numOfLocations;
        locations.resize(n);
        locations = places;
        int numOfPaths = paths.size();
        routes.resize(numOfPaths, vector<string>(3));
        routes = paths;
}

TravelPlanner* TravelPlanner :: getTravelPlanner(int numOfLocations, vector<string>places, vector<vector<string>>paths) {
    if(travelPlannerInstance == nullptr) {
        travelPlannerInstance = new TravelPlanner(numOfLocations, places, paths);
    }
    return travelPlannerInstance; 
}

void TravelPlanner :: displayLocations() {
    cout<<"---------------Welcome to Travel Planner of Bhubaneswar---------------"<<endl;
    cout<<"These are our famous locations : "<<endl;
    for(auto location : locations) {
        cout<<location<<endl;
    }
    cout<<"----------------------------------------------------------------------"<<endl;
}

void TravelPlanner :: displayRoutes() {
    cout<<"These are the direct routes from source to destination spot with kms : "<<endl;
    for(auto r : routes) {
        cout<<r[0]<<" to "<<r[1]<<" takes "<<r[2]<<" kms "<<endl;
    }
    cout<<"----------------------------------------------------------------------"<<endl;
}

void TravelPlanner :: createEdgeVector() {
    int index = 0;
    for(auto location : locations) {
        string tmpLocation = location;
        transform(tmpLocation.begin(), tmpLocation.end(), tmpLocation.begin(), ::tolower);
        locationToIndex[tmpLocation] = index;
        indexToLocation[index] = tmpLocation;
        locationToDisplayName[tmpLocation] = location;
        index++;
    }
    edges.resize(routes.size());
    index = 0;
    for(auto r : routes) {
        string source = r[0], destination = r[1];
        transform(source.begin(), source.end(), source.begin(), ::tolower);
        transform(destination.begin(), destination.end(), destination.begin(), ::tolower);
        string kilometers = r[2];
        double pathDistance = stod(kilometers);
        int sourceIndex = locationToIndex[source], destinationIndex = locationToIndex[destination];
        vector<double>temp = {sourceIndex, destinationIndex, pathDistance};
        edges[index++] = temp;
    }
}

void TravelPlanner :: createAdjacencyMatrix() {
    adj.resize(n);
    for(auto edge : edges) {
        int source = edge[0], destination = edge[1];
        double edgeDistance = edge[2];
        adj[source].push_back({destination, edgeDistance});
    }
}

void TravelPlanner :: shortestPathWithMinimumStops(string src, string dst) {
    priority_queue<pair<double, pair<int,int>>, vector<pair<double, pair<int,int>>>, greater<pair<double, pair<int,int>>>>p;
    transform(src.begin(), src.end(), src.begin(), ::tolower);
    transform(dst.begin(), dst.end(), dst.begin(), ::tolower);
    if(locationToIndex.find(src) == locationToIndex.end() || locationToIndex.find(dst) == locationToIndex.end()) {
        cout<<"Sorry, these locations are not listed in our list, please try again!"<<endl;
    } else {
        int source = locationToIndex[src];
        int destination = locationToIndex[dst];
        vector<double>distance(n, INT_MAX);
        vector<int>parent(n, -1);
        vector<int>stops(n, INT_MAX);
        distance[source] = 0;
        stops[source] = 0;
        parent[source] = source;
        p.push({0, {0, source}});
        double finalAns = INT_MAX;
        while(!p.empty()) {
            auto top = p.top();
            p.pop();
            double currentDistance = top.first;
            int currentStops = top.second.first, u = top.second.second;
            if(distance[u] < currentDistance) continue;
            if(u == destination) {
                finalAns = distance[destination];
                break;
            }
            for(auto x : adj[u]) {
                int totalStops = currentStops + 1;
                int v = x.first;
                double edgeDistance = x.second;
                double totalDistance = currentDistance + edgeDistance;
                if(distance[v] > totalDistance) {
                    distance[v] = totalDistance;
                    stops[v] = totalStops;
                    parent[v] = u;
                    p.push({distance[v], {stops[v], v}});
                } else if(distance[v] == totalDistance) {
                    if(stops[v] > totalStops) {
                        stops[v] = totalStops;
                        parent[v] = u;
                        p.push({distance[v], {stops[v], v}});
                    }
                }
            }
        }
        if(finalAns == INT_MAX) {
            cout<<"Sorry there are no routes available!"<<endl;
        } else {
            int finalStops = stops[destination] > 0 ? stops[destination] - 1 : 0;
            int sizeOfPath = stops[destination] + 1;
            vector<string>finalPath(sizeOfPath);
            int index = sizeOfPath - 1;
            int node = destination;
            while(index >= 0 && parent[node] != node) {
                finalPath[index--] = indexToLocation[node];
                node = parent[node];
            }
            finalPath[index--] = indexToLocation[node];
            cout<<"The total distance that has to be travelled is "<<finalAns<< " kms. "<<endl;
            cout<<"The number of stops will be "<<finalStops<<". "<<endl;
            cout<<"The path will be: "<<endl;
            for(int i=0; i<finalPath.size(); i++) {
                if(i == finalPath.size() - 1) {
                    cout<<locationToDisplayName[finalPath[i]]<<"."<<endl;
                } else {
                    cout<<locationToDisplayName[finalPath[i]]<<" -> ";
                }
            }
            cout<<endl;
        }
    }
}
