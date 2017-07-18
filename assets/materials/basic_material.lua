-- Pegasus Engine
-- 2017 - Benjamin Carter (bencarterdev@outlook.com)
--
-- This software is provided 'as-is', without any express or implied warranty.
-- In no event will the authors be held liable for any damages arising from the use of this software.
--
-- Permission is granted to anyone to use this software for any purpose,
-- including commercial applications, and to alter it and redistribute it freely,
-- subject to the following restrictions:
--
-- 1. The origin of this software must not be misrepresented;
--    you must not claim that you wrote the original software.
--    If you use this software in a product, an acknowledgement
--    in the product documentation would be appreciated but is not required.
--
-- 2. Altered source versions must be plainly marked as such,
--    and must not be misrepresented as being the original software.
--
-- 3. This notice may not be removed or altered from any source distribution.

-- An example of a serialized material.
Material = {
    -- The name of the material. Used for debugging purposes.
    name = "basic material",
    -- Whether lighting calculations will affect this material.
    lighting_enabled = false,
    -- Whether the diffuse colour of the mesh will be edited.
    diffuse_colour = { 
        r = 1.0,
        g = 1.0,
        b = 1.0,
        a = 1.0
    },
    -- How shiny the specular lighting will be.
    shininess = 1.0,
    -- The textures that are bound with this material.
    textures = {
        diffuse = "asset.texture.diffuse",
        specular = "asset.texture.specular"
    }
    -- The shader that the material will utilise.
    shader = "asset.shader.basic"
}