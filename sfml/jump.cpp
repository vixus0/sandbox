#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <cstdio>

using namespace std;

#define b2scale 30.f

void CreateGround(b2World &world, b2Body **body, float w, float h, float x, float y) {
  // box2d: create a body definition
  b2BodyDef bodydef;
  bodydef.position = b2Vec2(x/b2scale, y/b2scale);
  bodydef.type = b2_staticBody;

  // box2d: place the body in the world
  *body = world.CreateBody(&bodydef);
 
  // box2d: create a shape
  b2PolygonShape shape;
  shape.SetAsBox(w/(2*b2scale), h/(2*b2scale));
  
  // box2d: create a fixture definition to define physical properties
  //        and give it the shape defined above
  b2FixtureDef  fixdef;
  fixdef.density = 0.f;
  fixdef.shape = &shape;

  // box2d: attach the fixture definition to the body
  (*body)->CreateFixture(&fixdef);
  printf("ground: %f %f\n", (*body)->GetWorldCenter().x, (*body)->GetWorldCenter().y);
}

void CreateRob(b2World& world, b2Body **body, float w, float h, float x, float y) {
  b2BodyDef bodydef;
  bodydef.position = b2Vec2(x/b2scale, y/b2scale);
  bodydef.type = b2_dynamicBody;
  bodydef.active = true;
  *body = world.CreateBody(&bodydef);
  b2PolygonShape shape;
  shape.SetAsBox(w/(2*b2scale), h/(2*b2scale));
  b2FixtureDef fixdef;
  fixdef.density = 1.f;
  fixdef.friction = 0.7f;
  fixdef.shape = &shape;
  (*body)->CreateFixture(&fixdef);
  printf("rob: %f %f\n", (*body)->GetWorldCenter().x, (*body)->GetWorldCenter().y);
} 

int main() {

  // sfml window
  sf::RenderWindow win(sf::VideoMode(800,600), "Jumper");
  win.setFramerateLimit(60);

  // boc2d world
  float groundw=800.f, groundh=50.f;
  float robw=24.f, robh=32.f;
  b2Vec2 g(0.f, 9.8f);
  b2World world(g);

  // graphics
  sf::Texture texRob;
  sf::RectangleShape shpGround(sf::Vector2f(groundw,groundh));
  texRob.loadFromFile("rob.png");
  sf::Sprite  sprRob(texRob);

  sprRob.setOrigin(robw/2.0, robh);
  shpGround.setOrigin(groundw/2.0, groundh/2.0);

  // create stuff
  b2Body* rob;
  b2Body* ground;
  b2Vec2 prob;
  b2Vec2 pgrnd;

  CreateGround(world, &ground, groundw, groundh, groundw/2.0, 600.0f-groundh/2.0);
  CreateRob(world, &rob, robw, robh, 400.f, 200.f);

  // loop
  float robx=0, roby=0, grnx=0, grny=0;
  while (win.isOpen()) {
    //printf("Starting\n");

    prob = rob->GetWorldCenter();
    pgrnd = ground->GetWorldCenter();

    //robx = rob->GetTransform().p.x * b2scale - robw/2.f;
    //roby = rob->GetTransform().p.y * b2scale - robh/2.f;
    //grnx = ground->GetTransform().p.x * b2scale - groundw/2.f;
    //grny = ground->GetTransform().p.y * b2scale - groundh/2.f;
    
    robx = prob.x * b2scale;
    roby = prob.y * b2scale;
    grnx = pgrnd.x * b2scale;
    grny = pgrnd.y * b2scale;

    //printf("Got positions\n");

    //fprintf(stdout, "robx: %f, roby: %f\n", robx, roby);
    //fprintf(stdout, "grnx: %f, grny: %f\n", grnx, grny);

    shpGround.setPosition(grnx, grny);
    sprRob.setPosition(robx,roby);

    //printf("Set positions\n");

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) win.close();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
      rob->ApplyForce(b2Vec2(-5.0,0.0), prob);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
      rob->ApplyForce(b2Vec2(5.0,0.0), prob);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
      rob->ApplyForce(b2Vec2(0.0,-20.0), prob);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    }

    win.clear();
    win.draw(sprRob);
    win.draw(shpGround);
    win.display();
    world.Step(1/60.f, 8, 3);
  }

  return EXIT_SUCCESS;
}
  

