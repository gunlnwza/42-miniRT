from Vector3 import Vector3
from Color import Color
from SceneObject import SceneObject

class AmbientLight:
	def __init__(self, intensity, color):
		if not 0 <= intensity <= 1:
			raise ValueError("Brightness not in [0.0, 1.0]")
		self.intensity = intensity

		self.color = Color(color)

class Light:
	def __init__(self, intensity, color, center):
		self.center = Vector3(center)
		self.color = Color(color)

		if not 0 <= intensity <= 1:
			raise ValueError("Brightness not in [0.0, 1.0]")
		self.intensity = intensity

class Scene:
	def __init__(self, ambient_light: AmbientLight, light: Light,
		objects: SceneObject):

		self.ambient_light = ambient_light
		self.light = light
		self.objects = objects
