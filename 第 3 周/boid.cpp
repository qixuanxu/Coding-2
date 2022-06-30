/*
 *  boid.cpp
 *  boids
 *
 *  Created by Marco Gillies on 05/10/2010.
 *  Copyright 2010 Goldsmiths, University of London. All rights reserved.
 *
 */

#include "boid.h"
#include "ofMain.h"


Boid::Boid()
{
	separationWeight = 1.0f;
	cohesionWeight = 0.2f;
	alignmentWeight = 0.1f;
	
	separationThreshold = 15;
	neighbourhoodSize = 100;
	
	position = ofVec3f(ofRandom(0, 200), ofRandom(0, 200));
	velocity = ofVec3f(ofRandom(-2, 2), ofRandom(-2, 2));
}

Boid::Boid(ofVec3f &pos, ofVec3f &vel)
{
	separationWeight = 1.0f;
	cohesionWeight = 0.2f;
	alignmentWeight = 0.1f;
	
	separationThreshold = 15;
	neighbourhoodSize = 100;
	
	position = pos;
	velocity = vel;
}
//constructor

Boid::~Boid()
{
	
}
//destructor

float Boid::getSeparationWeight()
{
	return separationWeight;
}
float Boid::getCohesionWeight()
{
	return cohesionWeight;
}

float Boid::getAlignmentWeight()
{
	return alignmentWeight;
}


float Boid::getSeparationThreshold()
{
	return separationThreshold;
}

float Boid::getNeighbourhoodSize()
{
	return neighbourhoodSize;
}


void Boid::setSeparationWeight(float f)
{
	separationWeight = f;
}
void Boid::setCohesionWeight(float f)
{
	cohesionWeight = f;
}

void Boid::setAlignmentWeight(float f)
{
	alignmentWeight = f;
}


void Boid::setSeparationThreshold(float f)
{
	separationThreshold = f;
}

void Boid::setNeighbourhoodSize(float f)
{
	neighbourhoodSize = f;
}


ofVec3f Boid::getPosition()
{
	return position;
}

ofVec3f Boid::getVelocity()
{
	return velocity;
}

ofVec3f Boid::separation(std::vector<Boid *> &otherBoids)
{
	// finds the first collision and avoids that
	// should probably find the nearest one
	// can you figure out how to do that?找到并避免第一次碰撞
    //应该找到最近的一个
    //你能想出怎么做吗?我认为我们所做的是我们得到单位向量（the unit vector）并用它来反转方向。
	for (int i = 0; i < otherBoids.size(); i++)
	{	
		if(position.distance(otherBoids[i]->getPosition()) < separationThreshold)
		{
			ofVec3f v = position -  otherBoids[i]->getPosition();
			v.normalize();// unit vector of distance
			return v;
		}
	}
}

ofVec3f Boid::cohesion(std::vector<Boid *> &otherBoids)
{
	ofVec3f average(0,0,0);
	int count = 0;
	for (int i = 0; i < otherBoids.size(); i++)
	{
		if (position.distance(otherBoids[i]->getPosition()) < neighbourhoodSize)
		{
			average += otherBoids[i]->getPosition();
			count += 1;
		}
	}
	average /= count;
	ofVec3f v =  average - position;
	v.normalize();//And normally what you do is you move towards the centre of mass of all the Boyds.向所有 Boids 的质心移动。所以你计算质心（重心）。你可以通过获取羊群中每个 Boid 的位置并说：当您将它们全部加起来并除以点数时，平均位置是多少？
	return v;
}

ofVec3f Boid::alignment(std::vector<Boid *> &otherBoids)
{
	ofVec3f average(0,0,0);
	int count = 0;
	for (int i = 0; i < otherBoids.size(); i++)
	{
		if (position.distance(otherBoids[i]->getPosition()) < neighbourhoodSize)
		{
			average += otherBoids[i]->getVelocity();
			count += 1;
		}
	}
	average /= count;
	ofVec3f v =  average - velocity;
	v.normalize();
    //因此，如果您知道每个人的去向，请获取平均值，因为每个人都在远离彼此。所以你可以做的是你可以在你当前的方向上添加另一个方向，它代表所有其他男孩的方向的平均值。You just calculate the average heading the average direction vector normalised vector您只需计算平均航向向量归一化向量的平均航向。所以如果你的对齐权重很高，你的羊群会有更多的方向，它会更直接地飞来飞去。如果你的凝聚力很高，那么它们的羊群会非常紧密，非常紧密。如果你的分离权重很高，那么它会推动凝聚力。
	return v;
}

void Boid::update(std::vector<Boid *> &otherBoids, ofVec3f &min, ofVec3f &max)
{
	velocity += separationWeight*separation(otherBoids);
	velocity += cohesionWeight*cohesion(otherBoids);
	velocity += alignmentWeight*alignment(otherBoids);
	
	walls(min, max);
	position += velocity;
}

void Boid::walls(ofVec3f &min, ofVec3f &max)
{
	if (position.x < min.x){
		position.x = min.x;
		velocity.x *= -1;
	} else if (position.x > max.x){
		position.x = max.x;
		velocity.x *= -1;
	}
	
	if (position.y < min.y){
		position.y = min.y;
		velocity.y *= -1;
	} else if (position.y > max.y){
		position.y = max.y;
		velocity.y *= -1;
	}
    
    if (position.z < min.z){
        position.z = min.z;
        velocity.z *= -1;
    } else if (position.z > max.z){
        position.z = max.z;
        velocity.z *= -1;
    }
	
	
}

void Boid::draw()
{
    
    float time = ofGetSystemTimeMillis()/10;
    
    for(int i=0; i < 900; i+= 5 ){
    ofSetColor (127 + 127 * sin (i*0.01+time),
                127 + 127 *  sin (i*0.012+time),
                127 + 127 *  sin (i*0.023+time) );
	//ofCircle(position.x, position.y, 5);
    ofDrawBox(position.x, position.y, position.z, 10);
    }
    
}
