#include <main.hpp>
#include <data.hpp>
#include <fallmath.hpp>

/* ************************************************************************** */
/*                                  DATA.CPP                                  */
/* ************************************************************************** */

/* *************************** UTILITARY FUNCTIONS ************************** */
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

bool	isRouteCreated(t_building const& building, t_building const& target)
{
	for (unsigned int i = 0; i < building.routes.size(); i++)
	{
		if (target.id == building.routes[i].b1Id || target.id == building.routes[i].b2Id)
			return (true);
	}
	return (false);
}

bool	isRouteCreated(std::vector<t_route> const& routes, t_building const& b1, t_building const& b2)
{
	for (unsigned int i = 0; i < routes.size(); i++)
	{
		if (isInRoute(b1, routes[i]) && isInRoute(b2, routes[i]))
			return (true);
	}
	return (false);
}

bool	isInRoute(t_building const& building, t_route const& route)
{
	if (building.id == route.b1Id || building.id == route.b2Id)
		return (true);
	return (false);
}

bool	isRouteCreationPossible(t_data const& data, t_building const& building, t_building const& target)
{
	// Check if a building is on the segment about to be created
	for (unsigned int i = 0; i < data.buildings.size(); i++)
	{
		if (data.buildings[i].id == building.id || data.buildings[i].id == target.id)
			continue; // if building C = building A or B, no need to check
		if (isOnSegment(building, target, data.buildings[i]))
			return (false); // means data.buildings[i] is between building and tmpTarget
	}

	// Check if a segment is crossing the segment about to be created
	for (unsigned int i = 0; i < data.routes.size(); i++)
	{
		if (isInRoute(building, data.routes[i]) || isInRoute(target, data.routes[i]))
			continue; //  no need to check if building or target are concerned by the route about to be checked
		if (isCrossing(building, target, data.routes[i].b1, data.routes[i].b2))
			return (false); // means the route about to be created is crossed by an already existing route
	}

	// Check resource usage
	double	distance = getDistance(building, target);
	if ((distance * 10 + COST_POD) >= data.resources)
		return (false); // not enough resource to build the route with pod included
	return (true);
}

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
	data.podNumber = data.pods.size();
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