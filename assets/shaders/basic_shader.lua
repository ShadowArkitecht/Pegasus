-- Sparky Engine
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

-- An example of a serialized shader program.
ShaderProgram = {
    -- The name of the shader. Used for debugging purposes.
    name = "basic shader",
    -- The individual shaders that make up this program.
    -- Stored as an array of tables.
    shader = {
        {
            -- The source directory of the shader.
            source = "data/assets/basic_vertex.glsl",
            -- The type of shader.
            shader_type = ShaderType.Vertex
        },
        {
            -- The source directory of the shader.
            source = "data/assets/basic_fragment.glsl",
            -- The type of shader.
            shader_type = ShaderType.Fragment
        }
    }
    -- TODO(Ben): Add functions for binding constant uniforms and uniforms per frame.
}