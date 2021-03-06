#ifndef MATERIALH
#define MATERIALH

struct hit_record;

#include "ray.h"
#include "hitable.h"

using namespace std;


class material {
    public:
        material() {}
        material(vec3 c, float e, float d, float s, float al) : color(c), ke(e), ks(s), kd(d), alpha(al) {}

        vec3 color;
        float ke;
        float ks;
        float kd;
        float alpha;
};

class materialLight {
    public:
        materialLight() {}
        materialLight(vec3 cor, vec3 dir) : color(cor), position(dir) {}

        vec3 color;
        vec3 position;
};

inline float max(float a, float b) {
    if(a > b) return a;
    return b;
}

vec3 reflect(const vec3 &v, const vec3 &n) {
    return 2*dot(v,n)*n - v;
}

vec3 phong(materialLight light, const hit_record& rec, const camera& view) {
    vec3 lightDirection = unit_vector(light.position - rec.p);
    vec3 viewDirection = unit_vector(view.origin - rec.p);
    vec3 normaNormal = unit_vector(rec.normal);

    float cosTheta = max(0.0f, dot(normaNormal, lightDirection));

    //cores
    vec3 emissive = rec.mat_ptr->ke*rec.mat_ptr->color*light.color;
    vec3 diffuse = vec3(0.0, 0.0, 0.0);
    vec3 specular = vec3(0.0, 0.0, 0.0);
    vec3 relfectionDir = reflect(lightDirection, normaNormal);

    if(cosTheta > 0.0) {
        diffuse = rec.mat_ptr->kd * rec.mat_ptr->color * light.color * cosTheta;
        specular = rec.mat_ptr->ks * rec.mat_ptr->color * light.color * pow(max(0.0, dot(viewDirection, relfectionDir)), rec.mat_ptr->alpha*128.0);
    }

    //return specular;
    //return diffuse;
    //return emissive;
    return emissive + diffuse + specular;
}
#endif