    #include <iostream>
    #include <string>
    #include <vector>
    #include <algorithm>

    /**
    * Auto-generated code below aims at helping you parse
    * the standard input according to the problem statement.
    **/

    int main()
    {

        // game loop
        while (1) {
            int resources;
            std::cin >> resources; std::cin.ignore();
            int num_travel_routes;
            std::cin >> num_travel_routes; std::cin.ignore();
            for (int i = 0; i < num_travel_routes; i++) {
                int building_id_1;
                int building_id_2;
                int capacity;
                std::cin >> building_id_1 >> building_id_2 >> capacity; std::cin.ignore();
            }
            int num_pods;
            std::cin >> num_pods; std::cin.ignore();
            for (int i = 0; i < num_pods; i++) {
                std::string pod_properties;
                std::getline(std::cin, pod_properties);
            }
            int num_new_buildings;
            std::cin >> num_new_buildings; std::cin.ignore();
            for (int i = 0; i < num_new_buildings; i++) {
                std::string building_properties;
                std::getline(std::cin, building_properties);
            }

            // Write an action using cout. DON'T FORGET THE "<< endl"
            // To debug: cerr << "Debug messages..." << endl;

            std::cout << "TUBE 0 1;TUBE 0 2;POD 42 0 1 0 2 0 1 0 2" << std::endl; // TUBE | UPGRADE | TELEPORT | POD | DESTROY | WAIT
        }
    }