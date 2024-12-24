import time

from PIL import Image

from Camera import Camera
from Scene import Scene
from Ray import Ray

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


    a = camera.pixel00_loc

    for j in range(height):
        print(f"Rendering: y={j}/{height}", end="\r")
        pixel_center = a + (j * camera.pixel_delta_v)
		
        for i in range(width):
            ray_direction = (pixel_center - camera.center).normalize()
            ray = Ray(camera.center, ray_direction)

            color = trace_ray(ray, scene)
            image.putpixel((i, j), color)
            
            pixel_center += camera.pixel_delta_u

    time_end = time.time() - time_start
    print(" " * 80, end="\r")
    print(f"Rendered for {time_end:.3f}s")
