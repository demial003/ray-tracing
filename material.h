#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"
#include "ray.h"
double reflectance(double cosine, double refraction_index) {
  double r0 = (1 - refraction_index) / (1 + refraction_index);
  r0 *= r0;
  return r0 + (1 - r0) * pow((1 - cosine), 5);
}

bool material_scatter(ray r_in, hit_record rec, color *attenuation,
                      ray *scattered) {
  switch (rec.mat.type) {
  case 0:
    exit(1);
  case LAMBERTIAN:
    vec3 scatter_direction = vec3_add(rec.normal, vec3_random_unit_vector());

    if (vec3_near_zero(scatter_direction))
      scatter_direction = rec.normal;

    *scattered = ray_init(rec.p, scatter_direction);
    *attenuation = rec.mat.albedo;
    return true;
  case METAL:
    vec3 reflected = vec3_reflect(r_in.dir, rec.normal);
    reflected =
        vec3_add(vec3_unit_vector(reflected),
                 vec3_scalar_multiply(vec3_random_unit_vector(), rec.mat.fuzz));
    *scattered = ray_init(rec.p, reflected);
    *attenuation = rec.mat.albedo;
    return (vec3_dot(scattered->dir, rec.normal) > 0);
  case DIELECTRIC:
    *attenuation = vec3_init(1.0, 1.0, 1.0);
    double ri = rec.front_face ? (1.0 / rec.mat.refraction_index)
                               : rec.mat.refraction_index;

    vec3 unit_dir = vec3_unit_vector(r_in.dir);
    double cos_theta =
        fmin(vec3_dot(vec3_scalar_multiply(unit_dir, -1), rec.normal), 1.0);
    double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

    bool cannot_refract = ri * sin_theta > 1.0;
    vec3 dir;
    if (cannot_refract || reflectance(cos_theta, ri) > rand_double()) {
      dir = vec3_reflect(unit_dir, rec.normal);
    } else {
      dir = vec3_refract(unit_dir, rec.normal, ri);
    }

    *scattered = ray_init(rec.p, dir);
    return true;
  }
  return false;
}

#endif
