import time

from PIL import Image

from Camera import Camera
from Scene import Scene
from Ray import Ray
from Vector3 import Vector3

from debug import log_error

def trace_ray(ray: Ray, scene: Scene) -> tuple:
	closest_t = 2147483647
	closest_object = None
	for object in scene.objects:
		t = object.get_hit_t(ray)
		if t == -1:
			continue
		t = float(t)
		if t < closest_t:
			closest_t = t
			closest_object = object

	if not closest_object:
		return (0, 0, 0)

	color = tuple(map(int, closest_object.color))
	return color

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
            image.putpixel((i, j), color)
            
            pixel_center += camera.pixel_delta_u

        pixel_start_left += camera.pixel_delta_v

    time_end = time.time() - time_start
    print(" " * 30, end="\r")
    print(f"Rendered for {time_end:.3f}s")
