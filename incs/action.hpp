#pragma once

#include <iostream>
#include <string>
#include <vector>

/* ************************************************************************** */
/*                                 ACTION.HPP                                 */
/* ************************************************************************** */

/* ****************************** BASIC ACTIONS ***************************** */
std::string	sendTransportMessage(std::string const action, int const buildingId1, int const buildingId2);
std::string	createPod(int const podId, std::vector<int> const checkpointList);
std::string	destroyPod(int const podId);

/* ***************************** ACTION MODULES ***************************** */
std::string	createRoute(int const podId, int const buildingId1, int const buildingId2);