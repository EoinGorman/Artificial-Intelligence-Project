#include "Predator.h"
#define ReloadTime 3
#define MissileRange 400
#define MaxSpeed 3.5
#define MaxForce 0.5

Predator::Predator(sf::Vector2f pos, sf::Vector2f dir, sf::FloatRect bounds)
: Spaceship(pos, dir, bounds)
{
	wanderTime = (std::rand() % 5000) / 1000.0f;
	wanderTimer = 0;
	reloadTimer = ReloadTime;
	m_speed = 5;
	currentState = State::Flocking;
	wanderTimer = wanderTime;

	m_texture.loadFromFile("../Images/Spaceship_4.png");
	m_sprite.setTexture(m_texture, true);
	m_width = m_sprite.getLocalBounds().width;
	m_height = m_sprite.getLocalBounds().height;
	m_sprite.setOrigin(m_width / 2, m_height / 2);

	velocity = Pvector(rand() % 3 - 2, rand() % 3 - 2); // Allows for range of -2 -> 2
	m_direction = sf::Vector2f(velocity.x, velocity.y);
	m_sprite.setRotation(atan2(m_direction.y, m_direction.x));
}

void Predator::Update(float deltaTime, std::vector<Predator*> flock, Pvector playerPos)
{
	switch (currentState)
	{
	case Seeking:
		Finding(deltaTime,playerPos);
		break;
	case Flocking:
		Flock(flock, deltaTime, playerPos);
		break;
	}

	CheckForShoot(deltaTime, playerPos);
	WrapAroundScreen();

	for (int i = 0; i < missiles.size(); i++)
	{
		if (missiles.at(i)->MarkedForDeletion())
		{
			delete missiles.at(i);
			missiles.erase(missiles.begin() + i);
			break;
		}
		else
		{
			missiles.at(i)->Update(deltaTime, sf::Vector2f(playerPos.x, playerPos.y));
		}
	}
}

void Predator::Draw(sf::RenderWindow* window)
{
	window->draw(m_sprite);
	for (int i = 0; i < missiles.size(); i++)
	{
		missiles.at(i)->Draw(window);
	}
}

Predator::State Predator::GetState()
{
	return currentState;
}
void Predator::SetState(State newState)
{
	currentState = newState;
}

sf::Rect<float> Predator::GetBounds()
{
	return m_sprite.getGlobalBounds();
}

void Predator::Move(float deltaTime)
{
	//To make the slow down not as abrupt
	acceleration.mulScalar(.1);
	// Update velocity
	velocity.addVector(acceleration);
	// Limit speed
	velocity.limit(MaxSpeed);	//Max speed
	m_position += sf::Vector2f(velocity.x, velocity.y) * (float)(deltaTime * m_speed);
	// Reset accelertion to 0 each cycle
	acceleration.mulScalar(0);

	m_sprite.setPosition(m_position);
}


void Predator::Flock(std::vector<Predator*> flock, float deltaTime, Pvector playerPos)
{
	m_speed = 100;

	float deltaX = playerPos.x - m_position.x;
	float deltaY = playerPos.y - m_position.y;
	float facing = (float)(atan2(deltaY, deltaX) * 180 / PI);
	m_sprite.setRotation(facing);

	//
	if (playerPos.distance(Pvector(m_position.x, m_position.y)) > 250.0f)
	{
		Pvector ali = Finding(deltaTime, playerPos);
		ali.mulScalar(1.0); // Might need to alter weights for different characteristics
		ApplyForce(ali);
	}

	else
	{
		acceleration = Pvector(0, 0);
		velocity = Pvector(0, 0);

	}
	//

	Pvector sep = Separation(flock, playerPos);
	Pvector coh = Cohesion(deltaTime,flock);
	// Arbitrarily weight these forces
	sep.mulScalar(1.5);
	coh.mulScalar(1.0);
	// Add the force vectors to acceleration
	ApplyForce(sep);
	ApplyForce(coh);
	Move(deltaTime);
}

// Three Laws that boids follow
Pvector Predator::Separation(vector<Predator*> flock, Pvector playerPos)
{
	// Distance of field of vision for separation between boids
	float desiredseparation = 50;

	Pvector steer(0, 0);
	int count = 0;
	Pvector location(m_position.x, m_position.y);
	// For every boid in the system, check if it's too close
	for (int i = 0; i < flock.size(); i++)
	{
		Pvector otherLocation(flock[i]->m_position.x, flock[i]->m_position.y);
		// Calculate distance from current boid to boid we're looking at
		float d = location.distance(otherLocation);
		// If this is a fellow boid and it's too close, move away from it
		if ((d > 0) && (d < desiredseparation) && flock[i]->GetState() == State::Flocking)
		{
			Pvector diff(0, 0);
			diff = diff.subTwoVector(location, otherLocation);
			diff.normalize();
			diff.divScalar(d);      // Weight by distance
			steer.addVector(diff);
			count++;
		}
	}
	//this is where we run from the player
	if (location.distance(playerPos) < 200)
	{
		Pvector diff(0, 0);
		diff = diff.subTwoVector(location, playerPos);
		diff.normalize();
		diff.mulScalar(3);      // Weight
		steer.addVector(diff);
		velocity.addVector(diff);
		count++;
	}

	// Adds average difference of location to acceleration
	if (count > 0)
		steer.divScalar((float)count);
	if (steer.magnitude() > 0)
	{
		// Steering = Desired - Velocity
		steer.normalize();
		steer.mulScalar(MaxSpeed);	//max speed
		steer.subVector(velocity);
		steer.limit(MaxForce);
	}
	return steer;
}

