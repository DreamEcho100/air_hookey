#pragma once
class StrikerMoveAreaLimits
{
public:
	float north;
	float east;
	float south;
	float west;

public:
	StrikerMoveAreaLimits() = default;
	StrikerMoveAreaLimits(
		float north,
		float east,
		float south,
		float west
	) {
		this->north = north;
		this->east = east;
		this->south = south;
		this->west = west;
	}
};

