#include <fallchallenge.hpp>
#include <fallmath.hpp>

/* ************************************************************************** */
/*                                FALLMATH.CPP                                */
/* ************************************************************************** */
double	getDistance(t_building const& A, t_building const& B)
{
	int	distanceX = pow(A.pos.x - B.pos.x, 2);
	int	distanceY = pow(A.pos.y - B.pos.y, 2);
	double	distance = sqrt(distanceX + distanceY);
	return (distance);
}

bool	isInRange(t_building const& A, t_building const& B, int radius)
{
	double	distance = getDistance(A, B) - radius;
	if (distance <= 0)
		return (true);
	return (false);
}

// Verify if A is on segment BC by creating triangle ABC and checking if BC = AB + AC
bool	isOnSegment(t_building const& A, t_building const& B, t_building const& C)
{
	double	epsilon = 0.0000001;
	double	distanceAB = getDistance(A, B);
	double	distanceAC = getDistance(A, C);
	double	distanceBC = getDistance(B, C);
	double	result = distanceAB + distanceAC - distanceBC;
	if (-epsilon < result && result < epsilon)
		return (true);
	return (false);
}

int	getOrientation(t_building const& A, t_building const& B, t_building const& C)
{
	int	CAy = C.pos.y - A.pos.y;
	int	BAx = B.pos.x - A.pos.x;
	int	BAy = B.pos.y - A.pos.y;
	int	CAx = C.pos.x - A.pos.x;
	int	prod = CAy * BAx - BAy * CAx;
	if (prod < 0)
		return (-1);
	else if (prod == 0)
		return (0);
	return (1);
}

// Verify if two segment AB and CD are crossing
bool	isCrossing(t_building const& A, t_building const& B, t_building const& C, t_building const& D)
{
	int	orientationABC = getOrientation(A, B, C);
	int	orientationABD = getOrientation(A, B, D);
	int	orientationCDA = getOrientation(C, D, A);
	int	orientationCDB = getOrientation(C, D, B);
	if ((orientationABC * orientationABD) < 0 && (orientationCDA * orientationCDB) < 0)
		return (true);
	return (false);
}
