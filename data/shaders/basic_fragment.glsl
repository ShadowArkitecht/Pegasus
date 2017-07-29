/*
* Pegasus Engine
* 2017 - Benjamin Carter (bencarterdev@outlook.com)
*
* This software is provided 'as-is', without any express or implied warranty.
* In no event will the authors be held liable for any damages arising from the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it freely,
* subject to the following restrictions:
*
* 1. The origin of this software must not be misrepresented;
*    you must not claim that you wrote the original software.
*    If you use this software in a product, an acknowledgement
*    in the product documentation would be appreciated but is not required.
*
* 2. Altered source versions must be plainly marked as such,
*    and must not be misrepresented as being the original software.
*
* 3. This notice may not be removed or altered from any source distribution.
*/

#version 330 core

//====================
// Uniform variables
//====================
uniform sampler2D u_texture;

//====================
// Interfaces
//====================
in VS_OUT 
{
	vec2 uv_coords;

} fs_in;

//====================
// Out variables
//====================
out vec4 diffuse_colour;

//====================
// Functions
//====================
void main()
{
	// Create the diffuse texture and map it to the rendering context.
	vec4 diffuse_texture = texture2D(u_texture, fs_in.uv_coords);
	// Set the diffuse colour of the fragment and output it.
	diffuse_colour = vec4(diffuse_texture.rgb, 1.0);
}