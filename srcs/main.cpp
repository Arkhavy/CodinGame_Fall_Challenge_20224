#include <fallchallenge.hpp>
#include <debug.hpp>
#include <input_handling.hpp>

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

		std::cout << "TUBE 0 1;TUBE 0 2;POD 42 0 1 0 2 0 1 0 2" << std::endl; // TUBE | UPGRADE | TELEPORT | POD | DESTROY | WAIT
	} // game loop
	return (0);
}
