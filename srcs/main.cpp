#include <main.hpp>
#include <data.hpp>
#include <debug.hpp>
#include <fallmath.hpp>
#include <action.hpp>

t_data	data;
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