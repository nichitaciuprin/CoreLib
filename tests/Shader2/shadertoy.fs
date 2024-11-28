// https://www.youtube.com/watch?v=PGtv-dBi2wE&list=PLGmrMu-IwbguU_nY2egTFmlg691DN7uE5&index=22

#define MAX_STEPS 100
#define MAX_DIST 100.0
#define SURF_DIST 0.01

float GetDist(vec3 p)
{
	vec3 sphere1 = vec3(0, 1, 6); float radius1 = 1.0;
    vec3 sphere2 = vec3(3, 2, 6); float radius2 = 1.0;
    float sphereDist1 = length(p - sphere1.xyz) - radius1;
    float sphereDist2 = length(p - sphere2.xyz) - radius2;
    float planeDist = p.y;
    float d;
    d = planeDist;
    d = min(d, sphereDist1);
    d = min(d, sphereDist2);
    return d;
}
float RayMarch(vec3 ro, vec3 rd)
{
	float dO = 0.0;

    for (int i = 0; i < MAX_STEPS; i++)
    {
    	vec3 p = ro + rd * dO;
        float dS = GetDist(p);
        dO += dS;
        if(dO > MAX_DIST) break;
        if(dS < SURF_DIST) break;
    }

    return dO;
}
vec3 GetNormal(vec3 p)
{
    float offset = 0.01;

    vec3 p0 = p;
    vec3 p1 = p; p1.x -= offset;
    vec3 p2 = p; p2.y -= offset;
    vec3 p3 = p; p3.z -= offset;

	float d0 = GetDist(p0);
    float d1 = GetDist(p1);
    float d2 = GetDist(p2);
    float d3 = GetDist(p3);

    float x = d0 - d1;
    float y = d0 - d2;
    float z = d0 - d3;

    return normalize(vec3(x, y, z));
}
float GetLight(vec3 p)
{
    vec3 lightPos = vec3(0, 5, 6);
    lightPos.xz += vec2(sin(iTime), cos(iTime)) * 2.0;
    vec3 dirToLight = normalize(lightPos - p);
    vec3 surfaceNomal = GetNormal(p);
    float lightFraction = clamp(dot(surfaceNomal, dirToLight), 0.0, 1.0);

    // adds shadows
    float d = RayMarch(p + surfaceNomal * SURF_DIST * 2.0, dirToLight);
    bool rayhit = d < length(lightPos - p);
    if (rayhit)
        lightFraction *= 0.1;
        // lightFraction = 0.0;

    return lightFraction;
}
float ToBrightnes(float dist)
{
    if (dist > 20.0)
        dist = 20.0;

    dist /= 20.0;

    return 1.0 - dist;
}
void mainImage(out vec4 fragColor, in vec2 fragCoord)
{
    vec2 uv = (fragCoord - iResolution.xy / 2.0) / iResolution.y;
    vec3 ro = vec3(0, 1, 0);
    vec3 rd = normalize(vec3(uv.x, uv.y, 1));
    float d = RayMarch(ro, rd);
    vec3 p = ro + rd * d;
    float dif = GetLight(p);
    vec3 col = vec3(dif);

    // gamma correction
    // col = pow(col, vec3(.4545));

    fragColor = vec4(col,1.0);
}