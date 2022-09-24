#version 450
// no buildt in output unlike the vert file so we need to maeke our ownx
//   layout qualifier (can output to multiple values)
//layout (location = 0) in vec3 fragColor;

layout (location = 0) out vec4 outColor;

layout(push_constant) uniform Push{
    mat2 transform;
    vec2 offset;
    vec3 color;
} push;

void main(){
    outColor = vec4(push.color, 1.0);
    //outColor = vec4(0.0, 0.5, 0.5, 1.0); 
                    //R    G    B    Alpha(opacity)
}