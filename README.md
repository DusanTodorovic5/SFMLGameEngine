# Small but functional game engine created in C++ using SFML as media library

## Features

 - Component system like Unity. Current components are:
   - Collision component
   - Animated sprite
   - Sprite
 - Collisions
 - Animations
 - Scenes and scene managment
 - UI Layer with only Text at the moment

## How it works

User can inherit Node class and override methods like Update, Start, Destroy... For UI elements, user can use UINode which does not render in the world view but renders in screen view. That means that UINode will not move as the camera moves. 

## Future plan

Currently, engine can be used to create fully functional 2D game including some puzzles, platformer, point to click or whatever inovative 2D idea you have. SFML library is exposed to the user, so for any advanced feature, the library can be used. Only problem at the moment is that the scene build is very complicated and the reason for that is lack of GUI Editor, so the build of GUI Editor is future plan.

## Example game

Example game is simple platformer where player gets to play frog hero. The objective is to collect all fruits. There are 2 enemies, passive bee, which doesn't like chasing the frog, so it waits for frog to hit her, also, there is agressive rhino that will chase the frog in attempt to hit it. Oh, there are traps too. 
Example game shows how to make game in this engine, it is very similiar to Unity or Godot, but it has much less funtionality and is always 2D, but hey, at least the build runs faster here :)
