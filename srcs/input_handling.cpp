#include <fallchallenge.hpp>
#include <input_handling.hpp>

/* ************************************************************************** */
/*                             INPUT_HANDLING.CPP                             */
/* ************************************************************************** */

/* ************************* BUILDING INITIALIZATION ************************ */
void	init_building(t_data& data)
{
	int	num_new_buildings;
	std::cin >> num_new_buildings;
	std::cin.ignore();
	for (int i = 0; i < num_new_buildings; i++)
	{
		t_building	tmp_building;
		std::cin >> tmp_building.type >> tmp_building.id;
		std::cin >> tmp_building.pos.x >> tmp_building.pos.y;
		if (tmp_building.type == 0) // if landing pad, get astronauts number and type
		{
			int	num_astronauts;
			std::cin >> num_astronauts;
			for (int j = 0; j < num_astronauts; j++)
			{
				int	astronaut_type;
				std::cin >> astronaut_type;
				tmp_building.astronaut_types.push_back(astronaut_type);
			}
		}
		data.buildings.push_back(tmp_building);
		std::cin.ignore();
	}
}

/* *************************** POD INITIALIZATION *************************** */
void	init_pod(t_data& data)
{
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
		data.pods.push_back(tmp_pod);
	}
}

/* ************************** ROUTE INITIALIZATION ************************** */
void	init_route(t_data& data)
{
	int	num_travel_routes;
	std::cin >> num_travel_routes;
	std::cin.ignore();
	for (int i = 0; i < num_travel_routes; i++)
	{
		t_route	tmp_route;
		std::cin >> tmp_route.building_id_1 >> tmp_route.building_id_2 >> tmp_route.capacity;
		std::cin.ignore();
		data.routes.push_back(tmp_route);
	}
}

/* *************************** DATA INITIALIZATION ************************** */
void	init_data(t_data& data)
{
		std::cin >> data.resources;
		std::cin.ignore();
		init_route(data);
		init_pod(data);
		init_building(data);
}