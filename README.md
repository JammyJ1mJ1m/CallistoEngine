# Callisto Engine

Calisto engine is being written in C++ with Abstraction and an ECS in mind. 
The original aim is to create the engine in such a way that the rendering can be swapped out between different rendering API's such as OpenGL or D3D11/12. 
Currently, I am focusing on implementing the OpenGL side of things.

## How to use  
### Resources
- Cubemaps can be loaded from a config file and its layout is as follows:
```
kright   local location to right image\\right.png
kleft    local location to left image\\left.png
ktop     local location to top image\\top.png
kbottom  local location to bottom image\\bottom.png
kfront   local location to front image\\front.png
kback    local location to back image\\back.png
```
lines marked with # are ignored so can be used as comments, at least that's what I use. It isn't picky so you could use whatever you wanted or none at all.