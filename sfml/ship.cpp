#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstring>
#include <cstdio>

#define PI 3.14f
#define HPI 3.14f/2.f

int main() {
  float boost, rot;
  float maxspd=4,vpar=0,vper=0;
  float vx=0,vy=0;

  sf::Vector2f spos;  // ship position
  sf::Vector2f mpos;  // mouse position in world
  sf::Vector2i cpos;  // cursor position in window
  sf::Vector2f dir;   // direction from ship to mouse

  // window
  sf::RenderWindow win(sf::VideoMode(800,600), "Shipface");

  // text
  sf::Font font;
  font.loadFromFile("futura.ttf");
  sf::Text text("bla", font);
  text.setCharacterSize(30);
  text.setPosition(10,10);
  char dbgchr[100];
  sf::String dbgstr;

  // sprite
  sf::Texture tex;
  if (!tex.loadFromFile("ship.png"))
    return EXIT_FAILURE;
  sf::Sprite sprite(tex);
  sprite.scale(0.5,0.5);
  sprite.setPosition(200,200);

  // set the origin to the centre of the sprite
  sf::FloatRect sbox = sprite.getLocalBounds();
  sf::Vector2f offs(sbox.width/2.0, sbox.height/2.0);
  sprite.setOrigin(offs);

  // loop
  while (win.isOpen()) {
    // mouse rotation
    spos = sprite.getPosition();
    cpos = sf::Mouse::getPosition(win);
    mpos = win.mapPixelToCoords(cpos);
    dir  = mpos - spos;

    // need to convert radians -> degrees
    rot  = atan2(dir.y, dir.x) + (HPI);
    sprite.setRotation(rot*(180.f/PI) - 180.f);

    // events
    sf::Event event;

    vx = 0;
    vy = 0;
    vpar = 0;
    vper = 0;
    boost = 1;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
      boost = 2;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
      win.close();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
      vper = -maxspd;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
      vper = maxspd;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
      vpar = maxspd;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
      vpar = -maxspd;
    }

    vx = boost * (vpar*sin(rot) + vper*sin(rot+HPI));
    vy = boost * (vpar*-cos(rot)+ vper*-cos(rot+HPI));

    sprintf(dbgchr, "%4.1f %4.1f %4.1f %4.1f %4.1f %4.1f %4.1f", rot*(180.f/PI), sin(rot), cos(rot), vpar, vper, vx, vy);
    dbgstr = dbgchr;
    text.setString(dbgstr);

    while (win.pollEvent(event)) {
      switch (event.type) {
        // exit on close
        case sf::Event::Closed:
          win.close();
          break;
      }
    }

    sprite.move(vx,vy);

    win.clear();
    win.draw(text);
    win.draw(sprite);
    win.display();
  }

  return EXIT_SUCCESS;
}
