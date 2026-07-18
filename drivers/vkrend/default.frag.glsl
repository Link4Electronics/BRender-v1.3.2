#version 450

layout (location = 0) in vec3 colour;
layout (location = 1) in vec2 uv;

layout (location = 0) out vec4 mainColour;

layout (binding = 0) uniform sampler2D uSampler;

layout (binding = 3) uniform uDefaultUBO {
    float uFlipVertically;
    int uDiscardPurplePixels;
};

void main()
{
    mainColour = texture(uSampler, vec2(uv.x, abs(uFlipVertically - uv.y)));
    if (uDiscardPurplePixels == 1 && mainColour.rgb == vec3(1.0, 0.0, 1.0)) {
        discard;
    }
}
