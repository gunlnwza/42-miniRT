from Vector3 import Vector3
from SceneObject import SceneObject

class AmbientLight:
	def __init__(self, intensity, color):
		if not 0 <= intensity <= 1:
			raise ValueError("Brightness not in [0.0, 1.0]")
		self.intensity = intensity

		self.color = Vector3((c / 255 for c in color))

class Light:
	def __init__(self, center, intensity):
		self.center = Vector3(center)
		
		if not 0 <= intensity <= 1:
			raise ValueError("Brightness not in [0.0, 1.0]")
		self.intensity = intensity

class Scene:
	def __init__(self,
			ambient_light: AmbientLight,
			light: Light,
			objects: SceneObject):
		self.ambient_light = ambient_light
		self.light = light
		self.objects = objects
