#include<iostream>
#include <bits/stdc++.h>
#include <limits.h>
#include <algorithm>  
#include <vector>
#include <unordered_map>
#include <queue>
#include <string>
#include<mutex>
#include "travelplanner.hpp"
using namespace std;

int main() {
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
    
    TravelPlanner* tp = TravelPlanner::getTravelPlanner(n, places, paths);
    tp->displayLocations();
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