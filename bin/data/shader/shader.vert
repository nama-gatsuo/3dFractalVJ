#version 150
precision mediump float;

uniform mat4 modelViewProjectionMatrix;
in vec4 position;
in vec2 texcoord;

out vec2 vTexCoord;

void main(){
    vTexCoord = texcoord;
    gl_Position = modelViewProjectionMatrix * position;
}
