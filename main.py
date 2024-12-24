import os
import sys
from datetime import datetime
import time
import math

import numpy as np
from PIL import Image

from Vector3 import Vector3

# rendering module
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

	def get_hit_t(self, ray: Ray):
		# return first-hit t if actually hit, else -1
		
		oc = self.center - ray.origin
		ray_dot_oc = ray.direction.dot(oc)

		inside_sqrt = ray_dot_oc ** 2 - (oc.norm2() - self.radius ** 2)
		if inside_sqrt < 0:
			return -1

		t = ray_dot_oc - math.sqrt(inside_sqrt)
		return t

class Plane:
	pass

class Cylinder:
	pass

class Scene:
	def __init__(self, objects):
		self.objects = objects

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

def convert_to_rgb(color: Vector3):
	return tuple(int(255.99 * c) for c in color)

def render(image: Image, pixel00_loc, pixel_delta_u, pixel_delta_v, camera_center):
	time_start = time.time()
	width, height = image.size

	scene = Scene([
		Sphere(Vector3(0, 0, -1), 0.5, Vector3(50, 255, 50)),
		Sphere(Vector3(1, 0, -2), 0.5, Vector3(255, 50, 50)),
		Sphere(Vector3(-1, 0, -1), 0.5, Vector3(50, 50, 255)),
		Sphere(Vector3(1, 1, 3), 2, Vector3(50, 255, 50)),
		Sphere(Vector3(2, 0, -10), 0.5, Vector3(255, 50, 50)),
		Sphere(Vector3(3, 0, -5), 0.5, Vector3(50, 50, 255)),
	])

	for j in range(height):
		print(f"Rendering: y={j}/{height}", end="\r")

		for i in range(width):
			pixel_center = pixel00_loc + (j * pixel_delta_v) + (i * pixel_delta_u)
			# print("computing ray_direction", file=sys.stderr)
			ray_direction = (pixel_center - camera_center).normalize()
			# print(ray_direction, file=sys.stderr)
			ray = Ray(camera_center, ray_direction)

			color = trace_ray(ray, scene)
			image.putpixel((i, j), color)

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
