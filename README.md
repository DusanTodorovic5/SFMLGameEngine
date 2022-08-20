# Small but functional game engine created in C++ using SFML as a media library

## Features

 - A component system like Unity. Current components are:
   - Collision component
   - Animated sprite
   - Sprite
 - Collisions
 - Animations
 - Scenes and scene management
 - UI Layer with only Text at the moment

## How it works

Users can inherit Node class and override methods like Update, Start, Destroy... For UI elements, the user can use UINode which does not render in the world view but renders in the screen view. That means that UINode will not move as the camera moves. 

## Future plan

Currently, the engine can be used to create a fully functional 2D game including some puzzles, platformer, point-to-click, or whatever innovative 2D idea you have. SFML library is exposed to the user, so for any advanced feature, the library can be used. The only problem at the moment is that the scene build is very complicated and the reason for that is the lack of GUI Editor, so the build of GUI Editor is a future plan.

## Example game

An example game is a simple platformer where the player gets to play frog ninja. The objective is to collect all fruits. There are 2 enemies, the passive bee, which doesn't like chasing the frog, so it waits for the frog to hit her, also, there is an aggressive rhino that will chase the frog in an attempt to hit it. Oh, there are traps too. 
Example game shows how to make a game in this engine, it is very similar to Unity or Godot, but it has much less functionality and is always 2D, but hey, at least the build runs faster here :)
