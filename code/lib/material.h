#ifndef MATERIALH
#define MATERIALH

struct hit_record;

#include "ray.h"
#include "hitable.h"


class material {
    public:
        material() {}
        material(vec3 c, float a, float d, float s, float al) : color(c), ka(a), ks(s), kd(d), alpha(al) {}

        vec3 color;
        float ka;
        float ks;
        float kd;
        float alpha;
};

class materialLight {
    public:
        materialLight() {}
        materialLight(vec3 cor, vec3 dir) : color(cor), direction(dir) {}

        vec3 color;
        vec3 direction;
};

inline float max(float a, float b) {
    if(a > b) return a;
    return b;
}

vec3 reflect(const vec3 &v, const vec3 &n) {
    return v- 2*dot(v,n)*n;
}

vec3 phong(materialLight& light, const hit_record& rec, const camera& view) {
    vec3 lightDirection = normalize(light.direction);
    vec3 viewDirection = normalize(view.origin - rec.p);

    float cosTheta = max(0.0, dot(rec.normal, lightDirection));

    //cores
    vec3 ka = rec.mat_ptr->ka*light.color;
    vec3 kd = rec.mat_ptr->kd*light.color;
    vec3 ks = rec.mat_ptr->ks*light.color;

    vec3 ambient = rec.mat_ptr->ka*light.color;
    vec3 diffuse = vec3(0.0, 0.0, 0.0);
    vec3 specular = vec3(0.0, 0.0, 0.0);

    if(cosTheta > 0.0) {
        vec3 relfectionDir = reflect(-lightDirection, rec.normal);
        diffuse = rec.mat_ptr->kd * light.color * cosTheta;
        specular = rec.mat_ptr->ks * light.color * pow(max(0.0, dot(relfectionDir, rec.normal)), 128.0);
    }

    return ambient + diffuse + specular;
}
#endif