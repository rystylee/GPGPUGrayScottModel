#version 400 core
precision highp float;

in vec4 vPosition;
in vec2 vTexCoord;

out vec4 fragColor;

uniform sampler2DRect u_tex;

void main()
{
    vec2 uv = vPosition.xy;
    vec4 c = texture(u_tex, uv.st);
    fragColor = vec4(vec3(1.0 - c.r), 1.0);
}
