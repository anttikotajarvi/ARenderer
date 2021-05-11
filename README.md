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

# Render .obj
ARenderer::buildModel n\
Current obj implementation only supports faces in order of three (i.e teapot.obj works fine) 
Quick script to move the object on screen with keyboard controls, WASD and QE for movement,
arrow keys and .- for rotation and ÖÄ (148 and 132) for scale, dont know what the keys are for other than finnish keyboard layouts...
```c++
ARenderer d(classic, SCREEN_WIDTH, SCREEN_HEIGHT);
	ARC::Models::Model model = ARC::Models::import_obj("path\\to\\model.obj");

	bool on = true;
	Point O{ 100, 100, 100 };
	double scale = 20;
	Point R{ 0,0,0 };
	while (on) {
		int key = _getch();
		switch (key) {
		case 27: on = false; break;
		case 113: O.y -= 1; break;
		case 119: O.z += 1; break;
		case 101: O.y += 1; break;
		case 97: O.x -= 1; break;
		case 115: O.z -= 1; break;
		case 100: O.x += 1; break;
		case 72: R.x += 0.2; break;
		case 80: R.x -= 0.2; break;
		case 75: R.y -= 0.2; break;
		case 77: R.y += 0.2; break;
		case 46: R.z -= 0.2; break;
		case 45: R.z += 0.2; break;
		case 148: scale -= 1; break;
		case 132: scale += 1; break;
		}
		d.MainVMap.resetData();
		d.buildModel(model, O, scale, R);
		d.render();
		d.CM.print();
	}

```
