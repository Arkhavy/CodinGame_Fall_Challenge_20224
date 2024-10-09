#include <main.hpp>
#include <debug.hpp>

/* ************************************************************************** */
/*                                  DEBUG.CPP                                 */
/* ************************************************************************** */

/* **************************** DISPLAY FUNCTIONS *************************** */
void	displayRoute(t_route const& route)
{
	std::cerr << "b1Id = " << route.b1Id;
	std::cerr << " | b2Id = " << route.b2Id;
	std::cerr << " | capacity = " << route.capacity;

	std::cerr << std::endl;

	std::cerr << "b1.type = " << route.b1.type;
	std::cerr << " | b1.id = " << route.b1.id;
	std::cerr << " | b1.pos.x = " << route.b1.pos.x;
	std::cerr << " | b1.pos.y = " << route.b1.pos.y;

	std::cerr << std::endl;

	std::cerr << "b2.type = " << route.b2.type;
	std::cerr << " | b2.id = " << route.b2.id;
	std::cerr << " | b2.pos.x = " << route.b2.pos.x;
	std::cerr << " | b2.pos.y = " << route.b2.pos.y;

	std::cerr << std::endl;
}

void	displayBuilding(t_building const& building)
{
	std::cerr << "type = " << building.type;
	std::cerr << " | id = " << building.id;
	std::cerr << " | pos.x = " << building.pos.x;
	std::cerr << " | pos.y = " << building.pos.y;

	std::cerr << std::endl;

	std::cerr << "astronaut Types = ";
	for (unsigned int i = 0; i < building.astronautTypes.size(); i++)
		std::cerr << building.astronautTypes[i] << " ";

	std::cerr << std::endl;

	std::cerr << "routes = " << building.routes.size() << std::endl;
	for (unsigned int i = 0; i < building.routes.size(); i++)
	{
		std::cerr << i << ".b1Id = " << building.routes[i].b1Id;
		std::cerr << " | " << i << ".b2Id = " << building.routes[i].b2Id;
		std::cerr << " | " << i << ".capacity = " << building.routes[i].capacity;
		std::cerr << std::endl;
	}
}

void	displayPod(t_pod const& pod)
{
	std::cerr << "id = " << pod.id << std::endl;
	std::cerr << "checkpoints = ";
	for (unsigned int j = 0; j < pod.checkpoints.size(); j++)
		std::cerr << pod.checkpoints[j] << " ";
	std::cerr << std::endl;
}

/* ***************************** DEBUG FUNCTIONS **************************** */
void	debugTubes(t_data const& data)
{
	std::cerr << std::endl;
	std::cerr << "/* ************************************************************************** */" << std::endl;
	std::cerr << "/*                                    TUBES                                   */" << std::endl;
	std::cerr << "/* ************************************************************************** */" << std::endl;
	std::cerr << std::endl;

	for (unsigned int i = 0; i < data.tubes.size(); i++)
	{
		std::cerr << "TUBE " << i << ":" << std::endl;
		displayRoute(data.tubes[i]);
	}
}

void	debugTeleporters(t_data const& data)
{
	std::cerr << std::endl;
	std::cerr << "/* ************************************************************************** */" << std::endl;
	std::cerr << "/*                                 TELEPORTERS                                */" << std::endl;
	std::cerr << "/* ************************************************************************** */" << std::endl;
	std::cerr << std::endl;

	for (unsigned int i = 0; i < data.teleporters.size(); i++)
	{
		std::cerr << "TELEPORTER " << i << ":" << std::endl;
		displayRoute(data.teleporters[i]);
	}
}

void	debugRoutes(t_data const& data)
{
	std::cerr << std::endl;
	std::cerr << "/* ************************************************************************** */" << std::endl;
	std::cerr << "/*                                   ROUTES                                   */" << std::endl;
	std::cerr << "/* ************************************************************************** */" << std::endl;
	std::cerr << std::endl;

	for (unsigned int i = 0; i < data.routes.size(); i++)
	{
		std::cerr << "ROUTE " << i << ":" << std::endl;
		displayRoute(data.routes[i]);
	}
}

void	debugLandingPads(t_data const& data)
{
	std::cerr << std::endl;
	std::cerr << "/* ************************************************************************** */" << std::endl;
	std::cerr << "/*                                LANDING PADS                                */" << std::endl;
	std::cerr << "/* ************************************************************************** */" << std::endl;
	std::cerr << std::endl;

	for (unsigned int i = 0; i < data.landingPads.size(); i++)
	{
		std::cerr << "LANDING PAD " << i << ":" << std::endl;
		displayBuilding(data.landingPads[i]);
	}
}

void	debugModules(t_data const& data)
{
	std::cerr << std::endl;
	std::cerr << "/* ************************************************************************** */" << std::endl;
	std::cerr << "/*                                   MODULES                                  */" << std::endl;
	std::cerr << "/* ************************************************************************** */" << std::endl;
	std::cerr << std::endl;

	for (unsigned int i = 0; i < data.modules.size(); i++)
	{
		std::cerr << "MODULE " << i << ":" << std::endl;
		displayBuilding(data.modules[i]);
	}
}

void	debugBuildings(t_data const& data)
{
	std::cerr << std::endl;
	std::cerr << "/* ************************************************************************** */" << std::endl;
	std::cerr << "/*                                  BUILDINGS                                 */" << std::endl;
	std::cerr << "/* ************************************************************************** */" << std::endl;
	std::cerr << std::endl;

	for (unsigned int i = 0; i < data.buildings.size(); i++)
	{
		std::cerr << "BUILDING " << i << ":" << std::endl;
		displayBuilding(data.buildings[i]);
	}
}

void	debugPods(t_data const& data)
{
	std::cerr << std::endl;
	std::cerr << "/* ************************************************************************** */" << std::endl;
	std::cerr << "/*                                    PODS                                    */" << std::endl;
	std::cerr << "/* ************************************************************************** */" << std::endl;
	std::cerr << std::endl;

	for (unsigned int i = 0; i < data.pods.size(); i++)
	{
		std::cerr << "POD " << i << ":" << std::endl;
		displayPod(data.pods[i]);
	}
}

void	debugData(t_data const& data)
{
	std::cerr << "resources = " << data.resources << std::endl;

	debugRoutes(data);
	debugTubes(data);
	debugTeleporters(data);

	debugBuildings(data);
	debugLandingPads(data);
	debugModules(data);

	debugPods(data);
}