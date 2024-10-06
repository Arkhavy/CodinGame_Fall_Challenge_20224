/* ************************************************************************** */
/*                           FALLCHALLENGE.HPP FILE                           */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

typedef struct	s_data			t_data;
typedef struct	s_route			t_route;
typedef struct	s_pod				t_pod;
typedef struct	s_building	t_building;
typedef struct	s_coord			t_coord;

struct	s_coord
{
	int	x;
	int	y;
};

struct	s_data
{
	int											resources;
	std::vector<t_route>		routes;
	std::vector<t_pod>			pods;
	std::vector<t_building>	buildings;
};

struct	s_route
{
	int	building_id_1;
	int	building_id_2;
	int	capacity;
};

struct	s_pod
{
	int								id;
	std::vector<int>	stops; // defined by building_id
};

struct	s_building
{
	int			type; // 0 = landing pad, use vector | other = building type, does not use vector
	int			id;
	t_coord	pos; // pos [x, y] of the building

	std::vector<int>	astronaut_types;
};

/* ************************************************************************** */
/*                                 DEBUG FILE                                 */
/* ************************************************************************** */

/* ******************************* ROUTE DEBUG ****************************** */
void	debug_routes(t_data&	data)
{
	std::cerr << std::endl;
	std::cerr << "/* ************************************************************************** */" << std::endl;
	std::cerr << "/*                                   ROUTES                                   */" << std::endl;
	std::cerr << "/* ************************************************************************** */" << std::endl;
	std::cerr << std::endl;
	for (unsigned int i = 0; i < data.routes.size(); i++)
	{
		std::cerr << "routes[" << i << "].building_id_1: " << data.routes[i].building_id_1 << std::endl;
		std::cerr << "routes[" << i << "].building_id_2: " << data.routes[i].building_id_2 << std::endl;
		std::cerr << "routes[" << i << "].capacity: " << data.routes[i].capacity << std::endl;
		if (i != (data.routes.size() - 1))
			std::cerr << "___" << std::endl;
	}
}

/* ******************************** POD DEBUG ******************************* */
void	debug_pods(t_data& data)
{
	std::cerr << std::endl;
	std::cerr << "/* ************************************************************************** */" << std::endl;
	std::cerr << "/*                                    PODS                                    */" << std::endl;
	std::cerr << "/* ************************************************************************** */" << std::endl;
	std::cerr << std::endl;
	for (unsigned int i = 0; i < data.pods.size(); i++)
	{
		std::cerr << "pod[" << i << "].id: " << data.pods[i].id << std::endl;
		std::cerr << "pod[" << i << "].stops.size(): " << data.pods[i].stops.size() << std::endl;
		std::cerr << "pod[" << i << "].stops: ";
		for (unsigned int j = 0; j < data.pods[i].stops.size(); j++)
		{
			std::cerr << data.pods[i].stops[j];
			if (j != (data.pods[i].stops.size() - 1))
				std::cerr << " | ";
		}
		if (i != (data.pods.size() - 1))
			std::cerr << "___" << std::endl;
	}
}

/* ***************************** BUILDING DEBUG ***************************** */
void	debug_buildings(t_data& data)
{
	std::cerr << std::endl;
	std::cerr << "/* ************************************************************************** */" << std::endl;
	std::cerr << "/*                                  BUILDINGS                                 */" << std::endl;
	std::cerr << "/* ************************************************************************** */" << std::endl;
	std::cerr << std::endl;
	for (unsigned int i = 0; i < data.buildings.size(); i++)
	{
		std::cerr << "data.buildings[" << i << "].type: " << data.buildings[i].type << std::endl;
		std::cerr << "data.buildings[" << i << "].id: " << data.buildings[i].id << std::endl;
		std::cerr << "data.buildings[" << i << "].pos.x: " << data.buildings[i].pos.x << std::endl;
		std::cerr << "data.buildings[" << i << "].pos.y: " << data.buildings[i].pos.y << std::endl;
		if (data.buildings[i].type == 0)
		{
			std::cerr << "data.buildings[" << i << "].astronaut_types: ";
			for (unsigned int j = 0; j < data.buildings[i].astronaut_types.size(); j++)
			{
				std::cerr << data.buildings[i].astronaut_types[j];
				if (j != (data.buildings[i].astronaut_types.size() - 1))
					std::cerr << " | ";
			}
		}
		if (i != (data.buildings.size() - 1))
			std::cerr << std::endl << "___" << std::endl;
	}
	std::cerr << std::endl;
}

/* ******************************* MAIN DEBUG ******************************* */
void	debug_data(t_data& data)
{
	std::cerr << "resources: " << data.resources << std::endl;

	debug_routes(data);
	debug_pods(data);
	debug_buildings(data);
}

/* ************************************************************************** */
/*                             INPUT_HANDLING FILE                            */
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

/* *************************** MAIN INITIALIZATION ************************** */
void	init_data(t_data& data)
{
		std::cin >> data.resources;
		std::cin.ignore();
		init_route(data);
		init_pod(data);
		init_building(data);
}

/* ************************************************************************** */
/*                                  MAIN FILE                                 */
/* ************************************************************************** */
t_data	data;

int	main()
{
	while (42)
	{
		init_data(data);
		debug_data(data);

		std::cout << "TUBE 0 1;TUBE 0 2;POD 42 0 1 0 2 0 1 0 2" << std::endl; // TUBE | UPGRADE | TELEPORT | POD | DESTROY | WAIT
	} // game loop
	return (0);
}
