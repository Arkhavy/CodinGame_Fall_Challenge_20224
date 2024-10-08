#pragma once

#include <iostream>
#include <algorithm>
#include <cmath>

/* ************************************************************************** */
/*                                FALLMATH.HPP                                */
/* ************************************************************************** */
double	getDistance(t_building const& A, t_building const& B);
bool		isInRange(t_building const& A, t_building const& B, int radius);
bool		isOnSegment(t_building const& A, t_building const& B, t_building const& C);
int			getOrientation(t_building cnost& A, t_building const& B, t_building const& C);
bool		isCrossing(t_building const& A, t_building const& B, t_building const& C, t_building const& D);