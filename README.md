# ARenderer
Example of rendering a triangle

```c++
//Create instance of the class, 'classic' is one of 2 character palettes defined in palettes.cpp
ARenderer d(classic, SCREEN_WIDTH, SCREEN_HEIGHT);

//Create Triangle structure with three 3d points (xyz)
Triangle Example{
  {10,10,10},
  {20,150,60},
  {150,100,180}
};		
//Build a virtual map of the shape (VMap)
  VMap ex = d.build(Example); 
  
//Place it to the MainVMap of the ARenderer instance
d.placeVMap(ex);
  
//Render the MainVMap
d.render();

//Print with the consoleManager object
d.CM.print();
  ```
 The render() function takes in a VMap as a parameter (ARenderer::MainVMap is passed if no arguments) so its possible to just do render(build(triangle)) but it will just render the shape on top of everything because depth and overlapping of polygons is handled by placeVMap
 
```c++
Triangle Example{
  {10,10,10},
  {20,150,60},
  {150,100,180}
};
d.render(d.build(example));
d.CM.print();
```
