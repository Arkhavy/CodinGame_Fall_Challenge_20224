#include <main.hpp>
#include <data.hpp>
#include <debug.hpp>

/* ************************************************************************** */
/*                                  MAIN.CPP                                  */
/* ************************************************************************** */
t_data	data;

int	main()
{
	while (42)
	{
		std::string	output;

		initData(data);
		initAdditionalData(data);

		debugData(data);

		clearData(data);
		output.clear();
	}
}