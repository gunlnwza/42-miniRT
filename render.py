import time
import math

from PIL import Image

from Camera import Camera
from Scene import Scene
from Ray import Ray
from Vector3 import Vector3
from Color import Color

from debug import log_error

class HitRecord:
	def __init__(self, t, obj, point):
		self.update(t, obj, point)

	def update(self, t, obj, point):
		self.t = t
		self.object = obj
		self.point = point
		if point:
			self.normal = obj.surface_normal(point)
		else:
			self.normal = None

def get_intersect_point(ray: Ray, scene: Scene):
	hit_record = HitRecord(math.inf, None, None)

	for obj in scene.objects:
		t = obj.get_hit_t(ray)
		if t is None:
			continue
		t = float(t)
		if t < hit_record.t:
			hit_record.update(t, obj, ray.at(t))

	return hit_record if hit_record.t < math.inf else None

def ray_color(ray: Ray, scene: Scene) -> Vector3:
	hit_record = get_intersect_point(ray, scene)
	if not hit_record:
		return Color(0, 0, 0)

	ambient_color = hit_record.object.color * scene.ambient_light.intensity

	shadow_ray = Ray(hit_record.point, scene.light.center - hit_record.point)
	hit_record_2 = get_intersect_point(shadow_ray, scene)
	if not hit_record_2:
		return ambient_color

	N = hit_record.normal.normalize()
	P = ray.at(hit_record.t)
	L_pos = scene.light.center

	L = L_pos - P
	I = L.normalize()
	diffuse_color = \
		hit_record.object.color * scene.light.intensity * max(0, N.dot(I))

	return ambient_color + diffuse_color

def render(image: Image, scene: Scene, camera: Camera):
    time_start = time.time()
    width, height = image.size

    pixel_start_left = Vector3(camera.pixel00_loc)

    for j in range(height):
        print(f"\rRendering: {(100 * j) // height}%", end="")
        pixel_center = Vector3(pixel_start_left)
        for i in range(width):
            ray_direction = (pixel_center - camera.center).normalize()
            ray = Ray(camera.center, ray_direction)

            color = ray_color(ray, scene)
            image.putpixel((i, j), color.to_255())

            pixel_center += camera.pixel_delta_u

        pixel_start_left += camera.pixel_delta_v

    time_end = time.time() - time_start
    print("\r" + " " * 30, end="\r")
    print(f"Rendered for {time_end:.3f}s")
