#version 400 core
precision highp float;

in vec4 vPosition;
in vec2 vTexCoord;

out vec4 fragColor;

uniform sampler2DRect u_prevBuffer;
uniform float u_feed;
uniform float u_kill;
uniform float u_dA;
uniform float u_dB;
uniform float u_dt;

vec2 calcLaplacian(const in sampler2DRect prevBuffer, const in vec2 uv)
{
    vec2 offset[9];
    offset[0] = vec2( 0.0, -1.0);
    offset[1] = vec2(-1.0,  0.0);
    offset[2] = vec2( 0.0,  0.0);
    offset[3] = vec2( 1.0,  0.0);
    offset[4] = vec2( 0.0,  1.0);
    offset[5] = vec2(-1.0, -1.0);
    offset[6] = vec2( 1.0, -1.0);
    offset[7] = vec2(-1.0,  1.0);
    offset[8] = vec2( 1.0,  1.0);
    
    float kernel[9];
    kernel[0] = 0.2;
    kernel[1] = 0.2;
    kernel[2] = -1.0;
    kernel[3] = 0.2;
    kernel[4] = 0.2;
    kernel[5] = 0.05;
    kernel[6] = 0.05;
    kernel[7] = 0.05;
    kernel[8] = 0.05;
    
    vec2 lap = vec2(0.0, 0.0);
    for(int i=0; i<9; i++){
        vec2 tmp = texture(prevBuffer, uv + offset[i]).xy;
        lap += tmp * kernel[i];
    }
    return lap;
}

void main()
{
    vec2 uv = vPosition.xy;
    vec2 lap = calcLaplacian(u_prevBuffer, uv);
    vec2 prevAB = texture(u_prevBuffer, uv).xy;
    
    float a = prevAB.x;
    float b = prevAB.y;

    float A = clamp(a + (u_dA * lap.x - (a * b * b) + u_feed * (1.0 - a)) * u_dt, 0.0, 1.0);
    float B = clamp(b + (u_dB * lap.y + (a * b * b) - (u_kill + u_feed) * b) * u_dt, 0.0, 1.0);
    
    fragColor = vec4(A, B, 0.0, 1.0);
}