Pvector Predator::Alignment(vector<Predator*> flock)
{
	float neighbordist = 100;

	Pvector sum(0, 0);
	int count = 0;
	Pvector location(m_position.x, m_position.y);
	for (int i = 0; i < flock.size(); i++)
	{
		Pvector otherLocation(flock[i]->m_position.x, flock[i]->m_position.y);
		float d = location.distance(otherLocation);
		if ((d > 0) && (d < neighbordist) && flock[i]->GetState() == State::Flocking) // 0 < d < 50
		{
			sum.addVector(flock[i]->velocity);
			count++;
		}
	}
	// If there are boids close enough for alignment...
	if (count > 0)
	{
		sum.divScalar((float)count);// Divide sum by the number of close boids (average of velocity)
		sum.normalize();	   		// Turn sum into a unit vector, and
		sum.mulScalar(MaxSpeed);    // Multiply by maxSpeed
		// Steer = Desired - Velocity
		Pvector steer;
		steer = steer.subTwoVector(sum, velocity); //sum = desired(average)  
		steer.limit(MaxForce);
		return steer;
	}
	else {
		Pvector temp(0, 0);
		return temp;
	}
}
Pvector Predator::Cohesion(float deltaTime,vector<Predator*> flock)
{
	float neighbordist = 100;

	Pvector sum(0, 0);
	int count = 0;
	Pvector location(m_position.x, m_position.y);
	for (int i = 0; i < flock.size(); i++)
	{
		Pvector otherLocation(flock[i]->m_position.x, flock[i]->m_position.y);

		float d = location.distance(otherLocation);
		if ((d > 0) && (d < neighbordist) && flock[i]->GetState() == State::Flocking)
		{
			sum.addVector(otherLocation);
			count++;
		}
	}
	if (count > 0)
	{
		sum.divScalar(count);
		return Seek(deltaTime,sum);
	}
	else {
		Pvector temp(0, 0);
		return temp;
	}
}

Pvector Predator::Seek(float deltaTime,Pvector v)
{
	Pvector desired;
	desired.subVector(v);  // A vector pointing from the location to the target
	// Normalize desired and scale to maximum speed
	desired.normalize();
	desired.mulScalar(MaxSpeed);

	// Steering = Desired minus Velocity
	acceleration.subTwoVector(desired, velocity);
	acceleration.limit(MaxForce);  // Limit to maximum steering force
	return acceleration;
}

Pvector Predator::Finding(float deltaTime,Pvector playerPos)
{
	//m_speed = 350;
	
	/*if (wanderTimer >= wanderTime)
	{
		wanderTime = (std::rand() % 5000) / 1000.0f;
		wanderTimer = 0;

		m_direction = sf::Vector2f(((std::rand() % 200) - 100) / 100.0f, ((std::rand() % 200) - 100) / 100.0f);
		velocity = Pvector(m_direction.x, m_direction.y);
		m_sprite.setRotation(atan2(m_direction.y, m_direction.x) * 180 / PI);
	
	}*/

	Pvector location = Pvector(m_position.x, m_position.y);

	
		Pvector sum(0, 0);

		//Intercept
		Pvector dirToTarget = playerPos;
		dirToTarget.subVector(Pvector(m_position.x, m_position.y));

		dirToTarget.normalize();
		sum.addVector(dirToTarget);
		return sum;
		//Pvector diff(0, 0);
		//diff = diff.subTwoVector(location, playerPos);
		//diff.normalize();
		//diff.mulScalar(0.2f);      // Weight
		//m_direction += sf::Vector2f(diff.x, diff.y);
		////normalise direction
		//float mag = sqrt(m_direction.x * m_direction.x + m_direction.y * m_direction.y); //Magnitude of vector formula
		//m_direction /= mag;

		//Move(deltaTime);
		//velocity = Pvector(m_direction.x, m_direction.y);
		//m_sprite.setRotation(atan2(m_direction.y, m_direction.x) * 180 / PI);
	

	/*
	if (steer.magnitude() > 0)
	{
	// Steering = Desired - Velocity
	steer.normalize();
	steer.mulScalar(MaxSpeed);	//max speed
	steer.subVector(velocity);
	steer.limit(MaxForce);
	}
	*/
}

float Predator::Angle()
{
	float angle = (float)(atan2(velocity.y, velocity.x) * 180 / PI);
	return angle;
}

void Predator::ApplyForce(Pvector force)
{
	acceleration.addVector(force);
}


void Predator::CheckForShoot(float deltaTime, Pvector playerPos)
{
	reloadTimer += deltaTime;
	if (reloadTimer >= ReloadTime)
	{
		Pvector location = Pvector(m_position.x, m_position.y);
		if (playerPos.distance(location) <= MissileRange)
		{
			Shoot(playerPos);
		}
	}
}

void Predator::Shoot(Pvector playerPos)
{
	reloadTimer = 0;
	missiles.push_back(new InterceptorMissile(m_position, Angle(), m_bounds, sf::Vector2f(playerPos.x, playerPos.y)));
}