#pragma once

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
