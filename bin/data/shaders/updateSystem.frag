#version 150
precision highp float;

uniform sampler2DRect backbuffer;
uniform float feed;
uniform float kill;
uniform float dA;
uniform float dB;
uniform float dt;

in vec2 vTexCoord;
in vec2 vPos;

out vec4 fragColor;

float kernel[9];
vec2 offset[9];

void main(){
        
    offset[0] = vec2( 0.0, -1.0);
    offset[1] = vec2(-1.0,  0.0);
    offset[2] = vec2( 0.0,  0.0);
    offset[3] = vec2( 1.0,  0.0);
    offset[4] = vec2( 0.0,  1.0);
    
    offset[5] = vec2(-1.0, -1.0);
    offset[6] = vec2( 1.0, -1.0);
    offset[7] = vec2(-1.0,  1.0);
    offset[8] = vec2( 1.0,  1.0);
    
    kernel[0] = 1.0;
    kernel[1] = 1.0;
    kernel[2] = -6.82842712;
    kernel[3] = 1.0;
    kernel[4] = 1.0;
    
    kernel[5] = 0.707106781;
    kernel[6] = 0.707106781;
    kernel[7] = 0.707106781;
    kernel[8] = 0.707106781;
    
    vec2 lap = vec2(0.0, 0.0);
    for(int i=0; i<9; i++){
        vec2 tmp = texture(backbuffer, vPos + offset[i]).rb;
        lap += tmp * kernel[i];
    }
    
    vec2 uv = texture(backbuffer, vPos).rb;
    
    float du = dA * lap.r - uv.r * uv.g * uv.g + feed * (1.0 - uv.r);
    float dv = dB * lap.g + uv.r * uv.g * uv.g - (feed + kill) * uv.g;
    
    vec2 dst = uv + dt * vec2(du, dv);
    
    fragColor = vec4(clamp(dst.r, 0.0, 1.0), 1.0 - dst.r/dst.g, clamp(dst.g, 0.0, 1.0), 1.0);
}
