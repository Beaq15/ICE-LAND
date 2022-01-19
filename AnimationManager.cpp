#include "AnimationManager.h"



AnimationManager::AnimationManager()
{
	currentAnimation = NULL;
	currentFrame = 0;
	frameTimer = 0;
	animationEnded = false;
	loopAnimation = true;
}

void AnimationManager::changeAnimation(Animation* animation)
{
	currentAnimation = animation;
	resetAnimation();
}

void AnimationManager::setAnimationLooping(bool loopAnimation)
{
	this->loopAnimation = loopAnimation;
}

void AnimationManager::resetAnimation()
{
	currentFrame = 0;
	frameTimer = 0;
	animationEnded = false;
}

void AnimationManager::update(float dt)
{
	if (currentAnimation != NULL)
	{
		//update frameTimer
		frameTimer += dt;

		//if this frame has been shown long enough 
		if (frameTimer >= currentAnimation->frameDuration)
		{
			//move onto next frame
			currentFrame++;
			//reset frame Timer
			frameTimer = 0;

			//check to see if currentFrame is past the last frame of our animation
			if (currentFrame >= currentAnimation->numberOfFrames)
			{
				if (loopAnimation) {
					//loop back around to the first frame again
					currentFrame = 0;
				}
				else
				{
					//we finished this animation
					animationEnded = true;
					//make the currentFrame the last one in the set
					currentFrame = currentAnimation->numberOfFrames - 1;
				}

			}
		}
	}
}

void AnimationManager::draw(int x, int y)
{
	if (currentAnimation != NULL)
		currentAnimation->draw(currentFrame, x, y);
}


