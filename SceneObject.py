import math

from Vector3 import Vector3
from Ray import Ray

class SceneObject:
    def __init__(self, center, normal, radius, color):
        self.center = Vector3(center)

        if normal:
            self.normal = Vector3(normal)
        else:
            self.normal = None
             
        if radius:
            self.radius = radius
        else:
            self.radius = None
 
        self.color = Vector3((c / 255 for c in color))

    # return first-hit t if actually hit, else -1
    # assume ray.direction is normalized
    def get_hit_t(self, ray: Ray):
        return -1


class Sphere(SceneObject):
    def __init__(self, center, radius, color):
        super().__init__(center, None, radius, color)

    def get_hit_t(self, ray: Ray):
        oc = self.center - ray.origin
        ray_dot_oc = ray.direction.dot(oc)

        inside_sqrt = ray_dot_oc ** 2 - (oc.norm2() - self.radius ** 2)
        if inside_sqrt < 0:
            return -1

        t = ray_dot_oc - math.sqrt(inside_sqrt)
        return t

class Plane(SceneObject):
    def __init__(self, center, normal, color):
        super().__init__(center, normal, None, color)

    def get_hit_t(self, ray: Ray):
        oc = self.center - ray.origin
        num = oc.dot(self.normal)
        den = ray.direction.dot(self.normal)
        if den == 0:
            return 0
        t = num / den
        return t if t >= 0 else -1

class Cylinder(SceneObject):
	def __init__(self, center, radius, normal, color):
		super().__init__(center, radius, normal, color)

	def get_hit_t(self, ray: Ray):
		return -1
