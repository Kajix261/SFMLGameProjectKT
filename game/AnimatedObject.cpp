#include "AnimatedObject.h"

//contructors
AnimatedObject::AnimatedObject(sf::Texture t, sf::Vector2f p, int af) : position(p), texture(t), animation_fps(af) {
	this->setTexture(texture);
	this->setPosition(position);
}
AnimatedObject::~AnimatedObject() {

}

//animation methods
void AnimatedObject::add_animation_frame(sf::IntRect frame) {
    frames.emplace_back(frame);
    //std::cout << "added_anim_frame\n";
}
void AnimatedObject::animate(sf::Time& time_elapsed) {
    object_time += time_elapsed;

    float frame_moment = 1.0f / animation_fps;

    if (object_time.asSeconds() >= frame_moment) {
        animated_frame = (animated_frame + 1) % frames.size();
        this->setTextureRect(frames[animated_frame]);
        object_time = sf::Time::Zero;
    }
}