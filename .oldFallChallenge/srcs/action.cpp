#include <fallchallenge.hpp>
#include <action.hpp>

/* ************************************************************************** */
/*                                 ACTION.CPP                                 */
/* ************************************************************************** */

/* ****************************** BASIC ACTIONS ***************************** */
std::string	sendTransportMessage(std::string const action, int const buildingId1, int const buildingId2)
{
	std::string	result = action + " "; // action can be either TUBE, UPGRADE or TELEPORT
	result += std::to_string(buildingId1) + " "; // TELEPORT action Entrance
	result += std::to_string(buildingId2) + ";"; // TELEPORT action Exit
	return (result);
}

std::string	createPod(int const podId, std::vector<int> const checkpointList)
{
	std::string	result = "POD " + std::to_string(podId) + " ";
	for (unsigned int i = 0; i < checkpointList.size(); i++)
	{
		if (i != checkpointList.size() - 1)
			result += std::to_string(checkpointList[i]) + " ";
		else
			result += std::to_string(checkpointList[i]) + ";";
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
	for (int i = 0; i < MAX_CHECKPOINT_SIZE; i++)
	{
		if (i % 2 == 0)
			checkpointList.push_back(buildingId1);
		else
			checkpointList.push_back(buildingId2);
	}
	result += createPod(podId, checkpointList);
	return (result);
}
