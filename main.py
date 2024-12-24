import os
from datetime import datetime

from PIL import Image

from Camera import Camera

from Vector3 import Vector3

from Scene import Scene, Light, AmbientLight
from SceneObject import Sphere, Plane, Cylinder

from render import render

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

def main():
	image_size = (300, 300)

	camera = Camera(center=(1, 1, 0), dir=(0, 0, 1), image_size=image_size)
	objects = [
			Sphere(center=(0, -0.2, -1), radius=0.5, color=(0.8, 0.1, 0.1)),
			Sphere(center=(0, 8, -6), radius=8, color=(0.1, 0.8, 0.1)),
			# Sphere(center=(-2, 0, -2), radius=1, color=(0.1, 0.1, 0.8)),
			# Sphere(center=(0, 0, 0), radius=3, color=(0, 0.5, 0.5))
		]
	scene = Scene(
		AmbientLight(intensity=0.1, color=(0, 0, 0.8)),
		Light(center=(-0.6, -0.2, -0.1), intensity=1, color=(1, 1, 1)),
		objects
	)

	image = Image.new("RGB", image_size, "black")
	render(image, scene, camera)
	save_image(image)

if __name__ == "__main__":
	main()
