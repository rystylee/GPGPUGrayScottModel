#version 150
precision mediump float;

uniform sampler2DRect resultTex;

in vec2 vTexCoord;
in vec2 vPos;

out vec4 fragColor;

void main(){
    
    vec4 smpColor = texture(resultTex, vPos);
    
    fragColor = smpColor;
}
