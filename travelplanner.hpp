#ifndef travelplanner_hpp
#define travelplanner_hpp

#include<iostream>
using namespace std;

class TravelPlanner {

    int n;
    vector<string>locations;
    vector<vector<string>>routes;
    unordered_map<string, int>locationToIndex;
    unordered_map<int, string>indexToLocation;
    unordered_map<string, string>locationToDisplayName;
    vector<vector<double>> edges;
    vector<vector<pair<int,double>>>adj;
    static TravelPlanner* travelPlannerInstance;
    
    TravelPlanner(int numOfLocations, vector<string>places, vector<vector<string>>paths);
    TravelPlanner(const TravelPlanner &);
    TravelPlanner operator=(const TravelPlanner &);

    public:
        static TravelPlanner* getTravelPlanner(int numOfLocations, vector<string>places, vector<vector<string>>paths);
        void displayLocations();
        void displayRoutes();
        void createEdgeVector();
        void createAdjacencyMatrix();
        void shortestPathWithMinimumStops(string src, string dst);
};

#endif
