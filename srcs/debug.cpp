#include <fallchallenge.hpp>
#include <debug.hpp>

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

void	debug_data(t_data& data)
{
	std::cerr << "resources: " << data.resources << std::endl;

	debug_routes(data);
	debug_pods(data);
	debug_buildings(data);
}