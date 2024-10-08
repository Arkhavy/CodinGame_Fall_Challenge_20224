#pragma once

/* ************************************************************************** */
/*                              FALLCHALLENGE.HPP                             */
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

#define LANDING_PAD 0
#define MAX_CHECKPOINT_SIZE 20

// int	main();