Credits:
https://craftpix.net/freebies/free-forest-battle-backgrounds/
https://kenney.nl/assets/animal-pack-redux
https://kenney.nl/assets/simplified-platformer-pack
https://freesound.org/people/PRINCEofWORMS/sounds/571273/
https://freesound.org/people/Hitrison/sounds/216675/
https://pixabay.com/sound-effects/owl-144750/

//problem
SeeSaw joint radomly lose balnce to one side
            PhysicsObject* Box6 = CreateBox(b2Vec2(16.0f, 8.5f), 0.0f);
            PhysicsObject* Box7 = CreateBox(b2Vec2(18.00f, 8.5f), 0.0f);
            PhysicsObject* Box8 = CreateBox(b2Vec2(17.00f, 8.5f), 0.0f);
            PhysicsObject* Duck3 = CreateEnemy(b2Vec2(16.99465f, 7.5f), 0.0f);
This makes it balance "on the first attempt".
If retrying the level, it will lose balance.

tried to use ropejoint but couldn't find it in the header file.