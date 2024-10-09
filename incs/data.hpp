#pragma once

/* ************************************************************************** */
/*                                  DATA.HPP                                  */
/* ************************************************************************** */
void	initBuilding(t_data& data);
void	initPod(t_data& data);
void	initRoute(t_data& data);
void	initData(t_data& data);

bool	isAlreadyInBuildingVector(t_building const& building, std::vector<t_building> const& buildingVector);
bool	isAlreadyInRouteVector(t_route const& route, std::vector<t_route> const& routeVector);
void	addRoutesToBuilding(t_building& building, std::vector<t_route>& routes);

void	initAdditionalBuilding(t_data& data);
void	initAdditionalRoute(t_data& data);
void	initAdditionalData(t_data& data);

void	clearData(t_data& data);