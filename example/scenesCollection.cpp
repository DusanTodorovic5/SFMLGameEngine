#include "EngineDirectory/scenesCollection.hpp"
#include "EngineDirectory/emptyNode.hpp"
#include "EngineDirectory/sprite.hpp"
#include "EngineDirectory/scene.hpp"
#include "EngineDirectory/engine.hpp"
#include "EngineDirectory/sceneManager.hpp"
#include "frog.hpp"
#include "banana.hpp"
#include "apple.hpp"
#include "strawberry.hpp"
#include "platform.hpp"
#include "bee.hpp"
#include "rhino.hpp"
#include "saw.hpp"
void scene1(){
    

    Scene* scene = new Scene();
    EmptyNode* background = new EmptyNode("background");
    background->setComponent(new Sprite("background.png"));
    background->setPosition(0,0);
    scene->root = new Scene::SceneNode(background);


    EmptyNode* ground = new EmptyNode("ground");
    Collision* col = new Collision(ground,false,true);
    col->setRectangle(sf::FloatRect(0,0,3400,240));
    ground->setComponent(col);
    ground->setComponent(new Sprite("groundGrass.png"));
    ground->setPosition(0, 840);

    scene->instantiate(ground,background);
    
    //setovan box
    EmptyNode* leftBarrier = new EmptyNode("barrier");
    Collision* col1 =  new Collision(leftBarrier,false,true);
    col1->setRectangle(sf::FloatRect(0,0,400,2000));
    leftBarrier->setComponent(col1);
    leftBarrier->setPosition(-400,-500);

    EmptyNode* rightBarrier = new EmptyNode("barrier");
    Collision* col2 =  new Collision(rightBarrier,false,true);
    col2->setRectangle(sf::FloatRect(0,0,400,2000));
    rightBarrier->setComponent(col2);
    rightBarrier->setPosition(3400,-500);
    //kraj setovanja boxa



    scene->instantiate(rightBarrier,background);
    scene->instantiate(leftBarrier,background);

    EmptyNode* fruitHolder = new EmptyNode("holder");
    fruitHolder->setName("holder");

    scene->instantiate(fruitHolder,background);

    Banana* b = new Banana();

    b->setPosition(1000,400);

    scene->instantiate(b,fruitHolder);

    Apple* a = new Apple();

    a->setPosition(1100,400);

    scene->instantiate(a,fruitHolder);

    Strawberry* s = new Strawberry();

    s->setPosition(900,400);

    scene->instantiate(s,fruitHolder);


    Platform* p = new Platform(5);
    p->setPosition(sf::Vector2f(900,500));

    scene->instantiate(p,background);


    Bee* bee = new Bee();
    bee->setPosition(1500,600);
    scene->instantiate(bee,background);


    Rhino* rhino = new Rhino();
    rhino->setPosition(1100,770);
    scene->instantiate(rhino,background);

    Saw* saw = new Saw();
    saw->setPosition(700,700);
    scene->instantiate(saw,background);

    Frog* frog = new Frog();

    scene->instantiate(frog,background);
    
    SceneManager::manager()->addScene("scene1",scene);
}

void SceneCollection::loadScenes(){
    scene1();
    SceneManager::manager()->switchScene("scene1");
    //Engine::engine()->setDebugMode(true);
}