#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdio>

typedef struct b_box {
  int left;
  int right;
  int top;
  int bot;
} b_box;

int main() {
  float spd = 5.5;
  float vx = 0,vy = 0;
  float g = 9.8;
  float gravity = 0;
  sf::Vector2f spos;  // ship position
  sf::Vector2f opos;  // mouse position in world
  sf::Vector2i cpos;  // cursor position in window
  sf::Vector2f dir;   // direction from ship to mouse
  sf::Vector2f coldif(0.0f,0.0f);

  unsigned int COLL_L = 0;
  unsigned int COLL_R = 0;
  unsigned int COLL_T = 0;
  unsigned int COLL_B = 0;
  unsigned int XCOLLISION = 0;
  unsigned int YCOLLISION = 0;

  b_box s1;
  b_box s2;


  // window
  sf::RenderWindow win(sf::VideoMode(800,600), "Shipface");

  // sprite
  sf::Texture rabbit;
  if (!rabbit.loadFromFile("box.png"))
    return EXIT_FAILURE;
  sf::Sprite sprite(rabbit);
  sprite.scale(3,3);
  sprite.setPosition(0,0);

  sf::Texture cat;
  if (!cat.loadFromFile("box.png"))
    return EXIT_FAILURE;
  sf::Sprite obstacle(cat);
  obstacle.scale(3,3);
  obstacle.setPosition(400,300);



  // set the origin to the centre of the sprite
  sf::FloatRect sbox1 = sprite.getLocalBounds();
  sf::Vector2f offs1(sbox1.width/2.0, sbox1.height/2.0);
  sprite.setOrigin(offs1);
  sf::FloatRect sbox2 = obstacle.getLocalBounds();
  sf::Vector2f offs2(sbox2.width/2.0, sbox2.height/2.0);
  obstacle.setOrigin(offs2);
  sf::Vector2f radius1(sbox1.width, sbox1.height);
  sf::Vector2f radius2(sbox2.width, sbox2.height);

  // loop
  while (win.isOpen()) {

  //view definition
    sf::View cam1(sf::FloatRect(0,0,800,600));

    // mouse rotation
    spos = sprite.getPosition();
    opos = obstacle.getPosition();
    //cpos = sf::Mouse::getPosition(win);
    //mpos = win.convertCoords(cpos);
    //dir  = mpos - spos;

    // need to convert radians -> degrees
    //rot  = atan2(dir.y, dir.x) * (180./3.14) - 90.0;

    // events
    sf::Event event;

    vx = 0;
    vy = 0;
    gravity = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
      win.close();
    }

    //COLLISIOOOOOOON!!!!


    sf::FloatRect cbox1 = sprite.getGlobalBounds();
    sf::FloatRect cbox2 = obstacle.getGlobalBounds();

    s1.left  = cbox1.left;
    s1.right = cbox1.left+cbox1.width;
    s1.top   = cbox1.top;
    s1.bot   = cbox1.top+cbox1.height;

    s2.left  = cbox2.left;
    s2.right = cbox2.left+cbox2.width;
    s2.top   = cbox2.top;
    s2.bot   = cbox2.top+cbox2.height;


    COLL_L = 0; COLL_R = 0;
    COLL_T = 0; COLL_B = 0;
    coldif.x = 0; coldif.y = 0;

    if (cbox1.intersects(cbox2)) {
      // Horizontal collision  
      COLL_L = (s1.left  > s2.left && s1.left  < s2.right);
      COLL_R = (s1.right > s2.left && s1.right < s2.right);
      COLL_T = (s1.top   > s2.top  && s1.top   < s2.bot);
      COLL_B = (s1.bot> s2.top  && s1.bot< s2.bot);

      if (COLL_R)
      {
          printf("Right edge\n");
          coldif.x =  s1.right - s2.left + 1;
      } else if (COLL_L) {
          printf("Left edge\n");
          coldif.x = -(s2.right - s1.left + 1);
      }
      if (COLL_B)
      {
          printf("Bottom edge\n");
          coldif.y = -(s1.bot - s2.top + 1);
      } else if (COLL_T) {
          printf("Top edge\n");
          coldif.y = s1.top - s2.bot + 1;
      }

      XCOLLISION = COLL_L || COLL_R;
      YCOLLISION = COLL_T || COLL_B;
      printf("xcol=%d ycol=%d\n", XCOLLISION, YCOLLISION);
    } else {
      XCOLLISION = 0; YCOLLISION = 0;
    }

    sprite.move(-coldif);
    printf("bounds: %f %f\n", coldif.x, coldif.y);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
      vx = (spos.x > 40 && !XCOLLISION)? -spd:0;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
      vx = (spos.x < 780 && !XCOLLISION)? spd:0;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
      gravity = (!YCOLLISION)? -g:0;
    } else  {
      gravity = (spos.y < 500 && !YCOLLISION)? g:0;
    }
    sprite.move(vx,gravity);




    while (win.pollEvent(event)) {
      switch (event.type) {
        // exit on close
        case sf::Event::Closed:
          win.close();
          break;


      }
    }
    cam1.setCenter(spos.x,300);

    win.clear();
    win.setView(cam1);
    win.draw(sprite);
    win.draw(obstacle);
    win.display();
  }

  return EXIT_SUCCESS;
}
