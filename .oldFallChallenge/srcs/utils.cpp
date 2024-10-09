#include <fallchallenge.hpp>
#include <utils.hpp>

/* ************************************************************************** */
/*                                  UTILS.CPP                                 */
/* ************************************************************************** */
t_route const	getRoute(t_data const& data, int const& buildingId1, int const& buildingId2)
{
	for (unsigned int i = 0; i < data.routes.size(); i++)
	{
		if (data.routes[i].building_id_1 == buildingId1)
			if (data.routes[i].building_id_2 == buildingId2)
				return (data.routes[i]);
		if (data.routes[i].building_id_2 == buildingId1)
			if (data.routes[i].building_id_1 == buildingId2)
				return (data.routes[i]);
	}
	t_route	invalidRoute;
	invalidRoute.building_id_1 = -1;
	invalidRoute.building_id_2 = -1;
	invalidRoute.capacity = -1;
	return (invalidRoute);
}

bool	isRouteCreated(t_data const& data, int const& buildingId1, int const& buildingId2)
{
	t_route	tmpRoute = getRoute(data, buildingId1, buildingId2);
	if (tmpRoute.building_id_1 == -1 && tmpRoute.building_id_2 == -1 && tmpRoute.capacity == -1)
		return (false);
	return (true);
}