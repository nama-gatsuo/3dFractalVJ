#version 150
precision highp float;
in vec2 vTexCoord;
out vec4 outputColor;

uniform vec2 size;
uniform float time;
uniform vec3 cp;

uniform float minRadius2;
uniform float fixedRadius2;
uniform float foldingLimit;
uniform float scale;
uniform float rep;

float pixel_size;

void sphereFold(inout vec3 z, inout float dz){
    float r2 = dot(z, z);
    if (r2 < minRadius2) {
        float tmp = fixedRadius2 / minRadius2;
        z *= tmp;
        dz *= tmp;
    } else if (r2 < fixedRadius2) {
        float tmp = fixedRadius2 / r2;
        z *= tmp;
        dz *= tmp;
    }
}

void boxFold(inout vec3 z, inout float dz){
    z = clamp(z, - foldingLimit, foldingLimit) * 2.0 - z;
}

float DF(vec3 z){
    z.xy = mod(z.xy + vec2(rep * 0.5), rep) - rep * 0.5;
    vec3 offset = z;
    float dr = 1.0;

    for (int n = 0; n < 15; n++) {

        boxFold(z, dr);
        sphereFold(z, dr);

        z = scale * z + offset;
        dr = dr * abs(scale) + 1.0;
    }
    return length(z) / abs(dr);
}

vec3 intersect(in vec3 ro, in vec3 rd){
    float t = 0.2;
    float d = 1.0;
    float tm = 0.0;
    float dm = 100.0;
    float pd = 100.0;
    float os = 0.0;
    float s = 0.0;
    float count = 0.0;

    for (int i = 0; i < 64; i++) {

        if (d < pixel_size * t){
        } else {
            d = DF(ro + t * rd);
            count += 1.0;

            if (d > os) {
                os = 0.4 * d * d / pd;
                s = d + os;
                pd = d;
            } else {
                s = - os;
                os = 0.0;
                pd = 100.0;
                d = 1.0;
            }

            if (d < dm * t) {
                tm = t;
                dm = d;
            }

            t += s;
        }

    }
    return vec3(tm, dm, count);
}

vec3 getNormal(in vec3 p){
    vec3 e = vec3(0.5 * pixel_size, 0.0, 0.0);
    return normalize(vec3(
        DF(p + e.xyy) - DF(p - e.xyy),
        DF(p + e.yxy) - DF(p - e.yxy),
        DF(p + e.yyx) - DF(p - e.yyx)
        ));
}

void main(){
    vec2 p = (vTexCoord * 2.0 - size) / min(size.x, size.y);
    pixel_size = 1.0 / (size.y * 2.8);

    float rad = 3.0 + 0.4 * sin(time);

    vec3 cd = normalize(vec3(0.0) - cp);
    vec3 cs = normalize(cross(cd, vec3(0.0, 1.0, 1.0)));
    vec3 cu = normalize(cross(cs, cd));
    float depth = 1.0;

    vec3 rd = normalize(cs * p.x * 0.5 + cu * p.y * 0.5 + cd * depth);
    vec3 rp = cp;

    vec3 result = intersect(rp, rd);
    float t = result.x, d = result.y, c = result.z;

    if (d < pixel_size * t) {
        rp = rp + t * rd;

        vec3 n = getNormal(rp);
        float d = clamp(dot(vec3(0.577), n), 0.1, 1.0);
        float a = 1.0 - c / 48.0;

        outputColor = vec4(sqrt(vec3(0.2, 0.8, 1.0) * d * a), 1.0);
    } else {
        outputColor = vec4(vec3(0.0), 1.0);
    }

}
