#pragma once

/* ************************************************************************** */
/*                                  DATA.HPP                                  */
/* ************************************************************************** */
bool	isAlreadyInRouteVector(t_route const& route, std::vector<t_route> const& routeVector);
bool	isAlreadyInBuildingVector(t_building const& building, std::vector<t_building> const& buildingVector);
bool	isRouteCreated(t_building const& building, t_building const& target);
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