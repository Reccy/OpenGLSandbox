#shader vertex
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aUV;

out vec2 v_UV;

uniform mat4 uMVP;

void main()
{
    gl_Position = uMVP * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    v_UV = aUV;
}
#shader fragment
#version 330 core

out vec4 FragColor;

in vec2 v_UV;

uniform sampler2D uTexture;
uniform vec4 uColor;

void main()
{
    vec4 texColor = texture(uTexture, v_UV);
    FragColor = uColor * texColor;
}