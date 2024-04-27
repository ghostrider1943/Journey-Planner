# travel-planner-bbsr

This is a DSA project that implements a modified Dijkstra's algorithm in C++ to create a travel planner for Bhubaneswar. 
<br> <br> The project aims to provide users with the shortest path and minimum number of stops between famous spots in the city. By representing the city's locations and routes as a graph, the algorithm efficiently computes the optimal route. <br><br>
Implemented within a limited timeframe, this project showcases the application of graph algorithms in solving real-world travel planning problems, while also serving as a learning opportunity for students to reinforce their knowledge of data structures and algorithms.<br>

<br>
#To run the application, run the following commands
<br><br>
#Creating objects
<br>
g++ -c travelplanner.cpp 
<br><br>
#Creating library
<br>
ar ru travelplanner_library.a travelplanner.o  
<br><br>
#Client
<br>
g++ -o client client.cpp travelplanner_library.a  
<br><br>
#Running client
<br>
./client 
