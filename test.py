import os
from datetime import datetime
import time

import numpy as np
from PIL import Image

from Vector3 import Vector3

# init
OUTPUT_DIR = "pictures"

ASPECT_RATIO = 16 / 9
IMAGE_WIDTH = 500
IMAGE_HEIGHT = max(1, int(IMAGE_WIDTH / ASPECT_RATIO))

FOCAL_LENGTH = 1.0
VIEWPORT_HEIGHT = 2
VIEWPORT_WIDTH = VIEWPORT_HEIGHT * float(IMAGE_WIDTH / IMAGE_HEIGHT)
camera_center = Vector3(0, 0, 0)

viewport_u = Vector3(VIEWPORT_WIDTH, 0, 0)
viewport_v = Vector3(0, VIEWPORT_HEIGHT, 0)

pixel_delta_u = viewport_u / IMAGE_WIDTH
pixel_delta_v = viewport_v / IMAGE_HEIGHT

viewport_upper_left = camera_center - Vector3(0, 0, FOCAL_LENGTH) - viewport_u / 2 - viewport_v / 2

pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v)


class Ray:
	def __init__(self, origin: Vector3, direction: Vector3):
		self.orig = origin
		self.dir = direction

	def direction(self):
		return self.dir

	def origin(self):
		return self.orig

	def at(self, t):
		return self.orig + t * self.dir

def hit_sphere(center, radius, r: Ray):
	oc = center - r.origin()
	a = r.direction().norm2()
	b = -2 * r.direction().dot(oc)
	c = oc.norm2() - radius * radius
	discriminant = b * b - 4 * a * c
	return discriminant >= 0

def ray_color(r: Ray):
	if hit_sphere(Vector3(0, 0, -1), 0.5, r):
		return (255, 0, 0)
	
	unit_direction = r.direction().normalize()
	a = 0.5 * (unit_direction[1] + 1)
	color = (1 - a) * Vector3(1, 1, 1) + a * Vector3(0.5, 0.7, 1.0)

	return tuple(int(255.99 * c) for c in color)

image = Image.new("RGB", (IMAGE_WIDTH, IMAGE_HEIGHT), "black")

time_start = time.time()

for j in range(IMAGE_HEIGHT):
	print(f"Rendering: y={j} ({time.time() - time_start:.3f}s)", end="\r")
	for i in range(IMAGE_WIDTH):
		pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v)
		ray_direction = pixel_center - camera_center
		r = Ray(camera_center, ray_direction)

		color = ray_color(r)
		image.putpixel((i, j), color)

print(" " * 80 + "\r", f"Rendered for ({time.time() - time_start:.3f}s)")

# save file
timestamp = datetime.now().strftime("%Y-%m-%d_%H%M%S")
filename = f"{timestamp}.png"
file_path = os.path.join(OUTPUT_DIR, filename)
image.save(file_path)
print(f"Image saved at {file_path}")
image.show()
