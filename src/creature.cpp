#include "creature.h"
Uint16 getUID()
{
    static Uint16 cur;
    cur++;
    return cur;
}
Creature::Creature(std::list<Creature> render, Uint16 _type,Uint16 _x, Uint16 _y):
genes({rand()%50, rand()%5, rand()%5}),
health(genes.maxHealth),
hunger(0)
{
    sight = render;
    type = _type;
    uid = getUID();
    place.x = _x;
    place.y = _y;
    switch(type)
    {
        case types::carn:
            tile = loadImage("image\\carn.png");
            break;
        case types::herb:
            tile = loadImage("image\\herb.png");
            break;
        case types::plant:
            tile = loadImage("image\\plant.png");
            break;
    }
}

Creature Creature::getFromList(Uint16 id)
{
    for(std::list<Creature>::iterator i = sight.begin(); i != sight.end(); i++)
    {
        if((*i).uid == id)
            return (*i);
    }
}

void Creature::update()
{
    std::list<Creature>::iterator it;
    Creature *target;
	float curMax, priority, distance;
    for(it = sight.begin(); it != sight.end(); it++)
    {
		distance = sqrt(pow(((*it).place.x - this->place.x),2)+pow(((*it).place.y - this->place.y), 2));
		if(type == types::carn)
		{
			switch((*it).type)
			{
				case types::carn:
					if((*it).sex == this->sex)
						priority = (this->health * this->genes.damage * (*it).genes.speed) / ((*it).health * (*it).genes.damage * distance);
					else if ((*it).sex != this->sex)
					    priority = ((*it).genes.maxHealth * (*it).genes.speed * (*it).genes.damage)/2*distance;
					break;
                case types::herb:
                    priority = (this->genes.speed * this->genes.damage * this->hunger)/((*it).genes.speed * (*it).genes.damage * distance);
                    break;
			}
		}
		else if(type == types::herb)
		{
		    switch((*it).type)
		    {
		        case types::carn:
                    priority = (this->health * this->genes.damage * (*it).genes.speed) / ((*it).health * (*it).genes.damage * distance);
                //case types::herb:
                    //if((*it).sex == male)

		    }
		}
		curMax = (priority>curMax) ? priority : curMax;
    }
}

void Creature::handleMsg(msg _msg)
{
    Creature sender = getFromList(_msg.sender);
    switch(_msg.content)
    {
        case actions::eat:
            health -=  sender.genes.damage;
            sender.hunger += sender.genes.damage;
            break;
        case actions::strike:
            health -= sender.genes.damage;
            break;
        case actions::mate:
            Creature newCre(sight, type, place.x+1, place.y);
            newCre.genes.maxHealth = rand()%(sender.genes.maxHealth+this->genes.maxHealth);
            newCre.genes.speed = rand()%(sender.genes.speed+this->genes.speed);
            newCre.genes.damage = rand()%(sender.genes.damage+this->genes.damage);
            sight.push_back(newCre);
            break;
    }
}
