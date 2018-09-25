#include "ContactListener.h"

#include "Pig.h"

MyContactListener::MyContactListener()
{}

MyContactListener::~MyContactListener()
{}

void MyContactListener::BeginContact(b2Contact* _contact)
{
	void* bodyUserData = _contact->GetFixtureA()->GetBody()->GetUserData();
	if (bodyUserData)
	{
		static_cast<CPig*>(bodyUserData)->startContact();
	}

	bodyUserData = _contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData)
	{
		static_cast<CPig*>(bodyUserData)->endContact();
	}
}

void MyContactListener::EndContact(b2Contact* _contact)
{
	void* bodyUserData = _contact->GetFixtureA()->GetBody()->GetUserData();
	if (bodyUserData)
	{
		static_cast<CPig*>(bodyUserData)->endContact();
	}

	bodyUserData = _contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData)
	{
		static_cast<CPig*>(bodyUserData)->endContact();
	}
}