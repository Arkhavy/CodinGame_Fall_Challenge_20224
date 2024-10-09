/* ************************************************************************** */
/*                                  MAIN.HPP                                  */
/* ************************************************************************** */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

typedef	struct	s_data			t_data; // contains everything
typedef	struct	s_route			t_route; // contains route = pod + 2 buildings
typedef	struct	s_pod				t_pod; // contains pod = route + building list
typedef	struct	s_building	t_building; // contains building = contains building + route

typedef	struct	s_coord			t_coord; // contains [x, y]

struct	s_coord
{
	int	x;
	int	y;
};

struct	s_data
{
	int	resources;
	int	podNumber;

	std::vector<t_route>			routes; // TUBES and TELEPORTERS
	std::vector<t_pod>				pods; // PODS on TUBES
	std::vector<t_building>		buildings; // ALL BUILDINGS

	std::vector<t_building>		landingPads; // only LANDING PADS from BUILDINGS
	std::vector<t_building>		modules; // only MODULES from BUILDINGS

	std::vector<t_route>			tubes; // only TUBES from ROUTES
	std::vector<t_route>			teleporters; // only TELEPORTERS from ROUTES
};

struct	s_building
{
	int										type; // 0 if LANDING PAD, else type from 1 to 20
	int										id; // buildingId
	t_coord								pos; // pos[x, y] of building
	std::vector<int>			astronautTypes; // types of astronauts according to buildings

	std::vector<t_route>	routes; // list of routes linked to building
};

struct	s_route
{
	int									b1Id;
	int									b2Id;
	t_building					b1; // building 1 of route
	t_building					b2; // building 2 of route

	int									capacity; // number of pod that can be present, 0 if teleporter
};

struct	s_pod
{
	int								id; // podId, defines its priority
	std::vector<int>	checkpoints; // buildingId where the pod will stop
};

#define	LANDING_PAD					0
#define MAX_LINKED_ROUTES		5
#define MAX_POD_CHECKPOINT	20
#define COST_POD						1000
#define COST_TELEPORT				5000

t_data data;

/* ************************************************************************** */
/*                                 ACTION.HPP                                 */
/* ************************************************************************** */
std::string	sendTransportMessage(std::string const action, int const buildingId1, int const buildingId2);
std::string	createPod(int const podId, std::vector<int> const checkpoints);
std::string	destroyPod(int const podId);
std::string	createRoute(int const podId, int const buildingId1, int const buildingId2);

/* ************************************************************************** */
/*                                  DATA.HPP                                  */
/* ************************************************************************** */
bool	isAlreadyInRouteVector(t_route const& route, std::vector<t_route> const& routeVector);
bool	isAlreadyInBuildingVector(t_building const& building, std::vector<t_building> const& buildingVector);
bool	isRouteCreated(t_building const& building, t_building const& target);
bool	isRouteCreated(std::vector<t_route> const& routes, t_building const& b1, t_building const& b2);
bool	isInRoute(t_building const& building, t_route const& route);
bool	isRouteCreationPossible(t_data const& data, t_building const& building, t_building const& target);

void	initBuilding(t_data& data);
void	initPod(t_data& data);
void	initRoute(t_data& data);
void	initData(t_data& data);

void	addRoutesToBuilding(t_building& building, std::vector<t_route>& routes);

void	initAdditionalBuilding(t_data& data);
void	initAdditionalRoute(t_data& data);
void	initAdditionalData(t_data& data);

void	clearData(t_data& data);

/* ************************************************************************** */
/*                                  DEBUG.HPP                                 */
/* ************************************************************************** */
void	displayRoute(t_route const& route);
void	displayBuilding(t_building const& building);
void	displayPod(t_pod const& pod);

void	debugTubes(t_data const& data);
void	debugTeleporters(t_data const& data);
void	debugRoutes(t_data const& data);

void	debugLandingPads(t_data const& data);
void	debugModules(t_data const& data);
void	debugBuildings(t_data const& data);

void	debugPods(t_data const& data);
void	debugData(t_data const& data);

/* ************************************************************************** */
/*                                FALLMATH.HPP                                */
/* ************************************************************************** */
double	getDistance(t_building const& A, t_building const& B);
bool		isInRange(t_building const& A, t_building const& B, int radius);
bool		isOnSegment(t_building const& A, t_building const& B, t_building const& C);
int			getOrientation(t_building const& A, t_building const& B, t_building const& C);
bool		isCrossing(t_building const& A, t_building const& B, t_building const& C, t_building const& D);

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

/* ************************************************************************** */
/*                                FALLMATH.CPP                                */
/* ************************************************************************** */
double	getDistance(t_building const& A, t_building const& B)
{
	int	distanceX = pow(B.pos.x - A.pos.x, 2);
	int	distanceY = pow(B.pos.y - A.pos.y, 2);
	double	distance = sqrt(distanceX + distanceY);
	return (distance);
}

