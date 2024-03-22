uniform vec3 u_diffuseLightDirection;
uniform vec3 u_diffuseLightColour;
uniform vec3 u_ambientLightColour;

// Light 1
uniform vec4 u_pointLightPosRange1; // range is in .w
uniform vec3 u_pointLightColour1;
uniform vec3 u_pointLightAttenuation1;
uniform vec3 u_pointLightAmbient1;

in vec2 v_uv1;
in vec4 v_normal;
in vec3 v_pos;
uniform sampler2D tex;
out vec4 PixelColour;

vec3 calcLighting(vec4 pointLightPosRange, vec3 pointLightColour, vec3 pointLightAttenuation, vec3 pointLightAmbient, vec3 normal, vec3 samplePos) {
    
    float distance = length(pointLightPosRange.xyz - samplePos);
    if(distance > pointLightPosRange.w){
        return vec3(0.0, 0.0, 0.0);
    }

    vec3 lightDir = normalize(pointLightPosRange.xyz - samplePos.xyz);

	vec3 diff = pointLightColour * max(dot(normal, lightDir), 0.0);
    //vec3 light = pointLightColour;

    diff = clamp(diff, 0, 1);
    float attenuation = 1.0 / (pointLightAttenuation.x + pointLightAttenuation.y * distance + pointLightAttenuation.z * (distance * distance));
    vec3 light = (diff + pointLightAmbient) * attenuation;
    return light;
}

void main() {
    vec4 texColor = texture(tex, v_uv1);

    if (texColor.a < 0.5) {
        discard; 
    }

    vec3 n = normalize( v_normal.xyz );
    vec3 colour = vec3(0,0,0);

    colour += calcLighting(u_pointLightPosRange1, u_pointLightColour1, u_pointLightAttenuation1, u_pointLightAmbient1, v_normal.xyz, v_pos);
    vec3 diffuseLight = u_diffuseLightColour * max(0, dot(v_normal.xyz, u_diffuseLightDirection));
    
    vec3 greyscale = vec3(0.30, 0.59, 0.11);
    vec4 finalColour = texColor * vec4(diffuseLight + u_ambientLightColour + colour, 1.0);
    //finalColour = vec4(vec3(dot(finalColour.rgb, greyscale)), finalColour.a);
    PixelColour =  finalColour;
}