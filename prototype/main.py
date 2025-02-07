import os
from datetime import datetime

from PIL import Image

from Camera import Camera

from Vector3 import Vector3
from Scene import Scene
from SceneObject import Sphere

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
	scene = Scene([
		Sphere(Vector3(0, 0, -1), 0.5, Vector3(200, 50, 50)),
		Sphere(Vector3(1, 1, -3), 2, Vector3(50, 50, 200)),
	])
	camera = Camera(Vector3(0, 0, 0), image_size)

	image = Image.new("RGB", image_size, "black")
	render(image, scene, camera)
	save_image(image)

if __name__ == "__main__":
	main()
