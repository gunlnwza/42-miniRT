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
	camera = Camera(Vector3(0, 0, 0), image_size)
	scene = Scene(
		AmbientLight(intensity=0.4, color=(0, 0, 200)),
		Light(intensity=1, center=(0, 0, -4)),
		[
			Sphere(center=(0, -0.2, -1), radius=0.5, color=(200, 10, 10)),
			# Plane(center=(0, -2, -0.5), normal=(0.42, -0.5, 0), color=(50, 200, 50))
			Sphere(center=(0, 8, -6), radius=8, color=(10, 200, 10))
		]
	)

	image = Image.new("RGB", image_size, "black")
	render(image, scene, camera)
	save_image(image)

if __name__ == "__main__":
	main()
