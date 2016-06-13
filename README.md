# README #

SnakeArduBoy !

A simple Snake for Arduboy.

### How do I get set up? ###

* Open sketch with Arduino IDE
* Upload sketch to Arduboy
* Play !


### Code overview ###
This code has been written in a rush so it is not well tested nor documented...

#### H Namespace ####
All classes have been placed under the namespace _H_

##### H::Snake #####
Model class for the game.
A _Snake_ has a _List_ of bones (a bone is a 2D position), a width and height (in _model_ space).
Its public methods are :
- movement orders (returning true if movement is possible)
- show/hide apple
- check if snake has grown (eaten an apple)

##### H::List #####
Custom implementation of a circular doubly linked list (where list head and tail are connected).
List elements are _Nodes_. A node contains a pointer to a value (here a _Position_ of a bone) and pointers to the next and previous bones.

##### H::Position #####
2D position with + and == operators for conveniency.

##### H::SnakeDrawer #####
This is the games view. It can be adjusted to render the _Snake_ in _view_ space so the _Snake_ do not evolve on a 1 pixel thin grid (_model_ space).

#### Sketch ####
This is the game controller. It sends orders to the model whenever button events appear. It also uses the view to render _Snake_, score and maximum score (and also to toggle sound).
