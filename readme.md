# The House

## Link

GitHub link: https://github.com/bizhouJia/COMP3016-CW2

YouTube link: https://www.youtube.com/watch?v=gNltx1cx8dQ

## Program Environment

freeglut 3.0.0.v140.1.0.2

glew v140.1.12.0

glfw 3.3.9

Visual Studio 2022

## Description

Draw a map, with a house located on the left, and a little maze for decoration. Users can change the location of the character, change the shape and color of furniture.

The program starts with drawing the terrain, followed by filling textures, building houses including walls, windows, doors, door handles and roofs, drawing trees, fences, pillars, and finally, drawing a maze.

Users can use keyboards to control the program

Arrow keys to rotate camera

F1, F2, F3, F4 to control the movement of the character

F7 and F8 to control the scaling of the camera

HOME to hide the house

F5 to change the type of the table

F6 to change the type of the chair

END to change the type of the bed

## Prototype

This program is inspired by some decoration games, which use beautiful colors and texture to decorate house. Compared to these games, this program has a little maze as a decoration, and users can control the character to move on the map.  However, the material textures in this program are not refined enough, and the character is merely represented by a single sphere. There's no collision volume between objects, allowing characters to pass through walls. This creates a sense of unreality and severely undermines the immersive experience.

## Code

GLfloat matiral_specular[4] = { 0.00, 0.00, 0.00, 1.00 };

It defines the specular reflection properties of the material. The first three values of the array (0.00, 0.00, 0.00) represent the specular reflection coefficients for the red, green, and blue channels, respectively. They are all set to 0, meaning that the material will not reflect any specular light. The last value of the array (1.00) is typically used to indicate transparency, and in this case, it is set to 1, indicating complete opacity.

GLfloat matiral_emission[4] = { 0.00, 0.00, 0.00, 1.00 };

It defines the emissive properties of the material. The first three values of the array (0.00, 0.00, 0.00) represent the intensity of the light emitted by the material itself. Here they are all set to 0, indicating that the material will not emit any light. Similar to the specular reflection property, the last value of the array (1.00) represents transparency.

In these two lines of code, since the color components are all set to 0, it means that the material will neither reflect light nor emit light, with only the transparency being set to completely opaque.



"glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matiral_diffuse_ambient);

It sets the ambient and diffuse properties of the object's material.

GL_FRONT_AND_BACK specifies that the setting will affect both the front and back of the object.

GL_AMBIENT_AND_DIFFUSE indicates that both ambient and diffuse properties are being set simultaneously.

matiral_diffuse_ambient is an array defining the color for both ambient and diffuse lighting.



glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matiral_specular);

It sets the specular reflection properties of the object.

The GL_SPECULAR parameter indicates that the specular reflection color is being set.

The matiral_specular array defines the color for specular reflection.



glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, matiral_emission);

It sets the emissive properties of the material.

GL_EMISSION indicates that the emissive color of the material is being set.

The matiral_emission array provides the color values for emission.



glMaterialf(GL_FRONT_AND_BACK, matiral_shininess, 0);

It sets the shininess of the object (the sharpness of the specular highlights).

GL_FRONT_AND_BACK indicates that the setting applies to both the front and back of the object.

The final 0 is the value for shininess, which typically ranges from 0 to 128. A value of 0 indicates no shininess."



void construct(double x, double y, double z, double x1, double y1, double z1)

The function 'construct' takes six parameters: x, y, z, x1, y1, z1. These parameters seem to be used for defining the position and size of a house. x, y, z represent the coordinates of a starting point of the house, while x1, y1, z1 represent the extension lengths along the x, y, z axes, respectively.



glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

It clears the screen and the depth buffer.

GL_COLOR_BUFFER_BIT indicates to clear the color buffer, which clears the colors on the screen and resets them to a preset background color.

GL_DEPTH_BUFFER_BIT indicates to clear the depth buffer, which is very important when rendering each frame, as it ensures that depth information (which object is in front of another) is not carried over from the previous frame.



glMatrixMode(GL_MODELVIEW);

It sets the current matrix mode to the model-view matrix.

In OpenGL, the matrix mode determines which matrix the subsequent matrix operations (such as translation, rotation, scaling) will affect. The model-view matrix is used for handling the position and orientation of objects, as well as the position and orientation of the camera (observer).



glLoadIdentity();

It resets the current model-view matrix to the identity matrix.

Calling glLoadIdentity() eliminates all previous transformations applied to the model-view matrix, returning it to its original state with no translations, rotations, or scaling.

