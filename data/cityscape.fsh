in vec2 v_uv1;
uniform sampler2D buildingTexture;
out vec4 PixelColor;

void main() {
    PixelColor = texture(buildingTexture, v_uv1);
    
}