#include <fallchallenge.hpp>
#include <debug.hpp>
#include <input_handling.hpp>
#include <action.hpp>
#include <fallmath.hpp>
#include <utils.hpp>

/* ************************************************************************** */
/*                                  MAIN FILE                                 */
/* ************************************************************************** */
t_data	data;

/* ************************************************************************** */
/*                                   MAIN 1                                   */
/* ************************************************************************** */
// int	main()
// {
// 	while (42)
// 	{
// 		init_data(data);
// 		debug_data(data);

// 		std::string	output;
// 		for (unsigned int i = 0; i < data.buildings.size() - 1; i++)
// 			output += createRoute(i, data.buildings[i].id, data.buildings[i + 1].id);
// 		std::cout << output << std::endl;
// 	} // game loop
// 	return (0);
// }

/* ************************************************************************** */
/*                                   MAIN 2                                   */
/* ************************************************************************** */
int	main()
{
	while (42)
	{
		initData(data);
		debugData(data);

		std::string	output;
		for(unsigned int i = 0; i < data.buildings.size(); i++)
		{

			// if LANDING PAD, try to create a route from it
			if (data.buildings[i].type == LANDING_PAD)
			{
				int			tmp_target_id = -1;
				double	tmp_distance = 0;

				// searching for a building to target
				for (unsigned int j = 0; j < data.buildings.size(); j++)
				{
					if (data.buildings[i].id == data.buildings[j].id)
						continue; // if same building, skip
					if (data.buildings[j].type == LANDING_PAD)
						continue; // if LANDING PAD, skip
					if (isRouteCreated(data, data.buildings[i].id, data.buildings[j].id))
						continue; // if route already exists, skip

					// getting the closest building possible to avoid expensive cost
					if (tmp_target_id == -1 || tmp_distance == 0 || tmp_distance > getDistance(data.buildings[i], data.buildings[j]))
					{
						tmp_target_id = data.buildings[j].id;
						tmp_distance = getDistance(data.buildings[i], data.buildings[j]);
					}
				}

				// if target is found, add a route to it
				if (tmp_target_id != -1)
					output += createRoute(data.pods.size(), data.buildings[i].id, tmp_target_id);
			}
		}
		clearData(data);
	} // game loop
	return (0);
}