#include "frog.hpp"
#include "EngineDirectory/collision.hpp"
#include "EngineDirectory/sceneManager.hpp"
#include "EngineDirectory/engine.hpp"
#include "fruit.hpp"
#include "bee.hpp"
#include "rhino.hpp"
Frog::Frog() : Node("character") , score(0)
{
    sprite = new AnimatedSprite(this);
    sprite->addSpriteSheet("idle", new SpriteSheet("frog/frogIdle.png", 100, true, sprite, 32, 32));
    sprite->addSpriteSheet("run", new SpriteSheet("frog/frogRun.png", 100, true, sprite, 32, 32));
    sprite->addSpriteSheet("jump", new SpriteSheet("frog/frogJump.png", 150, false, sprite, 32, 32));
    sprite->addSpriteSheet("fall", new SpriteSheet("frog/frogFall.png", 150, false, sprite, 32, 32));
    sprite->addSpriteSheet("hit", new SpriteSheet("frog/frogHit.png", 150, false, sprite, 32, 32));
    sprite->setAnimation("idle");

    sprite->setSize(72,72);
    collision = new Collision(this, true);
    collision->setRectangle(sf::FloatRect(0, 0, 60, 60));
    collision->setOffset(sf::Vector2f(6, 11));
    this->setComponent(collision);
    this->setComponent(sprite);
    grounded = false;


    text = new Text();
    text->setColor(sf::Color::Black);
    text->setText("Score : 0");
    text->setPosition(40,40);
    
    move(200, 40);
    container = nullptr;
    setName("character");
}
void Frog::start()
{
    container = (EmptyNode*)SceneManager::manager()->getNodeByName("holder");
    SceneManager::manager()->getCurrentScene()->instantiate(text,this);
}
void Frog::update()
{
    if (hitFinished){
        sprite->setAnimation("idle");
        hitFinished = false;
    }
    x = getPosition().x;
    y = getPosition().y;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ){
        if (!jumped)
            sprite->setAnimation("run");
        sprite->setOrientation(false);
        // move(speed,0);
        velocity.x = speed;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ){
        if (!jumped)
            sprite->setAnimation("run");
        sprite->setOrientation(true);
        //move(-speed,0);
        velocity.x = -speed;
    }
    if (!jumped && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sprite->getCurrentAnimation() != "hit"){
        sprite->setAnimation("idle");
        velocity.x = 0;
    }
   

    updateMovement();
     if (container && SceneManager::manager()->getNodeChildCount(container) == 0){
         std::string scoreString = "GOOD JOB!";
         text->setText(scoreString);
     }
        
    int tx = Engine::engine()->getView()->getCenter().x;
    int ty = Engine::engine()->getView()->getCenter().y;
    if (x > 500 && x < 2900){
        tx = x;
    }
    if (y > 0 + Engine::engine()->getView()->getSize().y/2){
        ty = y;
    }
    
    
    Engine::engine()->getView()->setCenter(tx,ty);

    ground = 0;
}
void Frog::animationFinished(std::string name){
    if (name == "hit"){
        hitFinished = true;
    }
}
void Frog::_draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  //  target.draw(*text,states);
}

void Frog::updateMovement()
{
    if (!grounded){
        if (velocity.y < 20)
            velocity.y += gravity;
    }
    else {
        if (velocity.y > 0)
            velocity.y = 0;
        jumped = 0;
    }

    velocity.x += accelerationX;
    if (accelerationX > 0)
        accelerationX--;
    else if (accelerationX < 0)
        accelerationX++;
    velocity.y += accelerationY;
    if (accelerationY > 0)
        accelerationY--;
    else if (accelerationY < 0)
        accelerationY++;
}
void Frog::jump()
{
    if (grounded || jumped < 2)
    {
        sprite->setAnimation("jump");
        if (velocity.y > 0){
            velocity.y = 0;
        }
        if (velocity.y < 0){
            velocity.y = 0;
        }
        velocity.y -= 30;
        grounded = false;
        jumped++;
    }
}
void Frog::processInput(sf::Event::EventType type, sf::Event::KeyEvent key)
{
    if (type == (sf::Event::KeyPressed) && key.code == sf::Keyboard::Space)
    {
        jump();
    }
}
void Frog::onCollision(sf::Vector2f direction, Node* node)
{
    if ((node->getTag() == "ground" || node->getTag() == "platform") && direction.y > 0){
        grounded = true;
        jumped = 0;
    }
    if (node->getTag() == "platform" && direction.y > 0){
        move(0,node->getVelocity().y);
    }

}
void Frog::noCollision(sf::IntRect dir){
    if (dir.top){
        grounded = false;
    }
}
void Frog::onCollide(sf::Vector2f v, Node* n){
    if (n->getTag() == "fruit"){
        SceneManager::manager()->getCurrentScene()->destroy(n);
        score+= ((Fruit*)n)->getPoints();
        std::string scoreString = "Score : " + std::to_string(score);
       //t.setString(scoreString);
        text->setText(scoreString);
    }
    if (n->getTag() == "bee" || n->getTag() == "rhino"){
        Collision* myCol = (Collision*)getComponent("Collision");
        if (n->getPosition().y < myCol->getSize().y + myCol->getPosition().y){
            velocity.x = 0;
            velocity.y = 0;
            if (n->getPosition().x > getPosition().x){
            // velocity.x -= 30;
                accelerationX = -3;
                accelerationY = -4;
            }
            else{
                //velocity.x += 30;
                accelerationX = 3;
                accelerationY = -4;
            }
            hitFinished = false;
            sprite->setAnimation("hit");
        }
        else{
            velocity.y = -20;
            //SceneManager::manager()->getCurrentScene()->destroy(n);
            if (n->getTag() == "bee")
                ((Bee*)n)->killed();
            else if (n->getTag() == "rhino")
                ((Rhino*)n)->killed();
        }
    }
    if (n->getTag() == "saw"){
        velocity.x = 0;
        velocity.y = 0;
        if (n->getPosition().x > getPosition().x){
        // velocity.x -= 30;
            accelerationX = -5;
            accelerationY = -6;
        }
        else{
            //velocity.x += 30;
            accelerationX = 5;
            accelerationY = -6;
        }
        hitFinished = false;
        sprite->setAnimation("hit");
    }
}
void Frog::exitCollide(Node* n){
    if (n->getTag() == "pushable"){

    }
}