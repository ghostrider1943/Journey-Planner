#include <iostream>
#include <bits/stdc++.h>
#include <limits.h>
#include <algorithm>  
#include <vector>
#include <unordered_map>
#include <queue>
#include <string>
using namespace std;
class TravelPlanner {
public:
    int n;
    vector<string>locations;
    vector<vector<string>>routes;
    unordered_map<string, int>locationToIndex;
    unordered_map<int, string>indexToLocation;
    unordered_map<string, string>locationToDisplayName;
    vector<vector<double>> edges;
    vector<vector<pair<int,double>>>adj;

    TravelPlanner(int numOfLocations, vector<string>places, vector<vector<string>>paths) {
        n = numOfLocations;
        locations.resize(n);
        locations = places;
        int numOfPaths = paths.size();
        routes.resize(numOfPaths, vector<string>(3));
        routes = paths;
    }
    void displayLocations() {
        cout<<"---------------Welcome to Travel Planner of Bhubaneswar---------------"<<endl;
        cout<<"These are our famous locations : "<<endl;
        for(auto location : locations) {
            cout<<location<<endl;
        }
        cout<<"----------------------------------------------------------------------"<<endl;
    }
    void displayRoutes() {
        cout<<"These are the direct routes from source to destination spot with kms : "<<endl;
        for(auto r : routes) {
            cout<<r[0]<<" to "<<r[1]<<" takes "<<r[2]<<" kms "<<endl;
        }
        cout<<"----------------------------------------------------------------------"<<endl;
    }
    void createEdgeVector() {
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
    void createAdjacencyMatrix() {
        adj.resize(n);
        for(auto edge : edges) {
            int source = edge[0], destination = edge[1];
            double edgeDistance = edge[2];
            adj[source].push_back({destination, edgeDistance});
        }
    }
    void shortestPathWithMinimumStops(string src, string dst) {
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
};
int main() {
    // Write C++ code here
    int n = 11;
    vector<string>places = {"Bhubaneswar Railway Station", "Lingaraj Temple", "Udayagiri and Khandagiri Caves", "Nandankanan Zoological Park", "Dhauli Shanti Stupa", "Kalinga Stadium", "Regional Science Centre", "Odisha State Museum", "Ekamra Kanan Botanical Gardens", "Pathani Samanta Planetarium", "Rajarani Temple"};
    vector<vector<string>>paths = {{"Bhubaneswar Railway Station", "Lingaraj Temple", "3.5"}, 
        {"Bhubaneswar Railway Station", "Udayagiri and Khandagiri Cavese", "6"},
        {"Lingaraj Temple", "Nandankanan Zoological Park", "15"},
        {"Lingaraj Temple", "Dhauli Shanti Stupa", "8"},
        {"Lingaraj Temple", "Rajarani Temple", "4.5"},
        {"Udayagiri and Khandagiri Caves", "Regional Science Centre", "5"},
        {"Nandankanan Zoological Park", "Kalinga Stadium", "12"},
        {"Nandankanan Zoological Park", "Udayagiri and Khandagiri Caves", "9"},
        {"Dhauli Shanti Stupa", "Odisha State Museum", "8"},
        {"Kalinga Stadium",  "Ekamra Kanan Botanical Gardens", "7"},
        {"Regional Science Centre", "Lingaraj Temple", "4"},
        {"Regional Science Centre", "Pathani Samanta Planetarium", "4"},
        {"Regional Science Centre", "Odisha State Museum", "4"},
        {"Regional Science Centre", "Kalinga Stadium", "6"},
        {"Odisha State Museum", "Rajarani Temple", "4.5"},
        {"Odisha State Museum", "Dhauli Shanti Stupa", "8"},
        {"Odisha State Museum", "Kalinga Stadium", "7"},
        {"Ekamra Kanan Botanical Gardens", "Lingaraj Temple", "5"},
        {"Pathani Samanta Planetarium", "Regional Science Centre", "4"},
        {"Pathani Samanta Planetarium", "Dhauli Shanti Stupa", "7"},
        {"Rajarani Temple", "Bhubaneswar Railway Station", "6"}
    };
    TravelPlanner* tp = new TravelPlanner(n, places, paths);
    tp->displayLocations();
    //tp->displayRoutes();
    tp->createEdgeVector();
    tp->createAdjacencyMatrix();
    string prompt;
    cout<<"Do you want to get the shortest path between your source and destination? Type Y or y to proceed : ";
    cin>>prompt;
    while(prompt == "Y" || prompt == "y") {
        string source, destination;
        cout<<"Enter source location ";
        cin.ignore();
        getline(cin, source);
        cout<<"Enter destination location ";
        getline(cin, destination);
        tp->shortestPathWithMinimumStops(source, destination);
        cout<<"Do you want to get the shortest path between your source and destination?";
        cin>>prompt;
    }
    cout<<endl<<"Thanks for using our application."<<endl;
    return 0;
}
