#include <fallchallenge.hpp>
#include <debug.hpp>
#include <input_handling.hpp>
#include <action.hpp>

/* ************************************************************************** */
/*                                  MAIN FILE                                 */
/* ************************************************************************** */
t_data	data;

int	main()
{
	while (42)
	{
		init_data(data);
		debug_data(data);

		std::string	output;
		for (unsigned int i = 0; i < data.buildings.size() - 1; i++)
			output += createRoute(i, data.buildings[i].id, data.buildings[i + 1].id);
		std::cout << output << std::endl;
	} // game loop
	return (0);
}
