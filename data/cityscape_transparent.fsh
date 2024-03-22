in vec2 v_uv1;
uniform sampler2D buildingTexture;
out vec4 PixelColor;

void main() {
vec4 texColor = texture(buildingTexture, v_uv1);

    if (texColor.a < 0.5) {
        discard; 
    }

    PixelColor = texColor;
    
}