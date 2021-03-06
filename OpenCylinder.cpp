#include "OpenCylinder.h"

OpenCylinder::OpenCylinder(void)
        : 	ObjetoGeometrico(),
        y0(-1.0),
        y1(1.0),
        radius(1.0),
        inv_radius(1.0) {}

OpenCylinder::OpenCylinder(const double bottom, const double top, const double r)
        :  	ObjetoGeometrico(),
        y0(bottom),
        y1(top),
        radius(r),
        inv_radius(1.0 / radius) {}

OpenCylinder::OpenCylinder(const OpenCylinder& c)
        : 	ObjetoGeometrico(c),
        y0(c.y0),
        y1(c.y1),
        radius(c.radius),
        inv_radius(c.inv_radius) {}

OpenCylinder* OpenCylinder::clone(void) const {
    return (new OpenCylinder(*this));
}


OpenCylinder& OpenCylinder::operator= (const OpenCylinder& rhs) {
    if (this == &rhs)
        return (*this);

    ObjetoGeometrico::operator= (rhs);

    y0 			= rhs.y0;
    y1 			= rhs.y1;
    radius 		= rhs.radius;
    inv_radius 	= rhs.inv_radius;

    return (*this) ;
}

OpenCylinder::~OpenCylinder(void) {}

bool OpenCylinder::hayImpacto(const Rayo& ray, double& tmin) const {

    double t;
    double ox = ray.o.x;
    double oy = ray.o.y;
    double oz = ray.o.z;
    double dx = ray.d.x;
    double dy = ray.d.y;
    double dz = ray.d.z;

    double a = dx * dx + dz * dz;
    double b = 2.0 * (ox * dx + oz * dz);
    double c = ox * ox + oz * oz - radius * radius;
    double disc = b * b - 4.0 * a * c ;


    if (disc < 0.0)
        return(false);
    else {
        double e = sqrt(disc);
        double denom = 2.0 * a;
        t = (-b - e) / denom;    // smaller root

        if (t > kEpsilon) {
            double yhit = oy + t * dy;

            if (yhit > y0 && yhit < y1) {
                tmin = t;
        
                return (true);
            }
        }

        t = (-b + e) / denom;    // larger root

        if (t > kEpsilon) {
            double yhit = oy + t * dy;

            if (yhit > y0 && yhit < y1) {
                tmin = t;

                return (true);
            }
        }
    }
    return (false);
}