#include <iostream>
#include <bits/stdc++.h>
#include "lib/sphere.h"
#include "lib/hitable_list.h"
#include "lib/camera.h"
#include "lib/material.h"
#include "float.h"

vec3 color(const ray& r, hitable *world, int depth, materialLight& light, camera& view) {
    hit_record rec;
    if(world->hit(r, 0.001, FLT_MAX, rec)) {
        hit_record hitted;
        if(!world->hit(ray(rec.p, light.direction-rec.p), 0.001, FLT_MAX, hitted)) {
            return phong(light, rec, view);
        }
    }
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5*(unit_direction.y()+1.0);
    return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}

int main() {
    int nx = 400;
    int ny = 200;
    int ns = 100;
    printf("P3\n%i %i\n255\n", nx, ny);
    hitable *list[4];
    list[0] = new sphere(vec3(0, 0, -1), 0.5, new material(vec3(0.8, 0.3, 0.3), 0.2, 0.5, 0.6, 1.0));
    list[1] = new sphere(vec3(0.0,-100.5,-1.0), 100, new material(vec3(0.8, 0.8, 0.0), 0.2, 0.5, 0.6, 1.0));
    list[2] = new sphere(vec3(1,0,-1), 0.5, new material(vec3(0.8, 0.6, 0.2), 0.2, 0.5, 0.6, 1.0));
    list[3] = new sphere(vec3(-1,0,-1), 0.5, new material(vec3(0.8, 0.8, 0.8), 0.2, 0.5, 0.6, 1.0));
    hitable *world = new hitable_list(list,4);
    camera cam;
    materialLight light(vec3(1.0, 1.0, 1.0), vec3(1.0, 100.0, -1.0));
    for(int i = ny-1; i > -1; i--) {
        for(int j = 0; j < nx; j++) {
            vec3 col(0,0,0);
            for(int s = 0; s < ns; s++) {
                float u = float (j+ drand48()) / float(nx);
                float v = float (i+ drand48()) / float(ny);
                ray r = cam.get_ray(u, v);
                vec3 p = r.point_at_parameter(2.0);
                col += color(r, world, 0, light, cam);
            }
            col /= float(ns);
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);
            printf("%i %i %i\n", ir, ig, ib);
        }
    }
}