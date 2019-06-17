const int MAX_SHIP_SIZE = 4;

class battle_ship
{
private:
	int size;
	int x1;
	int y1;
	int x2;
	int y2;
	bool part_destroyed[MAX_SHIP_SIZE];
	bool destroyed;
public:
	battle_ship(int INsize, int INx1, int INy1, int INx2, int INy2)
	{
		size = INsize;
		x1 = INx1;
		y1 = INy1;
		x2 = INx2;
		y2 = INy2;

		for(int c1 = 0; c1 < size; c1++)
			part_destroyed[c1] = false;
		destroyed = false;
	}

	friend int Fire(battle_ship &INShip, int INx, int INy);
	
}

int Fire(battle_ship &INShip, int INx, int INy)
{
	if(INShip.x1 == INShip.x2)
	{
		if(INx == INShip.x1 && INy >= INShip.y1 && INy <= INShip.y2)
			INShip.part_destroyed[abs(INy - INShip.y1)] = true;
	}
	else if(INShip.y1 == INShip.y2)
	{
		if(INy == INShip.y1 && INx >= INShip.x1 && INx <= INShip.x2)
			INShip.part_destroyed[abs(INx - INShip.x1)] = true;
	}

	int c1;
	for(c1 = 0; c1 < INShip.size && INShip.part_destroyed[c1] == true; c1++);
	
	if(INShip.part_destroyed[c1]) INShip.destroyed = true;
}