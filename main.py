import os
from datetime import datetime
import time

import numpy as np
from PIL import Image

from Vector3 import Vector3

# rendering module
def convert_to_rgb(color: Vector3):
	return tuple(int(255.99 * c) for c in color)

class Ray:
	def __init__(self, origin: Vector3, direction: Vector3):
		self.origin = origin
		self.direction = direction

	def at(self, t):
		return self.origin + t * self.direction
	
class SceneObject:
	pass

class Sphere:
	def __init__(self, center: Vector3, radius: float, color: Vector3):
		self.center = center
		self.radius = radius
		self.color = color

	def is_hit(self, ray: Ray):
		oc = self.center - ray.origin
		a = ray.direction.norm2()
		b = -2 * ray.direction.dot(oc)
		c = oc.norm2() - self.radius ** 2
		discriminant = b * b - 4 * a * c
		return discriminant >= 0

class Plane:
	pass

class Cylinder:
	pass

class Scene:
	def __init__(self, objects):
		self.objects = objects

def trace_ray(ray: Ray, scene: Scene):
	closest_object = None
	for object in scene.objects:
		if object.is_hit(ray):
			color = object.color
			# TODO: get closest object, by computing t
			return color
		
	unit_direction = ray.direction.normalize()
	a = 0.5 * (unit_direction[1] + 1)
	color = (1 - a) * Vector3(1, 1, 1) + a * Vector3(0.5, 0.7, 1.0)
	return color

def render(image: Image, pixel00_loc, pixel_delta_u, pixel_delta_v, camera_center):
	time_start = time.time()
	width, height = image.size

	scene = Scene([
		Sphere(Vector3(0, 0, -1), 0.5, Vector3(100, 100, 100)),
		Sphere(Vector3(1, 0, -2), 0.5, Vector3(255, 100, 100)),
		Sphere(Vector3(-1, 0, -1), 0.5, Vector3(100, 100, 255)),
	])

	for j in range(height):
		print(f"Rendering: y={j}/{height}", end="\r")

		for i in range(width):
			pixel_center = pixel00_loc + (j * pixel_delta_v) + (i * pixel_delta_u)
			ray_direction = pixel_center - camera_center
			ray = Ray(camera_center, ray_direction)

			color = trace_ray(ray, scene)
			image.putpixel((i, j), convert_to_rgb(color))


	time_end = time.time() - time_start
	print(" " * 80, end="\r")
	print(f"Rendered for {time_end:.3f}s")

# debugging module
def save_image(image, show=True):
	timestamp = datetime.now().strftime("%Y-%m-%d_%H%M%S")
	filename = f"{timestamp}.png"
	file_path = os.path.join("pictures", filename)

	if not os.path.exists("pictures"):
		os.mkdir("pictures")

	image.save(file_path)
	print(f"Image saved at {file_path}")
	if show:
		image.show()

# main
def main():
	ASPECT_RATIO = 16 / 9
	IMAGE_WIDTH = 300
	IMAGE_HEIGHT = max(1, int(IMAGE_WIDTH / ASPECT_RATIO))

	VIEWPORT_HEIGHT = 2
	VIEWPORT_WIDTH = VIEWPORT_HEIGHT * float(IMAGE_WIDTH / IMAGE_HEIGHT)
	viewport_u = Vector3(VIEWPORT_WIDTH, 0, 0)
	viewport_v = Vector3(0, VIEWPORT_HEIGHT, 0)
	pixel_delta_u = viewport_u / IMAGE_WIDTH
	pixel_delta_v = viewport_v / IMAGE_HEIGHT

	FOCAL_LENGTH = 1.0
	camera_center = Vector3(0, 0, 0)
	viewport_upper_left = camera_center - Vector3(0, 0, FOCAL_LENGTH) - viewport_u / 2 - viewport_v / 2

	pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v)

	image = Image.new("RGB", (IMAGE_WIDTH, IMAGE_HEIGHT), "black")
	render(image, pixel00_loc, pixel_delta_u, pixel_delta_v, camera_center)
	save_image(image)

if __name__ == "__main__":
	main()