bool	isInRange(t_building const& A, t_building const& B, int radius)
{
	double	distance = getDistance(A, B) - radius;
	if (distance <= 0)
		return (true);
	return (false);
}

// Verify if A is on segment BC by creating triangle ABC and checking if BC = AB + AC
bool	isOnSegment(t_building const& A, t_building const& B, t_building const& C)
{
	double	epsilon = 0.0000001;
	double	distanceBA = getDistance(B, A);
	double	distanceAC = getDistance(A, C);
	double	distanceBC = getDistance(B, C);
	double	result = distanceBA + distanceAC - distanceBC;
	if (-epsilon < result && result < epsilon)
		return (true);
	return (false);
}

int	getOrientation(t_building const& A, t_building const& B, t_building const& C)
{
	int	CAy = C.pos.y - A.pos.y;
	int	BAx = B.pos.x - A.pos.x;
	int	BAy = B.pos.y - A.pos.y;
	int	CAx = C.pos.x - A.pos.x;
	int	prod = CAy * BAx - BAy * CAx;

	if (prod < 0)
		return (-1);
	else if (prod == 0)
		return (0);
	return (1);
}

// Verify if two segment AB and CD are crossing
bool	isCrossing(t_building const& A, t_building const& B, t_building const& C, t_building const& D)
{
	int	orientationABC = getOrientation(A, B, C);
	int	orientationABD = getOrientation(A, B, D);
	int	orientationCDA = getOrientation(C, D, A);
	int	orientationCDB = getOrientation(C, D, B);

	if ((orientationABC * orientationABD) < 0 && (orientationCDA * orientationCDB) < 0)
		return (true);
	return (false);
}


/* ************************************************************************** */
/*                                 ACTION.CPP                                 */
/* ************************************************************************** */

/* ****************************** BASIC ACTIONS ***************************** */
std::string	sendTransportMessage(std::string const action, int const buildingId1, int const buildingId2)
{
	std::string	result = action + " "; // can either be TUBE, UPGRADE or TELEPORT
	result += std::to_string(buildingId1) + " "; // TELEPORT action Entrance
	result += std::to_string(buildingId2) + ";"; // TELEPORT action Exit
	return (result);
}

std::string	createPod(int const podId, std::vector<int> const checkpoints)
{
	std::string	result = "POD " + std::to_string(podId) + " ";
	for (unsigned int i = 0; i < checkpoints.size(); i++)
	{
		if (i != checkpoints.size() - 1)
			result += std::to_string(checkpoints[i]) + " ";
		else
			result += std::to_string(checkpoints[i]) + ";";
	}
	return (result);
}

std::string	destroyPod(int const podId)
{
	std::string	result = "DESTROY " + std::to_string(podId) + ";";
	return (result);
}

/* ***************************** ACTION MODULES ***************************** */
std::string	createRoute(int const podId, int const buildingId1, int const buildingId2)
{
	std::string	result = sendTransportMessage("TUBE", buildingId1, buildingId2);
	std::vector<int>	checkpointList;
	for (int i = 0; i < MAX_POD_CHECKPOINT; i++)
	{
		if (i % 2 == 0)
			checkpointList.push_back(buildingId1);
		else
			checkpointList.push_back(buildingId2);
	}
	result += createPod(podId, checkpointList);
	return (result);
}

/* ************************************************************************** */
/*                                  MAIN.CPP                                  */
/* ************************************************************************** */

int	main()
{
	while (42)
	{
		std::string	output;

		initData(data);
		initAdditionalData(data);
		debugData(data);

		// route creation
		for (unsigned int i = 0; i < data.landingPads.size(); i++)
		{
			if (data.landingPads[i].routes.size() == MAX_LINKED_ROUTES)
				continue; // if routes linked to the building are at max, no need to create a new route

			t_building	tmpTarget;
			tmpTarget.id = -1;
			double	tmpDistance = 0;

			for (unsigned int j = 0; j < data.modules.size(); j++)
			{
				if (isRouteCreated(data.landingPads[i], data.modules[j]))
					continue; // if there is already a route created between the two buildings
				if (isRouteCreated(data.routes, data.landingPads[i], data.modules[j]))
					continue; // second check through route vector

				double	currentDistance = getDistance(data.landingPads[i], data.modules[j]);
				if (tmpTarget.id == -1 || tmpDistance == 0 || tmpDistance > currentDistance)
				{
					tmpTarget = data.modules[j];
					tmpDistance = currentDistance;
				}
			}
			if (tmpTarget.id != -1)
			{
				if (isRouteCreationPossible(data, data.landingPads[i], tmpTarget))
				{
					output += createRoute(data.pods.size(), data.landingPads[i].id, tmpTarget.id);
					data.resources -= getDistance(data.landingPads[i], tmpTarget);
					data.podNumber++;
				}
			}
		}
		if (output.empty() || output == "")
			output = "WAIT;";
		std::cout << output << std::endl;
		clearData(data);
		output.clear();
	}
	return (0);
}