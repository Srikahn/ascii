#include "Enemy.h"

// ----- Constructeur/Destructeur -----
Enemy::Enemy(int x, int y, std::string name, float speed) : Destructible(x, y, 100, "e"), m_name(name), m_speed(speed) {}

Enemy::~Enemy() {}
// ------------------------------------


void Enemy::tick(float deltaTime)
{
	// Let's move towards the player character to shoot him / bump him

	// The amount of move available this turn
	float move = deltaTime * m_speed + m_moveRemaining;

	// We get the integer part of the move to see what movement is actually performed this tick, and put the rest in moveRemaining
	int intMove = modff(move, &m_moveRemaining);

	//TODO: get the character X and Y coordinated from GameLogic
	int targetX = 0;
	int targetY = 0;

	while(intMove > 0)
	{
		bool success = true;
		
		if(targetX != m_positionX && targetY != m_positionY)
		{
			// The character is in a different row and column
			int diffX = abs(targetX - m_positionX);
			int diffY = abs(targetY - m_positionY);

			// We pick an axis to move to using weighted random (we're more likely to pick the axis where the target is furthest
			int random = rand() % (diffX + diffY);
			if(random > diffX)
			{
				// We move on the X axis!
				// Is the target upper or lower in the axis?
				int direction = (targetX > m_positionX) ? 1 : -1;

				// Make the move and check if it's successful
				success = moveTo(m_positionX + direction, m_positionX);
			}
			else
			{
				// We move on the Y axis!
				// Is the target upper or lower in the axis?
				int direction = (targetY > m_positionY) ? 1 : -1;

				// Make the move and check if it's successful
				success = moveTo(m_positionY + direction, m_positionY);
			}
		}

		if (!success)
		{
			// Oops, the enemy collided with something... we interrupt the whole move by breaking out of the loop
			break;
		}
		intMove--;
	}
}
