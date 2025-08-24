#version 330 core

#define MAX_POINT_LIGHT 8
#define MAX_SPOT_LIGHT 8

in vec3 vColor;
in vec2 vUV;
in vec3 vNormal;
in vec3 vFragPos;

out vec4 FragColor;

struct DirLight
{
    vec3 dir;
    vec3 color;
    float intensity;
};

struct PointLight
{
    vec3 pos;
    vec3 color;
    float intensity;
    float constant;
    float linear;
    float quadratic;
};

struct SpotLight
{
    vec3 pos;
    vec3 color;
    vec3 dir;
    float intensity;
    float cutOff;
    float outerCutOff;
    float constant;
    float linear;
    float quadratic;
};

struct Material
{
    vec3 ambientK;
    vec3 specularK;
    float shininess;
    bool isUseTex;
};

uniform Material uMaterial;
uniform DirLight uDirLight;
uniform int uPointLightCount;
uniform PointLight uPointLight[MAX_POINT_LIGHT];
uniform int uSpotLightCount;
uniform SpotLight uSpotLight[MAX_SPOT_LIGHT];

uniform sampler2D uAlbedo;
uniform vec3 uViewPos;
uniform float uAlpha;

vec3 calcAmbient(vec3 lightColor, float intensity, vec3 Ka)
{
    return Ka * lightColor * intensity;
}

vec3 calcDiffuse(vec3 n, vec3 l, vec3 lightColor, float intensity)
{
    float diff = max(dot(n, l), 0.0);
    return diff * lightColor * intensity;
}

// calculate specular light by Blinn.
vec3 calcSpecular(vec3 n, vec3 l, vec3 v, vec3 lightColor, vec3 Ks, float shininess, float intensity)
{
    vec3 h = normalize(l + v);
    float spec = pow(max(dot(n, h), 0.0), shininess);
    return Ks * spec * lightColor * intensity;
}

void main()
{
    vec3 N = normalize(vNormal);
    vec3 V = normalize(uViewPos - vFragPos);

    vec3 base = vColor;
    if (uMaterial.isUseTex)
    {
        base *= texture(uAlbedo, vUV).rgb;
    }

    vec3 Ld = normalize(-uDirLight.dir);
    vec3 ambient = calcAmbient(uDirLight.color, uDirLight.intensity, uMaterial.ambientK) * base;
    vec3 dirDiff = calcDiffuse(N, Ld, uDirLight.color, uDirLight.intensity) * base;
    vec3 dirSpec = calcSpecular(N, Ld, V, uDirLight.color, uMaterial.specularK, uMaterial.shininess, uDirLight.intensity);

    vec3 pointDiffSum = vec3(0.0);
    vec3 pointSpecSum = vec3(0.0);
    for (int i = 0; i < uPointLightCount; i++)
    {
        vec3 Lp = uPointLight[i].pos - vFragPos;
        float dist = length(Lp);
        vec3 L = Lp / max(dist, 1e-6);

        float atten = 1.0 / (uPointLight[i].constant
            + uPointLight[i].linear * dist
            + uPointLight[i].quadratic * dist * dist);

        vec3 pd = calcDiffuse(N, L, uPointLight[i].color, uPointLight[i].intensity) * base;
        vec3 ps = calcSpecular(N, L, V, uPointLight[i].color, uMaterial.specularK, uMaterial.shininess, uPointLight[i].intensity);

        pointDiffSum += pd * atten;
        pointSpecSum += ps * atten;
    }

    vec3 spotDiffSum = vec3(0.0);
    vec3 spotSpecSum = vec3(0.0);
    for (int i = 0; i < uSpotLightCount; i++)
    {
        vec3 toL = uSpotLight[i].pos - vFragPos;
        float d = length(toL);
        vec3 L = toL / max(d, 1e-6);

        float theta = dot(L, normalize(-uSpotLight[i].dir));
        float eps = max(uSpotLight[i].cutOff - uSpotLight[i].outerCutOff, 1e-6);
        float spot = clamp((theta - uSpotLight[i].outerCutOff) / eps, 0.0, 1.0);

        float att = 1.0
            / (uSpotLight[i].constant
            + uSpotLight[i].linear * d
            + uSpotLight[i].quadratic * d * d);
        float weight  = spot * att;

        spotDiffSum += calcDiffuse(N, L, uSpotLight[i].color, uSpotLight[i].intensity) * weight;
        spotSpecSum += calcSpecular(N, L, V, uSpotLight[i].color, uMaterial.specularK, uMaterial.shininess, uSpotLight[i].intensity) * weight;
    }

    vec3 color = ambient + dirDiff + dirSpec + pointDiffSum + pointSpecSum + spotDiffSum + spotSpecSum;
    FragColor = vec4(color, uAlpha);
}
