#include "SwarmShip.h"
#define MaxSpeed 200

SwarmShip::SwarmShip(sf::Vector2f pos, sf::Vector2f dir, sf::FloatRect bounds)
	: Spaceship(pos, dir, bounds)
{
	currentState = State::Swarming;
}

void SwarmShip::Update(float deltaTime, vector<SwarmShip*> otherShips, Pvector targetPos)
{
	switch (currentState)
	{
	case State::Swarming:
		Swarm(otherShips, targetPos);
		break;
	case State::Intercepting:
		Intercept(targetPos);
		break;
	}

	Move(deltaTime);
	WrapAroundScreen();
}

SwarmShip::State SwarmShip::GetState()
{
	return currentState;
}

void SwarmShip::SetState(State newState)
{
	currentState = newState;
}

void SwarmShip::Move(float deltaTime)
{
	switch (currentState)
	{
	case State::Swarming:
		//To make the slow down not as abrupt
		acceleration.mulScalar(0.5);
		// Update velocity
		velocity.addVector(acceleration);
		// Limit speed
		velocity.limit(MaxSpeed);
		m_position += sf::Vector2f(velocity.x, velocity.y) * (deltaTime);
		// Reset accelertion to 0 each cycle
		acceleration.mulScalar(0);

		break;
	case State::Intercepting:
		//To make the slow down not as abrupt
		acceleration.mulScalar(0.5);
		// Update velocity
		velocity.addVector(acceleration);
		// Limit speed
		velocity.normalize();
		m_position += sf::Vector2f(velocity.x, velocity.y) * (deltaTime * (MaxSpeed/2));
		// Reset accelertion to 0 each cycle
		acceleration.mulScalar(0);
		break;
	}

	//Update Sprite
	m_sprite.setPosition(m_position);
	m_sprite.setRotation(Angle());
}

void SwarmShip::Swarm(vector<SwarmShip*> otherShips, Pvector targetPos)
{
	/*		Lenard-Jones Potential function
	Vector R = me.position - you.position
	Real D = R.magnitude()
	Real U = -A / pow(D, N) + B / pow(D, M)
	R.normalise()
	force = force + R*U
	*/
	Pvector	R;
	Pvector sum(0, 0);
	float neighbordist = 500;
	float A = 200;
	float B = 700;
	float N = 0.65f;
	float M = 1;
	int count = 0;
	Pvector location = Pvector(m_position.x, m_position.y);
	Pvector dirToTarget = targetPos;
	dirToTarget.subVector(location);
	//Swarm
	for (int i = 0; i < otherShips.size(); i++)
	{
		Pvector otherLocation = Pvector(otherShips[i]->m_position.x, otherShips[i]->m_position.y);

		float d = location.distance(otherLocation);
		if ((d > 0) && (d < neighbordist) && otherShips[i]->GetState() == State::Swarming) // 0 < d < 50
		{
			R = location;
			R.subVector(otherLocation);

			float D = R.magnitude();
			float U = -A / pow(D, N) + B / pow(D, M);
			R.normalize();

			R.mulScalar(U);
			sum.addVector(R);

			count++;
		}
		dirToTarget.normalize();
		dirToTarget.mulScalar(0.1f);
		sum.addVector(dirToTarget);
	}

	if (count > 0)
		sum.divScalar(count);

	ApplyForce(sum);
}

void SwarmShip::Intercept(Pvector targetPos)
{
	Pvector sum(0, 0);
	
	//Intercept
	Pvector dirToTarget = targetPos;
	dirToTarget.subVector(Pvector(m_position.x, m_position.y));

	dirToTarget.normalize();
	sum.addVector(dirToTarget);

	ApplyForce(sum);
}

// Calculates the angle for the velocity of a boid which allows the visual 
// image to rotate in the direction that it is going in.
float SwarmShip::Angle()
{
	// From the definition of the dot product
	float angle = (float)(atan2(velocity.y, velocity.x) * 180 / PI);
	return angle;
}

void SwarmShip::ApplyForce(Pvector force)
{
	acceleration.addVector(force);
}