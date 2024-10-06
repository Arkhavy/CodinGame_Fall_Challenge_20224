#include <fallchallenge.hpp>
#include <debug.hpp>

t_data	data;

int	main()
{
	while (42)
	{
		std::cin >> data.resources; std::cin.ignore();


		// route initialization
		int	num_travel_routes;
		std::cin >> num_travel_routes; std::cin.ignore();
		for (int i = 0; i < num_travel_routes; i++)
		{
			t_route	tmp_route;
			std::cin >> tmp_route.building_id_1 >> tmp_route.building_id_2 >> tmp_route.capacity; std::cin.ignore();
			data.routes.push_back(tmp_route);
		}

		// pod initialization
		int	num_pods;
		std::cin >> num_pods; std::cin.ignore();
		for (int i = 0; i < num_pods; i++)
		{
			t_pod	tmp_pod;
			int	num_stops;
			std::cin >> tmp_pod.id >> num_stops;
			for (int j = 0; j < num_stops; j++)
			{
				int	stop_id;
				std::cin >> stop_id;
				tmp_pod.stops.push_back(stop_id);
			}
			std::cin.ignore();
		}

		// building initialization
		int	num_new_buildings;
		std::cin >> num_new_buildings; std::cin.ignore();
		for (int i = 0; i < num_new_buildings; i++)
		{
			t_building	tmp_building;
			std::cin >> tmp_building.type >> tmp_building.id >> tmp_building.pos.x >> tmp_building.pos.y;
			if (tmp_building.type == 0)
			{
				int	num_astronauts;
				std::cin >> num_astronauts;
				for (int j = 0; j < num_astronauts; j++)
				{
					int	astronaut_id;
					std::cin >> astronaut_id;
					tmp_building.astronaut_types.push_back(astronaut_id);
				}
			}
			data.buildings.push_back(tmp_building);
			std::cin.ignore();
		}

		debug_data(data);

		std::cout << "TUBE 0 1;TUBE 0 2;POD 42 0 1 0 2 0 1 0 2" << std::endl; // TUBE | UPGRADE | TELEPORT | POD | DESTROY | WAIT
	} // game loop
	return (0);
}
