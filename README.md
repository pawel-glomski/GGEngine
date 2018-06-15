# GameEngine
A simple and easy to use game code structure base. This framework seperates every functionality on different modules with an api, that makes adding new modules easy and fast and also handles dependencies between them automaticly. 
It makes use of my ECSpp library for fast Entities decoupled logic and data handling.

Third party dependencies:
------------------------

[SFML 2.4.2](https://github.com/SFML/SFML) - display, input and audio.

Example:
------------------------
As an example of use I made 2D rigid body physics simulation:

All the physics math equations are based on [this tutorial]( https://gamedevelopment.tutsplus.com/series/how-to-create-a-custom-physics-engine--gamedev-12715)

[cute_c2](https://github.com/RandyGaul/cute_headers/blob/master/cute_c2.h) was also used for collision detection
