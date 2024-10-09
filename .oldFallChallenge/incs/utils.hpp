#pragma once

#include <iostream>
#include <vector>
#include <string>

/* ************************************************************************** */
/*                                  UTILS.HPP                                 */
/* ************************************************************************** */
t_route const	getRoute(t_data const& data, int const& buildingId1, int const& buildingId2);
bool					isRouteCreated(t_data const& data, int const& buildingId1, int const& buildingId2);