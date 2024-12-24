import time

from PIL import Image

from Camera import Camera
from Scene import Scene
from Ray import Ray
from Vector3 import Vector3

from debug import log_error

def trace_ray(ray: Ray, scene: Scene) -> Vector3:
	closest_obj_t = 2147483647
	closest_obj = None
	closest_obj_normal = None

	for obj in scene.objects:
		t = obj.get_hit_t(ray)
		if t == -1:
			continue
		t = float(t)
		if t < closest_obj_t:
			closest_obj_t = t
			closest_obj = obj
			closest_obj_normal = ray.at(t) - obj.center

	if not closest_obj:
		return Vector3(0, 0, 0)

	ambient_color = closest_obj.color * scene.ambient_light.intensity

	N = closest_obj_normal.normalize()
	P = ray.at(closest_obj_t)
	L_pos = scene.light.center

	L = L_pos - P
	I = L.normalize()

	diffuse_term = max(0, N.dot(I))
	diffuse_color = closest_obj.color * scene.light.intensity * diffuse_term

	return ambient_color + diffuse_color

def render(image: Image, scene: Scene, camera: Camera):
    time_start = time.time()
    width, height = image.size

    pixel_start_left = Vector3(camera.pixel00_loc)

    for j in range(height):
        print(f"Rendering: y={j}/{height}", end="\r")
        pixel_center = Vector3(pixel_start_left)
        for i in range(width):
            ray_direction = (pixel_center - camera.center).normalize()
            ray = Ray(camera.center, ray_direction)

            color = trace_ray(ray, scene)
            color = tuple(int(255.99 * c) for c in color)
            image.putpixel((i, j), color)
            
            pixel_center += camera.pixel_delta_u

        pixel_start_left += camera.pixel_delta_v

    time_end = time.time() - time_start
    print(" " * 30, end="\r")
    print(f"Rendered for {time_end:.3f}s")
