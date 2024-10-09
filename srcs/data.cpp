#include <main.hpp>
#include <data.hpp>

/* ************************************************************************** */
/*                                  DATA.CPP                                  */
/* ************************************************************************** */

/* ************************ MAIN DATA INITIALIZATION ************************ */
void	initBuilding(t_data& data)
{
	int	newBuildingNumber;
	std::cin >> newBuildingNumber;
	std::cin.ignore();

	for (int i = 0; i < newBuildingNumber; i++)
	{
		t_building	tmpBuilding;
		std::cin >> tmpBuilding.type >> tmpBuilding.id;
		std::cin >> tmpBuilding.pos.x >> tmpBuilding.pos.y;

		if (tmpBuilding.type == LANDING_PAD)
		{
			int	astronautNumber;
			std::cin >> astronautNumber;

			for (int j = 0; j < astronautNumber; j++)
			{
				int	astronautType;
				std::cin >> astronautType;
				tmpBuilding.astronautTypes.push_back(astronautType);
			}
		}
		data.buildings.push_back(tmpBuilding);
		std::cin.ignore();
	}
}

void	initPod(t_data& data)
{
	int	podNumber;
	std::cin >> podNumber;
	std::cin.ignore();

	for (int i = 0; i < podNumber; i++)
	{
		t_pod	tmpPod;
		int	checkpointNumber;
		std::cin >> tmpPod.id >> checkpointNumber;

		for (int j = 0; j < checkpointNumber; j++)
		{
			int	checkpointId;
			std::cin >> checkpointId;
			tmpPod.checkpoints.push_back(checkpointId);
		}
		std::cin.ignore();
		data.pods.push_back(tmpPod);
	}
}

void	initRoute(t_data& data)
{
	int	routeNumber;
	std::cin >> routeNumber;
	std::cin.ignore();

	for (int i = 0; i < routeNumber; i++)
	{
		t_route	tmpRoute;
		std::cin >> tmpRoute.b1Id >> tmpRoute.b2Id >> tmpRoute.capacity;
		std::cin.ignore();
		data.routes.push_back(tmpRoute);
	}
}

void	initData(t_data& data)
{
	std::cin >> data.resources;
	std::cin.ignore();
	initRoute(data);
	initPod(data);
	initBuilding(data);
}

/* ********************* ADDITIONAL DATA INITIALIZATION ********************* */
bool	isAlreadyInBuildingVector(t_building const& building, std::vector<t_building> const& buildingVector)
{
	for (unsigned int i = 0; i < buildingVector.size(); i++)
	{
		if (building.id == buildingVector[i].id)
			return (true);
	}
	return (false);
}

bool	isAlreadyInRouteVector(t_route const& route, std::vector<t_route> const& routeVector)
{
	for (unsigned int i = 0; i < routeVector.size(); i++)
	{
		if (route.b1Id == routeVector[i].b1Id)
			if (route.b2Id == routeVector[i].b2Id)
				return (true);
		if (route.b2Id == routeVector[i].b1Id)
			if (route.b1Id == routeVector[i].b2Id)
				return (true);
	}
	return (false);
}

void	addRoutesToBuilding(t_building& building, std::vector<t_route>& routes)
{
	for (unsigned int j = 0; j < routes.size(); j++)
	{
		if (isAlreadyInRouteVector(routes[j], building.routes))
			continue;
		if (building.routes.size() == MAX_LINKED_ROUTES)
			continue;

		if (building.id == routes[j].b1Id || building.id == routes[j].b2Id)
			building.routes.push_back(routes[j]);
	}
}

void	initAdditionalBuilding(t_data& data)
{
	for (unsigned int i = 0; i < data.buildings.size(); i++)
	{
		addRoutesToBuilding(data.buildings[i], data.routes);
		if (data.buildings[i].type == LANDING_PAD)
		{
			if (isAlreadyInBuildingVector(data.buildings[i], data.landingPads))
				continue;

			data.landingPads.push_back(data.buildings[i]);
		}
		else
		{
			if (isAlreadyInBuildingVector(data.buildings[i], data.modules))
				continue;

			data.modules.push_back(data.buildings[i]);
		}
	}
}

void	initAdditionalRoute(t_data& data)
{
	for (unsigned int i = 0; i < data.routes.size(); i++)
	{
		for (unsigned int j = 0; j < data.buildings.size(); j++)
		{
			if (data.routes[i].b1Id == data.buildings[j].id)
				data.routes[i].b1 = data.buildings[j];
			else if (data.routes[i].b2Id == data.buildings[j].id)
				data.routes[i].b2 = data.buildings[j];
		}

		if (data.routes[i].capacity > 0)
			data.tubes.push_back(data.routes[i]);
		else
			data.teleporters.push_back(data.routes[i]);
	}
}

void	initAdditionalData(t_data& data)
{
	initAdditionalRoute(data);
	initAdditionalBuilding(data);
}

/* ****************************** DATA DELETION ***************************** */
void	clearData(t_data& data)
{
	// clear data.routes
	data.routes.clear();

	// clear data.pods.checkpoints + data.pods
	for (unsigned int i = 0; i < data.pods.size(); i++)
		data.pods[i].checkpoints.clear();
	data.pods.clear();

	// clear data.tubes
	data.tubes.clear();

	// clear data.teleporters
	data.teleporters.clear();
}