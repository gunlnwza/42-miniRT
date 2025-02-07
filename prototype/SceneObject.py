import math

from Vector3 import Vector3
from prototype.Ray import Ray

class SceneObject:
	# return first-hit t if actually hit, else -1
	# assume ray.direction is normalized
    def get_hit_t(self, ray: Ray):
        pass

class Sphere(SceneObject):
	def __init__(self, center: Vector3, radius: float, color: Vector3):
		self.center = center
		self.radius = radius
		self.color = color

	def get_hit_t(self, ray: Ray):
		oc = self.center - ray.origin
		ray_dot_oc = ray.direction.dot(oc)

		inside_sqrt = ray_dot_oc ** 2 - (oc.norm2() - self.radius ** 2)
		if inside_sqrt < 0:
			return -1

		t = ray_dot_oc - math.sqrt(inside_sqrt)
		return t

class Plane(SceneObject):
	pass

class Cylinder(SceneObject):
	pass
